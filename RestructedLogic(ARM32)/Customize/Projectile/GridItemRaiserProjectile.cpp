#include "GridItemRaiserProjectile.h"
#include "../../PvZ2/GridItem.h"

void* GridItemRaiserProjectile::vftable = nullptr;
Sexy::RtClass* GridItemRaiserProjectile::s_rtClass = nullptr;

#pragma region hk SpawnGridItem Proj

// the anim and sound code can be used in ImpactPAM and ImpactSoundEvent, i don't need to recreate any of them
uintptr_t hkSpawnGridItem(GridItemRaiserProjectile* self)
{
    typedef int (*board1)();
    //寻找该偏移方法：
    //HEX搜索文本ShockwavePerkProjectileDefault
    //然后比如你跳转到了诸如"ShockwavePerkProjectileDefault..PennyPerkShockwaveProjectileProperties"字样时候
    //把鼠标单击ShockwavePerkProjectileDefault的"S"上面，然后根据该偏移让ida pro跳转
    //这个时候，如下所示：
    /*.rodata:01ADB7B8 53 68 6F 63 6B 77 61 76 65 50 + aShockwaveperkp DCB "ShockwavePerkProjectileDefault", 0
        .rodata : 01ADB7B8 65 72 6B 50 72 6F 6A 65 63 74 + ; DATA XREF : sub_29C6B0 + 48↑o
        .rodata : 01ADB7B8 69 6C 65 44 65 66 61 75 6C 74 + ; sub_29C6B0 + 50↑o
        .rodata:01ADB7B8 00;.text:off_29CA54↑o*/

    //双击示例中的DATA XREF: sub_29C6B0+48↑o或sub_29C6B0+50↑o位置
    //跳转按F5后，所得如下：
    //int __fastcall sub_29C6B0(int a1)
    //{
    //    char* v1; // r5
    //    int v2; // r2
    //    int v3; // r0
    //    unsigned int* v4; // r7
    //    void* v5; // r4
    //    char v6; // r6
    //    int v7; // r0
    //    int v8; // r0
    //    int v9; // r0
    //    int v10; // r0
    //    unsigned int* v11; // r0
    //    unsigned int* v12; // r0
    //    int v13; // r0
    //    int v14; // r5
    //    int v15; // r9
    //    int v16; // r0
    //    int v17; // r0
    //    int v18; // r5
    //    int v19; // r5
    //    int(__fastcall * v20)(int, int); // r4
    //    int v21; // r0
    //    int v22; // r0
    //    __int64* v25; // [sp+Ch] [bp-7Ch]
    //    int v26; // [sp+14h] [bp-74h]
    //    int v27; // [sp+18h] [bp-70h]
    //    int v28; // [sp+1Ch] [bp-6Ch]
    //    unsigned int v29[2]; // [sp+20h] [bp-68h] BYREF
    //    unsigned int v30[3]; // [sp+28h] [bp-60h] BYREF
    //    int v31[2]; // [sp+34h] [bp-54h] BYREF
    //    void* v32; // [sp+3Ch] [bp-4Ch]
    //    char v33; // [sp+40h] [bp-48h] BYREF
    //    void* v34; // [sp+48h] [bp-40h]
    //    int v35; // [sp+50h] [bp-38h] BYREF
    //    void* v36; // [sp+54h] [bp-34h]
    //    __int64 v37; // [sp+58h] [bp-30h] BYREF
    //    __int64 v38; // [sp+60h] [bp-28h] BYREF
    //    int v39; // [sp+68h] [bp-20h]
    //    v1 = &v33;
    //    v2 = -1;
    //    v27 = 198;
    //    v25 = (__int64*)(a1 + 24);
    //    do
    //    {
    //        v26 = v2;
    //        v28 = sub_265FA4();
    //        v32 = (void*)operator new(0x20u);
    //        v31[0] = 33;
    //        v31[1] = 30;
    //        strcpy((char*)v32, "ShockwavePerkProjectileDefault");
    //        v3 = sub_10C0954(v1, v31);
    //        v4 = (unsigned int*)v1;
    //        v5 = v34;
    //        v6 = v33;
    //        v7 = sub_10C85A4(v3);
    //        if ((v6 & 1) == 0)
    //            v5 = v1 + 4;
    //        v35 = sub_10C87A4(v7, v5);
    //        v8 = sub_10C85A4(v35);
    //        v9 = sub_10C8830(v8, v35);
    //        v10 = sub_10C85A4(v9);
    //        v36 = (void*)sub_10C87E0(v10, v35);
    //        sub_29CBB0(&v37, v28, 24, &v35);
    //        v11 = sub_10C8A34(&v38);
    //        sub_10C8BF8(v11, &v37);
    //        v12 = sub_10C8B38((unsigned int*)&v37);
    //        v13 = sub_10C85A4(v12);
    //        sub_10C8858(v13, v35);
    //        v36 = &unk_1B6C5F4;
    //        if ((v33 & 1) != 0)
    //            operator delete(v34);
    //        if ((v31[0] & 1) != 0)
    //            operator delete(v32);
    //        sub_10C8A34(v30);
    //        sub_10C8BF8(v30, v25);
    //        v14 = sub_10D99A4();
    //        sub_10DFA5C((int)v4, v14, (int)v30);
    //        v15 = 0;
    //        if (!sub_10C8C60(v4))
    //        {
    //            v16 = sub_10C8B64(v4);
    //            v17 = sub_10DF644(v14, v16);
    //            if (v17)
    //                v15 = sub_10DB9C0(v17, v4);
    //        }
    //        sub_10C8B38(v4);
    //        sub_10C8B38(v30);
    //        v18 = sub_949EFC();
    //        sub_10C8A34(v29);
    //        sub_10C8BF8(v29, &v38);
    //        v19 = ((int(__fastcall*)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))sub_720A2C)(
    //            v18,
    //            1128792064,
    //            (float)v27,
    //            0,
    //            v29,
    //            0);
    //        if (v19)
    //        {
    //            v20 = *(int(__fastcall**)(int, int))(*(_DWORD*)v19 + 16);
    //            v21 = sub_29CF98();
    //            if (!v20(v19, v21))
    //                v19 = 0;
    //        }
    //        else
    //        {
    //            v19 = 0;
    //        }
    //        sub_10C8B38(v29);
    //        *(_DWORD*)(v19 + 32) = 1;
    //        v22 = *(_DWORD*)(*(_DWORD*)(v15 + 112) + 4 * *(_DWORD*)(a1 + 16));
    //        *(_BYTE*)(v19 + 200) = 1;
    //        *(_DWORD*)(v19 + 320) = v22;
    //        sub_10C8B38((unsigned int*)&v38);
    //        v27 += 76;
    //        v2 = v26 + 1;
    //        v1 = (char*)v4;
    //    } while ((unsigned int)(v26 + 1) < 4);
    //    return _stack_chk_guard - v39;
    //}

    //其中sub_949EFC即int board = ((board1)getActualOffset(填入))();
    int board = ((board1)getActualOffset(Customize_Projectile_GridItemRaiserProjectile_GetBoardAddr))();

    typedef GridItem* (*func716690)(int, Sexy::SexyString, int, int);
    func716690 func_716690 = (func716690)getActualOffset(GridItem_SpawnGridItemAtAddr);

    float posX = self->m_position.mX;
    float posY = self->m_position.mY;

    int gridPosY = (((int)posY - 540) / 76) + 4;
    int gridPosX = (int)((posX - 200.0f) / 64.0f);


    Sexy::SexyString gridType = "molten_pool";

    typedef bool (*func716FA4)(int, uint, uint, int, int);
    //寻找该偏移方法：
    //HEX搜索文本POPANIM_EFFECTS_ZOMBIE_EGYPT_TOMBRAISER_BONE_HIT
    //然后比如你跳转到了诸如"POPANIM_EFFECTS_ZOMBIE_EGYPT_TOMBRAISER_BONE_HIT"字样时候
    //把鼠标单击POPANIM_EFFECTS_ZOMBIE_EGYPT_TOMBRAISER_BONE_HIT的"P"上面，然后根据该偏移让ida pro跳转
    //这个时候，如下所示：
    /*.rodata:01AF85C0 50 4F 50 41 4E 49 4D 5F 45 46 + aPopanimEffects_153 DCB "POPANIM_EFFECTS_ZOMBIE_EGYPT_TOMBRAISER_BONE_HIT", 0
        .rodata : 01AF85C0 46 45 43 54 53 5F 5A 4F 4D 42 + ; DATA XREF : sub_794628 + 114↑o
        .rodata : 01AF85C0 49 45 5F 45 47 59 50 54 5F 54 + ; sub_794628 + 12C↑o
        .rodata:01AF85C0 4F 4D 42 52 41 49 53 45 52 5F + ;.text:off_794964↑o*/

    //双击示例中DATA XREF: sub_794628+114↑o或sub_794628+12C↑o的位置
    //跳转后按F5,所得如下：
    //int __fastcall sub_794628(int* a1)
    //{
    //    int v2; // r5
    //    int v3; // r10
    //    int v4; // r8
    //    int v5; // r5
    //    int v6; // r0
    //    int v7; // r6
    //    int v8; // r5
    //    int v9; // r7
    //    int v10; // r0
    //    int v11; // r0
    //    int v12; // r0
    //    int v13; // r0
    //    int v14; // r0
    //    int v16; // [sp+4h] [bp-44h]
    //    unsigned int v17[2]; // [sp+8h] [bp-40h] BYREF
    //    float v18[4]; // [sp+10h] [bp-38h] BYREF
    //    unsigned int v19[2]; // [sp+20h] [bp-28h] BYREF
    //    if (sub_716FA4(*(_DWORD*)(dword_1D92A94 + 1728), a1[80], *((float*)a1 + 81), 0, 1))
    //    {
    //        v2 = *(_DWORD*)(dword_1D92A94 + 1728);
    //        LODWORD(v18[2]) = operator new(0x20u);
    //        LODWORD(v18[0]) = 33;
    //        LODWORD(v18[1]) = 16;
    //        strcpy((char*)LODWORD(v18[2]), "gravestone_egypt");
    //        v3 = sub_716690(v2, (int)v18, a1[80], a1[81]);
    //        if ((LOBYTE(v18[0]) & 1) != 0)
    //            operator delete((void*)LODWORD(v18[2]));
    //        sub_E86C58(v3, 0);
    //        v16 = a1[80];
    //        v4 = a1[81];
    //        v5 = *(_DWORD*)(dword_1D92A94 + 1728);
    //        v6 = sub_E54A84();
    //        v7 = sub_716354(v5, v6);
    //        LODWORD(v18[2]) = operator new(0x40u);
    //        LODWORD(v18[0]) = 65;
    //        LODWORD(v18[1]) = 48;
    //        strcpy((char*)LODWORD(v18[2]), "POPANIM_EFFECTS_ZOMBIE_EGYPT_TOMBRAISER_BONE_HIT");
    //        sub_C9B7D4(v17, v18);
    //        v8 = sub_10D99A4();
    //        sub_10DFA5C((int)v19, v8, (int)v17);
    //        v9 = 0;
    //        if (!sub_10C8C60(v19))
    //        {
    //            v10 = sub_10C8B64(v19);
    //            v11 = sub_10DF644(v8, v10);
    //            if (v11)
    //                v9 = sub_10DB9C0(v11, v19);
    //        }
    //        sub_10C8B38(v19);
    //        sub_E56188(v7, v9, 0);
    //        sub_10C8B38(v17);
    //        if ((LOBYTE(v18[0]) & 1) != 0)
    //            operator delete((void*)LODWORD(v18[2]));
    //        sub_E56260(v7, 1);
    //        v18[2] = 0.0;
    //        v18[1] = (float)(76 * v4 + 192);
    //        v18[0] = (float)((v16 << 6) + 232);
    //        v12 = (*(int(__fastcall**)(int))(*(_DWORD*)v3 + 176))(v3);
    //        sub_735B60(v7, v18, v12 + 2);
    //        LOBYTE(v18[0]) = 18;
    //        HIBYTE(v18[2]) = 0;
    //        strcpy((char*)v18 + 1, "animation");
    //        BYTE2(v18[2]) = 0;
    //        sub_E564A4(v7, v18, 0);
    //        v13 = LOBYTE(v18[0]);
    //        if ((LOBYTE(v18[0]) & 1) != 0)
    //            operator delete((void*)LODWORD(v18[2]));
    //        v14 = sub_26AA10(v13);
    //        sub_6B3068(v14, "Play_Zomb_Egypt_TombRaiser_Grave_Rise", 0);
    //    }
    //    return (*(int(__fastcall**)(int*, _DWORD))(*a1 + 164))(a1, 0);
    //}

    //其中sub_716FA4即auto* fun716FA4 = ((func716FA4)getActualOffset(填入));
    auto* fun716FA4 = ((func716FA4)getActualOffset(Customize_Projectile_GridItemRaiserProjectile_SpawnGridItemOnBoardAddr));

    if (fun716FA4(board, gridPosX, gridPosY, 0, 1) == true)
    {
        GridItem* gridItem = func_716690(board, gridType, gridPosX, gridPosY);

        typedef void (*funcCEB640)(GridItem*, int);
        //寻找该偏移方法：
        //HEX搜索文本future_jetpack_disco
        //然后比如你跳转到了诸如"future_jetpack_disco....ZombieMechDiscoSubsystem"字样时候
        //把鼠标单击future_jetpack_disco的"f"上面，然后根据该偏移让ida pro跳转
        //这个时候，如下所示：
       /* .rodata:01AF9858 66 75 74 75 72 65 5F 6A 65 74 + aFutureJetpackD DCB "future_jetpack_disco", 0
            .rodata : 01AF9858 70 61 63 6B 5F 64 69 73 63 6F + ; DATA XREF : sub_7BFC74 + 44↑o
            .rodata : 01AF9858 00; sub_7BFC74 + 5C↑o
            .rodata:01AF9858;.text:off_7C02C4↑o
            .rodata : 01AF9858; sub_1066160:off_1066810↑o
            .rodata : 01AF9858; sub_1066160 + 1364↑o
            .rodata:01AF9858; sub_1066160 + 137C↑o*/

        //双击示例中的DATA XREF: sub_7BFC74+44↑o或sub_7BFC74+5C↑o
        //跳转后按F5，所得如下：
        //int __fastcall sub_7BFC74(_DWORD * a1)
        //{
        //    int v2; // r5
        //    unsigned int* v3; // r5
        //    int* v4; // r10
        //    unsigned int* i; // r0
        //    unsigned int v6; // r5
        //    int v7; // r6
        //    int v8; // r7
        //    int v9; // r7
        //    int v10; // r7
        //    int v11; // r7
        //    int v12; // r7
        //    int v13; // r5
        //    int v14; // r7
        //    int v15; // r7
        //    int v16; // r5
        //    int v17; // r6
        //    int v18; // r6
        //    int v19; // r5
        //    unsigned int v20; // r5
        //    int v21; // r8
        //    int v22; // r7
        //    int v23; // r6
        //    int* v24; // r7
        //    int v25; // r0
        //    int v26; // r0
        //    int v27; // r0
        //    int v28; // r0
        //    int v29; // r0
        //    unsigned int v31[2]; // [sp+8h] [bp-60h] BYREF
        //    unsigned int v32[2]; // [sp+10h] [bp-58h] BYREF
        //    unsigned int v33[2]; // [sp+18h] [bp-50h] BYREF
        //    unsigned int v34[2]; // [sp+20h] [bp-48h] BYREF
        //    unsigned int v35[2]; // [sp+28h] [bp-40h] BYREF
        //    unsigned int v36[2]; // [sp+30h] [bp-38h] BYREF
        //    void* v37; // [sp+38h] [bp-30h]
        //    __int64 v38; // [sp+40h] [bp-28h] BYREF
        //    int v39; // [sp+48h] [bp-20h]
        //    a1[200] = *(_DWORD*)(sub_7BF8D4(a1) + 440);
        //    v2 = sub_281008();
        //    v37 = (void*)operator new(0x20u);
        //    v36[0] = 33;
        //    v36[1] = 20;
        //    strcpy((char*)v37, "future_jetpack_disco");
        //    sub_28107C(&v38, v2, (int)v36);
        //    if ((v36[0] & 1) != 0)
        //        operator delete(v37);
        //    v4 = a1 + 201;
        //    v3 = (unsigned int*)a1[201];
        //    for (i = (unsigned int*)a1[202]; v3 != i; i = sub_10C8B38(i - 2))
        //        ;
        //    a1[202] = v3;
        //    v6 = -1;
        //    do
        //    {
        //        sub_10C8A34(v36);
        //        if (a1[202] >= a1[203])
        //        {
        //            sub_33D400(a1 + 201, v36);
        //        }
        //        else
        //        {
        //            sub_10C8A6C();
        //            a1[202] += 8;
        //        }
        //        sub_10C8B38(v36);
        //        ++v6;
        //    } while (v6 < 3);
        //    v7 = sub_634490(a1[6]);
        //    v8 = *(_DWORD*)(dword_1D92A94 + 1728);
        //    sub_10C8A34(v34);
        //    sub_10C8BF8(v34, &v38);
        //    v9 = sub_722300(v8, v34, 0, 6, -1);
        //    sub_10C8A34(v35);
        //    sub_10C8BF8(v35, (__int64*)(v9 + 8));
        //    v10 = *v4;
        //    sub_10C8A84(v36, v35);
        //    sub_10C8BB0(v10, v36);
        //    sub_10C8B38(v36);
        //    sub_10C8B38(v35);
        //    sub_10C8B38(v34);
        //    if (sub_7226C0(*(_DWORD*)(dword_1D92A94 + 1728), v7 - 1))
        //    {
        //        v11 = *(_DWORD*)(dword_1D92A94 + 1728);
        //        sub_10C8A34(v33);
        //        sub_10C8BF8(v33, &v38);
        //        v12 = sub_722300(v11, v33, 0, 6, -1);
        //        sub_10C8A34(v35);
        //        sub_10C8BF8(v35, (__int64*)(v12 + 8));
        //        v13 = *v4;
        //        sub_10C8A84(v36, v35);
        //        sub_10C8BB0(v13 + 8, v36);
        //        sub_10C8B38(v36);
        //        sub_10C8B38(v35);
        //        sub_10C8B38(v33);
        //    }
        //    v14 = *(_DWORD*)(dword_1D92A94 + 1728);
        //    sub_10C8A34(v32);
        //    sub_10C8BF8(v32, &v38);
        //    v15 = sub_722300(v14, v32, 0, 6, -1);
        //    sub_10C8A34(v35);
        //    sub_10C8BF8(v35, (__int64*)(v15 + 8));
        //    v16 = *v4;
        //    sub_10C8A84(v36, v35);
        //    sub_10C8BB0(v16 + 16, v36);
        //    sub_10C8B38(v36);
        //    sub_10C8B38(v35);
        //    sub_10C8B38(v32);
        //    if (sub_7226C0(*(_DWORD*)(dword_1D92A94 + 1728), v7 + 1))
        //    {
        //        v17 = *(_DWORD*)(dword_1D92A94 + 1728);
        //        sub_10C8A34(v31);
        //        sub_10C8BF8(v31, &v38);
        //        v18 = sub_722300(v17, v31, 0, 6, -1);
        //        sub_10C8A34(v35);
        //        sub_10C8BF8(v35, (__int64*)(v18 + 8));
        //        v19 = *v4;
        //        sub_10C8A84(v36, v35);
        //        sub_10C8BB0(v19 + 24, v36);
        //        sub_10C8B38(v36);
        //        sub_10C8B38(v35);
        //        sub_10C8B38(v31);
        //    }
        //    v20 = -1;
        //    v21 = 0;
        //    do
        //    {
        //        if (sub_279198((_QWORD*)(*v4 + v21)))
        //        {
        //            v22 = *v4;
        //            v23 = sub_10D99A4();
        //            sub_10DFA5C((int)v36, v23, v22 + v21);
        //            v24 = 0;
        //            if (!sub_10C8C60(v36))
        //            {
        //                v25 = sub_10C8B64(v36);
        //                v26 = sub_10DF644(v23, v25);
        //                if (v26)
        //                    v24 = (int*)sub_10DB9C0(v26, v36);
        //            }
        //            sub_10C8B38(v36);
        //            if (sub_8A584C(a1, 23))
        //                sub_8A7EC8(v24, 23, 2139095039, 0, 0);
        //            sub_8A4AAC(v24, 16, 0);
        //            sub_CEB640(v24, a1[8]);
        //            v27 = sub_8A5A8C(a1);
        //            sub_8A8450(v24, v27);
        //            if (sub_8A584C(a1, 44))
        //                sub_8A7EC8(v24, 44, 2139095039, 0, 0);
        //        }
        //        ++v20;
        //        v21 += 8;
        //    } while (v20 < 3);
        //    sub_7C02E4(a1, 0);
        //    v28 = sub_736DE4(a1);
        //    sub_7C05B8(v28);
        //    v29 = sub_7BF8D4(a1);
        //    sub_CEBAE8(a1, v29 + 448, 0);
        //    sub_10C8B38((unsigned int*)&v38);
        //    return _stack_chk_guard - v39;
        //}
        
        //其中sub_CEB640即auto* setTeamFlag = ((funcCEB640)getActualOffset(填入));
        auto* setTeamFlag = ((funcCEB640)getActualOffset(Customize_Projectile_GridItemRaiserProjectile_SetTeamFlagAddr));
        setTeamFlag(gridItem, 1);

    }
    else
    {
        LOGI("Error: Grid position invalid. Skipping grid spawn.");
    }
    typedef int (*VirtualFunc41)(void*, int);
    void** vtable = *(void***)self;
    VirtualFunc41 func = (VirtualFunc41)vtable[41];
    int result = func(self, 0);
    return result;
}
void GridItemRaiserProjectile::modInit() {
    LOGI("GridItemRaiserProjectile init");
    //寻找该偏移方法：
    //由于Projectile这个字符串遍布so，所以非常之刻要用非常之法
    //HEX搜索16进制数值003F3F50726F6A656374696C6500，选中作为通配符，通配符填入3F
    //然后比如你跳转到了诸如"20EgyptStageProperties.10Projectile"字样时候
    //把鼠标单击Projectile的"P"上面，然后根据该偏移让ida pro跳转
    //这个时候，如下所示：
    /*.rodata:01BA44B7; `typeinfo name for'Projectile
        .rodata:01BA44B7 31 30 50 72 6F 6A 65 63 74 69 + _ZTS10Projectile DCB "10Projectile", 0; DATA XREF : .data.rel.ro : 01CB01C8↓o
        .rodata : 01BA44B7 6C 65 00; type descriptor name*/

    //双击示例中的DATA XREF: .data.rel.ro:01CB01C8↓o位置
    //跳转即为该类虚表，向上翻页，整体如下：
    //.data.rel.ro:01CB00D0; `vtable for'Projectile
    //    .data.rel.ro:01CB00D0 00 00 00 00                   _ZTV10Projectile DCD 0; DATA XREF : sub_907508 + 28↑o
    //    .data.rel.ro : 01CB00D0; sub_907508 + 30↑o
    //    .data.rel.ro:01CB00D0;.text:off_907718↑o
    //    .data.rel.ro : 01CB00D0; sub_90774C + 14↑o
    //    .data.rel.ro:01CB00D0; sub_90774C + 28↑o
    //    .data.rel.ro:01CB00D0;.text:off_907948↑o
    //    .data.rel.ro : 01CB00D0; offset to this
    //    .data.rel.ro:01CB00D4 C4 01 CB 01                   DCD _ZTI10Projectile; `typeinfo for'Projectile
    //    .data.rel.ro:01CB00D8 24 5A 90 00                   DCD sub_905A24
    //    .data.rel.ro : 01CB00DC 44 5B 90 00                   DCD sub_905B44
    //    .data.rel.ro : 01CB00E0 4C 77 90 00                   DCD sub_90774C
    //    .data.rel.ro : 01CB00E4 5C 79 90 00                   DCD sub_90795C
    //    .data.rel.ro : 01CB00E8 F0 01 25 01                   DCD sub_12501F0
    //    .data.rel.ro : 01CB00EC 1C 02 25 01                   DCD sub_125021C
    //    .data.rel.ro : 01CB00F0 20 F2 53 00                   DCD sub_53F220
    //    .data.rel.ro : 01CB00F4 84 3D 25 00                   DCD nullsub_339
    //    .data.rel.ro : 01CB00F8 88 3D 25 00                   DCD nullsub_340
    //    .data.rel.ro : 01CB00FC 8C 3D 25 00                   DCD nullsub_341
    //    .data.rel.ro : 01CB0100 B8 22 25 00                   DCD nullsub_342
    //    .data.rel.ro : 01CB0104 90 3D 25 00                   DCD nullsub_343
    //    .data.rel.ro : 01CB0108 9C 47 45 00                   DCD sub_45479C
    //    .data.rel.ro : 01CB010C 6C D6 29 00                   DCD sub_29D66C
    //    .data.rel.ro : 01CB0110 F4 B4 CE 00                   DCD sub_CEB4F4
    //    .data.rel.ro : 01CB0114 28 B6 CE 00                   DCD sub_CEB628
    //    .data.rel.ro : 01CB0118 10 BA 90 00                   DCD sub_90BA10
    //    .data.rel.ro : 01CB011C AC 8A 90 00                   DCD sub_908AAC
    //    .data.rel.ro : 01CB0120 54 B9 CE 00                   DCD sub_CEB954
    //    .data.rel.ro : 01CB0124 B4 D6 90 00                   DCD sub_90D6B4
    //    .data.rel.ro : 01CB0128 FC C7 90 00                   DCD sub_90C7FC
    //    .data.rel.ro : 01CB012C 44 D7 90 00                   DCD sub_90D744
    //    .data.rel.ro : 01CB0130 00 9A 90 00                   DCD sub_909A00
    //    .data.rel.ro : 01CB0134 7C D6 29 00                   DCD sub_29D67C
    //    .data.rel.ro : 01CB0138 E0 22 25 00                   DCD sub_2522E0
    //    .data.rel.ro : 01CB013C F0 22 25 00                   DCD nullsub_417
    //    .data.rel.ro : 01CB0140 F4 22 25 00                   DCD nullsub_418
    //    .data.rel.ro : 01CB0144 18 B3 90 00                   DCD sub_90B318
    //    .data.rel.ro : 01CB0148 38 BA 90 00                   DCD sub_90BA38
    //    .data.rel.ro : 01CB014C 00 4F 45 00                   DCD sub_454F00
    //    .data.rel.ro : 01CB0150 94 B6 CE 00                   DCD sub_CEB694
    //    .data.rel.ro : 01CB0154 38 BA CE 00                   DCD sub_CEBA38
    //    .data.rel.ro : 01CB0158 5C B9 CE 00                   DCD sub_CEB95C
    //    .data.rel.ro : 01CB015C 18 4C 45 00                   DCD nullsub_421
    //    .data.rel.ro : 01CB0160 0C 4F 45 00                   DCD sub_454F0C
    //    .data.rel.ro : 01CB0164 E0 9A 90 00                   DCD sub_909AE0
    //    .data.rel.ro : 01CB0168 C0 A3 90 00                   DCD sub_90A3C0
    //    .data.rel.ro : 01CB016C CC C6 90 00                   DCD sub_90C6CC
    //    .data.rel.ro : 01CB0170 84 D6 29 00                   DCD nullsub_800
    //    .data.rel.ro : 01CB0174 88 D6 29 00                   DCD nullsub_801
    //    .data.rel.ro : 01CB0178 5C 96 90 00                   DCD sub_90965C
    //    .data.rel.ro : 01CB017C 24 AC 90 00                   DCD sub_90AC24
    //    .data.rel.ro : 01CB0180 DC A4 90 00                   DCD sub_90A4DC
    //    .data.rel.ro : 01CB0184 94 D6 29 00                   DCD sub_29D694
    //    .data.rel.ro : 01CB0188 1C CC 90 00                   DCD sub_90CC1C
    //    .data.rel.ro : 01CB018C AC D6 90 00                   DCD sub_90D6AC
    //    .data.rel.ro : 01CB0190 70 9E 90 00                   DCD sub_909E70
    //    .data.rel.ro : 01CB0194 18 A0 90 00                   DCD sub_90A018
    //    .data.rel.ro : 01CB0198 9C D6 29 00                   DCD nullsub_802
    //    .data.rel.ro : 01CB019C A0 D6 29 00                   DCD nullsub_803
    //    .data.rel.ro : 01CB01A0 40 A1 90 00                   DCD sub_90A140
    //    .data.rel.ro : 01CB01A4 84 D5 90 00                   DCD sub_90D584
    //    .data.rel.ro : 01CB01A8 9C BD 90 00                   DCD sub_90BD9C
    //    .data.rel.ro : 01CB01AC F0 FF FF FF                   DCD - 16; offset to this
    //    .data.rel.ro:01CB01B0 C4 01 CB 01                   DCD _ZTI10Projectile; `typeinfo for'Projectile
    //    .data.rel.ro:01CB01B4 54 79 90 00                   DCD sub_907954
    //    .data.rel.ro : 01CB01B8 70 79 90 00                   DCD sub_907970
    //    .data.rel.ro : 01CB01BC 34 B6 CE 00                   DCD sub_CEB634
    //    .data.rel.ro : 01CB01C0 C4 D6 29 00                   DCD sub_29D6C4
    //    .data.rel.ro : 01CB01C4; public Projectile :
    //.data.rel.ro : 01CB01C4;   public /* offset 0x0 */ ModularRealObject :
    //.data.rel.ro : 01CB01C4;     public /* offset 0x0 */ RealObject :
    //.data.rel.ro : 01CB01C4;       public /* offset 0x0 */ GameObject :
    //.data.rel.ro : 01CB01C4;         public /* offset 0x0 */ Sexy::RtObject,
    //    .data.rel.ro:01CB01C4;       public /* offset 0x10 */ Renderable
    //    .data.rel.ro:01CB01C4; `typeinfo for'Projectile
    //    .data.rel.ro:01CB01C4 D8 74 DF 01                   _ZTI10Projectile DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
    //    .data.rel.ro : 01CB01C4; DATA XREF : .data.rel.ro : 01C5EDDC↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C64810↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C6F158↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C6F870↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C7BFA8↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C8CFB0↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C94E60↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C963D4↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C9DA94↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01C9E258↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA0EC0↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA8E84↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CA9FCC↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CB00D4↑o
    //    .data.rel.ro : 01CB01C4;.data.rel.ro:01CB01B0↑o ...
    //    .data.rel.ro : 01CB01C4; reference to RTTI's type class
    //    .data.rel.ro:01CB01C8 B7 44 BA 01                   DCD _ZTS10Projectile; reference to type's name
    //    .data.rel.ro:01CB01CC C4 E1 C6 01                   DCD _ZTI17ModularRealObject; reference to parent's type name
    
    //其中偏移引用部分后面的
    /*.data.rel.ro:01CB00D4 C4 01 CB 01                   DCD _ZTI10Projectile                    ; `typeinfo for'Projectile
.data.rel.ro:01CB00D8 24 5A 90 00                   DCD sub_905A24*/
    //部分的.data.rel.ro:01CB00D8的01CB00D8即vftable = copyVFTable(getActualOffset(填入), 53);
    vftable = copyVFTable(getActualOffset(Customize_Projectile_GridItemRaiserProjectile_ProjectileVFTableAddr), 53);

    patchVFTable(vftable, (void*)GridItemRaiserProjectile::getRtClass, 0);

    patchVFTable(vftable, (void*)hkSpawnGridItem, 36);

    GridItemRaiserProjectile::getRtClass();

    LOGI("GridItemRaiserProjectile finish init");
}