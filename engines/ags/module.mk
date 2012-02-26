MODULE := engines/ags

MODULE_OBJS := \
	ags.o \
	audio.o \
	detection.o \
	gamefile.o \
	gamestate.o \
	gui.o \
	resourceman.o \
	room.o \
	script.o \
	scripting/audio.o \
	scripting/character.o \
	scripting/dialog.o \
	scripting/file.o \
	scripting/game.o \
	scripting/graphics.o \
	scripting/gui.o \
	scripting/input.o \
	scripting/inventory.o \
	scripting/misc.o \
	scripting/object.o \
	scripting/parser.o \
	scripting/room.o \
	scripting/scripting.o \
	scripting/string.o \
	scripting/utils.o \
	sprites.o \
	util.o

# This module can be built as a plugin
ifeq ($(ENABLE_AGS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
