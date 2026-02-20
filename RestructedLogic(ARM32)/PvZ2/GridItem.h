#pragma once
#include "BoardEntity.h"
#include "GridItemPropertySheet.h"
#include "EntityConditions.h"
#include "AttachedEffectManager.h"
#include "ObjectTypeDescriptor.h"
#include "../SexyTypes.h"
#include "../PvZ2/Board.h"
#include "../memUtils.h"


// the reflected fields are not checked!
// todo: fix the field order
class GridItemType : public ObjectTypeDescriptor
{
public:
	
	Sexy::SexyString GridItemClass;
	std::vector<Sexy::SexyString> ResourceGroups;
	std::vector<Sexy::SexyString> AudioGroups;
	Sexy::RtWeakPtr<GridItemPropertySheet> Properties;
};

class GridItem : public BoardEntity
{
public:
	//AttachedEffectManager m_attachedEffects
	int unk;
	GridItemConditionTracker m_conditionTracker;
	char unk2[76];
	Sexy::RtWeakPtr<GridItemType> m_type;
	float m_health;
	float m_healthMax;
	Sexy::Point m_gridLocation;
	Sexy::RtWeakPtr<GridItemPropertySheet> m_props;

	static GridItem* SpawnGridItemAt(const Sexy::SexyString& gridItemName, int gridPosX, int gridPosY)
	{
		typedef GridItem* (*func716690)(Board*, Sexy::SexyString, int, int);
		//寻找该偏移方法：
		//HEX搜索文本POPANIM_EFFECTS_LOSTCITY_PACK_BACKPACK
		//然后比如你跳转到了诸如"pack_poof.POPANIM_EFFECTS_LOSTCITY_PACK_BACKPACK"字样时候
		//把鼠标单击POPANIM_EFFECTS_LOSTCITY_PACK_BACKPACK的"P"上面，然后根据该偏移让ida pro跳转
		//这个时候，如下所示：
        /*.rodata:01B43496 50 4F 50 41 4E 49 4D 5F 45 46 + aPopanimEffects_74 DCB "POPANIM_EFFECTS_LOSTCITY_PACK_BACKPACK", 0
            .rodata : 01B43496 46 45 43 54 53 5F 4C 4F 53 54 + ; DATA XREF : sub_812864 + EC↑o
            .rodata : 01B43496 43 49 54 59 5F 50 41 43 4B 5F + ; sub_812864 + 11C↑o
            .rodata:01B43496 42 41 43 4B 50 41 43 4B 00;.text:off_812B60↑o*/

		//双击示例中的DATA XREF: sub_812864+EC↑o或者sub_812864+11C↑o位置
		//跳转后按F5，所得如下：
        //int __fastcall sub_812864(int a1)
        //{
        //    float v2; // s16
        //    unsigned int v3; // r1
        //    int v4; // r0
        //    bool v5; // cc
        //    float v6; // s0
        //    float v7; // s16
        //    _BOOL4 v8; // r0
        //    int v9; // r1
        //    bool v10; // zf
        //    int* v11; // r2
        //    int v12; // s0
        //    int v13; // r0
        //    int v14; // r0
        //    int v15; // r0
        //    int v16; // r6
        //    void(__fastcall * v17)(int, _DWORD*); // r7
        //    int v18; // r0
        //    int v19; // r4
        //    unsigned int v21; // [sp+18h] [bp-78h] BYREF
        //    unsigned int v22; // [sp+1Ch] [bp-74h]
        //    _DWORD v23[28]; // [sp+20h] [bp-70h] BYREF
        //    v2 = *(float*)(a1 + 20) + 40.0;
        //    sub_634354(&v21, *(float*)(a1 + 20) + 40.0, *(float*)(a1 + 24) - *(float*)(a1 + 28));
        //    v3 = v21;
        //    v4 = 0;
        //    v5 = v21 > 8;
        //    if (v21 <= 8)
        //        v5 = v22 > 4;
        //    if (!v5)
        //        v4 = (v21 << 6) + 232;
        //    v6 = (float)v4;
        //    v7 = (float)v4 - v2;
        //    if (v7 < 0.0)
        //        v3 = ++v21;
        //    if (v7 < 0.0)
        //        v6 = 64.0;
        //    if (v7 < 0.0)
        //        v7 = v7 + v6;
        //    v8 = sub_716FA4(*(_DWORD*)(dword_1D92A94 + 1728), v3, *(float*)&v22, 1, 0);
        //    v9 = *(_DWORD*)(a1 + 32) & 2;
        //    if (!v8 || (v10 = v9 == 0, v9 = 0, v10))
        //    {
        //        v23[1] = -1043857408;
        //        v11 = dword_812B6C;
        //        if (!v9)
        //            v11 = &dword_812B6C[1];
        //        v12 = *v11;
        //        v23[2] = 0;
        //        v23[0] = v12;
        //        sub_4547E4(
        //            a1,
        //            "pack_poof",
        //            (int)"POPANIM_EFFECTS_LOSTCITY_PACK_BACKPACK",
        //            (int)"animation3",
        //            (int)v23,
        //            (int)&word_61E68,
        //            1,
        //            0,
        //            2);
        //    }
        //    else
        //    {
        //        v13 = sub_29EC78();
        //        v14 = sub_63C558(v13, &v21);
        //        if (v14)
        //            sub_F4B680(v14, a1);
        //        v15 = sub_49F894(v21, v22);
        //        v16 = v15;
        //        if (v15)
        //        {
        //            v17 = *(void(__fastcall**)(int, _DWORD*))(*(_DWORD*)v15 + 144);
        //            v23[0] = a1;
        //            memset(&v23[1], 0, 0x40u);
        //            v17(v16, v23);
        //            sub_24DB98(&v23[13]);
        //            if (v23[10])
        //            {
        //                v23[11] = v23[10];
        //                operator delete((void*)v23[10]);
        //            }
        //            if (v23[7])
        //            {
        //                v23[8] = v23[7];
        //                operator delete((void*)v23[7]);
        //            }
        //            if (v23[4])
        //            {
        //                v23[5] = v23[4];
        //                operator delete((void*)v23[4]);
        //            }
        //        }
        //        v18 = *(_DWORD*)(dword_1D92A94 + 1728);
        //        HIWORD(v23[2]) = 0;
        //        strcpy((char*)v23 + 1, "backpack");
        //        LOBYTE(v23[0]) = 16;
        //        v19 = sub_716690(v18, (int)v23, v21, v22);
        //        if ((v23[0] & 1) != 0)
        //            operator delete((void*)v23[2]);
        //        sub_812B78(v19, LODWORD(v7) ^ 0x80000000, 0, 0);
        //    }
        //    return _stack_chk_guard - v23[19];
        //}
        
        //其中sub_716690即func716690 func_716690 = (func716690)getActualOffset(填入);
		func716690 func_716690 = (func716690)getActualOffset(GridItem_SpawnGridItemAtAddr);
		return func_716690(getBoard(), gridItemName, gridPosX, gridPosY);
	}
};

static_assert(sizeof(GridItem) == 0xF0);
static_assert(offsetof(GridItem, unk2) == 0x84);
static_assert(offsetof(GridItem, m_conditionTracker) == 0x68);