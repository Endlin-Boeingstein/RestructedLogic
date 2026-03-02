#include <map>
#include <string>

#ifndef __aarch64__

#error "This sub-project is only for ARM64 architecture."

#endif

static constexpr size_t UNKNOWN = 0;
#define GAME_VERSION 873
// 填入版本号，为去掉小数点的版本号
// UNKNOWN 表示暂时未知

#if GAME_VERSION == 873

constexpr size_t PlantNameMapperAddr = UNKNOWN;
constexpr size_t PrimeGlyphCacheAddr = UNKNOWN;
constexpr size_t RSBPathRecorderAddr = UNKNOWN;
constexpr size_t ResourceManagerFuncAddr = UNKNOWN;
constexpr size_t CDNLoadAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Simple = UNKNOWN;
constexpr size_t LogOutputFuncAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Struct = UNKNOWN;
constexpr size_t LogOutputFuncAddr_v2 = UNKNOWN;
constexpr size_t LawnAppScreenWidthHeightAddr = 0x8DDA28;
constexpr size_t BoardZoomAddr = 0xA331D4;
constexpr size_t BoardZoom2Addr = 0xA33434;
constexpr int firstFreePlantID = UNKNOWN;

#endif

#if GAME_VERSION == 941

constexpr size_t PlantNameMapperAddr = UNKNOWN;
constexpr size_t PrimeGlyphCacheAddr = UNKNOWN;
constexpr size_t RSBPathRecorderAddr = UNKNOWN;
constexpr size_t ResourceManagerFuncAddr = UNKNOWN;
constexpr size_t CDNLoadAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Simple = UNKNOWN;
constexpr size_t LogOutputFuncAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Struct = UNKNOWN;
constexpr size_t LogOutputFuncAddr_v2 = UNKNOWN;
constexpr size_t LawnAppScreenWidthHeightAddr = UNKNOWN;
constexpr size_t BoardZoomAddr = UNKNOWN;
constexpr size_t BoardZoom2Addr = UNKNOWN;
constexpr int firstFreePlantID = 185;

#endif

#if GAME_VERSION == 961

constexpr size_t PlantNameMapperAddr = UNKNOWN;
constexpr size_t PrimeGlyphCacheAddr = UNKNOWN;
constexpr size_t RSBPathRecorderAddr = UNKNOWN;
constexpr size_t ResourceManagerFuncAddr = UNKNOWN;
constexpr size_t CDNLoadAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Simple = UNKNOWN;
constexpr size_t LogOutputFuncAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Struct = UNKNOWN;
constexpr size_t LogOutputFuncAddr_v2 = UNKNOWN;
constexpr size_t LawnAppScreenWidthHeightAddr = UNKNOWN;
constexpr size_t BoardZoomAddr = UNKNOWN;
constexpr size_t BoardZoom2Addr = UNKNOWN;
constexpr int firstFreePlantID = 188;

#endif

#if GAME_VERSION == 981

constexpr size_t PlantNameMapperAddr = UNKNOWN;
constexpr size_t PrimeGlyphCacheAddr = UNKNOWN;
constexpr size_t RSBPathRecorderAddr = UNKNOWN;
constexpr size_t ResourceManagerFuncAddr = UNKNOWN;
constexpr size_t CDNLoadAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Simple = UNKNOWN;
constexpr size_t LogOutputFuncAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Struct = UNKNOWN;
constexpr size_t LogOutputFuncAddr_v2 = UNKNOWN;
constexpr size_t LawnAppScreenWidthHeightAddr = UNKNOWN;
constexpr size_t BoardZoomAddr = UNKNOWN;
constexpr size_t BoardZoom2Addr = UNKNOWN;
constexpr int firstFreePlantID = 191;

#endif

#if GAME_VERSION == 1031

constexpr size_t PlantNameMapperAddr = UNKNOWN;
constexpr size_t PrimeGlyphCacheAddr = UNKNOWN;
constexpr size_t RSBPathRecorderAddr = UNKNOWN;
constexpr size_t ResourceManagerFuncAddr = UNKNOWN;
constexpr size_t CDNLoadAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Simple = UNKNOWN;
constexpr size_t LogOutputFuncAddr = UNKNOWN;
constexpr size_t LogOutputFuncAddr_Struct = UNKNOWN;
constexpr size_t LogOutputFuncAddr_v2 = UNKNOWN;
constexpr size_t LawnAppScreenWidthHeightAddr = UNKNOWN;
constexpr size_t BoardZoomAddr = UNKNOWN;
constexpr size_t BoardZoom2Addr = UNKNOWN;
constexpr int firstFreePlantID = UNKNOWN;  // 10.3 不需要

#endif

// 在此仿照如上格式再续写所需版本号偏移分类

// 各版本 RtonTableID
std::map<std::string, int> rtonTableIDs;

void rtonTableIDsLoader() {
#if GAME_VERSION == 941

  rtonTableIDs["ScratchSpace.rton"] = UNKNOWN;
  rtonTableIDs["UknRton.rton"] = UNKNOWN;
  rtonTableIDs["Version.rton"] = UNKNOWN;
  rtonTableIDs["Manifest.rton"] = UNKNOWN;
  rtonTableIDs["CDNConfig.rton"] = UNKNOWN;
  rtonTableIDs["ForceUpdateConfig.rton"] = UNKNOWN;
  rtonTableIDs["LiveConfig.rton"] = UNKNOWN;
  rtonTableIDs["StartupConfig.rton"] = UNKNOWN;
  rtonTableIDs["NewMapConversionMapping.rton"] = UNKNOWN;
  rtonTableIDs["OldMapDataMapping.rton"] = UNKNOWN;
  rtonTableIDs["PropertySheets.rton"] = UNKNOWN;
  rtonTableIDs["PersonalConfig.rton"] = UNKNOWN;
  rtonTableIDs["PinataTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantLevels.rton"] = UNKNOWN;
  rtonTableIDs["PlantMastery.rton"] = UNKNOWN;
  rtonTableIDs["PlantPowerUps.rton"] = UNKNOWN;
  rtonTableIDs["PlantAlmanacData.rton"] = UNKNOWN;
  rtonTableIDs["PlantProperties.rton"] = UNKNOWN;
  rtonTableIDs["Powers.rton"] = UNKNOWN;
  rtonTableIDs["ZombieTypes.rton"] = UNKNOWN;
  rtonTableIDs["ZombieActions.rton"] = UNKNOWN;
  rtonTableIDs["ZombieProperties.rton"] = UNKNOWN;
  rtonTableIDs["CreatureTypes.rton"] = UNKNOWN;
  rtonTableIDs["ProjectileTypes.rton"] = UNKNOWN;
  rtonTableIDs["GridItemTypes.rton"] = UNKNOWN;
  rtonTableIDs["EffectObjectTypes.rton"] = UNKNOWN;
  rtonTableIDs["CollectableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantFamilyTypes.rton"] = UNKNOWN;
  rtonTableIDs["Quests.rton"] = UNKNOWN;
  rtonTableIDs["QuestsCategories.rton"] = UNKNOWN;
  rtonTableIDs["LoadingText.rton"] = UNKNOWN;
  rtonTableIDs["QuestThemes.rton"] = UNKNOWN;
  rtonTableIDs["QuestsActive.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuests.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestData.rton"] = UNKNOWN;
  rtonTableIDs["UIWidgetSheets.rton"] = UNKNOWN;
  rtonTableIDs["NPCDataSheets.rton"] = UNKNOWN;
  rtonTableIDs["LevelModules.rton"] = UNKNOWN;
  rtonTableIDs["HeroTypes.rton"] = UNKNOWN;
  rtonTableIDs["PowerupTypes.rton"] = UNKNOWN;
  rtonTableIDs["GameFeatures.rton"] = UNKNOWN;
  rtonTableIDs["ToolPackets.rton"] = UNKNOWN;
  rtonTableIDs["StreamingMusic.rton"] = UNKNOWN;
  rtonTableIDs["Products.rton"] = UNKNOWN;
  rtonTableIDs["MarketLayout.rton"] = UNKNOWN;
  rtonTableIDs["MarketSchedule.rton"] = UNKNOWN;
  rtonTableIDs["RAPSchedule.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestSchedule.rton"] = UNKNOWN;
  rtonTableIDs["PlayerSegments.rton"] = UNKNOWN;
  rtonTableIDs["BoardGridMaps.rton"] = UNKNOWN;
  rtonTableIDs["LevelModulesDifficulty.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorModules.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorTables.rton"] = UNKNOWN;

#endif

#if GAME_VERSION == 961

  rtonTableIDs["ScratchSpace.rton"] = UNKNOWN;
  rtonTableIDs["UknRton.rton"] = UNKNOWN;
  rtonTableIDs["Version.rton"] = UNKNOWN;
  rtonTableIDs["Manifest.rton"] = UNKNOWN;
  rtonTableIDs["CDNConfig.rton"] = UNKNOWN;
  rtonTableIDs["ForceUpdateConfig.rton"] = UNKNOWN;
  rtonTableIDs["LiveConfig.rton"] = UNKNOWN;
  rtonTableIDs["StartupConfig.rton"] = UNKNOWN;
  rtonTableIDs["NewMapConversionMapping.rton"] = UNKNOWN;
  rtonTableIDs["OldMapDataMapping.rton"] = UNKNOWN;
  rtonTableIDs["PropertySheets.rton"] = UNKNOWN;
  rtonTableIDs["PersonalConfig.rton"] = UNKNOWN;
  rtonTableIDs["PinataTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantLevels.rton"] = UNKNOWN;
  rtonTableIDs["PlantMastery.rton"] = UNKNOWN;
  rtonTableIDs["PlantPowerUps.rton"] = UNKNOWN;
  rtonTableIDs["PlantAlmanacData.rton"] = UNKNOWN;
  rtonTableIDs["PlantProperties.rton"] = UNKNOWN;
  rtonTableIDs["Powers.rton"] = UNKNOWN;
  rtonTableIDs["ZombieTypes.rton"] = UNKNOWN;
  rtonTableIDs["ZombieActions.rton"] = UNKNOWN;
  rtonTableIDs["ZombieProperties.rton"] = UNKNOWN;
  rtonTableIDs["CreatureTypes.rton"] = UNKNOWN;
  rtonTableIDs["ProjectileTypes.rton"] = UNKNOWN;
  rtonTableIDs["GridItemTypes.rton"] = UNKNOWN;
  rtonTableIDs["EffectObjectTypes.rton"] = UNKNOWN;
  rtonTableIDs["CollectableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantFamilyTypes.rton"] = UNKNOWN;
  rtonTableIDs["Quests.rton"] = UNKNOWN;
  rtonTableIDs["QuestsCategories.rton"] = UNKNOWN;
  rtonTableIDs["LoadingText.rton"] = UNKNOWN;
  rtonTableIDs["QuestThemes.rton"] = UNKNOWN;
  rtonTableIDs["QuestsActive.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuests.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestData.rton"] = UNKNOWN;
  rtonTableIDs["UIWidgetSheets.rton"] = UNKNOWN;
  rtonTableIDs["NPCDataSheets.rton"] = UNKNOWN;
  rtonTableIDs["LevelModules.rton"] = UNKNOWN;
  rtonTableIDs["HeroTypes.rton"] = UNKNOWN;
  rtonTableIDs["PowerupTypes.rton"] = UNKNOWN;
  rtonTableIDs["GameFeatures.rton"] = UNKNOWN;
  rtonTableIDs["ToolPackets.rton"] = UNKNOWN;
  rtonTableIDs["StreamingMusic.rton"] = UNKNOWN;
  rtonTableIDs["Products.rton"] = UNKNOWN;
  rtonTableIDs["MarketLayout.rton"] = UNKNOWN;
  rtonTableIDs["MarketSchedule.rton"] = UNKNOWN;
  rtonTableIDs["RAPSchedule.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestSchedule.rton"] = UNKNOWN;
  rtonTableIDs["PlayerSegments.rton"] = UNKNOWN;
  rtonTableIDs["BoardGridMaps.rton"] = UNKNOWN;
  rtonTableIDs["LevelModulesDifficulty.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorModules.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorTables.rton"] = UNKNOWN;

#endif

#if GAME_VERSION == 981

  rtonTableIDs["ScratchSpace.rton"] = UNKNOWN;
  rtonTableIDs["UknRton.rton"] = UNKNOWN;
  rtonTableIDs["Version.rton"] = UNKNOWN;
  rtonTableIDs["Manifest.rton"] = UNKNOWN;
  rtonTableIDs["CDNConfig.rton"] = UNKNOWN;
  rtonTableIDs["ForceUpdateConfig.rton"] = UNKNOWN;
  rtonTableIDs["LiveConfig.rton"] = UNKNOWN;
  rtonTableIDs["StartupConfig.rton"] = UNKNOWN;
  rtonTableIDs["NewMapConversionMapping.rton"] = UNKNOWN;
  rtonTableIDs["OldMapDataMapping.rton"] = UNKNOWN;
  rtonTableIDs["PropertySheets.rton"] = UNKNOWN;
  rtonTableIDs["PersonalConfig.rton"] = UNKNOWN;
  rtonTableIDs["PinataTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantLevels.rton"] = UNKNOWN;
  rtonTableIDs["PlantMastery.rton"] = UNKNOWN;
  rtonTableIDs["PlantPowerUps.rton"] = UNKNOWN;
  rtonTableIDs["PlantAlmanacData.rton"] = UNKNOWN;
  rtonTableIDs["PlantProperties.rton"] = UNKNOWN;
  rtonTableIDs["Powers.rton"] = UNKNOWN;
  rtonTableIDs["ZombieTypes.rton"] = UNKNOWN;
  rtonTableIDs["ZombieActions.rton"] = UNKNOWN;
  rtonTableIDs["ZombieProperties.rton"] = UNKNOWN;
  rtonTableIDs["CreatureTypes.rton"] = UNKNOWN;
  rtonTableIDs["ProjectileTypes.rton"] = UNKNOWN;
  rtonTableIDs["GridItemTypes.rton"] = UNKNOWN;
  rtonTableIDs["EffectObjectTypes.rton"] = UNKNOWN;
  rtonTableIDs["CollectableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTableTypes.rton"] = UNKNOWN;
  rtonTableIDs["PresentTypes.rton"] = UNKNOWN;
  rtonTableIDs["PlantFamilyTypes.rton"] = UNKNOWN;
  rtonTableIDs["Quests.rton"] = UNKNOWN;
  rtonTableIDs["QuestsCategories.rton"] = UNKNOWN;
  rtonTableIDs["LoadingText.rton"] = UNKNOWN;
  rtonTableIDs["QuestThemes.rton"] = UNKNOWN;
  rtonTableIDs["QuestsActive.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuests.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestData.rton"] = UNKNOWN;
  rtonTableIDs["UIWidgetSheets.rton"] = UNKNOWN;
  rtonTableIDs["NPCDataSheets.rton"] = UNKNOWN;
  rtonTableIDs["LevelModules.rton"] = UNKNOWN;
  rtonTableIDs["HeroTypes.rton"] = UNKNOWN;
  rtonTableIDs["PowerupTypes.rton"] = UNKNOWN;
  rtonTableIDs["GameFeatures.rton"] = UNKNOWN;
  rtonTableIDs["ToolPackets.rton"] = UNKNOWN;
  rtonTableIDs["StreamingMusic.rton"] = UNKNOWN;
  rtonTableIDs["Products.rton"] = UNKNOWN;
  rtonTableIDs["MarketLayout.rton"] = UNKNOWN;
  rtonTableIDs["MarketSchedule.rton"] = UNKNOWN;
  rtonTableIDs["RAPSchedule.rton"] = UNKNOWN;
  rtonTableIDs["DailyQuestSchedule.rton"] = UNKNOWN;
  rtonTableIDs["PlayerSegments.rton"] = UNKNOWN;
  rtonTableIDs["BoardGridMaps.rton"] = UNKNOWN;
  rtonTableIDs["LevelModulesDifficulty.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorModules.rton"] = UNKNOWN;
  rtonTableIDs["LevelMutatorTables.rton"] = UNKNOWN;

#endif

#if GAME_VERSION == 1031

  rtonTableIDs["ScratchSpace.rton"] = 0;
  rtonTableIDs["UknRton.rton"] = 1;
  rtonTableIDs["Version.rton"] = 2;
  rtonTableIDs["Manifest.rton"] = 3;
  rtonTableIDs["CDNConfig.rton"] = 4;
  rtonTableIDs["ForceUpdateConfig.rton"] = 5;
  rtonTableIDs["LiveConfig.rton"] = 6;
  rtonTableIDs["StartupConfig.rton"] = 7;
  rtonTableIDs["NewMapConversionMapping.rton"] = 8;
  rtonTableIDs["OldMapDataMapping.rton"] = 9;
  rtonTableIDs["PropertySheets.rton"] = 10;
  rtonTableIDs["PersonalConfig.rton"] = 11;
  rtonTableIDs["PinataTypes.rton"] = 12;
  rtonTableIDs["PlantTypes.rton"] = 13;
  rtonTableIDs["PlantLevels.rton"] = 14;
  rtonTableIDs["PlantMastery.rton"] = 15;
  rtonTableIDs["PlantPowerUps.rton"] = 16;
  rtonTableIDs["PlantAlmanacData.rton"] = 17;
  rtonTableIDs["PlantProperties.rton"] = 18;
  rtonTableIDs["Powers.rton"] = 19;
  rtonTableIDs["ZombieTypes.rton"] = 20;
  rtonTableIDs["ZombieActions.rton"] = 21;
  rtonTableIDs["ZombieProperties.rton"] = 22;
  rtonTableIDs["CreatureTypes.rton"] = 23;
  rtonTableIDs["ProjectileTypes.rton"] = 24;
  rtonTableIDs["GridItemTypes.rton"] = 25;
  rtonTableIDs["EffectObjectTypes.rton"] = 26;
  rtonTableIDs["CollectableTypes.rton"] = 27;
  rtonTableIDs["PresentTableTypes.rton"] = 28;
  rtonTableIDs["PresentTypes.rton"] = 29;
  rtonTableIDs["PlantFamilyTypes.rton"] = 30;
  rtonTableIDs["Quests.rton"] = 31;
  rtonTableIDs["QuestsCategories.rton"] = 32;
  rtonTableIDs["LoadingText.rton"] = 33;
  rtonTableIDs["QuestThemes.rton"] = 34;
  rtonTableIDs["QuestsActive.rton"] = 35;
  rtonTableIDs["DailyQuests.rton"] = 36;
  rtonTableIDs["DailyQuestData.rton"] = 37;
  rtonTableIDs["UIWidgetSheets.rton"] = 38;
  rtonTableIDs["NPCDataSheets.rton"] = 39;
  rtonTableIDs["LevelModules.rton"] = 40;
  rtonTableIDs["HeroTypes.rton"] = 41;
  rtonTableIDs["PowerupTypes.rton"] = 42;
  rtonTableIDs["GameFeatures.rton"] = 43;
  rtonTableIDs["ToolPackets.rton"] = 44;
  rtonTableIDs["StreamingMusic.rton"] = 45;
  rtonTableIDs["Products.rton"] = 46;
  rtonTableIDs["MarketLayout.rton"] = 47;
  rtonTableIDs["MarketSchedule.rton"] = 48;
  rtonTableIDs["RAPSchedule.rton"] = 49;
  rtonTableIDs["DailyQuestSchedule.rton"] = 50;
  rtonTableIDs["PlayerSegments.rton"] = 51;
  rtonTableIDs["BoardGridMaps.rton"] = 52;
  rtonTableIDs["LevelModulesDifficulty.rton"] = 53;
  rtonTableIDs["LevelMutatorModules.rton"] = 54;
  rtonTableIDs["LevelMutatorTables.rton"] = 55;
#endif

  // 在此仿照如上格式再续写所需 RtonTableID
}
