#pragma once
#include <map>
#include "VersionAddresses.h"

std::map<std::string, int> rtonTableIDs;
//警告：不同版本应该RTON编号不同，请自行寻找！！！！！
//你只需要在HEX搜索ui_layout
//单击ui_layout的"u"，看其偏移后使用ida pro跳转到对应的偏移地址
//然后观察周围的偏移引用地址，附近那些的几乎是一样的，随便选一个双击进入
//按F5后就可以看了
/*strcpy((char*)v1420 + 1, "CDN Config");
		LOBYTE(v1420[0]) = 20;
		v1409 = 20;
		strcpy(v1410, "cdn_config");
		memset(&v1471[1], 0, 16);
		v1471[0] = (int)off_21C1B24;
		sub_10CBCD8(&v1476, 4, &v1265, v1420, 0, 0, &v1409, v1471);*/
//如上所示，基本上这样为一组，有的会没有第二个小写的字符串
//然后sub_10CBCD8(&v1476, 4, &v1265, v1420, 0, 0, &v1409, v1471);这个函数的第二个参数即RTON编号

bool rtonTableIDsLoader() {
#if GAME_VERSION==940
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
#endif

#if GAME_VERSION==960
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
#endif

#if GAME_VERSION==980
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
#endif

#if GAME_VERSION==1030
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

//更多版本请自行填写
}
