#pragma once
#include "PropertySheetBase.h"
#include "CollisionTypeFlags.h"
#include "DamageTypeFlags.h"
#include "ZombieConditions.h"

#include "../Sexy/Color.h"

#define PROJECTILEPROPS_VFTABLE_FUNC_COUNT 14

//寻找该偏移方法：
//HEX搜索文本ProjectilePropertySheet
//然后比如你跳转到了诸如"22EffectObject_FrostWind........23ProjectilePropertySheet"字样时候
//把鼠标单击ProjectilePropertySheet的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B91390; `typeinfo name for'ProjectilePropertySheet
//.rodata:01B91390 32 33 50 72 6F 6A 65 63 74 69 + _ZTS23ProjectilePropertySheet DCB "23ProjectilePropertySheet", 0
//.rodata : 01B91390 6C 65 50 72 6F 70 65 72 74 79 + ; DATA XREF : .data.rel.ro : 01C62EEC↓o
//.rodata : 01B91390 53 68 65 65 74 00; type descriptor name

//双击示例中DATA XREF: .data.rel.ro:01C62EEC↓o位置
//跳转到该类虚表，向上翻页，整体如下：
//.data.rel.ro:01C62EA8; `vtable for'ProjectilePropertySheet
//.data.rel.ro:01C62EA8 00 00 00 00                   _ZTV23ProjectilePropertySheet DCD 0; DATA XREF : sub_29D4A4 + 10↑o
//.data.rel.ro : 01C62EA8; sub_29DC10 + 3C↑o
//.data.rel.ro:01C62EA8;.got:off_1D240EC↓o
//.data.rel.ro : 01C62EA8; offset to this
//.data.rel.ro:01C62EAC E8 2E C6 01                   DCD _ZTI23ProjectilePropertySheet; `typeinfo for'ProjectilePropertySheet
//.data.rel.ro:01C62EB0 CC 70 31 00                   DCD loc_3170CC
//.data.rel.ro : 01C62EB4 64 7B 31 00                   DCD sub_317B64
//.data.rel.ro : 01C62EB8 A4 D4 29 00                   DCD sub_29D4A4
//.data.rel.ro : 01C62EBC BC 9A 31 00                   DCD sub_319ABC
//.data.rel.ro : 01C62EC0 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C62EC4 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C62EC8 D4 99 31 00                   DCD sub_3199D4
//.data.rel.ro : 01C62ECC 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01C62ED0 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01C62ED4 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01C62ED8 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01C62EDC 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01C62EE0 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01C62EE4 98 3D 25 00                   DCD nullsub_345
//.data.rel.ro : 01C62EE8; public ProjectilePropertySheet :
//.data.rel.ro : 01C62EE8;   public /* offset 0x0 */ PropertySheetBase :
//.data.rel.ro : 01C62EE8;     public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01C62EE8;       public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C62EE8; `typeinfo for'ProjectilePropertySheet
//.data.rel.ro:01C62EE8 D8 74 DF 01                   _ZTI23ProjectilePropertySheet DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C62EE8; DATA XREF : .data.rel.ro : 01C5ECDC↑o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01C62EAC↑o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01C6F058↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01C6F770↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01C96420↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01C9DC38↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CA9970↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CB07C8↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CB5DEC↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CC2758↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CC4A5C↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CC7CB4↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CCB194↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CCC828↓o
//.data.rel.ro : 01C62EE8;.data.rel.ro:01CCF5C0↓o ...
//.data.rel.ro : 01C62EE8; reference to RTTI's type class
//.data.rel.ro:01C62EEC 90 13 B9 01                   DCD _ZTS23ProjectilePropertySheet; reference to type's name
//.data.rel.ro:01C62EF0 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; reference to parent's type name

//其中最右上角的偏移引用
//其中sub_29DC10+3C↑o的sub_29DC10为PROJECTILEPROPS_CTOR
#define PROJECTILEPROPS_CTOR ProjectilePropertySheet_PROJECTILEPROPS_CTORAddr
//接着
//.data.rel.ro:01C62EAC E8 2E C6 01                   DCD _ZTI23ProjectilePropertySheet; `typeinfo for'ProjectilePropertySheet
//.data.rel.ro:01C62EB0 CC 70 31 00                   DCD loc_3170CC

//其中.data.rel.ro:01C62EB0的01C62EB0为PROJECTILEPROPS_VFTABLE
#define PROJECTILEPROPS_VFTABLE ProjectilePropertySheet_PROJECTILEPROPS_VFTABLEAddr
//双击示例中DCD loc_3170CC位置
//跳转后可得：
//.text:003170CC; -------------------------------------------------------------------------- -
//.text:003170CC
//.text : 003170CC                               loc_3170CC; DATA XREF : .data.rel.ro : 01C62EB0↓o
//.text : 003170CC; __unwind{
//.text:003170CC E1 FF FF EA                   B               sub_317058
//.text : 003170CC; } // starts at 3170CC
//.text:003170CC
//.text : 003170D0

//其中sub_317058则为PROJECTILEPROPS_GETTYPE
#define PROJECTILEPROPS_GETTYPE ProjectilePropertySheet_PROJECTILEPROPS_GETTYPEAddr

class ZombieConditionEntry {
	ZombieConditions Condition;
	ValueRange Duration;
};

class ProjectilePropertySheet : public PropertySheetBase
{
public:
	static Sexy::RtClass* getRtClass() {
		typedef Sexy::RtClass* (*getType)();
		getType pGetType = (getType)getActualOffset(PROJECTILEPROPS_GETTYPE);
		return pGetType();
	};

	Sexy::SexyString ClassName = "Projectile";
	float BaseDamage;
	float HealAmount;
	char pad0030[0x10];
	float SplashDamage;
	float StunDuration;
	float SplashRadius;
	float SplashRadiusBaseDamageCutoff;
	bool ShakeBoardOnSplash;
	bool DiesOnImpact = true;
	bool HasShadow = true;
	bool ImpactShowsAtZombieFeet;
	bool RotateToMatchVelocity;
	bool ImpactSoundForce;
	bool FollowsGround;
	ZombieConditions OverrideStunCondition = zombie_condition_none;
	std::vector<ValueRange> InitialVelocity;
	std::vector<ValueRange> InitialAcceleration;
	std::vector<ValueRange> InitialVelocityScale;
	ValueRange InitialHeight;
	ValueRange InitialRotation;
	ValueRange InitialAngularVelocity;
	ValueRange InitialScale = ValueRange(1.0f, 1.0f);
	Sexy::SexyString AttachedPAM;
	Sexy::SexyString AttachedPAMAnimRigClass;
	Sexy::SexyVector2 AttachedPAMOffset;
	std::vector<Sexy::SexyString> AttachedPAMAnimationToPlay;
	Sexy::SexyString ShadowImage = "IMAGE_PEA_SHADOWS";
	Sexy::SexyString RenderImage;
	Sexy::Color RenderColor;
	FRect CollisionRect;
	Sexy::SexyString ImpactSoundEvent;
	float ImpactSoundThrottleTimer;
	Sexy::SexyString ImpactPAM;
	std::vector<Sexy::SexyString> ImpactPAMAnimationToPlay;
	std::vector<ValueRange> ImpactOffset;
	Sexy::SexyString SpawnPAM;
	std::vector<Sexy::SexyString> SpawnPAMAnimationToPlay;
	std::vector<ValueRange> SpawnPAMOffset;
	std::vector<ZombieConditionEntry> Conditions;
	Sexy::SexyVector2 AttachedPAMEffectOffset;
	std::vector<CollisionTypeFlags> CollisionFlags;
	std::vector<DamageTypeFlags> DamageFlags;

};

static_assert(sizeof(ProjectilePropertySheet) == 0x188);
static_assert(offsetof(ProjectilePropertySheet, ImpactPAM) == 0x114);
static_assert(offsetof(ProjectilePropertySheet, InitialScale) == 0x98);
static_assert(offsetof(ProjectilePropertySheet, OverrideStunCondition) == 0x58);