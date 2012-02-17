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

#include "engines/ags/scripting/scripting.h"

namespace AGS {

void addInventorySystemScripting(GlobalScriptState *state) {
	// inventory functions
	state->addSystemFunctionImport("GetInvAt", &Script_UnimplementedStub);
	state->addSystemFunctionImport("GetInvGraphic", &Script_UnimplementedStub);
	state->addSystemFunctionImport("GetInvName", &Script_UnimplementedStub);
	state->addSystemFunctionImport("GetInvProperty", &Script_UnimplementedStub);
	state->addSystemFunctionImport("GetInvPropertyText",
	                               &Script_UnimplementedStub);
	state->addSystemFunctionImport("SetInvItemName", &Script_UnimplementedStub);
	state->addSystemFunctionImport("SetInvItemPic", &Script_UnimplementedStub);
	state->addSystemFunctionImport("UpdateInventory",
	                               &Script_UnimplementedStub);
}

} // End of namespace AGS
