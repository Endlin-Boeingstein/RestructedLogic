#pragma once
#include "LevelModuleProperties.h"
#include "../Sexy/RtWeakPtr.h"

#define LEVELMODULE_VTBL_NFUNC 19
//寻找该偏移方法:
//HEX搜索文本LevelModule(这次搜索需要仔细，必须到符合条件的地方，否则找不到)
//然后比如你跳转到了诸如"N15PowerUpUIButton17AnimateSaturationE.11LevelModule............"字样时候
//把鼠标单击LevelModule的"L"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01BB00F7; `typeinfo name for'LevelModule
//.rodata:01BB00F7 31 31 4C 65 76 65 6C 4D 6F 64 + _ZTS11LevelModule DCB "11LevelModule", 0; DATA XREF : .data.rel.ro : 01CE7464↓o
//.rodata : 01BB00F7 75 6C 65 00; type descriptor name

//双击示例中DATA XREF: .data.rel.ro:01CE7464↓o位置
//跳转后，界面朝上一点，你会发现这块整体长这样：
//.data.rel.ro:01CE740C; `vtable for'LevelModule
//.data.rel.ro:01CE740C 00 00 00 00                   _ZTV11LevelModule DCD 0; DATA XREF : sub_28E534 + 18↑o
//.data.rel.ro : 01CE740C; sub_28E534 + 10C↑o
//.data.rel.ro:01CE740C; sub_295458 + B8↑o
//.data.rel.ro:01CE740C; sub_2A99B4 + 20↑o
//.data.rel.ro:01CE740C; sub_2A99B4 + 70↑o
//.data.rel.ro:01CE740C; sub_2AA8B0 + 28↑o
//.data.rel.ro:01CE740C; sub_2AA900 + 28↑o
//.data.rel.ro:01CE740C; sub_2D9234 + 1C↑o
//.data.rel.ro:01CE740C; sub_2DA89C + 28↑o
//.data.rel.ro:01CE740C; sub_2DA8EC + 28↑o
//.data.rel.ro:01CE740C; sub_2DED28 + 1C↑o
//.data.rel.ro:01CE740C; sub_2DF3B8 + 10↑o
//.data.rel.ro:01CE740C; sub_2DF3EC + 10↑o
//.data.rel.ro:01CE740C; sub_2F49A0 + 20↑o
//.data.rel.ro:01CE740C; sub_2F49A0 + 68↑o ...
//.data.rel.ro:01CE740C; offset to this
//.data.rel.ro:01CE7410 60 74 CE 01                   DCD _ZTI11LevelModule; `typeinfo for'LevelModule
//.data.rel.ro:01CE7414 D4 39 CF 00                   off_1CE7414 DCD sub_CF39D4
//.data.rel.ro : 01CE7418 34 3B CF 00                   DCD sub_CF3B34
//.data.rel.ro : 01CE741C B8 F3 2D 00                   DCD sub_2DF3B8
//.data.rel.ro : 01CE7420 E0 3D CF 00                   DCD sub_CF3DE0
//.data.rel.ro : 01CE7424 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01CE7428 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01CE742C 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01CE7430 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01CE7434 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01CE7438 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01CE743C B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01CE7440 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01CE7444 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01CE7448 50 55 29 00                   DCD nullsub_391
//.data.rel.ro : 01CE744C 54 55 29 00                   DCD nullsub_392
//.data.rel.ro : 01CE7450 58 55 29 00                   DCD sub_295558
//.data.rel.ro : 01CE7454 60 55 29 00                   DCD sub_295560
//.data.rel.ro : 01CE7458 40 A9 2D 00                   DCD nullsub_454
//.data.rel.ro : 01CE745C 50 56 29 00                   DCD nullsub_393
//.data.rel.ro : 01CE7460; public LevelModule :
//.data.rel.ro : 01CE7460;   public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01CE7460;     public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01CE7460; `typeinfo for'LevelModule
//.data.rel.ro:01CE7460 D8 74 DF 01                   _ZTI11LevelModule DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01CE7460; DATA XREF : .data.rel.ro : 01C60D34↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C610B8↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C630B4↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C67174↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C6785C↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68458↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68514↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C685D0↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C6868C↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68748↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68804↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C688C0↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C6897C↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68A38↑o
//.data.rel.ro : 01CE7460;.data.rel.ro:01C68AF4↑o ...
//.data.rel.ro : 01CE7460; reference to RTTI's type class
//.data.rel.ro:01CE7464 F7 00 BB 01                   DCD _ZTS11LevelModule; reference to type's name
//.data.rel.ro:01CE7468 F8 54 C7 01                   DCD _ZTI10GameObject; reference to parent's type name

//从sub_2DF3B8+10↑o可知sub_2DF3B8为LEVELMODULE_DTOR_ADDR
#define LEVELMODULE_DTOR_ADDR LevelModule_LEVELMODULE_DTOR_ADDRAddr
//从DATA XREF: sub_28E534+18↑o或者sub_28E534+10C↑o可知sub_28E534为LEVELMODULE_CTOR_ADDR
#define LEVELMODULE_CTOR_ADDR LevelModule_LEVELMODULE_CTOR_ADDRAddr
//双击其中的
//.data.rel.ro:01CE7410 60 74 CE 01                   DCD _ZTI11LevelModule                   ; `typeinfo for'LevelModule
//.data.rel.ro:01CE7414 D4 39 CF 00                   off_1CE7414 DCD sub_CF39D4
//部分的sub_CF39D4

//跳转后无需F5即可看到
//.text:00CF39D4; __unwind{
//.text:00CF39D4 E1 FF FF EA                   B               sub_CF3960
//.text : 00CF39D4; } // starts at CF39D4
//.text:00CF39D4
//.text : 00CF39D4; End of function sub_CF39D4

//其中sub_CF3960为LEVELMODULE_GETCLASS_ADDR
#define LEVELMODULE_GETCLASS_ADDR LevelModule_LEVELMODULE_GETCLASS_ADDRAddr
//双击DATA XREF: sub_28E534+18↑o跳转后按F5，所得如下：
//int __fastcall sub_28E534(int a1)
//{
//	sub_53EF3C((_DWORD*)a1);
//	*(_DWORD*)a1 = off_1CE7414;
//	sub_10C8A34((_DWORD*)(a1 + 16));
//	*(_DWORD*)a1 = off_1C5E454;
//	sub_10C8A34((_DWORD*)(a1 + 32));
//	memset((void*)(a1 + 56), 0, 0x3Cu);
//	sub_53EF3C((_DWORD*)(a1 + 120));
//	*(_DWORD*)(a1 + 136) = 0;
//	*(_BYTE*)(a1 + 140) = 0;
//	*(_DWORD*)(a1 + 120) = off_1D095B0;
//	memset((void*)(a1 + 144), 0, 0x18u);
//	return a1;
//}

//其中off_1CE7414则为LEVELMODULE_VTBL
#define LEVELMODULE_VTBL LevelModule_LEVELMODULE_VTBLAddr



class LevelModule : public GameObject
{
public:
	Sexy::RtWeakPtr<LevelModuleProperties> m_propertySheetPtr;
};