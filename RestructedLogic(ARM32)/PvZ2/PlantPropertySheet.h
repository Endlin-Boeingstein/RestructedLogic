#pragma once
#include <map>
#include <vector>

#include "BoardEntity.h"
#include "Plant.h"
#include "PropertySheetBase.h"

#define PLANTPROPS_VFTABLE_FUNC_COUNT 14

//寻找该偏移方法：
//HEX搜索文本PlantPropertySheet
//然后比如你跳转到了诸如"18PlantPropertySheet............19PultProjectileProps"字样时候
//把鼠标单击PlantPropertySheet的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B8FDD0; `typeinfo name for'PlantPropertySheet
//.rodata:01B8FDD0 31 38 50 6C 61 6E 74 50 72 6F + _ZTS18PlantPropertySheet DCB "18PlantPropertySheet", 0
//.rodata : 01B8FDD0 70 65 72 74 79 53 68 65 65 74 + ; DATA XREF : .data.rel.ro : 01C5F73C↓o
//.rodata : 01B8FDD0 00; type descriptor name

//双击示例中的DATA XREF: .data.rel.ro:01C5F73C↓o位置
//跳转到该类虚表位置，向上翻动，所得如下：
//.data.rel.ro:01C5F6F8; `vtable for'PlantPropertySheet
//.data.rel.ro:01C5F6F8 00 00 00 00                   _ZTV18PlantPropertySheet DCD 0; DATA XREF : sub_2B17D4 + 14↑o
//.data.rel.ro : 01C5F6F8; sub_2B17D4 + 24↑o
//.data.rel.ro:01C5F6F8;.text:off_2B19C8↑o
//.data.rel.ro : 01C5F6F8; sub_2C2B1C + C↑o
//.data.rel.ro:01C5F6F8; sub_2C2B1C + 10↑o
//.data.rel.ro:01C5F6F8;.text:off_2C2BE8↑o
//.data.rel.ro : 01C5F6F8; offset to this
//.data.rel.ro:01C5F6FC 38 F7 C5 01                   DCD _ZTI18PlantPropertySheet; `typeinfo for'PlantPropertySheet
//.data.rel.ro:01C5F700 BC FF 2A 00                   DCD sub_2AFFBC
//.data.rel.ro : 01C5F704 D0 19 2B 00                   DCD sub_2B19D0
//.data.rel.ro : 01C5F708 1C 2B 2C 00                   DCD sub_2C2B1C
//.data.rel.ro : 01C5F70C 58 2A 2C 00                   DCD sub_2C2A58
//.data.rel.ro : 01C5F710 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C5F714 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C5F718 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01C5F71C 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01C5F720 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01C5F724 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01C5F728 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01C5F72C 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01C5F730 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01C5F734 98 3D 25 00                   DCD nullsub_345
//.data.rel.ro : 01C5F738; public PlantPropertySheet :
//.data.rel.ro : 01C5F738;   public /* offset 0x0 */ PropertySheetBase :
//.data.rel.ro : 01C5F738;     public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01C5F738;       public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C5F738; `typeinfo for'PlantPropertySheet
//.data.rel.ro:01C5F738 D8 74 DF 01                   _ZTI18PlantPropertySheet DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C5F738; DATA XREF : .data.rel.ro : 01C5F6FC↑o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F7D8↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F824↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F870↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F8BC↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F908↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F954↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F9A0↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5F9EC↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FA38↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FA84↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FAD0↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FB1C↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FB68↓o
//.data.rel.ro : 01C5F738;.data.rel.ro:01C5FBB4↓o ...
//.data.rel.ro : 01C5F738; reference to RTTI's type class
//.data.rel.ro:01C5F73C D0 FD B8 01                   DCD _ZTS18PlantPropertySheet; reference to type's name
//.data.rel.ro:01C5F740 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; reference to parent's type name

//看最右上角的偏移引用
//其中DATA XREF: sub_2B17D4+14↑o或sub_2B17D4+24↑o的sub_2B17D4为PLANTPROPS_CTOR
#define PLANTPROPS_CTOR PlantPropertySheet_PLANTPROPS_CTORAddr
//然后接下来就是
//.data.rel.ro:01C5F6FC 38 F7 C5 01                   DCD _ZTI18PlantPropertySheet; `typeinfo for'PlantPropertySheet
//.data.rel.ro:01C5F700 BC FF 2A 00                   DCD sub_2AFFBC

//其中.data.rel.ro:01C5F700的01C5F700为PLANTPROPS_VFTABLE
#define PLANTPROPS_VFTABLE PlantPropertySheet_PLANTPROPS_VFTABLEAddr
//双击示例中的DCD sub_2AFFBC位置
//跳转后所得如下：
//.text:002AFFBC
//.text : 002AFFBC; ============== = S U B R O U T I N E ====================================== =
//.text:002AFFBC
//.text : 002AFFBC; Attributes: thunk
//.text : 002AFFBC
//.text : 002AFFBC                               sub_2AFFBC; DATA XREF : .data.rel.ro : 01C5F700↓o
//.text : 002AFFBC; __unwind{
//.text:002AFFBC E1 FF FF EA                   B               sub_2AFF48
//.text : 002AFFBC; } // starts at 2AFFBC
//.text:002AFFBC
//.text : 002AFFBC; End of function sub_2AFFBC
//.text:002AFFBC
//.text : 002AFFC0

//其中sub_2AFF48为PLANTPROPS_GETTYPE
#define PLANTPROPS_GETTYPE PlantPropertySheet_PLANTPROPS_GETTYPEAddr


class PlantBoost
{
public:
	Sexy::RtWeakPtr<void> PlantBoostProps;
	int Value;
	int CooldownDurationSeconds;
};

class PowerSet
{
public:
	std::vector<int> List;
};

class PlantPropertySheet : public PropertySheetBase
{
public:
	DEFINE_RT_CLASS_GET_CLASS_WRAPPER(PLANTPROPS_GETTYPE);

	Sexy::SexyString TypeName;
	int Cost;
	int BeghouledCost;
	float Hitpoints;
	float PacketCooldown;
	float StartingCooldown;
	float PlantFoodDurationSeconds;
	int PlantFoodPlayCount;
	float PlantFoodShineTime = 0.75f;
	Sexy::SexyString PlantfoodActivationSound;
	Sexy::SexyString HelpedActivationSound;
	int PlantGridType;
	int MultiPlantLayer = 1;
	std::vector<PlantAction> Actions;
	PowerSet Powers;
	int GridWidth = 1;
	int GridHeight = 1;
	int GridItemDamage;
	float PlantingOffsetY;
	Sexy::SexyVector2 CursorPreviewOffset;
	Sexy::SexyVector2 ArtCenter;
	Sexy::SexyVector2 ZenGardenOffset;
	float ZenGardenSmallScale = 0.6f;
	float ZenGardenLargeScale = 1.2f;
	Rect HitRectAdjust;
	int Height = 2;
	int DangerRoomWeight = 100;
	bool IsZenGardenTreasurePlant;
	bool IsZenGardenWaterPlant;
	int ZenGardenSproutWeight;
	int ZenGardenBoostCost;
	int ZenGardenDurationOverrideSeconds = -1;
	std::vector<PlantBoost> Boosts;
	Rect RestrictPlantingToGridArea;
	std::vector<BoardEntityStat> PlantStats;
	std::vector<Sexy::SexyString> ValidStages;
	std::vector<Sexy::SexyString> SuggestionAlts;
	bool CanReciveFirstAid;
	bool IsConsumable;
	bool IsInstant;
	bool CanLiveOnWaves;
	bool CanPlantAgainToUpgrade;
	std::map<Sexy::SexyString, int> IdleAnimationWeights;
	Sexy::RtWeakPtr<void> AnimRigProps;
	bool HidePlantingEffects;
	float MasteryBoostChance;
	float MasteryResistancePiercing;
};

static_assert(sizeof(PlantPropertySheet) == 0x140);
static_assert(offsetof(PlantPropertySheet, PlantGridType) == 0x60);
static_assert(offsetof(PlantPropertySheet, ArtCenter) == 0x98);
static_assert(offsetof(PlantPropertySheet, IdleAnimationWeights) == 0x120);