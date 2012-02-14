MODULE := engines/ags

MODULE_OBJS := \
	ags.o \
	detection.o \
	gamefile.o \
	gui.o \
	resourceman.o \
	room.o \
	script.o \
	sprites.o \
	util.o

# This module can be built as a plugin
ifeq ($(ENABLE_AGS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
