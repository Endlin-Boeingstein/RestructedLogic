#pragma once
#include "Plant.h"
#include "Projectile.h"
#include "PlantAction.h"

#include "../Sexy/RtObject.h"

#define PLANTFRAMEWORK_VFTABLE_FUNC_COUNT 120

//寻找该偏移方法：
//HEX搜索文本PlantFramework
//然后比如你跳转到了诸如"12DebugConsole.14PlantFramework"字样时候
//把鼠标单击PlantFramework的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B95900; `typeinfo name for'PlantFramework
//.rodata:01B95900 31 34 50 6C 61 6E 74 46 72 61 + _ZTS14PlantFramework DCB "14PlantFramework", 0
//.rodata : 01B95900 6D 65 77 6F 72 6B 00; DATA XREF : .data.rel.ro : 01C6E688↓o
//.rodata : 01B95900; type descriptor name

//双击示例中的DATA XREF: .data.rel.ro:01C6E688↓o
//即可跳转到该类的虚表，向上翻动，可得整个虚表如下所示：
//.data.rel.ro:01C6E498; `vtable for'PlantFramework
//.data.rel.ro:01C6E498 00 00 00 00                   _ZTV14PlantFramework DCD 0; DATA XREF : sub_45BBB8 + 18↑o
//.data.rel.ro : 01C6E498; sub_45BBB8 + 20↑o
//.data.rel.ro:01C6E498;.text:off_45BC00↑o
//.data.rel.ro : 01C6E498; offset to this
//.data.rel.ro:01C6E49C 84 E6 C6 01                   DCD _ZTI14PlantFramework; `typeinfo for'PlantFramework
//.data.rel.ro:01C6E4A0 B4 BB 45 00                   DCD sub_45BBB4
//.data.rel.ro : 01C6E4A4 00 BD 45 00                   DCD sub_45BD00
//.data.rel.ro : 01C6E4A8 74 10 25 01                   DCD nullsub_1
//.data.rel.ro : 01C6E4AC B8 E8 45 00                   DCD sub_45E8B8
//.data.rel.ro : 01C6E4B0 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C6E4B4 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C6E4B8 24 02 25 01                   DCD sub_1250224
//.data.rel.ro : 01C6E4BC CC E8 45 00                   DCD nullsub_493
//.data.rel.ro : 01C6E4C0 D0 E8 45 00                   DCD nullsub_494
//.data.rel.ro : 01C6E4C4 D4 E8 45 00                   DCD nullsub_495
//.data.rel.ro : 01C6E4C8 D8 E8 45 00                   DCD sub_45E8D8
//.data.rel.ro : 01C6E4CC E0 E8 45 00                   DCD nullsub_496
//.data.rel.ro : 01C6E4D0 08 E3 45 00                   DCD sub_45E308
//.data.rel.ro:01C6E4D4 E4 E8 45 00                   DCD sub_45E8E4
//.data.rel.ro : 01C6E4D8 E4 E3 45 00                   DCD sub_45E3E4
//.data.rel.ro : 01C6E4DC C4 D1 45 00                   DCD sub_45D1C4
//.data.rel.ro : 01C6E4E0 EC E8 45 00                   DCD nullsub_497
//.data.rel.ro : 01C6E4E4 7C D2 45 00                   DCD sub_45D27C
//.data.rel.ro : 01C6E4E8 F0 E8 45 00                   DCD sub_45E8F0
//.data.rel.ro : 01C6E4EC F8 E8 45 00                   DCD sub_45E8F8
//.data.rel.ro : 01C6E4F0 68 BD 45 00                   DCD sub_45BD68
//.data.rel.ro : 01C6E4F4 D0 CA 45 00                   DCD sub_45CAD0
//.data.rel.ro : 01C6E4F8 84 CF 45 00                   DCD sub_45CF84
//.data.rel.ro : 01C6E4FC 54 CC 45 00                   DCD sub_45CC54
//.data.rel.ro : 01C6E500 30 D0 45 00                   DCD sub_45D030
//.data.rel.ro : 01C6E504 00 E9 45 00                   DCD sub_45E900
//.data.rel.ro : 01C6E508 08 E9 45 00                   DCD sub_45E908
//.data.rel.ro:01C6E50C 9C D1 45 00                   DCD sub_45D19C
//.data.rel.ro : 01C6E510 10 E9 45 00                   DCD sub_45E910
//.data.rel.ro : 01C6E514 00 EA 45 00                   DCD sub_45EA00
//.data.rel.ro : 01C6E518 24 EB 45 00                   DCD nullsub_498
//.data.rel.ro : 01C6E51C 28 EB 45 00                   DCD nullsub_499
//.data.rel.ro : 01C6E520 2C EB 45 00                   DCD nullsub_500
//.data.rel.ro : 01C6E524 2C BD 45 00                   DCD sub_45BD2C
//.data.rel.ro : 01C6E528 30 EB 45 00                   DCD nullsub_501
//.data.rel.ro : 01C6E52C 34 EB 45 00                   DCD nullsub_502
//.data.rel.ro : 01C6E530 38 EB 45 00                   DCD nullsub_503
//.data.rel.ro : 01C6E534 3C EB 45 00                   DCD sub_45EB3C
//.data.rel.ro : 01C6E538 B0 EB 45 00                   DCD nullsub_504
//.data.rel.ro : 01C6E53C B4 EB 45 00                   DCD sub_45EBB4
//.data.rel.ro : 01C6E540 BC EB 45 00                   DCD sub_45EBBC
//.data.rel.ro : 01C6E544 A8 D2 45 00                   DCD sub_45D2A8
//.data.rel.ro : 01C6E548 A4 DA 45 00                   DCD sub_45DAA4
//.data.rel.ro : 01C6E54C 88 D8 45 00                   DCD sub_45D888
//.data.rel.ro : 01C6E550 C0 D9 45 00                   DCD sub_45D9C0
//.data.rel.ro : 01C6E554 C4 EB 45 00                   DCD sub_45EBC4
//.data.rel.ro : 01C6E558 DC EB 45 00                   DCD sub_45EBDC
//.data.rel.ro : 01C6E55C D8 D6 45 00                   DCD sub_45D6D8
//.data.rel.ro : 01C6E560 B0 D7 45 00                   DCD sub_45D7B0
//.data.rel.ro : 01C6E564 E4 EB 45 00                   DCD sub_45EBE4
//.data.rel.ro : 01C6E568 EC EB 45 00                   DCD sub_45EBEC
//.data.rel.ro : 01C6E56C 9C D4 45 00                   DCD sub_45D49C
//.data.rel.ro : 01C6E570 FC EB 45 00                   DCD sub_45EBFC
//.data.rel.ro : 01C6E574 58 ED 45 00                   DCD nullsub_505
//.data.rel.ro : 01C6E578 AC DA 45 00                   DCD sub_45DAAC
//.data.rel.ro : 01C6E57C 5C ED 45 00                   DCD sub_45ED5C
//.data.rel.ro : 01C6E580 74 ED 45 00                   DCD sub_45ED74
//.data.rel.ro : 01C6E584 7C ED 45 00                   DCD sub_45ED7C
//.data.rel.ro : 01C6E588 84 ED 45 00                   DCD sub_45ED84
//.data.rel.ro : 01C6E58C 90 ED 45 00                   DCD sub_45ED90
//.data.rel.ro : 01C6E590 98 ED 45 00                   DCD sub_45ED98
//.data.rel.ro : 01C6E594 A0 ED 45 00                   DCD sub_45EDA0
//.data.rel.ro : 01C6E598 A8 ED 45 00                   DCD sub_45EDA8
//.data.rel.ro : 01C6E59C B0 ED 45 00                   DCD sub_45EDB0
//.data.rel.ro : 01C6E5A0 B8 ED 45 00                   DCD sub_45EDB8
//.data.rel.ro : 01C6E5A4 C0 ED 45 00                   DCD sub_45EDC0
//.data.rel.ro : 01C6E5A8 C8 ED 45 00                   DCD sub_45EDC8
//.data.rel.ro : 01C6E5AC 00 E5 45 00                   DCD sub_45E500
//.data.rel.ro : 01C6E5B0 D0 ED 45 00                   DCD sub_45EDD0
//.data.rel.ro : 01C6E5B4 D8 ED 45 00                   DCD nullsub_506
//.data.rel.ro : 01C6E5B8 DC ED 45 00                   DCD sub_45EDDC
//.data.rel.ro : 01C6E5BC E4 ED 45 00                   DCD nullsub_507
//.data.rel.ro : 01C6E5C0 E8 ED 45 00                   DCD sub_45EDE8
//.data.rel.ro : 01C6E5C4 F8 ED 45 00                   DCD sub_45EDF8
//.data.rel.ro : 01C6E5C8 F0 DC 45 00                   DCD sub_45DCF0
//.data.rel.ro : 01C6E5CC C4 DE 45 00                   DCD sub_45DEC4
//.data.rel.ro : 01C6E5D0 00 EE 45 00                   DCD sub_45EE00
//.data.rel.ro : 01C6E5D4 08 EE 45 00                   DCD sub_45EE08
//.data.rel.ro:01C6E5D8 1C EE 45 00                   DCD nullsub_508
//.data.rel.ro : 01C6E5DC CC E1 45 00                   DCD sub_45E1CC
//.data.rel.ro : 01C6E5E0 20 EE 45 00                   DCD sub_45EE20
//.data.rel.ro : 01C6E5E4 A8 DC 45 00                   DCD sub_45DCA8
//.data.rel.ro : 01C6E5E8 10 EF 45 00                   DCD sub_45EF10
//.data.rel.ro : 01C6E5EC E8 DC 45 00                   DCD sub_45DCE8
//.data.rel.ro : 01C6E5F0 18 EF 45 00                   DCD sub_45EF18
//.data.rel.ro : 01C6E5F4 20 EF 45 00                   DCD sub_45EF20
//.data.rel.ro : 01C6E5F8 28 EF 45 00                   DCD sub_45EF28
//.data.rel.ro : 01C6E5FC 30 EF 45 00                   DCD sub_45EF30
//.data.rel.ro : 01C6E600 38 EF 45 00                   DCD sub_45EF38
//.data.rel.ro : 01C6E604 40 EF 45 00                   DCD sub_45EF40
//.data.rel.ro : 01C6E608 7C EF 45 00                   DCD sub_45EF7C
//.data.rel.ro : 01C6E60C 98 DB 45 00                   DCD sub_45DB98
//.data.rel.ro : 01C6E610 84 EF 45 00                   DCD nullsub_509
//.data.rel.ro : 01C6E614 88 EF 45 00                   DCD nullsub_510
//.data.rel.ro : 01C6E618 8C EF 45 00                   DCD nullsub_511
//.data.rel.ro : 01C6E61C 90 EF 45 00                   DCD nullsub_512
//.data.rel.ro : 01C6E620 94 EF 45 00                   DCD nullsub_513
//.data.rel.ro : 01C6E624 98 EF 45 00                   DCD nullsub_514
//.data.rel.ro : 01C6E628 9C EF 45 00                   DCD nullsub_515
//.data.rel.ro : 01C6E62C A0 EF 45 00                   DCD nullsub_516
//.data.rel.ro : 01C6E630 A4 EF 45 00                   DCD nullsub_517
//.data.rel.ro : 01C6E634 A8 EF 45 00                   DCD nullsub_518
//.data.rel.ro : 01C6E638 AC EF 45 00                   DCD nullsub_519
//.data.rel.ro : 01C6E63C B0 EF 45 00                   DCD nullsub_520
//.data.rel.ro : 01C6E640 B4 EF 45 00                   DCD sub_45EFB4
//.data.rel.ro : 01C6E644 BC EF 45 00                   DCD nullsub_521
//.data.rel.ro : 01C6E648 C0 EF 45 00                   DCD sub_45EFC0
//.data.rel.ro : 01C6E64C C8 EF 45 00                   DCD nullsub_522
//.data.rel.ro : 01C6E650 CC EF 45 00                   DCD nullsub_523
//.data.rel.ro : 01C6E654 D0 EF 45 00                   DCD sub_45EFD0
//.data.rel.ro : 01C6E658 DC EF 45 00                   DCD sub_45EFDC
//.data.rel.ro : 01C6E65C 7C CA 45 00                   DCD sub_45CA7C
//.data.rel.ro : 01C6E660 B8 CA 45 00                   DCD sub_45CAB8
//.data.rel.ro : 01C6E664 C8 CA 45 00                   DCD sub_45CAC8
//.data.rel.ro : 01C6E668 E4 EF 45 00                   DCD nullsub_524
//.data.rel.ro : 01C6E66C E8 EF 45 00                   DCD sub_45EFE8
//.data.rel.ro : 01C6E670 F0 EF 45 00                   DCD nullsub_525
//.data.rel.ro : 01C6E674 F4 EF 45 00                   DCD sub_45EFF4
//.data.rel.ro : 01C6E678 FC EF 45 00                   DCD sub_45EFFC
//.data.rel.ro : 01C6E67C C4 CE 45 00                   DCD sub_45CEC4
//.data.rel.ro : 01C6E680 10 F0 45 00                   DCD nullsub_526
//.data.rel.ro : 01C6E684; public PlantFramework :
//.data.rel.ro : 01C6E684;   public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C6E684; `typeinfo for'PlantFramework
//.data.rel.ro:01C6E684 D8 74 DF 01                   _ZTI14PlantFramework DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C6E684; DATA XREF : .data.rel.ro : 01C6E49C↑o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CB0598↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC1C78↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC2010↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC25C8↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC2950↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC2BFC↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC3014↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC3080↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC33C8↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC3674↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC3878↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC3BBC↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC4348↓o
//.data.rel.ro : 01C6E684;.data.rel.ro:01CC4360↓o ...
//.data.rel.ro : 01C6E684; reference to RTTI's type class
//.data.rel.ro:01C6E688 00 59 B9 01                   DCD _ZTS14PlantFramework; reference to type's name
//.data.rel.ro:01C6E68C BC DA D0 01                   DCD _ZTIN4Sexy8RtObjectE; reference to parent's type name

//找到最右上角的偏移引用
//DATA XREF: sub_45BBB8+18↑o或sub_45BBB8+20↑o的sub_45BBB8则为PLANTFRAMEWORK_CTOR
#define PLANTFRAMEWORK_CTOR PlantFramework_PLANTFRAMEWORK_CTORAddr

//然后引用部分后面：
//.data.rel.ro:01C6E49C 84 E6 C6 01                   DCD _ZTI14PlantFramework; `typeinfo for'PlantFramework
//.data.rel.ro:01C6E4A0 B4 BB 45 00                   DCD sub_45BBB4

//其中.data.rel.ro:01C6E4A0的01C6E4A0为PLANTFRAMEWORK_VFTABLE
#define PLANTFRAMEWORK_VFTABLE PlantFramework_PLANTFRAMEWORK_VFTABLEAddr
//双击示例中DCD sub_45BBB4位置
//进入后可得整个函数
//.text:0045BBB4
//.text : 0045BBB4; ============== = S U B R O U T I N E ====================================== =
//.text:0045BBB4
//.text : 0045BBB4; Attributes: thunk
//.text : 0045BBB4
//.text : 0045BBB4                               sub_45BBB4; DATA XREF : .data.rel.ro : 01C6E4A0↓o
//.text : 0045BBB4; __unwind{
//.text:0045BBB4 E1 FF FF EA                   B               sub_45BB40
//.text : 0045BBB4; } // starts at 45BBB4
//.text:0045BBB4
//.text : 0045BBB4; End of function sub_45BBB4
//.text:0045BBB4
//.text : 0045BBB8

//其中sub_45BB40则为PLANTFRAMEWORK_GETTYPE
#define PLANTFRAMEWORK_GETTYPE PlantFramework_PLANTFRAMEWORK_GETTYPEAddr

class Plant;

class PlantFramework : Sexy::RtObject
{
public:
	Plant* m_plant;

	virtual void Function7() {};
	virtual void Function8() {};
	virtual void Function9() {};
	virtual void RenderAnimRigs(Sexy::Graphics* g) {};
	virtual void Function11() {};
	virtual void Function12() {};
	virtual void Function13() {};
	virtual void SetupAnimRigFiringCallbacks(int* rig) {}; // should be changed to PlantAnimRig later
	virtual void PlayChompSound() {};
	virtual void Die() {};
	virtual Projectile* CreateProjectile() {};
	virtual float GetLaunchIntervalMultiplier() {};
	virtual std::vector<Sexy::RtWeakPtr<void>> FindAttackTargets(char unk1, int unk2) {};
	virtual void Function21() {};
	virtual void Function22() {};
	virtual void Function23() {};
	virtual void Function24() {};
	virtual void Function25() {};
	virtual void Function26() {};
	virtual Sexy::SexyVector3 GetProjectileOffset(PlantAction* action, float scale) {};
	virtual int GetPlantfoodPlayCount() {};
	virtual void Function29() {};
	virtual void Function30() {};
	virtual void Function31() {};
	virtual void Function32() {};
	virtual void Function33() {};
	virtual void Function34() {};
	virtual void Function35() {};
	virtual void Function36() {};
	virtual bool HasPlantFoodEnded() {};
	virtual void FirePlantFood() {};
	virtual bool IsInPlantFoodState() {};
	virtual void Function40() {};
	virtual void ActivatePlantFood() {};
	virtual void TriggerPlantFoodFlash() {};
	virtual void StartExhausted(float duration) {};
	virtual void FinishExhausted() {};
	virtual bool IsExhausted() {};
	virtual void Function46() {};
	virtual void PlayCharging() {};
	virtual void PlayCycling() {};
	virtual void Function49() {};
	virtual void Function50() {};
	virtual void PlayBeingHelped() {};
	virtual bool NotDeactivated() {}; // check if not being helped nor exhausted
	virtual void Function53() {};
	virtual void PlayHelpedOff() {}; // set state to READY
	virtual bool IsBeingHelped() {};
	virtual void Function56() {};
	virtual void Function57() {};
	virtual void Function58() {};
	virtual void PlayAttackBasedOnTier() {};
	virtual void Function60() {};
	virtual void Function61() {};
	virtual void Function62() {};
	virtual void Function63() {};
	virtual void Function64() {};
	virtual void Function65() {};
	virtual bool CanSink() {};
	virtual float GetSinkPercentage() {};
	virtual void Function68() {};
	virtual void Function69() {};
	virtual void Function70() {};
	virtual void Function71() {};
	virtual void Function72() {};
	virtual void Function73() {};
	virtual Rect GetActionTriggerRectGridCoords(int actionIdx) {};
	virtual Rect GetActionTriggerRect(int actionIdx) {};
	virtual void Function76() {};
	virtual void OnDamaged() {}; // TODO: I'm not sure the fields and return value for this
	virtual void Function78() {};
	virtual Sexy::SexyString GetProjectileLaunchSound() {};
	virtual int GetHeight() {};
	virtual void AttemptKill() {};
	virtual void Function82() {};
	virtual bool IsInvincible() {};
	virtual void Function84() {};
	virtual void Function85() {};
	virtual void Function86() {}; // TODO: this one is for use_action frames
	virtual void Function87() {};
	virtual void Function88() {};
	virtual void Function89() {};
	virtual void Function90() {};
	virtual float GetCost() {};
	virtual void Function92() {};
	virtual void Function93() {};
	virtual void Function94() {};
	virtual void Function95() {};
	virtual void Function96() {};
	virtual void Function97() {};
	virtual void PlantfoodStartedCallback() {}; // TODO: Check parameters for these 3
	virtual void PlantfoodLoopedCallback() {};
	virtual void PlantfoodEndedCallback() {};
	virtual void Function101() {};
	virtual void Function102() {};
	virtual void Function103() {};
	virtual void Function104() {};
	virtual void Function105() {};
	virtual void Function106() {};
	virtual void Function107() {};
	virtual void Function108() {};
	virtual void Function109() {};
	virtual void Function110() {};
	virtual bool CanPlantBasedOnCellType() {};
	virtual void Function112() {};
	virtual void Function113() {};
	virtual void Function114() {};
	virtual void Function115() {};
	virtual void Function116() {};
	virtual void Function117() {};
	virtual void Function118() {};
	virtual void SetCollisionRect() {}; // Idk the return value of this one
	virtual void Function120() {};
};