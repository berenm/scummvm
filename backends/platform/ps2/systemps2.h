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

#ifndef SYSTEMPS2_H
#define SYSTEMPS2_H

#include "backends/base-backend.h"

class DefaultTimerManager;

class Gs2dScreen;
class Ps2Input;
class Ps2SaveFileManager;
// class Ps2FilesystemFactory;
struct IrxReference;

#define MAX_MUTEXES 16

struct Ps2Mutex {
	int sema;
	int owner;
	int count;
};

namespace Common {
	class TimerManager;
};

namespace Audio {
	class MixerImpl;
};

class OSystem_PS2 : public BaseBackend {
public:
	OSystem_PS2(const char *elfPath);
	virtual ~OSystem_PS2(void);
	virtual void initSize(uint width, uint height);

	void init(void);

	virtual int16 getHeight(void);
	virtual int16 getWidth(void);
	virtual void setPalette(const byte *colors, uint start, uint num);
	virtual void copyRectToScreen(const byte *buf, int pitch, int x, int y, int w, int h);
	virtual void setShakePos(int shakeOffset);
	virtual void grabPalette(byte *colors, uint start, uint num);
	virtual bool grabRawScreen(Graphics::Surface *surf);
	virtual Graphics::Surface *lockScreen();
	virtual void unlockScreen();
	virtual void updateScreen();

	virtual void showOverlay();
	virtual void hideOverlay();
	virtual void clearOverlay();
	virtual void grabOverlay(OverlayColor *buf, int pitch);
	virtual void copyRectToOverlay(const OverlayColor *buf, int pitch, int x, int y, int w, int h);
	virtual int16 getOverlayHeight()  { return getHeight(); }
	virtual int16 getOverlayWidth()   { return getWidth(); }

	virtual bool showMouse(bool visible);

	virtual void warpMouse(int x, int y);
	virtual void setMouseCursor(const byte *buf, uint w, uint h, int hotspot_x, int hotspot_y, byte keycolor, int cursorTargetScale = 1);

	virtual uint32 getMillis();
	virtual void delayMillis(uint msecs);
	virtual Common::TimerManager *getTimerManager();
	virtual bool pollEvent(Common::Event &event);

	virtual Audio::Mixer *getMixer();

	virtual bool openCD(int drive);
	virtual bool pollCD();
	virtual void playCD(int track, int num_loops, int start_frame, int duration);
	virtual void stopCD();
	virtual void updateCD();

	virtual MutexRef createMutex(void);
	virtual void lockMutex(MutexRef mutex);
	virtual void unlockMutex(MutexRef mutex);
	virtual void deleteMutex(MutexRef mutex);

	virtual const GraphicsMode *getSupportedGraphicsModes() const;
	virtual int getDefaultGraphicsMode() const;
	virtual bool setGraphicsMode(int mode);
	virtual int getGraphicsMode() const;

	virtual void quit();

	virtual Common::SeekableReadStream *createConfigReadStream();
	virtual Common::WriteStream *createConfigWriteStream();

	virtual Graphics::PixelFormat getOverlayFormat() const { return Graphics::createPixelFormat<555>(); }

	virtual Common::SaveFileManager *getSavefileManager();
	virtual FilesystemFactory *getFilesystemFactory();

	virtual void getTimeAndDate(struct tm &t) const;

	void timerThread(void);
	void soundThread(void);
	void msgPrintf(int millis, char *format, ...);
	void makeConfigPath(char *dest);

	void powerOffCallback(void);
	bool hddPresent(void);
	bool usbMassPresent(void);

	bool runningFromHost(void);
private:
	void startIrxModules(int numModules, IrxReference *modules);

	void initMutexes(void);
	void initTimer(void);
	void readRtcTime(void);

	DefaultTimerManager *_scummTimerManager;
	Audio::MixerImpl *_scummMixer;


	bool _mouseVisible;
	bool _useMouse, _useKbd, _useHdd, _usbMassLoaded;

	Ps2SaveFileManager *_saveManager;

	Gs2dScreen	*_screen;
	Ps2Input	*_input;
	uint16		_oldMouseX, _oldMouseY;
	uint32		_msgClearTime;
	uint16		_printY;

	int			_mutexSema;
	Ps2Mutex	_mutex[MAX_MUTEXES];

	uint8		*_timerStack, *_soundStack;
	int			_timerTid, _soundTid;
	int			_intrId;
	volatile bool _systemQuit;
	static const GraphicsMode _graphicsMode;

	int			_bootDevice;
};

#endif // SYSTEMPS2_H

