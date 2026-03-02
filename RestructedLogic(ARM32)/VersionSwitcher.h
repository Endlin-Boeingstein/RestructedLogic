#include <map>
#include <string>

#ifndef __arm__

#error "This sub-project is only for ARM architecture."

#endif

static constexpr size_t UNKNOWN = 0;
#define GAME_VERSION 1031
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
constexpr size_t LawnAppScreenWidthHeightAddr = 0x5A1454;
constexpr size_t BoardZoomAddr = 0x6E467C;
constexpr size_t BoardZoom2Addr = 0x6E4910;
constexpr int firstFreePlantID = UNKNOWN;

#endif

#if GAME_VERSION == 941

constexpr size_t PlantNameMapperAddr = 0xD994B8;
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

constexpr size_t PlantNameMapperAddr = 0xDA5C58;
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

constexpr size_t PlantNameMapperAddr = 0xDFC008;
constexpr size_t PrimeGlyphCacheAddr = 0x13FBA38;
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

/* MeteorFlower：为什么写了这么多版本但很多没找偏移？因为这是历史遗留问题。以前就 9.4 9.6 9.8
这三个版本外国友人找偏移找的最多。所以一开始 RestructedLogic
就写了这三个版本。后来幽幽子找我做高视角（虽然 Edgest 现在是不用我做的 so 了。当年因为到处传搞 so
修改有风险，所以为了保密我让他别写我名字，但实际上如果你能找到老 Edgest
的安装包，那里面还能逆向出来我在里面留的防盗标记。），当年他还没找到外国友人给他整外包 so
修改，用的还是 10.3。就这样 10.3 也成了 RL 的常驻版本之一。但是后来发现 BB2
搞的原始工程能用的东西太少了。虽然 EB 是还留着那堆无效代码，但我做 Lite
的时候就给删了。所以本来是有效偏移最全的那三个版本反而被删光了。后来 EB 自己做新功能的时候（是的，RL
真正的有效代码除了框架已经几乎没有外国友人的代码了。），由于 end(exd) 用的也是 10.3。EB 就在 10.3
上面分析了，所以 10.3 偏移找的最全。但我为什么仍然称 RL 是一个 "multi-version"
的工程。是因为其他工程的偏移基本全是在 main
函数里面写个常量完事了。你要是想给自己版本做适配你就慢慢改去吧。只有 RL
提供了一个最有前景的多版本适配框架（当然现在的 RL 的版本适配框架基本都是我写的。EB
是提出了这个概念，但他写的巨不优雅。）至于 8.7.3 是我自己锁 A
包用的版本。如果您也找了其他版本的偏移，希望您向我们发一下 pr 或者用其他方式告知我们偏移。*/
