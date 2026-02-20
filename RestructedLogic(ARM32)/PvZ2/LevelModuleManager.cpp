#include "../pch.h"
#include "LevelModuleManager.h"

//寻找该偏移方法：
//HEX搜索文本Play_WinMusic
//然后比如你跳转到了诸如"Play_WinMusic.Stop_Prize_Menu"字样时候
//把鼠标单击Play_WinMusic的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B3A390 50 6C 61 79 5F 57 69 6E 4D 75 + aPlayWinmusic DCB "Play_WinMusic", 0; DATA XREF : sub_29274C + 94↑o
//.rodata : 01B3A390 73 69 63 00; sub_29274C + 9C↑o
//.rodata:01B3A390;.text:off_292AB0↑o

//双击示例中sub_29274C+94↑o或sub_29274C+9C↑o位置
//跳转后按F5,所得如下：
//int __fastcall sub_29274C(int a1)
//{
//    int* v2; // r6
//    float* v3; // r5
//    int v4; // r0
//    int v5; // r0
//    unsigned int* v6; // r0
//    int v7; // r0
//    float v8; // s16
//    int v9; // r6
//    int v10; // r7
//    int v11; // r0
//    int v12; // r8
//    int v13; // r9
//    int v14; // r10
//    int v15; // r4
//    int v16; // r4
//    float v17; // s18
//    int v18; // r0
//    float* v19; // r6
//    int v21; // [sp+10h] [bp-50h]
//    int v22; // [sp+18h] [bp-48h]
//    float* v23; // [sp+1Ch] [bp-44h]
//    __int64 v24; // [sp+20h] [bp-40h] BYREF
//    void* v25; // [sp+28h] [bp-38h]
//    int v26; // [sp+2Ch] [bp-34h]
//
//    v2 = sub_10D99A4();
//    sub_10DFA5C(&v24, (int)v2, (_DWORD*)(a1 + 16));
//    v3 = 0;
//    if (!sub_10C8C60(&v24))
//    {
//        v4 = sub_10C8B64((int)&v24);
//        v5 = sub_10DF644(v2, v4);
//        v3 = 0;
//        if (v5)
//            v3 = (float*)sub_10DB9C0(v5, (int)&v24);
//    }
//    v6 = sub_10C8B38((unsigned int*)&v24);
//    v7 = sub_26AA10(v6);
//    sub_6B3068(v7, "Play_WinMusic", 0);
//    *(_DWORD*)(a1 + 136) = 0;
//    v8 = v3[22] + 0.0;
//    v22 = sub_292ADC();
//    v21 = a1;
//    if (v22 && sub_5CE924(dword_1D92A94, 2) && *(int*)(*(_DWORD*)(dword_1D92A94 + 1728) + 152) >= 1)
//    {
//        v9 = a1 + 120;
//        v10 = 0;
//        v23 = v3;
//        do
//        {
//            v11 = sub_FC4D20(v22, (unsigned __int8)v10);
//            v12 = v11;
//            if (v11 && *(_DWORD*)(v11 + 132) == 2)
//            {
//                v25 = (void*)operator new(0x30u);
//                v24 = 0x2000000031LL;
//                strcpy((char*)v25, "Play_UI_Game_Mower_Appear_Single");
//                v13 = sub_292B00(v10, &v24);
//                if ((v24 & 1) != 0)
//                    operator delete(v25);
//                v14 = v9;
//                sub_1045850(v9, v13, LODWORD(v8), &v24);
//                v15 = *((_DWORD*)v23 + 21);
//                v16 = sub_6C95E8(*(_DWORD*)(dword_1D92A94 + 2000)) + v15;
//                if (v16 >= 1)
//                {
//                    v17 = (float)v16;
//                    v3 = v23;
//                    do
//                    {
//                        v18 = sub_292B58(
//                            v21,
//                            *(_DWORD*)(v12 + 20),
//                            COERCE_INT(*(float*)(v12 + 24) - *(float*)(v12 + 28)),
//                            *((_DWORD*)v23 + 26),
//                            5.0);
//                        sub_1045850(v9, v18, LODWORD(v8), &v24);
//                        --v16;
//                        v8 = v8 + (float)(v23[23] / v17);
//                    } while (v16);
//                    goto LABEL_19;
//                }
//            }
//            else
//            {
//                v14 = v9;
//            }
//            v3 = v23;
//        LABEL_19:
//            ++v10;
//            v9 = v14;
//            v8 = v8 + v3[24];
//        } while (v10 < *(_DWORD*)(*(_DWORD*)(dword_1D92A94 + 1728) + 152));
//    }
//    v19 = (float*)dword_1D7C3E4;
//    if (!dword_1D7C3E4)
//    {
//        v19 = (float*)operator new(0x58u);
//        memset(v19, 0, 0x58u);
//        dword_1D7C3E4 = (int)v19;
//        *(_DWORD*)v19 = off_1C5C77C;
//    }
//    *(float*)(v21 + 44) = (float)((float)(v8 + v19[9]) + v3[24]) + v3[25];
//    return _stack_chk_guard - v26;
//}

//双击其中的sub_292ADC()位置（10.x及以后版本中该位置有俩函数，第二个有两个参数的函数即为return ((getModule)getActualOffset(填入))(this, rtClass);，中间函数被精简掉了，然后就无需再往下做了）
//跳转后所得如下：
//int sub_292ADC()
//{
//	int v0; // r4
//	int v1; // r1
//
//	v0 = *(_DWORD*)(sub_949EFC() + 776);
//	v1 = sub_FC360C();
//	return sub_6FBB94(v0, v1);
//}

//其中sub_6FBB94即return ((getModule)getActualOffset(填入))(this, rtClass);
LevelModule* LevelModuleManager::getModule(Sexy::RtClass* rtClass) {
	typedef LevelModule* (*getModule)(LevelModuleManager*, Sexy::RtClass* rtClass);
	return ((getModule)getActualOffset(LevelModuleManager_getModuleAddr))(this, rtClass);
}

//寻找该偏移方法：
//HEX搜索文本InitialPlantPlacer
//然后比如你跳转到了诸如"22InitialPlantProperties........18InitialPlantPlacer"字样时候
//把鼠标单击InitialPlantPlacer的"I"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B90740; `typeinfo name for'InitialPlantPlacer
//.rodata:01B90740 31 38 49 6E 69 74 69 61 6C 50 + _ZTS18InitialPlantPlacer DCB "18InitialPlantPlacer", 0
//.rodata : 01B90740 6C 61 6E 74 50 6C 61 63 65 72 + ; DATA XREF : .data.rel.ro : 01C60D30↓o
//.rodata : 01B90740 00; type descriptor name

//双击示例中DATA XREF: .data.rel.ro:01C60D30↓o位置
//跳转到该类虚表后，向上翻动，所得如下：
//.data.rel.ro:01C60CD8; `vtable for'InitialPlantPlacer
//.data.rel.ro:01C60CD8 00 00 00 00                   _ZTV18InitialPlantPlacer DCD 0; DATA XREF : sub_2D9234 + 30↑o
//.data.rel.ro : 01C60CD8; sub_2D9234 + 3C↑o
//.data.rel.ro:01C60CD8;.text:off_2D92B4↑o
//.data.rel.ro : 01C60CD8; sub_2DA89C + C↑o
//.data.rel.ro:01C60CD8; sub_2DA89C + 10↑o
//.data.rel.ro:01C60CD8;.text:off_2DA8E4↑o
//.data.rel.ro : 01C60CD8; sub_2DA8EC + C↑o
//.data.rel.ro:01C60CD8; sub_2DA8EC + 10↑o
//.data.rel.ro:01C60CD8;.text:off_2DA938↑o
//.data.rel.ro : 01C60CD8; offset to this
//.data.rel.ro:01C60CDC 2C 0D C6 01                   DCD _ZTI18InitialPlantPlacer; `typeinfo for'InitialPlantPlacer
//.data.rel.ro:01C60CE0 30 92 2D 00                   DCD sub_2D9230
//.data.rel.ro : 01C60CE4 B4 93 2D 00                   DCD sub_2D93B4
//.data.rel.ro : 01C60CE8 9C A8 2D 00                   DCD sub_2DA89C
//.data.rel.ro : 01C60CEC EC A8 2D 00                   DCD sub_2DA8EC
//.data.rel.ro : 01C60CF0 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C60CF4 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C60CF8 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01C60CFC CC 95 2D 00                   DCD sub_2D95CC
//.data.rel.ro : 01C60D00 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01C60D04 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01C60D08 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01C60D0C 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01C60D10 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01C60D14 50 55 29 00                   DCD nullsub_391
//.data.rel.ro : 01C60D18 54 55 29 00                   DCD nullsub_392
//.data.rel.ro : 01C60D1C 58 55 29 00                   DCD sub_295558
//.data.rel.ro : 01C60D20 60 55 29 00                   DCD sub_295560
//.data.rel.ro : 01C60D24 40 A9 2D 00                   DCD nullsub_454
//.data.rel.ro : 01C60D28 50 56 29 00                   DCD nullsub_393
//.data.rel.ro : 01C60D2C; public InitialPlantPlacer :
//.data.rel.ro : 01C60D2C;   public /* offset 0x0 */ LevelModule :
//.data.rel.ro : 01C60D2C;     public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01C60D2C;       public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C60D2C; `typeinfo for'InitialPlantPlacer
//.data.rel.ro:01C60D2C D8 74 DF 01                   _ZTI18InitialPlantPlacer DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C60D2C; DATA XREF : .data.rel.ro : 01C60CDC↑o
//.data.rel.ro : 01C60D2C; reference to RTTI's type class
//.data.rel.ro:01C60D30 40 07 B9 01                   DCD _ZTS18InitialPlantPlacer; reference to type's name
//.data.rel.ro:01C60D34 60 74 CE 01                   DCD _ZTI11LevelModule; reference to parent's type name

//双击示例中DCD sub_2D95CC位置
//跳转后按F5，所得如下：
//int __fastcall sub_2D95CC(int a1)
//{
//    int v2; // r0
//    int v3; // r0
//    int v5[6]; // [sp+4h] [bp-4Ch] BYREF
//    int v6[13]; // [sp+1Ch] [bp-34h] BYREF
//
//    v2 = sub_CF3DCC();
//    v6[2] = 0;
//    v6[1] = (int)sub_2D96B0;
//    v6[3] = a1;
//    v6[4] = 1;
//    v6[0] = (int)off_1C5C758;
//    v6[5] = (int)sub_2DB760;
//    sub_295854((_DWORD*)(v2 + 84), v6, 0);
//    v3 = sub_CF3DCC();
//    v5[2] = 0;
//    v5[1] = (int)sub_2D9900;
//    v5[3] = a1;
//    v5[4] = 1;
//    v5[0] = (int)off_1C5C758;
//    v5[5] = (int)sub_2DB760;
//    sub_295854((_DWORD*)(v3 + 116), v5, 0);
//    return _stack_chk_guard - v6[6];
//}

//其中sub_295854即((AddDelegate)getActualOffset(填入))(this, &delegate, 0);（其中高版本函数被篡改分解，故还在原处的函数实际上是其子功能，需要手搓原来的函数以复现）
#if GAME_VERSION<1000
void Sexy::Event::AddDelegate(DelegateBase& delegate) {
	typedef void (*AddDelegate)(Sexy::Event*, Sexy::DelegateBase*, int);
	((AddDelegate)getActualOffset(LevelModuleManager_AddDelegateAddr))(this, &delegate, 0);
}
#endif
#if GAME_VERSION>=1000
//EA欺我太甚！！！它把这个函数给拆了，所以得手搓一个
// 1. 先定义好你的手搓函数（放在同一个文件或者头文件里）
void* My_AddDelegate(void* event_ptr, void* delegate_ptr, int a3) {
    uintptr_t* result = (uintptr_t*)event_ptr;
    uintptr_t finish = result[2];
    uintptr_t end = result[3];

    if (finish != end) {
        uint32_t* dest = (uint32_t*)finish;
        dest[0] = getActualOffset(DelegateBase_SEXYDELEGATE_VTBLAddr); // 10.3 虚表
        memcpy(dest + 1, (char*)delegate_ptr + 4, 20);
        result[2] += 24;
    }
    else {
        typedef void (*ReallocateAdd)(void*, void*);
        ((ReallocateAdd)getActualOffset(LevelModuleManager_AddDelegateAddr))(&result[1], delegate_ptr);
    }
    return event_ptr;
}

void Sexy::Event::AddDelegate(DelegateBase& delegate) {
    // 直接调用，简单粗暴
    My_AddDelegate(this, &delegate, 0);
}
#endif