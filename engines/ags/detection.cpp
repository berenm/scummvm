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
 * Jones, which is licensed under the Artistic License 2.0. You may also
 * modify/distribute the code in this file under that license.
 */

#include "base/plugins.h"
#include "common/debug.h"
#include "engines/advancedDetector.h"

#include "ags/ags.h"
#include "ags/constants.h"
#include "ags/resourceman.h"

namespace AGS {

struct AGSGameDescription {
	ADGameDescription desc;

	const char *title;
	const char *filename;
};

} // namespace AGS

static const PlainGameDescriptor AGSGames[] = {
    {"5days", "5 Days a Stranger"},     {"7days", "7 Days a Skeptic"},
    {"trilbysnotes", "Trilby's Notes"}, {"6days", "6 Days a Sacrifice"},
    {"ags", "Generic AGS game"},        {0, 0}};

#include "ags/detection_tables.h"

class AGSMetaEngine : public AdvancedMetaEngine {
public:
	AGSMetaEngine() :
	    AdvancedMetaEngine(AGS::gameDescriptions,
	                       sizeof(AGS::AGSGameDescription), AGSGames) {
		_singleId = "ags";
		_guiOptions = GUIO1(GUIO_NOLAUNCHLOAD);
	}

	virtual const char *getName() const { return "Adventure Game Studio"; }

	virtual const char *getOriginalCopyright() const {
		return "Copyright (C) 1999-2011 Chris Jones";
	}

	virtual bool hasFeature(MetaEngineFeature f) const;
	virtual bool createInstance(OSystem *syst, Engine **engine,
	                            const ADGameDescription *desc) const;

protected:
	virtual ADDetectedGame fallbackDetect(const FileMap &allFiles,
	                                      const Common::FSList &fslist) const;
};

static AGS::AGSGameDescription s_fallbackDesc = {};

static char s_fallbackFilenameBuffer[51];
static char s_fallbackTitleBuffer[51];

ADDetectedGame
AGSMetaEngine::fallbackDetect(const FileMap &allFiles,
                              const Common::FSList &fslist) const {
	ADDetectedGame d = detectGameFilebased(allFiles, fslist, AGS::fileBased);
	if (d.desc)
		return d;

	// reset fallback description
	AGS::AGSGameDescription *desc = &s_fallbackDesc;
	desc->desc.gameId = "ags";
	desc->desc.extra = "";
	desc->desc.language = Common::UNK_LANG;
	desc->desc.flags = ADGF_AUTOGENTARGET | ADGF_USEEXTRAASTITLE;
	desc->desc.platform = Common::kPlatformUnknown;
	desc->desc.guiOptions = GUIO0();
	desc->title = "";
	desc->filename = "";

	for (Common::FSList::const_iterator file = fslist.begin();
	     file != fslist.end(); ++file) {
		if (file->isDirectory())
			continue;

		Common::String filename = file->getName();
		debug(4, "Checking file %s", filename.c_str());

		// Looking for either the Windows engine with the game data attached
		// or a standalone data file
		filename.toLowercase();
		if (!filename.hasSuffix(".exe") && !filename.hasSuffix(".ags") &&
		    !filename.hasSuffix(".dat"))
			continue;

		if (filename.hasSuffix(".exe"))
			desc->desc.platform = Common::kPlatformWindows;

		SearchMan.clear();
		SearchMan.addDirectory(file->getParent().getName(), file->getParent());
		AGS::ResourceManager resourceManager;
		if (!resourceManager.init(filename)) {
			debug(4, "File %s failed ResourceManager init", filename.c_str());
			continue;
		}

		Common::SeekableReadStream *dta =
		    resourceManager.getFile(AGS::kGameDataNameV2);
		if (!dta) {
			// if no 2.x data, try 3.x
			debug(4, "No V2 game data. Trying V3...");
			dta = resourceManager.getFile(AGS::kGameDataNameV3);
			if (!dta) {
				debug(3, "AGS detection couldn't find game data file in '%s'",
				      filename.c_str());
				continue;
			}
		}
		dta->skip(30 + 4); // signature + version
		uint32 versionStringLength = dta->readUint32LE();
		assert(versionStringLength < 32);

		char versionString[32];
		dta->read(versionString, versionStringLength);
		versionString[versionStringLength] = 0;
		debug(2, "Found AGS version: '%s'", versionString);

		uint majorVersion = 0;
		uint minorVersion = 0;
		uint releaseVersion = 0;
		uint buildVersion = 0;

		int n = sscanf(versionString, "%u.%u.%u.%u", &majorVersion,
		               &minorVersion, &releaseVersion, &buildVersion);
		assert(n >= 2);

		if (majorVersion >= 3 && minorVersion >= 4)
			dta->skip(4);

		char gameTitle[51];
		dta->read(gameTitle, 50);
		gameTitle[50] = '\0';

		delete dta;

		strncpy(s_fallbackTitleBuffer, gameTitle, 50);
		s_fallbackTitleBuffer[50] = '\0';

		desc->title = s_fallbackTitleBuffer;
		desc->desc.extra = s_fallbackTitleBuffer;

		strncpy(s_fallbackFilenameBuffer, filename.c_str(), 50);
		s_fallbackFilenameBuffer[50] = '\0';

		desc->filename = s_fallbackFilenameBuffer;

		return ADDetectedGame((ADGameDescription *) desc);
	}

	return ADDetectedGame();
}

bool AGSMetaEngine::hasFeature(MetaEngineFeature f) const {
	return false;
}

bool AGS::AGSEngine::hasFeature(EngineFeature f) const {
	return f == kSupportsRTL;
}

bool AGSMetaEngine::createInstance(OSystem *syst, Engine **engine,
                                   const ADGameDescription *desc) const {
	const AGS::AGSGameDescription *gd = (const AGS::AGSGameDescription *) desc;
	if (gd) {
		*engine = new AGS::AGSEngine(syst, gd);
		((AGS::AGSEngine *) *engine)->initGame(gd);
	}
	return gd != 0;
}

#if PLUGIN_ENABLED_DYNAMIC(AGS)
REGISTER_PLUGIN_DYNAMIC(AGS, PLUGIN_TYPE_ENGINE, AGSMetaEngine);
#else
REGISTER_PLUGIN_STATIC(AGS, PLUGIN_TYPE_ENGINE, AGSMetaEngine);
#endif
