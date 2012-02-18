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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

/* Based on the Adventure Game Studio source code, copyright 1999-2011 Chris
 * Jones, which is licensed under the Artistic License 2.0.
 */

#ifndef AGS_CHARACTER_H
#define AGS_CHARACTER_H

#include "common/array.h"
#include "common/hash-str.h"

#include "engines/ags/scriptobj.h"

namespace AGS {

struct CharacterInfo : public ScriptObject {
	uint32 _defView, _talkView, _view;
	uint32 _room, _prevRoom;

	int32 _x, _y;

	uint32 _wait;
	uint32 _flags;

	uint16 _following;
	uint16 _followInfo;

	uint32 _idleView;            // the loop will be randomly picked
	uint16 _idleTime, _idleLeft; // num seconds idle before playing anim

	uint16 _transparency; // if character is transparent
	uint16 _baseLine;

	uint32 _activeInv;
	uint32 _talkColor;
	uint32 _thinkView;

	uint16 _blinkView, _blinkInterval; // design time
	uint16 _blinkTimer, _blinkFrame;   // run time

	uint16 _walkSpeedY, _picYOffs;

	int32 _z;

	uint32 _walkWait;

	uint16 _speechAnimSpeed;
	uint16 _blockingWidth, _blockingHeight;

	uint32 _indexId; // used for object functions to know the id

	uint16 _picXOffs;
	uint16 _walkWaitCounter;

	uint16 _loop;
	uint16 _frame;

	uint16 _walking;
	uint16 _animating;

	uint16 _walkSpeed, _animSpeed;

	Common::Array<uint16> _inventory;

	int16 _actX, _actY;

	Common::String _name;
	Common::String _scriptName;

	byte _on;

	Common::StringMap _properties;
};

} // End of namespace AGS

#endif // AGS_CHARACTER_H
