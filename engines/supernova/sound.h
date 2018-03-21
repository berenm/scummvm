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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef SUPERNOVA_SOUND_H
#define SUPERNOVA_SOUND_H

#include "audio/mixer.h"

namespace Supernova {

class SupernovaEngine;
class ResourceManager;

enum AudioIndex {
	kAudioFoundLocation,        // 44|0
	kAudioCrash,                // 45|0
	kAudioVoiceHalt,            // 46|0
	kAudioGunShot,              // 46|2510
	kAudioSmash,                // 46|4020
	kAudioVoiceSupernova,       // 47|0
	kAudioVoiceYeah,            // 47|24010
	kAudioRobotShock,           // 48|0
	kAudioRobotBreaks,          // 48|2510
	kAudioShock,                // 48|10520
	kAudioTurntable,            // 48|13530
	kAudioSiren,                // 50|0
	kAudioSnoring,              // 50|12786
	kAudioRocks,                // 51|0
	kAudioDeath,                // 53|0
	kAudioAlarm,                // 54|0
	kAudioSuccess,              // 54|8010
	kAudioSlideDoor,            // 54|24020
	kAudioDoorOpen,             // 54|30030
	kAudioDoorClose,            // 54|31040
	kAudioNumSamples
};

enum MusicIndex {
	kMusicIntro = 49,
	kMusicOutro = 52
};

class Sound {
public:

public:
	Sound(SupernovaEngine *vm, Audio::Mixer *mixer);

	void play(AudioIndex index);
	void play(MusicIndex index);
	void stop();
	bool isPlaying();
private:
	Audio::Mixer *_mixer;
	SupernovaEngine *_vm;
	Audio::SoundHandle _soundHandle;
	int _rate;
};

}

#endif
