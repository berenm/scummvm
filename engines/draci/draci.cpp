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
 * $URL$
 * $Id$
 *
 */

#include "common/scummsys.h"
 
#include "common/config-manager.h"
#include "common/events.h"
#include "common/file.h"

#include "graphics/cursorman.h"
#include "graphics/font.h"
 
#include "draci/draci.h"
#include "draci/barchive.h"
#include "draci/script.h"
#include "draci/font.h"
#include "draci/sprite.h"
#include "draci/screen.h"
#include "draci/mouse.h"

namespace Draci {

// Data file paths

const Common::String objectsPath("OBJEKTY.DFW");
const Common::String palettePath("PALETY.DFW");
const Common::String spritesPath("OBR_AN.DFW");
const Common::String overlaysPath("OBR_MAS.DFW");
const Common::String roomsPath("MIST.DFW");
const Common::String animationsPath("ANIM.DFW");

DraciEngine::DraciEngine(OSystem *syst, const ADGameDescription *gameDesc) 
 : Engine(syst) {
	// Put your engine in a sane state, but do nothing big yet;
	// in particular, do not load data from files; rather, if you
	// need to do such things, do them from init().
 
	// Do not initialize graphics here
 
	// However this is the place to specify all default directories
	//Common::File::addDefaultDirectory(_gameDataPath + "sound/");

	// Here is the right place to set up the engine specific debug levels
	Common::addDebugChannel(kDraciGeneralDebugLevel, "general", "Draci general debug info");
	Common::addDebugChannel(kDraciBytecodeDebugLevel, "bytecode", "GPL bytecode instructions");
	Common::addDebugChannel(kDraciArchiverDebugLevel, "archiver", "BAR archiver debug info");
	Common::addDebugChannel(kDraciLogicDebugLevel, "logic", "Game logic debug info");
	Common::addDebugChannel(kDraciAnimationDebugLevel, "animation", "Animation debug info");
 
	// Don't forget to register your random source
	_eventMan->registerRandomSource(_rnd, "draci");
}

int DraciEngine::init() {
	// Initialize graphics using following:
	initGraphics(kScreenWidth, kScreenHeight, false);

	// Open game's archives
	_objectsArchive = new BArchive(objectsPath);
	_spritesArchive = new BArchive(spritesPath);
	_paletteArchive = new BArchive(palettePath);
	_roomsArchive = new BArchive(roomsPath);
	_overlaysArchive = new BArchive(overlaysPath);
	_animationsArchive = new BArchive(animationsPath);

	_screen = new Screen(this);
	_font = new Font();
	_anims = new AnimationManager(this);
	_mouse = new Mouse(this);
	_script = new Script(this);
	_game = new Game(this);

	// Load default font
	_font->setFont(kFontBig);

	if(!_objectsArchive->isOpen()) {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Opening objects archive failed");
		return Common::kUnknownError;
	}	

	if(!_spritesArchive->isOpen()) {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Opening sprites archive failed");
		return Common::kUnknownError;
	}	

	if(!_paletteArchive->isOpen()) {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Opening palette archive failed");
		return Common::kUnknownError;
	}

	// Basic archive test
	debugC(2, kDraciGeneralDebugLevel, "Running archive tests...");	
	Common::String path("INIT.DFW");	
	BArchive ar(path);
	BAFile *f;
	debugC(3, kDraciGeneralDebugLevel, "Number of file streams in archive: %d", ar.size());	
	
	if(ar.isOpen()) {
		f = ar.getFile(0);	
	} else {
		debugC(2, kDraciGeneralDebugLevel, "ERROR - Archive not opened");
		return Common::kUnknownError;
	}	
		
	debugC(3, kDraciGeneralDebugLevel, "First 10 bytes of file %d: ", 0);
	for (unsigned int i = 0; i < 10; ++i) {
		debugC(3, kDraciGeneralDebugLevel, "0x%02x%c", f->_data[i], (i < 9) ? ' ' : '\n');
	}

	return Common::kNoError;
}

int DraciEngine::go() {
	debugC(1, kDraciGeneralDebugLevel, "DraciEngine::go()");
 
	debugC(2, kDraciGeneralDebugLevel, "Running graphics/animation test...");

	_game->init();

	_mouse->setCursorType(kNormalCursor);
	_mouse->cursorOn();

	Common::Event event;
	bool quit = false;
	while (!quit) {
		while (_eventMan->pollEvent(event)) {
			switch (event.type) {
			case Common::EVENT_QUIT:
				quit = true;
				break;
			default:
				_mouse->handleEvent(event);
			}		
		}
		_anims->drawScene(_screen->getSurface());
		_screen->copyToScreen();
		_system->delayMillis(20);
	}

	return Common::kNoError;
}

DraciEngine::~DraciEngine() {
	// Dispose your resources here
 
 	// TODO: Investigate possibility of using sharedPtr or similar
	delete _screen;
	delete _font;
	delete _mouse;
	delete _game;
	delete _script;
	delete _anims;

	delete _paletteArchive;
	delete _objectsArchive;
	delete _spritesArchive;
	delete _roomsArchive;
	delete _overlaysArchive;
	delete _animationsArchive;
	
	// Remove all of our debug levels here
	Common::clearAllDebugChannels();
}

Common::Error DraciEngine::run() {
	init();
	go();
	return Common::kNoError;
}

} // End of namespace Draci
