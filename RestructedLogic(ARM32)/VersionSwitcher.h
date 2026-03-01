#include <map>
#include <string>

#define GAME_VERSION 1031
// 填入版本号，为去掉小数点的版本号
// NULL 表示暂未知偏移。

#if GAME_VERSION == 941

constexpr size_t PlantNameMapperAddr = 0xD994B8;
constexpr size_t PrimeGlyphCacheAddr = NULL;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 185;

#endif

#if GAME_VERSION == 961

constexpr size_t PlantNameMapperAddr = 0xDA5C58;
constexpr size_t PrimeGlyphCacheAddr = NULL;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 188;

#endif

#if GAME_VERSION == 981

constexpr size_t PlantNameMapperAddr = 0xDFC008;
constexpr size_t PrimeGlyphCacheAddr = 0x13FBA38;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 191;

#endif

#if GAME_VERSION == 1031

constexpr size_t PlantNameMapperAddr = NULL;
constexpr size_t PrimeGlyphCacheAddr = 0x177ECF4;
constexpr size_t RSBPathRecorderAddr = 0x16431A8;
constexpr size_t ResourceManagerFuncAddr = 0x6EE218;
constexpr size_t CDNLoadAddr = 0x876CB0;
constexpr size_t LogOutputFuncAddr_Simple = 0x146E160;
constexpr size_t LogOutputFuncAddr = 0x146DE24;
constexpr size_t LogOutputFuncAddr_Struct = 0x146DFE4;
constexpr size_t LogOutputFuncAddr_v2 = 0x146E028;
constexpr size_t LawnAppScreenWidthHeightAddr = 0x6E4030;
constexpr size_t BoardZoomAddr = 0x88D3EC;
constexpr size_t BoardZoom2Addr = 0x88D670;
constexpr int firstFreePlantID = 0;  // 10.3 不需要

#endif

// 在此仿照如上格式再续写所需版本号偏移分类

// 各版本 RtonTableID
std::map<std::string, int> rtonTableIDs;

bool rtonTableIDsLoader() {
#if GAME_VERSION == 941
  rtonTableIDs["ScratchSpace.rton"] = 999;
  rtonTableIDs["UknRton.rton"] = 999;
  rtonTableIDs["Version.rton"] = 999;
  rtonTableIDs["Manifest.rton"] = 999;
  rtonTableIDs["CDNConfig.rton"] = 999;
  rtonTableIDs["ForceUpdateConfig.rton"] = 999;
  rtonTableIDs["LiveConfig.rton"] = 999;
  rtonTableIDs["StartupConfig.rton"] = 999;
  rtonTableIDs["NewMapConversionMapping.rton"] = 999;
  rtonTableIDs["OldMapDataMapping.rton"] = 999;
  rtonTableIDs["PropertySheets.rton"] = 999;
  rtonTableIDs["PersonalConfig.rton"] = 999;
  rtonTableIDs["PinataTypes.rton"] = 999;
  rtonTableIDs["PlantTypes.rton"] = 999;
  rtonTableIDs["PlantLevels.rton"] = 999;
  rtonTableIDs["PlantMastery.rton"] = 999;
  rtonTableIDs["PlantPowerUps.rton"] = 999;
  rtonTableIDs["PlantAlmanacData.rton"] = 999;
  rtonTableIDs["PlantProperties.rton"] = 999;
  rtonTableIDs["Powers.rton"] = 999;
  rtonTableIDs["ZombieTypes.rton"] = 999;
  rtonTableIDs["ZombieActions.rton"] = 999;
  rtonTableIDs["ZombieProperties.rton"] = 999;
  rtonTableIDs["CreatureTypes.rton"] = 999;
  rtonTableIDs["ProjectileTypes.rton"] = 999;
  rtonTableIDs["GridItemTypes.rton"] = 999;
  rtonTableIDs["EffectObjectTypes.rton"] = 999;
  rtonTableIDs["CollectableTypes.rton"] = 999;
  rtonTableIDs["PresentTableTypes.rton"] = 999;
  rtonTableIDs["PresentTypes.rton"] = 999;
  rtonTableIDs["PlantFamilyTypes.rton"] = 999;
  rtonTableIDs["Quests.rton"] = 999;
  rtonTableIDs["QuestsCategories.rton"] = 999;
  rtonTableIDs["LoadingText.rton"] = 999;
  rtonTableIDs["QuestThemes.rton"] = 999;
  rtonTableIDs["QuestsActive.rton"] = 999;
  rtonTableIDs["DailyQuests.rton"] = 999;
  rtonTableIDs["DailyQuestData.rton"] = 999;
  rtonTableIDs["UIWidgetSheets.rton"] = 999;
  rtonTableIDs["NPCDataSheets.rton"] = 999;
  rtonTableIDs["LevelModules.rton"] = 999;
  rtonTableIDs["HeroTypes.rton"] = 999;
  rtonTableIDs["PowerupTypes.rton"] = 999;
  rtonTableIDs["GameFeatures.rton"] = 999;
  rtonTableIDs["ToolPackets.rton"] = 999;
  rtonTableIDs["StreamingMusic.rton"] = 999;
  rtonTableIDs["Products.rton"] = 999;
  rtonTableIDs["MarketLayout.rton"] = 999;
  rtonTableIDs["MarketSchedule.rton"] = 999;
  rtonTableIDs["RAPSchedule.rton"] = 999;
  rtonTableIDs["DailyQuestSchedule.rton"] = 999;
  rtonTableIDs["PlayerSegments.rton"] = 999;
  rtonTableIDs["BoardGridMaps.rton"] = 999;
  rtonTableIDs["LevelModulesDifficulty.rton"] = 999;
  rtonTableIDs["LevelMutatorModules.rton"] = 999;
  rtonTableIDs["LevelMutatorTables.rton"] = 999;
  return 1;
#endif

#if GAME_VERSION == 961
  rtonTableIDs["ScratchSpace.rton"] = 999;
  rtonTableIDs["UknRton.rton"] = 999;
  rtonTableIDs["Version.rton"] = 999;
  rtonTableIDs["Manifest.rton"] = 999;
  rtonTableIDs["CDNConfig.rton"] = 999;
  rtonTableIDs["ForceUpdateConfig.rton"] = 999;
  rtonTableIDs["LiveConfig.rton"] = 999;
  rtonTableIDs["StartupConfig.rton"] = 999;
  rtonTableIDs["NewMapConversionMapping.rton"] = 999;
  rtonTableIDs["OldMapDataMapping.rton"] = 999;
  rtonTableIDs["PropertySheets.rton"] = 999;
  rtonTableIDs["PersonalConfig.rton"] = 999;
  rtonTableIDs["PinataTypes.rton"] = 999;
  rtonTableIDs["PlantTypes.rton"] = 999;
  rtonTableIDs["PlantLevels.rton"] = 999;
  rtonTableIDs["PlantMastery.rton"] = 999;
  rtonTableIDs["PlantPowerUps.rton"] = 999;
  rtonTableIDs["PlantAlmanacData.rton"] = 999;
  rtonTableIDs["PlantProperties.rton"] = 999;
  rtonTableIDs["Powers.rton"] = 999;
  rtonTableIDs["ZombieTypes.rton"] = 999;
  rtonTableIDs["ZombieActions.rton"] = 999;
  rtonTableIDs["ZombieProperties.rton"] = 999;
  rtonTableIDs["CreatureTypes.rton"] = 999;
  rtonTableIDs["ProjectileTypes.rton"] = 999;
  rtonTableIDs["GridItemTypes.rton"] = 999;
  rtonTableIDs["EffectObjectTypes.rton"] = 999;
  rtonTableIDs["CollectableTypes.rton"] = 999;
  rtonTableIDs["PresentTableTypes.rton"] = 999;
  rtonTableIDs["PresentTypes.rton"] = 999;
  rtonTableIDs["PlantFamilyTypes.rton"] = 999;
  rtonTableIDs["Quests.rton"] = 999;
  rtonTableIDs["QuestsCategories.rton"] = 999;
  rtonTableIDs["LoadingText.rton"] = 999;
  rtonTableIDs["QuestThemes.rton"] = 999;
  rtonTableIDs["QuestsActive.rton"] = 999;
  rtonTableIDs["DailyQuests.rton"] = 999;
  rtonTableIDs["DailyQuestData.rton"] = 999;
  rtonTableIDs["UIWidgetSheets.rton"] = 999;
  rtonTableIDs["NPCDataSheets.rton"] = 999;
  rtonTableIDs["LevelModules.rton"] = 999;
  rtonTableIDs["HeroTypes.rton"] = 999;
  rtonTableIDs["PowerupTypes.rton"] = 999;
  rtonTableIDs["GameFeatures.rton"] = 999;
  rtonTableIDs["ToolPackets.rton"] = 999;
  rtonTableIDs["StreamingMusic.rton"] = 999;
  rtonTableIDs["Products.rton"] = 999;
  rtonTableIDs["MarketLayout.rton"] = 999;
  rtonTableIDs["MarketSchedule.rton"] = 999;
  rtonTableIDs["RAPSchedule.rton"] = 999;
  rtonTableIDs["DailyQuestSchedule.rton"] = 999;
  rtonTableIDs["PlayerSegments.rton"] = 999;
  rtonTableIDs["BoardGridMaps.rton"] = 999;
  rtonTableIDs["LevelModulesDifficulty.rton"] = 999;
  rtonTableIDs["LevelMutatorModules.rton"] = 999;
  rtonTableIDs["LevelMutatorTables.rton"] = 999;
  return 1;
#endif

#if GAME_VERSION == 981
  rtonTableIDs["ScratchSpace.rton"] = 999;
  rtonTableIDs["UknRton.rton"] = 999;
  rtonTableIDs["Version.rton"] = 999;
  rtonTableIDs["Manifest.rton"] = 999;
  rtonTableIDs["CDNConfig.rton"] = 999;
  rtonTableIDs["ForceUpdateConfig.rton"] = 999;
  rtonTableIDs["LiveConfig.rton"] = 999;
  rtonTableIDs["StartupConfig.rton"] = 999;
  rtonTableIDs["NewMapConversionMapping.rton"] = 999;
  rtonTableIDs["OldMapDataMapping.rton"] = 999;
  rtonTableIDs["PropertySheets.rton"] = 999;
  rtonTableIDs["PersonalConfig.rton"] = 999;
  rtonTableIDs["PinataTypes.rton"] = 999;
  rtonTableIDs["PlantTypes.rton"] = 999;
  rtonTableIDs["PlantLevels.rton"] = 999;
  rtonTableIDs["PlantMastery.rton"] = 999;
  rtonTableIDs["PlantPowerUps.rton"] = 999;
  rtonTableIDs["PlantAlmanacData.rton"] = 999;
  rtonTableIDs["PlantProperties.rton"] = 999;
  rtonTableIDs["Powers.rton"] = 999;
  rtonTableIDs["ZombieTypes.rton"] = 999;
  rtonTableIDs["ZombieActions.rton"] = 999;
  rtonTableIDs["ZombieProperties.rton"] = 999;
  rtonTableIDs["CreatureTypes.rton"] = 999;
  rtonTableIDs["ProjectileTypes.rton"] = 999;
  rtonTableIDs["GridItemTypes.rton"] = 999;
  rtonTableIDs["EffectObjectTypes.rton"] = 999;
  rtonTableIDs["CollectableTypes.rton"] = 999;
  rtonTableIDs["PresentTableTypes.rton"] = 999;
  rtonTableIDs["PresentTypes.rton"] = 999;
  rtonTableIDs["PlantFamilyTypes.rton"] = 999;
  rtonTableIDs["Quests.rton"] = 999;
  rtonTableIDs["QuestsCategories.rton"] = 999;
  rtonTableIDs["LoadingText.rton"] = 999;
  rtonTableIDs["QuestThemes.rton"] = 999;
  rtonTableIDs["QuestsActive.rton"] = 999;
  rtonTableIDs["DailyQuests.rton"] = 999;
  rtonTableIDs["DailyQuestData.rton"] = 999;
  rtonTableIDs["UIWidgetSheets.rton"] = 999;
  rtonTableIDs["NPCDataSheets.rton"] = 999;
  rtonTableIDs["LevelModules.rton"] = 999;
  rtonTableIDs["HeroTypes.rton"] = 999;
  rtonTableIDs["PowerupTypes.rton"] = 999;
  rtonTableIDs["GameFeatures.rton"] = 999;
  rtonTableIDs["ToolPackets.rton"] = 999;
  rtonTableIDs["StreamingMusic.rton"] = 999;
  rtonTableIDs["Products.rton"] = 999;
  rtonTableIDs["MarketLayout.rton"] = 999;
  rtonTableIDs["MarketSchedule.rton"] = 999;
  rtonTableIDs["RAPSchedule.rton"] = 999;
  rtonTableIDs["DailyQuestSchedule.rton"] = 999;
  rtonTableIDs["PlayerSegments.rton"] = 999;
  rtonTableIDs["BoardGridMaps.rton"] = 999;
  rtonTableIDs["LevelModulesDifficulty.rton"] = 999;
  rtonTableIDs["LevelMutatorModules.rton"] = 999;
  rtonTableIDs["LevelMutatorTables.rton"] = 999;
  return 1;
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
  return 1;
#endif

  // 在此仿照如上格式再续写所需 RtonTableID

  return 0;
}