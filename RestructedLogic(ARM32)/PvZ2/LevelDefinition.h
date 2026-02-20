#pragma once
#include "PropertySheetBase.h"
#include "StageModuleProperties.h"
#include "LevelModule.h"

class LevelDefinition : public PropertySheetBase
{
public:
	Sexy::SexyString Name;
	Sexy::SexyString Description;
	Sexy::SexyString MainObjective;
	int16_t StartingSun;
	bool AddBonusStartingSun;
	bool SuppressSunSpawn;
	int LevelNumber;
	int FlickPowerupRightEdgeOFffset;
	int unk;
	Sexy::RtWeakPtr<StageModuleProperties> StageModuleProps;
	Sexy::RtWeakPtr<void> VictoryModuleProps;
	Sexy::RtWeakPtr<void> LossModuleProps;
	Sexy::RtWeakPtr<void> LevelMutatorModuleProps;
	std::vector<LevelModule> Modules;
	int unk2;
	Sexy::RtWeakPtr<void> Loot;
	Sexy::SexyString NormalPresentTable;
	Sexy::SexyString ShinyPresentTable;
	bool SuppressAwardScreen;
	int FirstRewardType;
	Sexy::SexyString FirstRewardParam;
	int ReplayRewardType;
	Sexy::SexyString replayRewardParam;
	bool GameOverDialogShowBrain;
	Sexy::SexyString FirstIntroNarrative;
	Sexy::SexyString ReplayIntroNarrative;
	Sexy::SexyString FirstOutroNarrative;
	Sexy::SexyString ReplayOutroNarrative;
	Sexy::SexyString ForceNextLevel;
	bool ForceWarpTunnel;
	bool ForceToWorldMap;
	bool RepeatPlayForceToWorldMap;
	bool IsVasebreaker;
	bool IsDangerRoom;
	bool IsLevelOfTheDay;
	bool DisableRestart;
	Sexy::SexyString CompletionAchievement;
	std::vector<int> GameFeaturesToUnlock; // vector<GameFeature>
	Sexy::SexyString MusicType;
	Sexy::SexyString DraperPromo;
	Sexy::SexyString LevelPowerupSet;
	Sexy::SexyString LevelJam;
	bool DoMusicChanges;
	std::vector<Sexy::SexyString> ResourceGroupNames;
	std::vector<Sexy::SexyString> LevelPrerequisites;
	std::vector<Sexy::SexyString> GroupsToUnloadForAds;
	std::vector<Sexy::SexyString> RandomLevelSet;
	bool LoadDefaultMusic;
	bool SuppressDynamicTutorial;
	int ZombieLevel;
	int GridItemLevel;
	int FixedPlantLevel;
	bool SuppressPlantfoodPurchase;
	char SuppressAccountUpgrades[2]; // it's actually a wide, but I need this to allow non-alignment
	bool DisablePlantBoosts;
	bool DisableSaveGame;
	bool pad19D[2];
	char GeneratorResults[192]; // this is its own object
	std::vector<Sexy::SexyString> PerksDisabledInLevel;
	std::vector<std::vector<Sexy::SexyString>> PerksDisabledPerDifficulty;
};

static_assert(sizeof(LevelDefinition) == 0x278);
static_assert(offsetof(LevelDefinition, FirstRewardType) == 0xA4);
static_assert(offsetof(LevelDefinition, StartingSun) == 0x40);
static_assert(offsetof(LevelDefinition, AddBonusStartingSun) == 0x42);
static_assert(offsetof(LevelDefinition, ForceNextLevel) == 0xF8);
static_assert(offsetof(LevelDefinition, GameFeaturesToUnlock) == 0x118);
static_assert(offsetof(LevelDefinition, DoMusicChanges) == 0x154);
static_assert(offsetof(LevelDefinition, SuppressAccountUpgrades) == 0x199);