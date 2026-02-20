#pragma once
#include <vector>
#include "PropertySheetBase.h"
#include "BoardEntity.h"

#define ZOMBIEPROPS_VFTABLE_FUNC_COUNT 14


//寻找该偏移方法：
//HEX搜索文本ZombiePropertySheet
//然后比如你跳转到了诸如"20ArcadeMenuRootDialog..........19ZombiePropertySheet"字样时候
//把鼠标单击ZombiePropertySheet的"Z"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01BA7CC0; `typeinfo name for'ZombiePropertySheet
//.rodata:01BA7CC0 31 39 5A 6F 6D 62 69 65 50 72 + _ZTS19ZombiePropertySheet DCB "19ZombiePropertySheet", 0
//.rodata : 01BA7CC0 6F 70 65 72 74 79 53 68 65 65 + ; DATA XREF : .data.rel.ro : 01CB8A0C↓o
//.rodata : 01BA7CC0 74 00; type descriptor name

//双击示例中的DATA XREF: .data.rel.ro:01CB8A0C↓o位置
//跳转到该类的虚表，如下：
//.data.rel.ro:01CB89C8; `vtable for'ZombiePropertySheet
//.data.rel.ro:01CB89C8 00 00 00 00                   _ZTV19ZombiePropertySheet DCD 0; DATA XREF : sub_87AEF8 + 14↑o
//.data.rel.ro : 01CB89C8; sub_87B2A4 + 28↑o
//.data.rel.ro:01CB89C8;.got:off_1D24A64↓o
//.data.rel.ro : 01CB89C8; offset to this
//.data.rel.ro:01CB89CC 08 8A CB 01                   DCD _ZTI19ZombiePropertySheet; `typeinfo for'ZombiePropertySheet
//.data.rel.ro:01CB89D0 C4 15 A0 00                   DCD sub_A015C4
//.data.rel.ro : 01CB89D4 7C 23 A0 00                   DCD sub_A0237C
//.data.rel.ro : 01CB89D8 F8 AE 87 00                   DCD sub_87AEF8
//.data.rel.ro : 01CB89DC FC 25 A1 00                   DCD sub_A125FC
//.data.rel.ro : 01CB89E0 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01CB89E4 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01CB89E8 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01CB89EC 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01CB89F0 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01CB89F4 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01CB89F8 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01CB89FC 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01CB8A00 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01CB8A04 98 3D 25 00                   DCD nullsub_345
//.data.rel.ro : 01CB8A08; public ZombiePropertySheet :
//.data.rel.ro : 01CB8A08;   public /* offset 0x0 */ PropertySheetBase :
//.data.rel.ro : 01CB8A08;     public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01CB8A08;       public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01CB8A08; `typeinfo for'ZombiePropertySheet
//.data.rel.ro:01CB8A08 D8 74 DF 01                   _ZTI19ZombiePropertySheet DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01CB8A08; DATA XREF : .data.rel.ro : 01C8C4BC↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C8D478↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C8E97C↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C905FC↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C90A68↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C90ACC↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C92714↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C95E4C↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C95EB0↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C9646C↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C96604↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C9679C↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C98E10↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C98E5C↑o
//.data.rel.ro : 01CB8A08;.data.rel.ro:01C9F510↑o ...
//.data.rel.ro : 01CB8A08; reference to RTTI's type class
//.data.rel.ro:01CB8A0C C0 7C BA 01                   DCD _ZTS19ZombiePropertySheet; reference to type's name
//.data.rel.ro:01CB8A10 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; reference to parent's type name

//其中最右上角的偏移引用
//DATA XREF: sub_87AEF8+14↑o中的sub_87AEF8为ZOMBIEPROPS_CTOR
#define ZOMBIEPROPS_CTOR ZombiePropertySheet_ZOMBIEPROPS_CTORAddr
//接下来，如下：
//.data.rel.ro:01CB89CC 08 8A CB 01                   DCD _ZTI19ZombiePropertySheet; `typeinfo for'ZombiePropertySheet
//.data.rel.ro:01CB89D0 C4 15 A0 00                   DCD sub_A015C4

//其中.data.rel.ro:01CB89D0的01CB89D0为ZOMBIEPROPS_VFTABLE
#define ZOMBIEPROPS_VFTABLE ZombiePropertySheet_ZOMBIEPROPS_VFTABLEAddr
//双击示例中DCD sub_A015C4位置，跳转后如下：
//.text:00A015C4
//.text : 00A015C4; ============== = S U B R O U T I N E ====================================== =
//.text:00A015C4
//.text : 00A015C4; Attributes: thunk
//.text : 00A015C4
//.text : 00A015C4                               sub_A015C4; DATA XREF : .data.rel.ro : 01CB89D0↓o
//.text : 00A015C4; __unwind{
//.text:00A015C4 E1 FF FF EA                   B               sub_A01550
//.text : 00A015C4; } // starts at A015C4
//.text:00A015C4
//.text : 00A015C4; End of function sub_A015C4
//.text:00A015C4
//.text : 00A015C8

//其中sub_A01550为ZOMBIEPROPS_GETTYPE
#define ZOMBIEPROPS_GETTYPE ZombiePropertySheet_ZOMBIEPROPS_GETTYPEAddr


class ZombiePropertySheet : public PropertySheetBase
{
public:
	DEFINE_RT_CLASS_GET_CLASS_WRAPPER(ZOMBIEPROPS_GETTYPE);

	enum ZombieSize {
		normal,
		large,
		chicken,
		imp
	};

	enum HelmType {
		none,
		cone,
		bucket,
		sarcophagus,
		camelsign,
		poncho,
		metalplate,
		cowboyhat,
		gravestone,
		crown,
		surfboard,
		iceblock,
		shovel,
		brick
	};

	char pad_1C[12];
	float Speed;
	float SpeedVariance;
	float Hitpoints;
	float TimeToKillInSeconds;
	float EatDPS;
	float PowerUpDamageModifier;
	float FireDamageMultiplier;
	float FoeEatDamageReflectPct;
	float AlmanacScale;
	Sexy::SexyVector2 AlmanacOffset;
	int Ammo;
	ZombieSize Size;
	bool CanSpawnPlantFood;
	bool CanTriggerZombieWin;
	bool CanSurrender;
	bool ExplodesWhenMowed;
	bool NormalDeathWhenMowed;
	bool IsValidPinchTarget;
	bool NormalDeathOnExplosion;
	bool ChillInsteadOfFreeze;
	bool CanBePlantTossedStrong;
	bool CanBePlantTossedWeak;
	bool SkipHeadDropState;
	float ArmDropFraction;
	HelmType Helm;
	float HelmHitpoints;
	int HelmDamageLayerIndices;
	bool HelmAbsorbsOverflowDamage;
	bool MetallicBodyParts;
	int GridHeight;
	Rect HitRect;
	Rect AttackRect;
	int Cost;
	int WavePointCost;
	int Weight;
	float ScoreOverride;
	Sexy::SexyVector2 StreetSize;
	Sexy::SexyVector2 StreetCriticalSize;
	Sexy::SexyVector2 StreetOffset;
	float ArtScale;
	Sexy::SexyVector2 ArtCenter;
	Sexy::SexyVector3 ShadowOffset;
	Sexy::SexyVector2 ShadowScaling;
	Sexy::SexyString GroundTrackName;
	Sexy::SexyVector2 ArtCenterBurnEffectOffset;
	Sexy::Point GridExtents;
	Sexy::SexyVector2 HypnoshroomEffectOffset;
	std::vector<int> ZombieStats;
	std::vector<Sexy::RtWeakPtr<void>> ZombieArmorProps;
	std::vector<int> ConditionImmunities;
	bool IgnoreWaterLine;
	float MaxTideLoweredPercent;
	Sexy::SexyString SoundOnDeath;
	Sexy::SexyString SoundOnTakeDamage;
	Sexy::SexyString SoundOnWalk;
	Sexy::SexyString SoundOnEat;
	Sexy::SexyString SoundOnIdle;
	Sexy::SexyString SoundOnAsh;
	Sexy::SexyString SoundOnElectrocute;
	bool CanBeFlicked;
	bool CanBeFlickedOff;
	bool FlickIsLaneRestricted;
	bool IsSpawnedFlying;
	float ShrunkenScale;
	float unk;
};

static_assert(sizeof(ZombiePropertySheet) == 0x198);
static_assert(offsetof(ZombiePropertySheet, Speed) == 0x28);
static_assert(offsetof(ZombiePropertySheet, SpeedVariance) == 0x2C);
static_assert(offsetof(ZombiePropertySheet, AlmanacOffset) == 0x4C);
static_assert(offsetof(ZombiePropertySheet, ArmDropFraction) == 0x68);
static_assert(offsetof(ZombiePropertySheet, HelmHitpoints) == 0x70);
static_assert(offsetof(ZombiePropertySheet, HitRect) == 0x80);
static_assert(offsetof(ZombiePropertySheet, ScoreOverride) == 0xAC);
static_assert(offsetof(ZombiePropertySheet, ShadowScaling) == 0xE0);
static_assert(offsetof(ZombiePropertySheet, GroundTrackName) == 0xE8);
static_assert(offsetof(ZombiePropertySheet, ArtCenterBurnEffectOffset) == 0xF4);
static_assert(offsetof(ZombiePropertySheet, GridExtents) == 0xFC);
static_assert(offsetof(ZombiePropertySheet, HypnoshroomEffectOffset) == 0x104);
static_assert(offsetof(ZombiePropertySheet, MaxTideLoweredPercent) == 0x134);
static_assert(offsetof(ZombiePropertySheet, ShrunkenScale) == 0x190);