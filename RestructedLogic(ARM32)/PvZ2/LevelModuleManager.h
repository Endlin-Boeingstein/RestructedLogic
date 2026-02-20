#pragma once
#include "LevelModule.h"
#include "../Sexy/RtObject.h"
#include "../Sexy/Event.h"

class LevelModuleManager : public Sexy::RtObject
{
public:
	std::vector<Sexy::RtWeakPtr<LevelModule>> m_modules;
	std::vector<Sexy::SexyString> m_loadedResourceGroups;
	int unk;
	Sexy::RtWeakPtr<void> unkPtr;
	std::vector<int> unkVec1; // these ain't ints
	std::vector<int> unkVec2; // these ain't ints
	bool unk0x40;
	Sexy::Event m_loadingEvent;
	Sexy::Event m_transitionFromLoadingEvent;
	Sexy::Event m_introEvent;
	Sexy::Event m_levelStartEvent;
	Sexy::Event unkEvent5;
	Sexy::Event unkEvent6;
	Sexy::Event unkEvent7;
	Sexy::Event unkEvent8;
	Sexy::Event unkEvent9;
	Sexy::Event unkEvent10;
	Sexy::Event unkEvent11;
	Sexy::Event unkEvent12;
	Sexy::Event unkEvent13;
	Sexy::Event unkEvent14; // off_1BCB188, Sexy::Event<bool>
	Sexy::Event m_winCond; // off_1BE0C10, with bool ret
	Sexy::Event unkEvent16; // off_1BE0C38
	Sexy::Event unkEvent17; // off_1BE0C60, Sexy::Event<RenderQueue*>
	Sexy::Event unkEvent18; // same as 17
	int unk2;

	LevelModule* getModule(Sexy::RtClass* rtClass);
};

static_assert(sizeof(LevelModuleManager) == 0x168);
static_assert(offsetof(LevelModuleManager, unkEvent12) == 0xF4);