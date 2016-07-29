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

#include "common/textconsole.h"
#include "titanic/true_talk/liftbot_script.h"
#include "titanic/true_talk/true_talk_manager.h"

namespace Titanic {

int LiftbotScript::_stateIndex;

static const int STATE_ARRAY[7] = {
	0x78BE, 0x78C0, 0x78C1, 0x78C2, 0x78C3, 0x78C4, 0x78C5
};

LiftbotScript::LiftbotScript(int val1, const char *charClass, int v2,
		const char *charName, int v3, int val2, int v4, int v5, int v6, int v7) :
		TTnpcScript(val1, charClass, v2, charName, v3, val2, v4, v5, v6, v7) {
	_stateIndex = 0;

	loadRanges("Ranges/Liftbot");
	loadResponses("Responses/Liftbot");
	setupSentences();
	_tagMappings.load("TagMap/Liftbot");
	_words.load("Words/Liftbot");
	_quotes.load("Quotes/Liftbot");
	_states.load("States/Liftbot");
}

void LiftbotScript::setupSentences() {
	CTrueTalkManager::setFlags(27, 0);
	setupDials(getRandomNumber(40) + 60, getRandomNumber(40) + 60, 0);

	_mappings.load("Mappings/Liftbot", 4);
	_entries.load("Sentences/Liftbot");
	_field68 = 0;
	_entryCount = 0;
}

int LiftbotScript::chooseResponse(TTroomScript *roomScript, TTsentence *sentence, uint tag) {
	switch (tag) {
	case MKTAG('D', 'N', 'A', '1'):
	case MKTAG('H', 'H', 'G', 'Q'):
	case MKTAG('A', 'N', 'S', 'W'):
		if (_stateIndex >= 7) {
			selectResponse(30918);
			setState(2);
			_stateIndex = 0;
		} else {
			addResponse(STATE_ARRAY[_stateIndex++]);
		}

		applyResponse();
		return 2;

	case MKTAG('O', 'R', 'D', '8'):
		addResponse(30475);
		addResponse(30467);
		addResponse(30466);
		addResponse(30474);
		applyResponse();
		return SS_2;

	default:
		return TTnpcScript::chooseResponse(roomScript, sentence, tag);
	}
}

int LiftbotScript::process(TTroomScript *roomScript, TTsentence *sentence) {
	// TODO
	return 0;
}

int LiftbotScript::proc9() const {
	warning("TODO");
	return 0;
}

ScriptChangedResult LiftbotScript::scriptChanged(TTscriptBase *roomScript, uint id) {
	warning("TODO");
	return SCR_1;
}

int LiftbotScript::handleQuote(TTroomScript *roomScript, TTsentence *sentence,
		uint val, uint tagId, uint remainder) {
	switch (tagId) {
	case MKTAG('A', 'D', 'V', 'T'):
	case MKTAG('A', 'R', 'T', 'I'):
	case MKTAG('A', 'R', 'T', 'Y'):
	case MKTAG('B', 'R', 'N', 'D'):
	case MKTAG('C', 'O', 'M', 'D'):
	case MKTAG('D', 'N', 'C', 'E'):
	case MKTAG('H', 'B', 'B', 'Y'):
	case MKTAG('L', 'I', 'T', 'R'):
	case MKTAG('M', 'A', 'G', 'S'):
	case MKTAG('M', 'C', 'P', 'Y'):
	case MKTAG('M', 'I', 'N', 'S'):
	case MKTAG('M', 'U', 'S', 'I'):
	case MKTAG('N', 'I', 'K', 'E'):
	case MKTAG('S', 'F', 'S', 'F'):
	case MKTAG('S', 'O', 'A', 'P'):
	case MKTAG('S', 'O', 'N', 'G'):
	case MKTAG('S', 'P', 'R', 'T'):
	case MKTAG('T', 'E', 'A', 'M'):
	case MKTAG('T', 'V', 'S', 'H'):
	case MKTAG('W', 'W', 'E', 'B'):
		tagId = MKTAG('E', 'N', 'T', 'N');
		break;
	case MKTAG('A', 'C', 'T', 'R'):
	case MKTAG('A', 'C', 'T', 'S'):
	case MKTAG('A', 'U', 'T', 'H'):
	case MKTAG('B', 'A', 'R', 'K'):
	case MKTAG('B', 'A', 'R', 'U'):
	case MKTAG('B', 'L', 'F', '1'):
	case MKTAG('B', 'L', 'F', '2'):
	case MKTAG('B', 'L', 'R', '1'):
	case MKTAG('B', 'L', 'R', '2'):
	case MKTAG('B', 'L', 'P', '1'):
	case MKTAG('B', 'L', 'P', '2'):
	case MKTAG('B', 'L', 'P', '3'):
	case MKTAG('B', 'L', 'P', '4'):
	case MKTAG('B', 'L', 'T', '1'):
	case MKTAG('B', 'L', 'T', '2'):
	case MKTAG('B', 'L', 'T', '3'):
	case MKTAG('B', 'L', 'T', '4'):
	case MKTAG('B', 'L', 'T', '5'):
	case MKTAG('B', 'O', 'Y', 'S'):
	case MKTAG('C', 'O', 'P', 'S'):
	case MKTAG('D', 'C', 'T', 'R'):
	case MKTAG('F', 'A', 'M', 'E'):
	case MKTAG('F', 'A', 'S', 'H'):
	case MKTAG('G', 'I', 'R', 'L'):
	case MKTAG('H', 'E', 'R', 'O'):
	case MKTAG('H', 'O', 'S', 'T'):
	case MKTAG('K', 'N', 'O', 'B'):
	case MKTAG('N', 'H', 'R', 'O'):
	case MKTAG('R', 'A', 'C', 'E'):
	case MKTAG('S', 'C', 'I', 'T'):
	case MKTAG('T', 'D', 'V', 'P'):
	case MKTAG('T', 'W', 'A', 'T'):
	case MKTAG('W', 'E', 'A', 'T'):
		tagId = MKTAG('P', 'R', 'S', 'N');
		break;
	case MKTAG('C', 'H', 'S', 'E'):
	case MKTAG('C', 'M', 'N', 'T'):
	case MKTAG('F', 'I', 'L', 'M'):
	case MKTAG('J', 'F', 'O', 'D'):
	case MKTAG('L', 'I', 'Q', 'D'):
		tagId = MKTAG('F', 'O', 'O', 'D');
		break;
	case MKTAG('C', 'R', 'I', 'M'):
	case MKTAG('C', 'S', 'P', 'Y'):
	case MKTAG('D', 'R', 'U', 'G'):
		tagId = MKTAG('V', 'B', 'A', 'D');
		break;
	case MKTAG('E', 'A', 'R', 'T'):
	case MKTAG('H', 'O', 'M', 'E'):
	case MKTAG('N', 'P', 'L', 'C'):
	case MKTAG('P', 'L', 'A', 'N'):
		tagId = MKTAG('P', 'L', 'A', 'C');
		break;
	case MKTAG('F', 'A', 'U', 'N'):
	case MKTAG('F', 'I', 'S', 'H'):
	case MKTAG('F', 'L', 'O', 'R'):
		tagId = MKTAG('N', 'A', 'T', 'R');
		break;
	case MKTAG('H', 'H', 'L', 'D'):
	case MKTAG('T', 'O', 'Y', 'S'):
	case MKTAG('W', 'E', 'A', 'P'):
		tagId = MKTAG('M', 'A', 'C', 'H');
		break;
	case MKTAG('M', 'L', 'T', 'Y'):
	case MKTAG('P', 'G', 'R', 'P'):
	case MKTAG('P', 'T', 'I', 'C'):
		tagId = MKTAG('G', 'R', 'U', 'P');
		break;
	case MKTAG('P', 'K', 'U', 'P'):
	case MKTAG('S', 'E', 'X', '1'):
	case MKTAG('S', 'W', 'E', 'R'):
		tagId = MKTAG('R', 'U', 'D', 'E');
		break;
	case MKTAG('P', 'H', 'I', 'L'):
	case MKTAG('R', 'C', 'K', 'T'):
		tagId = MKTAG('S', 'C', 'I', 'E');
		break;
	case MKTAG('T', 'R', 'A', '2'):
	case MKTAG('T', 'R', 'A', '3'):
		tagId = MKTAG('T', 'R', 'A', 'V');
		break;
	}

	return TTnpcScript::handleQuote(roomScript, sentence, val, tagId, remainder);
}

int LiftbotScript::updateState(int oldId, int newId, int index) {
	warning("TODO");
	return 0;
}

int LiftbotScript::proc22(int id) const {
	warning("TODO");
	return 0;
}

uint LiftbotScript::getDialsBitset() const {
	uint bits = 0;
	if (!getDialRegion(1))
		bits = 1;
	if (!getDialRegion(0))
		bits |= 2;
	if (bits > 1)
		bits ^= 1;

	return bits;
}


int LiftbotScript::proc25(int val1, const int *srcIdP, TTroomScript *roomScript, TTsentence *sentence) {
	static const int ARRAY13[] = {
		210724, 210735, 210746, 210757, 210758, 210759, 210760,
		210761, 210762, 210725, 210726, 210727, 210728, 210729,
		210730, 210731, 210732, 210733, 210734, 210736, 210737,
		210738, 210739, 210740, 210741, 210742, 210743, 210744,
		210745, 210747, 210748, 210749, 210750, 210751, 210752,
		210753, 210754, 210755, 210756
	};
	static const int ARRAY14[] = {
		0, 210849, 210850, 210851, 210852, 210838, 210839, 210840, 210841, 0
	};

	getState();
	int stateVal;

	switch (val1) {
	case 1:
		if (getValue(1) != 1)
			return 1;
		break;
	case 2:
		if (getValue(1) != 2)
			return 1;
		break;
	case 3:
		if (getValue(1) != 3)
			return 1;
		break;
	case 4:
	case 5:
		return !sentence1(sentence);
	case 6:
		if (sentence->localWord("big") || sentence->localWord("small")) {
			addResponse(getDialogueId(210215));
			applyResponse();
		} else if (sentence->localWord("my") || sentence->contains("my") ||
				sentence->contains("bedroom") || sentence->contains("state")) {
			addResponse1(CTrueTalkManager::getStateValue(4), true, 0);
		} else {
			selectResponse(210763);
			applyResponse();
		}
		return 2;
	case 7:
		if (!sentence->localWord("ill") && !sentence->localWord("well"))
			return 1;
		break;
	case 8:
		if (!sentence->localWord("long"))
			return 1;
		break;
	case 9:
		if (addResponse1(1, false, 0))
			return 2;
		break;
	case 10:
		if (addResponse1(39, false, 0))
			return 2;
		break;
	case 11:
		if (getState6() == 2 || getState6() == 4)
			return 1;
		break;
	case 12:
		if (getState6() == 1 || getState6() == 3)
			return 1;
		break;
	case 13:
		selectResponse(ARRAY13[getState5()]);
		applyResponse();
		return 2;
	case 14:
		stateVal = getState6();
		if (sentence->contains("elevator") ||
			(!sentence->contains("lift") && getRandomNumber(100) > 60))
			stateVal += 4;
		selectResponse(ARRAY14[stateVal]);
		applyResponse();
		return 2;
	case 15:
		if (getRandomNumber(100) > 60) {
			addResponse(getDialogueId(210440));
		} else {
			addResponse(getDialogueId(210906));
			addResponse(getDialogueId(210901));
		}
		applyResponse();
		return 2;
	case 16:
		if (sentence->contains("elevator") || sentence->contains("elavator"))
			addResponse(30579);
		else
			addResponse(30580);
		applyResponse();
		return 2;
	case 17:
		if (sentence->localWord("restaurant") || sentence->contains("restaurant"))
			return 1;
		break;
	default:
		break;
	}

	return 0;
}

void LiftbotScript::proc26(int v1, const TTsentenceEntry *entry, TTroomScript *roomScript, TTsentence *sentence) {
}

void LiftbotScript::setDialRegion(int dialNum, int region) {
	TTnpcScript::setDialRegion(dialNum, region);
	addResponse(getDialogueId(210688));
	applyResponse();
}

int LiftbotScript::getState5() const {
	int val = CTrueTalkManager::getStateValue(5);
	return CLIP(val, 1, 39);
}

int LiftbotScript::getState6() const {
	int val = CTrueTalkManager::getStateValue(6);
	return (val < 1 || val > 4) ? 1 : val;
}

int LiftbotScript::addDialogueAndState(int id, int state) {
	addResponse(id);
	applyResponse();

	if (state != 1)
		setState(state);
	return 2;
}

int LiftbotScript::addResponse1(int index, bool flag, int id) {
	static const int DIALOGUE_IDS[37] = {
		210735, 210746, 210757, 210758, 210759, 210760, 210761, 210762,
		210725, 210726, 210727, 210728, 210729, 210730, 210731, 210732,
		210733, 210734, 210736, 210737, 210738, 210739, 210740, 210741,
		210742, 210743, 210744, 210745, 210747, 210748, 210749, 210750,
		210751, 210752, 210753, 210754, 210755
	};

	int stateVal = getState6();
	int maxIndex = (stateVal == 2 || stateVal == 4) ? 27 : 39;

	if (index < 1 || index > maxIndex) {
		addResponse(getDialogueId(maxIndex == 27 ? 210587 : 210586));
		applyResponse();
		return 1;
	} else if (index == getState5()) {
		if (index == 1) {
			addResponse(30558 - getRandomBit() ? 290 : 0);
			addResponse(getDialogueId(210589));
		} else {
			if (index == 39)
				addResponse(30346);
			addResponse(getDialogueId(210589));
		}

		applyResponse();
		return 2;
	}

	stateVal = getValue(1);
	if (index >= 2 && index <= 19 && stateVal > 1) {
		addResponse(getDialogueId(210203));
		applyResponse();
		setState(7);
		return true;
	}

	if (index >= 20 && index <= 27 && stateVal > 2) {
		addResponse(getDialogueId(210210));
		applyResponse();
		setState(8);
		return true;
	}

	if (flag) {
		if (index == 1) {
			selectResponse(30558 - getRandomBit() ? 290 : 0);
		} else if (index == 39) {
			addResponse(30346);
		} else {
			if (getRandomNumber(100) > 35 && index >= 2 && index <= 38) {
				addResponse(getDialogueId(DIALOGUE_IDS[index - 2]));
			}

			addResponse(getDialogueId(210588));
		}

		if (id) {
			if (id == 210717 || id == 210716 || id == 210719 || id == 210718) {
				addResponse(getDialogueId(210720));
				addResponse(getDialogueId(id));
				addResponse(getDialogueId(210715));
			} else {
				addResponse(getDialogueId(id));
			}
		}

		applyResponse();
	}

	CTrueTalkManager::triggerAction(2, index);
	return flag;
}

int LiftbotScript::sentence1(const TTsentence *sentence) {
	warning("TODO: LiftbotScript::sentence1");
	return 0;
}

} // End of namespace Titanic
