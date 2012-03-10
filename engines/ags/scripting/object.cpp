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
#include "engines/ags/room.h"

namespace AGS {

// import void MergeObject(int object)
// Obsolete function for objects.
RuntimeValue Script_MergeObject(AGSEngine *vm, ScriptObject *,
                                const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("MergeObject unimplemented");

	return RuntimeValue();
}

// import void SetObjectTint(int object, int red, int green, int blue, int
// saturation, int luminance) Obsolete function for objects.
RuntimeValue Script_SetObjectTint(AGSEngine *vm, ScriptObject *,
                                  const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int red = params[1]._signedValue;
	UNUSED(red);
	int green = params[2]._signedValue;
	UNUSED(green);
	int blue = params[3]._signedValue;
	UNUSED(blue);
	int saturation = params[4]._signedValue;
	UNUSED(saturation);
	int luminance = params[5]._signedValue;
	UNUSED(luminance);

	// FIXME
	error("SetObjectTint unimplemented");

	return RuntimeValue();
}

// import void RemoveObjectTint(int object)
// Obsolete function for objects.
RuntimeValue
Script_RemoveObjectTint(AGSEngine *vm, ScriptObject *,
                        const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("RemoveObjectTint unimplemented");

	return RuntimeValue();
}

// import void StopObjectMoving(int object)
// Obsolete function for objects.
RuntimeValue
Script_StopObjectMoving(AGSEngine *vm, ScriptObject *,
                        const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("StopObjectMoving unimplemented");

	return RuntimeValue();
}

// import void RunObjectInteraction (int object, CursorMode)
// Obsolete function for objects.
RuntimeValue
Script_RunObjectInteraction(AGSEngine *vm, ScriptObject *,
                            const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	uint32 cursormode = params[1]._value;
	UNUSED(cursormode);

	// FIXME
	error("RunObjectInteraction unimplemented");

	return RuntimeValue();
}

// import int GetObjectProperty(int object, const string property)
// Obsolete function for objects.
RuntimeValue
Script_GetObjectProperty(AGSEngine *vm, ScriptObject *,
                         const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	ScriptString *property = (ScriptString *) params[1]._object;
	UNUSED(property);

	// FIXME
	error("GetObjectProperty unimplemented");

	return RuntimeValue();
}

// import void GetObjectPropertyText(int object, const string property, string
// buffer) Obsolete function for objects.
RuntimeValue
Script_GetObjectPropertyText(AGSEngine *vm, ScriptObject *,
                             const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	ScriptString *property = (ScriptString *) params[1]._object;
	UNUSED(property);
	ScriptString *buffer = (ScriptString *) params[2]._object;
	UNUSED(buffer);

	// FIXME
	error("GetObjectPropertyText unimplemented");

	return RuntimeValue();
}

// import void AnimateObject(int object, int loop, int delay, int repeat)
// Obsolete function for objects.
RuntimeValue Script_AnimateObject(AGSEngine *vm, ScriptObject *,
                                  const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int loop = params[1]._signedValue;
	UNUSED(loop);
	int delay = params[2]._signedValue;
	UNUSED(delay);
	int repeat = params[3]._signedValue;
	UNUSED(repeat);

	// FIXME
	error("AnimateObject unimplemented");

	return RuntimeValue();
}

// import void AnimateObjectEx(int object, int loop, int delay, int repeat, int
// direction, int blocking) Obsolete function for objects.
RuntimeValue Script_AnimateObjectEx(AGSEngine *vm, ScriptObject *,
                                    const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int loop = params[1]._signedValue;
	UNUSED(loop);
	int delay = params[2]._signedValue;
	UNUSED(delay);
	int repeat = params[3]._signedValue;
	UNUSED(repeat);
	int direction = params[4]._signedValue;
	UNUSED(direction);
	int blocking = params[5]._signedValue;
	UNUSED(blocking);

	// FIXME
	error("AnimateObjectEx unimplemented");

	return RuntimeValue();
}

// import void ObjectOff(int object)
// Obsolete function for objects.
RuntimeValue Script_ObjectOff(AGSEngine *vm, ScriptObject *,
                              const Common::Array<RuntimeValue> &params) {
	uint object = params[0]._value;

	if (object >= vm->getCurrentRoom()->_objects.size())
		error("ObjectOff: object %d is too high (only have %d)", object,
		      vm->getCurrentRoom()->_objects.size());

	if (vm->getCurrentRoom()->_objects[object]->_on == 1) {
		vm->getCurrentRoom()->_objects[object]->_on = 0;
		// StopObjectMoving
		vm->getCurrentRoom()->_objects[object]->_moving = false;
	}

	return RuntimeValue();
}

// import void ObjectOn(int object)
// Obsolete function for objects.
RuntimeValue Script_ObjectOn(AGSEngine *vm, ScriptObject *,
                             const Common::Array<RuntimeValue> &params) {
	uint object = params[0]._value;

	if (object >= vm->getCurrentRoom()->_objects.size())
		error("ObjectOn: object %d is too high (only have %d)", object,
		      vm->getCurrentRoom()->_objects.size());

	if (vm->getCurrentRoom()->_objects[object]->_on == 0)
		vm->getCurrentRoom()->_objects[object]->_on = 1;

	return RuntimeValue();
}

// import void SetObjectBaseline(int object, int baseline)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectBaseline(AGSEngine *vm, ScriptObject *,
                         const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int baseline = params[1]._signedValue;
	UNUSED(baseline);

	// FIXME
	error("SetObjectBaseline unimplemented");

	return RuntimeValue();
}

// import int GetObjectBaseline(int object)
// Obsolete function for objects.
RuntimeValue
Script_GetObjectBaseline(AGSEngine *vm, ScriptObject *,
                         const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("GetObjectBaseline unimplemented");

	return RuntimeValue();
}

// import void SetObjectFrame(int object, int view, int loop, int frame)
// Obsolete function for objects.
RuntimeValue Script_SetObjectFrame(AGSEngine *vm, ScriptObject *,
                                   const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int view = params[1]._signedValue;
	UNUSED(view);
	int loop = params[2]._signedValue;
	UNUSED(loop);
	int frame = params[3]._signedValue;
	UNUSED(frame);

	// FIXME
	error("SetObjectFrame unimplemented");

	return RuntimeValue();
}

// import void SetObjectGraphic(int object, int spriteSlot)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectGraphic(AGSEngine *vm, ScriptObject *,
                        const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int spriteSlot = params[1]._signedValue;
	UNUSED(spriteSlot);

	// FIXME
	error("SetObjectGraphic unimplemented");

	return RuntimeValue();
}

// import void SetObjectView(int object, int view)
// Obsolete function for objects.
RuntimeValue Script_SetObjectView(AGSEngine *vm, ScriptObject *,
                                  const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int view = params[1]._signedValue;
	UNUSED(view);

	// FIXME
	error("SetObjectView unimplemented");

	return RuntimeValue();
}

// import void SetObjectTransparency(int object, int amount)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectTransparency(AGSEngine *vm, ScriptObject *,
                             const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int amount = params[1]._signedValue;
	UNUSED(amount);

	// FIXME
	error("SetObjectTransparency unimplemented");

	return RuntimeValue();
}

// import void MoveObject(int object, int x, int y, int speed)
// Obsolete function for objects.
RuntimeValue Script_MoveObject(AGSEngine *vm, ScriptObject *,
                               const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int x = params[1]._signedValue;
	UNUSED(x);
	int y = params[2]._signedValue;
	UNUSED(y);
	int speed = params[3]._signedValue;
	UNUSED(speed);

	// FIXME
	error("MoveObject unimplemented");

	return RuntimeValue();
}

// import void MoveObjectDirect(int object, int x, int y, int speed)
// Obsolete function for objects.
RuntimeValue
Script_MoveObjectDirect(AGSEngine *vm, ScriptObject *,
                        const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int x = params[1]._signedValue;
	UNUSED(x);
	int y = params[2]._signedValue;
	UNUSED(y);
	int speed = params[3]._signedValue;
	UNUSED(speed);

	// FIXME
	error("MoveObjectDirect unimplemented");

	return RuntimeValue();
}

// import void SetObjectPosition(int object, int x, int y)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectPosition(AGSEngine *vm, ScriptObject *,
                         const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int x = params[1]._signedValue;
	UNUSED(x);
	int y = params[2]._signedValue;
	UNUSED(y);

	// FIXME
	error("SetObjectPosition unimplemented");

	return RuntimeValue();
}

// import int AreObjectsColliding(int object1, int object2)
// Obsolete function for objects.
RuntimeValue
Script_AreObjectsColliding(AGSEngine *vm, ScriptObject *,
                           const Common::Array<RuntimeValue> &params) {
	int object1 = params[0]._signedValue;
	UNUSED(object1);
	int object2 = params[1]._signedValue;
	UNUSED(object2);

	// FIXME
	error("AreObjectsColliding unimplemented");

	return RuntimeValue();
}

// import void GetObjectName(int object, string buffer)
// Obsolete function for objects.
RuntimeValue Script_GetObjectName(AGSEngine *vm, ScriptObject *,
                                  const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	ScriptString *buffer = (ScriptString *) params[1]._object;
	UNUSED(buffer);

	// FIXME
	error("GetObjectName unimplemented");

	return RuntimeValue();
}

// import int GetObjectX(int object)
// Obsolete function for objects.
RuntimeValue Script_GetObjectX(AGSEngine *vm, ScriptObject *,
                               const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("GetObjectX unimplemented");

	return RuntimeValue();
}

// import int GetObjectY(int object)
// Obsolete function for objects.
RuntimeValue Script_GetObjectY(AGSEngine *vm, ScriptObject *,
                               const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("GetObjectY unimplemented");

	return RuntimeValue();
}

// import int GetObjectGraphic(int object)
// Obsolete function for objects.
RuntimeValue
Script_GetObjectGraphic(AGSEngine *vm, ScriptObject *,
                        const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("GetObjectGraphic unimplemented");

	return RuntimeValue();
}

// import int IsObjectAnimating(int object)
// Obsolete function for objects.
RuntimeValue
Script_IsObjectAnimating(AGSEngine *vm, ScriptObject *,
                         const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("IsObjectAnimating unimplemented");

	return RuntimeValue();
}

// import int IsObjectMoving(int object)
// Obsolete function for objects.
RuntimeValue Script_IsObjectMoving(AGSEngine *vm, ScriptObject *,
                                   const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("IsObjectMoving unimplemented");

	return RuntimeValue();
}

// import int IsObjectOn (int object)
// Obsolete function for objects.
RuntimeValue Script_IsObjectOn(AGSEngine *vm, ScriptObject *,
                               const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);

	// FIXME
	error("IsObjectOn unimplemented");

	return RuntimeValue();
}

// import void SetObjectClickable(int object, int clickable)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectClickable(AGSEngine *vm, ScriptObject *,
                          const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int clickable = params[1]._signedValue;
	UNUSED(clickable);

	// FIXME
	error("SetObjectClickable unimplemented");

	return RuntimeValue();
}

// import void SetObjectIgnoreWalkbehinds (int object, int ignore)
// Obsolete function for objects.
RuntimeValue
Script_SetObjectIgnoreWalkbehinds(AGSEngine *vm, ScriptObject *,
                                  const Common::Array<RuntimeValue> &params) {
	int object = params[0]._signedValue;
	UNUSED(object);
	int ignore = params[1]._signedValue;
	UNUSED(ignore);

	// FIXME
	error("SetObjectIgnoreWalkbehinds unimplemented");

	return RuntimeValue();
}

// Object: import function Animate(int loop, int delay, RepeatStyle=eOnce,
// BlockingStyle=eBlock, Direction=eForwards) Animates the object using its
// current view.
RuntimeValue Script_Object_Animate(AGSEngine *vm, RoomObject *self,
                                   const Common::Array<RuntimeValue> &params) {
	int loop = params[0]._signedValue;
	UNUSED(loop);
	int delay = params[1]._signedValue;
	UNUSED(delay);
	uint32 repeatstyle = params[2]._value;
	UNUSED(repeatstyle);
	uint32 blockingstyle = params[3]._value;
	UNUSED(blockingstyle);
	uint32 direction = params[4]._value;
	UNUSED(direction);

	// FIXME
	error("Object::Animate unimplemented");

	return RuntimeValue();
}

// Object: import static Object* GetAtScreenXY(int x, int y)
// Gets the object that is on the screen at the specified co-ordinates.
RuntimeValue
Script_Object_GetAtScreenXY(AGSEngine *vm, ScriptObject *,
                            const Common::Array<RuntimeValue> &params) {
	int x = params[0]._signedValue;
	UNUSED(x);
	int y = params[1]._signedValue;
	UNUSED(y);

	// FIXME
	error("Object::GetAtScreenXY unimplemented");

	return RuntimeValue();
}

// Object: import void GetName(string buffer)
// Undocumented.
RuntimeValue Script_Object_GetName(AGSEngine *vm, RoomObject *self,
                                   const Common::Array<RuntimeValue> &params) {
	ScriptString *buffer = (ScriptString *) params[0]._object;
	UNUSED(buffer);

	// FIXME
	error("Object::GetName unimplemented");

	return RuntimeValue();
}

// Object: import function GetPropertyText(const string property, string buffer)
// Undocumented.
RuntimeValue
Script_Object_GetPropertyText(AGSEngine *vm, RoomObject *self,
                              const Common::Array<RuntimeValue> &params) {
	ScriptString *property = (ScriptString *) params[0]._object;
	UNUSED(property);
	ScriptString *buffer = (ScriptString *) params[1]._object;
	UNUSED(buffer);

	// FIXME
	error("Object::GetPropertyText unimplemented");

	return RuntimeValue();
}

// Object: import function GetProperty(const string property)
// Gets an integer Custom Property for this object.
RuntimeValue
Script_Object_GetProperty(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	ScriptString *property = (ScriptString *) params[0]._object;
	UNUSED(property);

	// FIXME
	error("Object::GetProperty unimplemented");

	return RuntimeValue();
}

// Object: import String GetTextProperty(const string property)
// Gets a text Custom Property for this object.
RuntimeValue
Script_Object_GetTextProperty(AGSEngine *vm, RoomObject *self,
                              const Common::Array<RuntimeValue> &params) {
	ScriptString *property = (ScriptString *) params[0]._object;
	UNUSED(property);

	// FIXME
	error("Object::GetTextProperty unimplemented");

	return RuntimeValue();
}

// Object: import bool IsCollidingWithObject(Object*)
// Checks whether this object is colliding with another.
RuntimeValue
Script_Object_IsCollidingWithObject(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	if (!params[0]._object->isOfType(sotRoomObject))
		error("Object::IsCollidingWithObject got incorrect object type "
		      "(expected a RoomObject) for parameter 1");
	RoomObject *object = (RoomObject *) params[0]._object;
	UNUSED(object);

	// FIXME
	error("Object::IsCollidingWithObject unimplemented");

	return RuntimeValue();
}

// Object: import function MergeIntoBackground()
// Merges the object's image into the room background, and disables the object.
RuntimeValue
Script_Object_MergeIntoBackground(AGSEngine *vm, RoomObject *self,
                                  const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::MergeIntoBackground unimplemented");

	return RuntimeValue();
}

// Object: import function Move(int x, int y, int speed, BlockingStyle=eNoBlock,
// WalkWhere=eWalkableAreas) Starts the object moving towards the specified
// co-ordinates.
RuntimeValue Script_Object_Move(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	int x = params[0]._signedValue;
	UNUSED(x);
	int y = params[1]._signedValue;
	UNUSED(y);
	int speed = params[2]._signedValue;
	UNUSED(speed);
	uint32 blockingstyle = params[3]._value;
	UNUSED(blockingstyle);
	uint32 walkwhere = params[4]._value;
	UNUSED(walkwhere);

	// FIXME
	error("Object::Move unimplemented");

	return RuntimeValue();
}

// Object: import function RemoveTint()
// Removes a specific object tint, and returns the object to using the ambient
// room tint.
RuntimeValue
Script_Object_RemoveTint(AGSEngine *vm, RoomObject *self,
                         const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::RemoveTint unimplemented");

	return RuntimeValue();
}

// Object: import function RunInteraction(CursorMode)
// Runs the event handler for the specified event.
RuntimeValue
Script_Object_RunInteraction(AGSEngine *vm, RoomObject *self,
                             const Common::Array<RuntimeValue> &params) {
	uint32 cursormode = params[0]._value;
	UNUSED(cursormode);

	// FIXME
	error("Object::RunInteraction unimplemented");

	return RuntimeValue();
}

// Object: import function SetPosition(int x, int y)
// Instantly moves the object to have its bottom-left at the new co-ordinates.
RuntimeValue
Script_Object_SetPosition(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	int x = params[0]._signedValue;
	UNUSED(x);
	int y = params[1]._signedValue;
	UNUSED(y);

	// FIXME
	error("Object::SetPosition unimplemented");

	return RuntimeValue();
}

// Object: import function SetView(int view, int loop=-1, int frame=-1)
// Sets the object to use the specified view, ahead of doing an animation.
RuntimeValue Script_Object_SetView(AGSEngine *vm, RoomObject *self,
                                   const Common::Array<RuntimeValue> &params) {
	int view = params[0]._signedValue;
	UNUSED(view);
	int loop = params[1]._signedValue;
	UNUSED(loop);
	int frame = params[2]._signedValue;
	UNUSED(frame);

	// FIXME
	error("Object::SetView unimplemented");

	return RuntimeValue();
}

// Object: import function StopAnimating()
// Stops any currently running animation on the object.
RuntimeValue
Script_Object_StopAnimating(AGSEngine *vm, RoomObject *self,
                            const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::StopAnimating unimplemented");

	return RuntimeValue();
}

// Object: import function StopMoving()
// Stops any currently running move on the object.
RuntimeValue
Script_Object_StopMoving(AGSEngine *vm, RoomObject *self,
                         const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::StopMoving unimplemented");

	return RuntimeValue();
}

// Object: import function Tint(int red, int green, int blue, int saturation,
// int luminance) Tints the object to the specified colour.
RuntimeValue Script_Object_Tint(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	int red = params[0]._signedValue;
	UNUSED(red);
	int green = params[1]._signedValue;
	UNUSED(green);
	int blue = params[2]._signedValue;
	UNUSED(blue);
	int saturation = params[3]._signedValue;
	UNUSED(saturation);
	int luminance = params[4]._signedValue;
	UNUSED(luminance);

	// FIXME
	error("Object::Tint unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute bool Animating
// Gets whether the object is currently animating.
RuntimeValue
Script_Object_get_Animating(AGSEngine *vm, RoomObject *self,
                            const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Animating unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Baseline
// Gets/sets the object's baseline. This can be 0 to use the object's Y position
// as its baseline.
RuntimeValue
Script_Object_get_Baseline(AGSEngine *vm, RoomObject *self,
                           const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Baseline unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Baseline
// Gets/sets the object's baseline. This can be 0 to use the object's Y position
// as its baseline.
RuntimeValue
Script_Object_set_Baseline(AGSEngine *vm, RoomObject *self,
                           const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_Baseline unimplemented");

	return RuntimeValue();
}

// Object: import attribute int BlockingHeight
// Allows you to manually specify the blocking height of the base of the object.
RuntimeValue
Script_Object_get_BlockingHeight(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_BlockingHeight unimplemented");

	return RuntimeValue();
}

// Object: import attribute int BlockingHeight
// Allows you to manually specify the blocking height of the base of the object.
RuntimeValue
Script_Object_set_BlockingHeight(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_BlockingHeight unimplemented");

	return RuntimeValue();
}

// Object: import attribute int BlockingWidth
// Allows you to manually specify the blocking width of the base of the object.
RuntimeValue
Script_Object_get_BlockingWidth(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_BlockingWidth unimplemented");

	return RuntimeValue();
}

// Object: import attribute int BlockingWidth
// Allows you to manually specify the blocking width of the base of the object.
RuntimeValue
Script_Object_set_BlockingWidth(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_BlockingWidth unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Clickable
// Gets/sets whether the mouse can be clicked on this object or whether it
// passes straight through.
RuntimeValue
Script_Object_get_Clickable(AGSEngine *vm, RoomObject *self,
                            const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Clickable unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Clickable
// Gets/sets whether the mouse can be clicked on this object or whether it
// passes straight through.
RuntimeValue
Script_Object_set_Clickable(AGSEngine *vm, RoomObject *self,
                            const Common::Array<RuntimeValue> &params) {
	uint32 value = params[0]._value;
	UNUSED(value);

	// FIXME
	error("Object::set_Clickable unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute int Frame
// Gets the current frame number during an animation.
RuntimeValue
Script_Object_get_Frame(AGSEngine *vm, RoomObject *self,
                        const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Frame unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Graphic
// Gets/sets the sprite number that is currently displayed on the object.
RuntimeValue
Script_Object_get_Graphic(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Graphic unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Graphic
// Gets/sets the sprite number that is currently displayed on the object.
RuntimeValue
Script_Object_set_Graphic(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_Graphic unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute int ID
// Gets the object's ID number.
RuntimeValue Script_Object_get_ID(AGSEngine *vm, RoomObject *self,
                                  const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_ID unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool IgnoreScaling
// Gets/sets whether the object ignores walkable area scaling.
RuntimeValue
Script_Object_get_IgnoreScaling(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_IgnoreScaling unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool IgnoreScaling
// Gets/sets whether the object ignores walkable area scaling.
RuntimeValue
Script_Object_set_IgnoreScaling(AGSEngine *vm, RoomObject *self,
                                const Common::Array<RuntimeValue> &params) {
	uint32 value = params[0]._value;
	UNUSED(value);

	// FIXME
	error("Object::set_IgnoreScaling unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool IgnoreWalkbehinds
// Gets/sets whether the object ignores walk-behind areas.
RuntimeValue
Script_Object_get_IgnoreWalkbehinds(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_IgnoreWalkbehinds unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool IgnoreWalkbehinds
// Gets/sets whether the object ignores walk-behind areas.
RuntimeValue
Script_Object_set_IgnoreWalkbehinds(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	uint32 value = params[0]._value;
	UNUSED(value);

	// FIXME
	error("Object::set_IgnoreWalkbehinds unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute int Loop
// Gets the current loop number during an animation.
RuntimeValue Script_Object_get_Loop(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Loop unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute bool Moving
// Gets whether the object is currently moving.
RuntimeValue
Script_Object_get_Moving(AGSEngine *vm, RoomObject *self,
                         const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Moving unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute String Name
// Gets the object's description.
RuntimeValue Script_Object_get_Name(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Name unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Solid
// Gets/sets whether other objects and characters can move through this object.
RuntimeValue
Script_Object_get_Solid(AGSEngine *vm, RoomObject *self,
                        const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Solid unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Solid
// Gets/sets whether other objects and characters can move through this object.
RuntimeValue
Script_Object_set_Solid(AGSEngine *vm, RoomObject *self,
                        const Common::Array<RuntimeValue> &params) {
	uint32 value = params[0]._value;
	UNUSED(value);

	// FIXME
	error("Object::set_Solid unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Transparency
// Gets/sets the object's transparency.
RuntimeValue
Script_Object_get_Transparency(AGSEngine *vm, RoomObject *self,
                               const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Transparency unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Transparency
// Gets/sets the object's transparency.
RuntimeValue
Script_Object_set_Transparency(AGSEngine *vm, RoomObject *self,
                               const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_Transparency unimplemented");

	return RuntimeValue();
}

// Object: readonly import attribute int View
// Gets the current view number during an animation.
RuntimeValue Script_Object_get_View(AGSEngine *vm, RoomObject *self,
                                    const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_View unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Visible
// Gets/sets whether the object is currently visible.
RuntimeValue
Script_Object_get_Visible(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Visible unimplemented");

	return RuntimeValue();
}

// Object: import attribute bool Visible
// Gets/sets whether the object is currently visible.
RuntimeValue
Script_Object_set_Visible(AGSEngine *vm, RoomObject *self,
                          const Common::Array<RuntimeValue> &params) {
	uint32 value = params[0]._value;
	UNUSED(value);

	// FIXME
	error("Object::set_Visible unimplemented");

	return RuntimeValue();
}

// Object: import attribute int X
// Gets/sets the X co-ordinate of the object's bottom-left hand corner.
RuntimeValue Script_Object_get_X(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_X unimplemented");

	return RuntimeValue();
}

// Object: import attribute int X
// Gets/sets the X co-ordinate of the object's bottom-left hand corner.
RuntimeValue Script_Object_set_X(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_X unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Y
// Gets/sets the Y co-ordinate of the object's bottom-left hand corner.
RuntimeValue Script_Object_get_Y(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	// FIXME
	error("Object::get_Y unimplemented");

	return RuntimeValue();
}

// Object: import attribute int Y
// Gets/sets the Y co-ordinate of the object's bottom-left hand corner.
RuntimeValue Script_Object_set_Y(AGSEngine *vm, RoomObject *self,
                                 const Common::Array<RuntimeValue> &params) {
	int value = params[0]._signedValue;
	UNUSED(value);

	// FIXME
	error("Object::set_Y unimplemented");

	return RuntimeValue();
}

static const ScriptSystemFunctionInfo ourFunctionList[] = {
    {"MergeObject", (ScriptAPIFunction *) &Script_MergeObject, "i", sotNone},
    {"SetObjectTint", (ScriptAPIFunction *) &Script_SetObjectTint, "iiiiii",
     sotNone},
    {"RemoveObjectTint", (ScriptAPIFunction *) &Script_RemoveObjectTint, "i",
     sotNone},
    {"StopObjectMoving", (ScriptAPIFunction *) &Script_StopObjectMoving, "i",
     sotNone},
    {"RunObjectInteraction", (ScriptAPIFunction *) &Script_RunObjectInteraction,
     "ii", sotNone},
    {"GetObjectProperty", (ScriptAPIFunction *) &Script_GetObjectProperty, "is",
     sotNone},
    {"GetObjectPropertyText",
     (ScriptAPIFunction *) &Script_GetObjectPropertyText, "iss", sotNone},
    {"AnimateObject", (ScriptAPIFunction *) &Script_AnimateObject, "iiii",
     sotNone},
    {"AnimateObjectEx", (ScriptAPIFunction *) &Script_AnimateObjectEx, "iiiiii",
     sotNone},
    {"ObjectOff", (ScriptAPIFunction *) &Script_ObjectOff, "i", sotNone},
    {"ObjectOn", (ScriptAPIFunction *) &Script_ObjectOn, "i", sotNone},
    {"SetObjectBaseline", (ScriptAPIFunction *) &Script_SetObjectBaseline, "ii",
     sotNone},
    {"GetObjectBaseline", (ScriptAPIFunction *) &Script_GetObjectBaseline, "i",
     sotNone},
    {"SetObjectFrame", (ScriptAPIFunction *) &Script_SetObjectFrame, "iiii",
     sotNone},
    {"SetObjectGraphic", (ScriptAPIFunction *) &Script_SetObjectGraphic, "ii",
     sotNone},
    {"SetObjectView", (ScriptAPIFunction *) &Script_SetObjectView, "ii",
     sotNone},
    {"SetObjectTransparency",
     (ScriptAPIFunction *) &Script_SetObjectTransparency, "ii", sotNone},
    {"MoveObject", (ScriptAPIFunction *) &Script_MoveObject, "iiii", sotNone},
    {"MoveObjectDirect", (ScriptAPIFunction *) &Script_MoveObjectDirect, "iiii",
     sotNone},
    {"SetObjectPosition", (ScriptAPIFunction *) &Script_SetObjectPosition,
     "iii", sotNone},
    {"AreObjectsColliding", (ScriptAPIFunction *) &Script_AreObjectsColliding,
     "ii", sotNone},
    {"GetObjectName", (ScriptAPIFunction *) &Script_GetObjectName, "is",
     sotNone},
    {"GetObjectX", (ScriptAPIFunction *) &Script_GetObjectX, "i", sotNone},
    {"GetObjectY", (ScriptAPIFunction *) &Script_GetObjectY, "i", sotNone},
    {"GetObjectGraphic", (ScriptAPIFunction *) &Script_GetObjectGraphic, "i",
     sotNone},
    {"IsObjectAnimating", (ScriptAPIFunction *) &Script_IsObjectAnimating, "i",
     sotNone},
    {"IsObjectMoving", (ScriptAPIFunction *) &Script_IsObjectMoving, "i",
     sotNone},
    {"IsObjectOn", (ScriptAPIFunction *) &Script_IsObjectOn, "i", sotNone},
    {"SetObjectClickable", (ScriptAPIFunction *) &Script_SetObjectClickable,
     "ii", sotNone},
    {"SetObjectIgnoreWalkbehinds",
     (ScriptAPIFunction *) &Script_SetObjectIgnoreWalkbehinds, "ii", sotNone},
    {"Object::Animate^5", (ScriptAPIFunction *) &Script_Object_Animate, "iiiii",
     sotRoomObject},
    {"Object::GetAtScreenXY^2",
     (ScriptAPIFunction *) &Script_Object_GetAtScreenXY, "ii", sotNone},
    {"Object::GetName^1", (ScriptAPIFunction *) &Script_Object_GetName, "s",
     sotRoomObject},
    {"Object::GetPropertyText^2",
     (ScriptAPIFunction *) &Script_Object_GetPropertyText, "ss", sotRoomObject},
    {"Object::GetProperty^1", (ScriptAPIFunction *) &Script_Object_GetProperty,
     "s", sotRoomObject},
    {"Object::GetTextProperty^1",
     (ScriptAPIFunction *) &Script_Object_GetTextProperty, "s", sotRoomObject},
    {"Object::IsCollidingWithObject^1",
     (ScriptAPIFunction *) &Script_Object_IsCollidingWithObject, "o",
     sotRoomObject},
    {"Object::MergeIntoBackground^0",
     (ScriptAPIFunction *) &Script_Object_MergeIntoBackground, "",
     sotRoomObject},
    {"Object::Move^5", (ScriptAPIFunction *) &Script_Object_Move, "iiiii",
     sotRoomObject},
    {"Object::RemoveTint^0", (ScriptAPIFunction *) &Script_Object_RemoveTint,
     "", sotRoomObject},
    {"Object::RunInteraction^1",
     (ScriptAPIFunction *) &Script_Object_RunInteraction, "i", sotRoomObject},
    {"Object::SetPosition^2", (ScriptAPIFunction *) &Script_Object_SetPosition,
     "ii", sotRoomObject},
    {"Object::SetView^3", (ScriptAPIFunction *) &Script_Object_SetView, "iii",
     sotRoomObject},
    {"Object::StopAnimating^0",
     (ScriptAPIFunction *) &Script_Object_StopAnimating, "", sotRoomObject},
    {"Object::StopMoving^0", (ScriptAPIFunction *) &Script_Object_StopMoving,
     "", sotRoomObject},
    {"Object::Tint^5", (ScriptAPIFunction *) &Script_Object_Tint, "iiiii",
     sotRoomObject},
    {"Object::get_Animating",
     (ScriptAPIFunction *) &Script_Object_get_Animating, "", sotRoomObject},
    {"Object::get_Baseline", (ScriptAPIFunction *) &Script_Object_get_Baseline,
     "", sotRoomObject},
    {"Object::set_Baseline", (ScriptAPIFunction *) &Script_Object_set_Baseline,
     "i", sotRoomObject},
    {"Object::get_BlockingHeight",
     (ScriptAPIFunction *) &Script_Object_get_BlockingHeight, "",
     sotRoomObject},
    {"Object::set_BlockingHeight",
     (ScriptAPIFunction *) &Script_Object_set_BlockingHeight, "i",
     sotRoomObject},
    {"Object::get_BlockingWidth",
     (ScriptAPIFunction *) &Script_Object_get_BlockingWidth, "", sotRoomObject},
    {"Object::set_BlockingWidth",
     (ScriptAPIFunction *) &Script_Object_set_BlockingWidth, "i",
     sotRoomObject},
    {"Object::get_Clickable",
     (ScriptAPIFunction *) &Script_Object_get_Clickable, "", sotRoomObject},
    {"Object::set_Clickable",
     (ScriptAPIFunction *) &Script_Object_set_Clickable, "i", sotRoomObject},
    {"Object::get_Frame", (ScriptAPIFunction *) &Script_Object_get_Frame, "",
     sotRoomObject},
    {"Object::get_Graphic", (ScriptAPIFunction *) &Script_Object_get_Graphic,
     "", sotRoomObject},
    {"Object::set_Graphic", (ScriptAPIFunction *) &Script_Object_set_Graphic,
     "i", sotRoomObject},
    {"Object::get_ID", (ScriptAPIFunction *) &Script_Object_get_ID, "",
     sotRoomObject},
    {"Object::get_IgnoreScaling",
     (ScriptAPIFunction *) &Script_Object_get_IgnoreScaling, "", sotRoomObject},
    {"Object::set_IgnoreScaling",
     (ScriptAPIFunction *) &Script_Object_set_IgnoreScaling, "i",
     sotRoomObject},
    {"Object::get_IgnoreWalkbehinds",
     (ScriptAPIFunction *) &Script_Object_get_IgnoreWalkbehinds, "",
     sotRoomObject},
    {"Object::set_IgnoreWalkbehinds",
     (ScriptAPIFunction *) &Script_Object_set_IgnoreWalkbehinds, "i",
     sotRoomObject},
    {"Object::get_Loop", (ScriptAPIFunction *) &Script_Object_get_Loop, "",
     sotRoomObject},
    {"Object::get_Moving", (ScriptAPIFunction *) &Script_Object_get_Moving, "",
     sotRoomObject},
    {"Object::get_Name", (ScriptAPIFunction *) &Script_Object_get_Name, "",
     sotRoomObject},
    {"Object::get_Solid", (ScriptAPIFunction *) &Script_Object_get_Solid, "",
     sotRoomObject},
    {"Object::set_Solid", (ScriptAPIFunction *) &Script_Object_set_Solid, "i",
     sotRoomObject},
    {"Object::get_Transparency",
     (ScriptAPIFunction *) &Script_Object_get_Transparency, "", sotRoomObject},
    {"Object::set_Transparency",
     (ScriptAPIFunction *) &Script_Object_set_Transparency, "i", sotRoomObject},
    {"Object::get_View", (ScriptAPIFunction *) &Script_Object_get_View, "",
     sotRoomObject},
    {"Object::get_Visible", (ScriptAPIFunction *) &Script_Object_get_Visible,
     "", sotRoomObject},
    {"Object::set_Visible", (ScriptAPIFunction *) &Script_Object_set_Visible,
     "i", sotRoomObject},
    {"Object::get_X", (ScriptAPIFunction *) &Script_Object_get_X, "",
     sotRoomObject},
    {"Object::set_X", (ScriptAPIFunction *) &Script_Object_set_X, "i",
     sotRoomObject},
    {"Object::get_Y", (ScriptAPIFunction *) &Script_Object_get_Y, "",
     sotRoomObject},
    {"Object::set_Y", (ScriptAPIFunction *) &Script_Object_set_Y, "i",
     sotRoomObject},
};

void addObjectSystemScripting(AGSEngine *vm) {
	GlobalScriptState *state = vm->getScriptState();

	state->addSystemFunctionImportList(ourFunctionList,
	                                   ARRAYSIZE(ourFunctionList));
}

} // End of namespace AGS
