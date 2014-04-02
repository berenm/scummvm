/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "illusions/illusions.h"
#include "illusions/actor.h"
#include "illusions/actorresource.h"
#include "illusions/backgroundresource.h"
#include "illusions/camera.h"
#include "illusions/cursor.h"
#include "illusions/dictionary.h"
#include "illusions/fontresource.h"
#include "illusions/graphics.h"
#include "illusions/input.h"
#include "illusions/resourcesystem.h"
#include "illusions/screen.h"
#include "illusions/scriptresource.h"
#include "illusions/scriptman.h"
#include "illusions/soundresource.h"
#include "illusions/specialcode.h"
#include "illusions/talkresource.h"
#include "illusions/thread.h"
#include "illusions/time.h"
#include "illusions/updatefunctions.h"

#include "audio/audiostream.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/fs.h"
#include "common/timer.h"
#include "engines/util.h"
#include "graphics/cursorman.h"
#include "graphics/font.h"
#include "graphics/fontman.h"
#include "graphics/palette.h"
#include "graphics/surface.h"

namespace Illusions {

IllusionsEngine::IllusionsEngine(OSystem *syst, const ADGameDescription *gd) :
	Engine(syst), _gameDescription(gd) {
	
	_random = new Common::RandomSource("illusions");
	
	Engine::syncSoundSettings();

}

IllusionsEngine::~IllusionsEngine() {

	delete _random;

}

Common::Error IllusionsEngine::run() {

	// Init search paths
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "music");
	SearchMan.addSubDirectoryMatching(gameDataDir, "resource");
	SearchMan.addSubDirectoryMatching(gameDataDir, "resrem");
	SearchMan.addSubDirectoryMatching(gameDataDir, "savegame");
	SearchMan.addSubDirectoryMatching(gameDataDir, "sfx");
	SearchMan.addSubDirectoryMatching(gameDataDir, "video");
	SearchMan.addSubDirectoryMatching(gameDataDir, "voice");

	Graphics::PixelFormat pixelFormat16(2, 5, 6, 5, 0, 11, 5, 0, 0);
	initGraphics(640, 480, true, &pixelFormat16);
	
	_dict = new Dictionary();

	_resSys = new ResourceSystem();
	_resSys->addResourceLoader(0x00060000, new ActorResourceLoader(this));
	_resSys->addResourceLoader(0x00080000, new SoundGroupResourceLoader(this));
	_resSys->addResourceLoader(0x000D0000, new ScriptResourceLoader(this));
	_resSys->addResourceLoader(0x000F0000, new TalkResourceLoader(this));
	_resSys->addResourceLoader(0x00100000, new ActorResourceLoader(this));
	_resSys->addResourceLoader(0x00110000, new BackgroundResourceLoader(this));
	_resSys->addResourceLoader(0x00120000, new FontResourceLoader(this));
	_resSys->addResourceLoader(0x00170000, new SpecialCodeLoader(this));

	_screen = new Screen(this);
	_input = new Input();	
	_scriptMan = new ScriptMan(this);
	_actorItems = new ActorItems(this);
	_backgroundItems = new BackgroundItems(this);
	_camera = new Camera(this);
	_controls = new Controls(this);
	_cursor = new Cursor(this);
	_talkItems = new TalkItems(this);
	_triggerFunctions = new TriggerFunctions();
	
	// TODO Move to own class
	_resGetCtr = 0;
	_unpauseControlActorFlag = false;
	_lastUpdateTime = 0;
	
#if 1
	// Actor/graphics/script test

	/* TODO 0x0010000B LinkIndex 0x00060AAB 0x00060556
	*/
	
	_scriptMan->_globalSceneId = 0x00010003;	
	
	_resSys->loadResource(0x000D0001, 0, 0);

	_scriptMan->startScriptThread(0x00020004, 0, 0, 0, 0);
	_scriptMan->_doScriptThreadInit = true;

	while (!shouldQuit()) {
		_scriptMan->_threads->updateThreads();
		updateActors();
		updateSequences();
		updateGraphics();
		_screen->updateSprites();
		_system->updateScreen();
		updateEvents();
		_system->delayMillis(10);
	}
#endif

	delete _triggerFunctions;
	delete _talkItems;
	delete _cursor;
	delete _controls;
	delete _camera;
	delete _backgroundItems;
	delete _actorItems;
	delete _scriptMan;
	delete _input;
	delete _screen;
	delete _resSys;
	delete _dict;
	
	debug("Ok");
	
	return Common::kNoError;
}

bool IllusionsEngine::hasFeature(EngineFeature f) const {
	return
		false;
		/*
		(f == kSupportsRTL) ||
		(f == kSupportsLoadingDuringRuntime) ||
		(f == kSupportsSavingDuringRuntime);
		*/
}

void IllusionsEngine::updateEvents() {
	Common::Event event;
	while (_eventMan->pollEvent(event)) {
		_input->processEvent(event);
		switch (event.type) {
		case Common::EVENT_QUIT:
			quitGame();
			break;
		default:
			break;
		}
	}
}

Common::Point *IllusionsEngine::getObjectActorPositionPtr(uint32 objectId) {
	Control *control = _dict->getObjectControl(objectId);
	if (control && control->_actor)
		return &control->_actor->_position;
	return 0;
}

void IllusionsEngine::notifyThreadId(uint32 &threadId) {
	if (threadId) {
		uint32 tempThreadId = threadId;
		threadId = 0;
		_scriptMan->_threads->notifyId(tempThreadId);
	}
}

uint32 IllusionsEngine::getElapsedUpdateTime() {
	uint32 result = 0;
	uint32 currTime = getCurrentTime();
	if (_resGetCtr <= 0 ) {
		if (_unpauseControlActorFlag) {
			_unpauseControlActorFlag = false;
			result = 0;
		} else {
			result = currTime - _lastUpdateTime;
		}
		_lastUpdateTime = currTime;
	} else {
		result = _resGetTime - _lastUpdateTime;
		_lastUpdateTime = _resGetTime;
	}
	return result;
}

int IllusionsEngine::updateActors() {
	// TODO Move to Controls class
	uint32 deltaTime = getElapsedUpdateTime();
	for (Controls::ItemsIterator it = _controls->_controls.begin(); it != _controls->_controls.end(); ++it) {
		Control *control = *it;
		if (control->_pauseCtr == 0 && control->_actor && control->_actor->_controlRoutine)
			control->_actor->runControlRoutine(control, deltaTime);
	}
	return 1;
}

int IllusionsEngine::updateSequences() {
	// TODO Move to Controls class
	for (Controls::ItemsIterator it = _controls->_controls.begin(); it != _controls->_controls.end(); ++it) {
		Control *control = *it;
		if (control->_pauseCtr == 0 && control->_actor && control->_actor->_seqCodeIp) {
			control->sequenceActor();
		}
	}
	return 1;
}

int IllusionsEngine::updateGraphics() {
	Common::Point panPoint(0, 0);

	uint32 currTime = getCurrentTime();
	
	_camera->update(currTime);

	// TODO Move to BackgroundItems class
	BackgroundItem *backgroundItem = _backgroundItems->findActiveBackground();
	if (backgroundItem) {
		BackgroundResource *bgRes = backgroundItem->_bgRes;
		for (uint i = 0; i < bgRes->_bgInfosCount; ++i) {
			BgInfo *bgInfo = &bgRes->_bgInfos[i];
			uint32 priority = getPriorityFromBase(bgInfo->_priorityBase);
			_screen->_drawQueue->insertSurface(backgroundItem->_surfaces[i],
				bgInfo->_surfInfo._dimensions, backgroundItem->_panPoints[i], priority);
			if (bgInfo->_flags & 1)
				panPoint = backgroundItem->_panPoints[i];
		}
	}

	// TODO Move to Controls class
	for (Controls::ItemsIterator it = _controls->_controls.begin(); it != _controls->_controls.end(); ++it) {
		Control *control = *it;
		Actor *actor = control->_actor;
		
		if (control->_pauseCtr == 0 && actor && (actor->_flags & 1) && !(actor->_flags & 0x0200)) {
			Common::Point drawPosition = control->calcPosition(panPoint);
			if (actor->_flags & 0x2000) {
				Frame *frame = &(*actor->_frames)[actor->_frameIndex - 1];
				_screen->_decompressQueue->insert(&actor->_drawFlags, frame->_flags,
					frame->_surfInfo._pixelSize, frame->_surfInfo._dimensions,
					frame->_compressedPixels, actor->_surface);
				actor->_flags &= ~0x2000;
			}
			/* Unused
			if (actor->_flags & 0x4000) {
				nullsub_1(&actor->drawFlags);
				actor->flags &= ~0x4000;
			}
			*/
			if (actor->_surfInfo._dimensions._width && actor->_surfInfo._dimensions._height) {
				uint32 priority = control->getPriority();
				_screen->_drawQueue->insertSprite(&actor->_drawFlags, actor->_surface,
					actor->_surfInfo._dimensions, drawPosition, control->_position,
					priority, actor->_scale, actor->_spriteFlags);
			}
		}
	}

#if 0 // TODO
	if (_textInfo._surface) {
		int16 priority = getPriorityFromBase(99);
		_screen->_drawQueue->insertTextSurface(_textInfo._surface, _textInfo._dimensions,
			_textInfo._position, priority);
	}
#endif

	return 1;
}

int IllusionsEngine::getRandom(int max) {
	return _random->getRandomNumber(max - 1);
}

bool IllusionsEngine::causeIsDeclared(uint32 sceneId, uint32 verbId, uint32 objectId2, uint32 objectId) {
	uint32 codeOffs;
	bool r =
		_triggerFunctions->find(sceneId, verbId, objectId2, objectId) ||
		_scriptMan->findTriggerCause(sceneId, verbId, objectId2, objectId, codeOffs);
	debug(3, "causeIsDeclared() sceneId: %08X; verbId: %08X; objectId2: %08X; objectId: %08X -> %d",
		sceneId, verbId, objectId2, objectId, r);
	return r;
}

void IllusionsEngine::causeDeclare(uint32 verbId, uint32 objectId2, uint32 objectId, TriggerFunctionCallback *callback) {
	_triggerFunctions->add(getCurrentScene(), verbId, objectId2, objectId, callback);
}

uint32 IllusionsEngine::causeTrigger(uint32 sceneId, uint32 verbId, uint32 objectId2, uint32 objectId, uint32 callingThreadId) {
	uint32 codeOffs;
	uint32 causeThreadId = 0;
	TriggerFunction *triggerFunction = _triggerFunctions->find(sceneId, verbId, objectId2, objectId);
	if (triggerFunction) {
		triggerFunction->run(callingThreadId);
	} else if (_scriptMan->findTriggerCause(sceneId, verbId, objectId2, objectId, codeOffs)) {
		//debug("Run cause at %08X", codeOffs);
		causeThreadId = _scriptMan->startTempScriptThread(_scriptMan->_scriptResource->getCode(codeOffs),
			callingThreadId, verbId, objectId2, objectId);
	}
	return causeThreadId;
}

int IllusionsEngine::convertPanXCoord(int16 x) {
	// TODO
	return 0;
}

Common::Point IllusionsEngine::getNamedPointPosition(uint32 namedPointId) {
	Common::Point pt;
	if (_backgroundItems->findActiveBackgroundNamedPoint(namedPointId, pt) ||
		_actorItems->findNamedPoint(namedPointId, pt) ||
		_controls->findNamedPoint(namedPointId, pt))
    	return pt;
	// TODO
	//debug("getNamedPointPosition(%08X) UNKNOWN", namedPointId);
	return Common::Point(0, 0);
}

uint32 IllusionsEngine::getPriorityFromBase(int16 priority) {
	return 32000000 * priority;
}

bool IllusionsEngine::calcPointDirection(Common::Point &srcPt, Common::Point &dstPt, uint &facing) {
	facing = 0;
	uint xd = 0, yd = 0;
	if (srcPt.x < dstPt.x)
		xd = 0x40;
	else if (srcPt.x > dstPt.x)
		xd = 0x04;
	else
		xd = 0x00;
	if (srcPt.y < dstPt.y)
		yd = 0x01;
	else if (srcPt.y > dstPt.y)
		yd = 0x10;
	else
		yd = 0x00;
	if (!xd && !yd)
		facing = 0;
	else if (!yd && xd)
		facing = xd;
	else if (yd && !xd)
		facing = yd;
	else if (xd == 0x04 && yd == 0x01)
		facing = 0x02;
	else if (xd == 0x40 && yd == 0x01)
		facing = 0x80;
	else if (xd == 0x04 && yd == 0x10)
		facing = 0x08;
	else if (xd == 0x40 && yd == 0x10)
		facing = 0x20;
	return facing != 0;
}

void IllusionsEngine::playVideo(uint32 videoId, uint32 objectId, uint32 priority, uint32 threadId) {
	// TODO
}

bool IllusionsEngine::isSoundActive() {
	// TODO
	return false;
}

bool IllusionsEngine::cueVoice(byte *voiceName) {
	// TODO
	return true;
}

bool IllusionsEngine::isVoiceCued() {
	// TODO
	return false;
}

void IllusionsEngine::startVoice(int volume, int panX) {
	// TODO
}

void IllusionsEngine::stopVoice() {
	// TODO
}

bool IllusionsEngine::isVoicePlaying() {
	// TODO
	return false;
}

uint32 IllusionsEngine::getCurrentScene() {
	return _scriptMan->_activeScenes.getCurrentScene();
}

} // End of namespace Illusions
