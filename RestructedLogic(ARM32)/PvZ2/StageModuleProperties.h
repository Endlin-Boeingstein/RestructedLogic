#pragma once
#include "LevelModuleProperties.h"

#define STAGEMODULEPROPS_VFUNCS 18
//寻找该偏移方法：
//HEX搜索文本StageModuleProperties
//然后比如你跳转到了诸如"21StageModuleProperties.........23MiniGameMusicEnableList"字样时候
//把鼠标单击StageModuleProperties的"S"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B96710; `typeinfo name for'StageModuleProperties
//.rodata:01B96710 32 31 53 74 61 67 65 4D 6F 64 + _ZTS21StageModuleProperties DCB "21StageModuleProperties", 0
//.rodata : 01B96710 75 6C 65 50 72 6F 70 65 72 74 + ; DATA XREF : .data.rel.ro : 01C7188C↓o
//.rodata : 01B96710 69 65 73 00; type descriptor name

//双击示例中的DATA XREF: .data.rel.ro:01C7188C↓o位置
//跳转到虚表地址，向上翻动，整体如下：
//.data.rel.ro:01C71838; `vtable for'StageModuleProperties
//.data.rel.ro:01C71838 00 00 00 00                   _ZTV21StageModuleProperties DCD 0; DATA XREF : sub_31DCB8 + 14↑o
//.data.rel.ro : 01C71838; sub_31E080 + 70↑o
//.data.rel.ro:01C71838;.got:off_1D241AC↓o
//.data.rel.ro : 01C71838; offset to this
//.data.rel.ro:01C7183C 88 18 C7 01                   DCD _ZTI21StageModuleProperties; `typeinfo for'StageModuleProperties
//.data.rel.ro:01C71840 94 F9 4A 00                   DCD sub_4AF994
//.data.rel.ro : 01C71844 84 FE 4A 00                   DCD sub_4AFE84
//.data.rel.ro : 01C71848 B8 DC 31 00                   DCD sub_31DCB8
//.data.rel.ro : 01C7184C 58 4F 4B 00                   DCD sub_4B4F58
//.data.rel.ro : 01C71850 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C71854 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C71858 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01C7185C 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01C71860 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01C71864 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01C71868 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01C7186C 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01C71870 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01C71874 00 0D 4B 00                   DCD sub_4B0D00
//.data.rel.ro : 01C71878 6C 4F 4B 00                   DCD sub_4B4F6C
//.data.rel.ro : 01C7187C 84 4F 29 00                   DCD sub_294F84
//.data.rel.ro : 01C71880 B4 4F 29 00                   DCD sub_294FB4
//.data.rel.ro : 01C71884 94 20 DF 00                   DCD sub_DF2094
//.data.rel.ro : 01C71888; public StageModuleProperties :
//.data.rel.ro : 01C71888;   public /* offset 0x0 */ LevelModuleProperties :
//.data.rel.ro : 01C71888;     public /* offset 0x0 */ PropertySheetBase :
//.data.rel.ro : 01C71888;       public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01C71888;         public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C71888; `typeinfo for'StageModuleProperties
//.data.rel.ro:01C71888 D8 74 DF 01                   _ZTI21StageModuleProperties DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C71888; DATA XREF : .data.rel.ro : 01C63110↑o
//.data.rel.ro : 01C71888;.data.rel.ro:01C63C84↑o
//.data.rel.ro : 01C71888;.data.rel.ro:01C7183C↑o
//.data.rel.ro : 01C71888;.data.rel.ro:01C73B74↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01C79BD4↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01C7FC54↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01C84BC4↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CB00CC↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CE52D4↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CE627C↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CEA504↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CF1904↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01CFB0D8↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01D073D4↓o
//.data.rel.ro : 01C71888;.data.rel.ro:01D075F0↓o ...
//.data.rel.ro : 01C71888; reference to RTTI's type class
//.data.rel.ro:01C7188C 10 67 B9 01                   DCD _ZTS21StageModuleProperties; reference to type's name
//.data.rel.ro:01C71890 B8 07 CF 01                   DCD _ZTI21LevelModuleProperties; reference to parent's type name

//其中最右上角的引用偏移处
//DATA XREF: sub_31DCB8+14↑o的sub_31DCB8为STAGEMODULEPROPS_CONSTRUCT_ADDR
#define STAGEMODULEPROPS_CONSTRUCT_ADDR StageModuleProperties_STAGEMODULEPROPS_CONSTRUCT_ADDRAddr
//接下来如下：
//.data.rel.ro:01C7183C 88 18 C7 01                   DCD _ZTI21StageModuleProperties; `typeinfo for'StageModuleProperties
//.data.rel.ro:01C71840 94 F9 4A 00                   DCD sub_4AF994

//其中.data.rel.ro:01C71840的01C71840为STAGEMODULEPROPS_VTBL
#define STAGEMODULEPROPS_VTBL StageModuleProperties_STAGEMODULEPROPS_VTBLAddr
//双击示例中的DCD sub_4AF994位置
//跳转后如下：
//.text:004AF994
//.text : 004AF994; ============== = S U B R O U T I N E ====================================== =
//.text:004AF994
//.text : 004AF994; Attributes: thunk
//.text : 004AF994
//.text : 004AF994                               sub_4AF994; DATA XREF : .data.rel.ro : 01C71840↓o
//.text : 004AF994; __unwind{
//.text:004AF994 E1 FF FF EA                   B               sub_4AF920
//.text : 004AF994; } // starts at 4AF994
//.text:004AF994
//.text : 004AF994; End of function sub_4AF994
//.text:004AF994
//.text : 004AF998

//其中sub_4AF920为STAGEMODULEPROPS_GETCLASS_ADDR
#define STAGEMODULEPROPS_GETCLASS_ADDR StageModuleProperties_STAGEMODULEPROPS_GETCLASS_ADDRAddr


class StageModuleProperties : public LevelModuleProperties
{
public:
	char pad0048[4];
	Sexy::SexyString BackgroundResourceGroup;
	Sexy::SexyString BackgroundImagePrefix;
	Sexy::SexyString StagePrefix;
	Sexy::SexyString BasicZombieTypeName;
	Sexy::SexyString FlagZombieTypeName;
	std::vector<Sexy::SexyString> FlagVeteranZombieTypenames;
	Sexy::SexyString Armor1ZombieTypeName;
	Sexy::SexyString Armor2ZombieTypeName;
	Sexy::SexyString Armor4ZombieTypeName;
	Sexy::SexyString MusicSuffix;
	Sexy::SexyString MusicSuffixMinigame;
	Sexy::SexyString AmbientAudioSuffix;
	Sexy::SexyString RailcartDefaultTypeName;
	Sexy::SexyString GravestoneDefaultTypeName;
	Sexy::SexyString DirtSpawnEffectName;
	Sexy::SexyString ZombieEventAudio;
	Sexy::SexyString LevelPowerupSet;
	std::vector<Sexy::Point> DisabledStreetCells;
	Sexy::SexyString ProgressFlagAsset;
	Sexy::SexyString StarChallengeUnlockLevel;
};

static_assert(sizeof(StageModuleProperties) == 0x13C);
static_assert(offsetof(StageModuleProperties, RailcartDefaultTypeName) == 0xDC);