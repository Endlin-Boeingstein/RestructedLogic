#pragma once
#pragma once
#include "ModularRealObject.h"
#include "Component.h"

//寻找该偏移方法：
//HEX搜索文本POPANIM_EFFECTS_PRIZE_RAYS
//然后比如你跳转到了诸如"POPANIM_EFFECTS_PRIZE_RAYS......POPANIM_EFFECTS_PRIZE_TWINKLE"字样时候
//把鼠标单击POPANIM_EFFECTS_PRIZE_RAYS的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01ADE710 50 4F 50 41 4E 49 4D 5F 45 46 + aPopanimEffects_46 DCB "POPANIM_EFFECTS_PRIZE_RAYS", 0
//.rodata : 01ADE710 46 45 43 54 53 5F 50 52 49 5A + ; DATA XREF : sub_2ED9A8 + 224↑o
//.rodata : 01ADE710 45 5F 52 41 59 53 00; sub_2ED9A8 + 23C↑o
//.rodata:01ADE710;.text:off_2EDEE0↑o

//双击示例中DATA XREF: sub_2ED9A8+224↑o的位置
//跳转后按F5，所得如下：
//unsigned int __fastcall sub_2ED9A8(int a1, char a2)
//{
//    int* v4; // r5
//    int v5; // r0
//    int v6; // r7
//    int v7; // r6
//    int v8; // r0
//    int v9; // r0
//    int v10; // r7
//    int v11; // r6
//    int v12; // r0
//    int v13; // r0
//    int v14; // r6
//    int v15; // r5
//    int v16; // r0
//    int v17; // r0
//    int v18; // r5
//    int v19; // r0
//    int v20; // r6
//    int v21; // r5
//    int v22; // r7
//    int v23; // r0
//    int v24; // r0
//    int v25; // r5
//    int v26; // r7
//    int v27; // r0
//    int v28; // r0
//    unsigned int v30[2]; // [sp+0h] [bp-40h] BYREF
//    unsigned int v31[4]; // [sp+8h] [bp-38h] BYREF
//    unsigned int v32[10]; // [sp+18h] [bp-28h] BYREF
//
//    if (*(_DWORD*)(a1 + 120) != 1)
//    {
//        sub_2EC834(a1, 1);
//        sub_2EDEEC(a1);
//        *(_DWORD*)(a1 + 112) = *(_DWORD*)(a1 + 112) & 0xFFFFFFDD | (2 * (a2 & 1));
//        v4 = off_1D2A050;
//        v5 = (*(int(__fastcall**)(int*, int (*)()))(*off_1D2A050 + 12))(off_1D2A050, nullsub_287);
//        sub_2F1558(v4, nullsub_287, v5, a1);
//        v6 = sub_10D99A4();
//        sub_10DFA5C((int)v31, v6, a1 + 104);
//        v7 = 0;
//        if (!sub_10C8C60(v31))
//        {
//            v8 = sub_10C8B64(v31);
//            v9 = sub_10DF644(v6, v8);
//            if (v9)
//                v7 = sub_10DB9C0(v9, v31);
//        }
//        sub_10C8B38(v31);
//        if (*(_BYTE*)(v7 + 192) && sub_279198(a1 + 232))
//        {
//            v10 = sub_10D99A4();
//            sub_10DFA5C((int)v31, v10, a1 + 232);
//            v11 = 0;
//            if (!sub_10C8C60(v31))
//            {
//                v12 = sub_10C8B64(v31);
//                v13 = sub_10DF644(v10, v12);
//                if (v13)
//                    v11 = sub_10DB9C0(v13, v31);
//            }
//            sub_10C8B38(v31);
//            sub_53F498(v11);
//        }
//        if ((*(_BYTE*)(a1 + 113) & 1) != 0)
//        {
//            v14 = sub_10D99A4();
//            sub_10DFA5C((int)v31, v14, a1 + 104);
//            v15 = 0;
//            if (!sub_10C8C60(v31))
//            {
//                v16 = sub_10C8B64(v31);
//                v17 = sub_10DF644(v14, v16);
//                if (v17)
//                    v15 = sub_10DB9C0(v17, v31);
//            }
//            sub_10C8B38(v31);
//            if (*(_BYTE*)(v15 + 192))
//            {
//                v18 = *(_DWORD*)(dword_1D92A94 + 1728);
//                v19 = sub_E54A84();
//                v20 = sub_716354(v18, v19);
//                v31[2] = operator new(0x20u);
//                v31[0] = 33;
//                v31[1] = 26;
//                strcpy((char*)v31[2], "POPANIM_EFFECTS_PRIZE_RAYS");
//                sub_C9B7D4(v32, v31);
//                if ((v31[0] & 1) != 0)
//                    operator delete((void*)v31[2]);
//                v21 = sub_10D99A4();
//                sub_10DFA5C((int)v31, v21, (int)v32);
//                v22 = 0;
//                if (!sub_10C8C60(v31))
//                {
//                    v23 = sub_10C8B64(v31);
//                    v24 = sub_10DF644(v21, v23);
//                    if (v24)
//                        v22 = sub_10DB9C0(v24, v31);
//                }
//                sub_10C8B38(v31);
//                sub_E56188(v20, v22, 0);
//                sub_E56260(v20, 1);
//                LOBYTE(v31[0]) = 18;
//                HIBYTE(v31[2]) = 0;
//                strcpy((char*)v31 + 1, "animation");
//                BYTE2(v31[2]) = 0;
//                sub_E56504(v20, v31, 2139095039, 0);
//                if ((v31[0] & 1) != 0)
//                    operator delete((void*)v31[2]);
//                v25 = sub_10D99A4();
//                sub_10DFA5C((int)v31, v25, v20 + 136);
//                v26 = 0;
//                if (!sub_10C8C60(v31))
//                {
//                    v27 = sub_10C8B64(v31);
//                    v28 = sub_10DF644(v25, v27);
//                    if (v28)
//                        v26 = sub_10DB9C0(v28, v31);
//                }
//                sub_10C8B38(v31);
//                sub_65FA9C(v26, 1);
//                if (v20)
//                {
//                    sub_10C8A34(v30);
//                    sub_10C8BF8(v30, v20 + 8);
//                    sub_10C8A84(v31, v30);
//                    sub_10C8BB0(a1 + 240, v31);
//                    sub_10C8B38(v31);
//                    sub_10C8B38(v30);
//                    v31[1] = 0;
//                    v31[0] = 0;
//                    sub_735C30(v20, a1, v31, -2);
//                    sub_735DA0(v20, 1);
//                    (*(void(__fastcall**)(int, _DWORD))(*(_DWORD*)v20 + 56))(v20, 0);
//                }
//                sub_10C8B38(v32);
//            }
//        }
//    }
//    return _stack_chk_guard - v32[3];
//}

//其中sub_53F498是OFFSET_BOARDENTITY_DIE
#define OFFSET_BOARDENTITY_DIE BoardEntity_OFFSET_BOARDENTITY_DIEAddr

class ComponentRunner;
class BoardEntity : public ModularRealObject
{
public:
	int m_level;
	int m_unk0x3C;
	Rect m_collisionRect;
	int m_boardEntityFlags;
	int m_unk0x54;
	Sexy::RtWeakPtr<ComponentRunner> m_componentRunner;
	float m_createdTime;

	void Die() {
		typedef void (*DieFunc)(BoardEntity*);
		((DieFunc)getActualOffset(OFFSET_BOARDENTITY_DIE))(this);
	}

	void GetGridCoords(int* res) {
		res[0] = (this->m_position.mX - 200.0) / 64.0;
		res[1] = (this->m_position.mY - 160.0) / 76.0;
	}

	virtual void Function35() {};
	virtual void Function36() {};
	virtual void Function37() {};
	virtual void Function38() {};
	virtual void Function39() {};
	virtual void Function40() {};
	virtual void Function41() {};
	virtual void Function42() {};
	virtual void Function43() {};
	virtual void Function44() {};
	virtual void Function45() {};
	virtual void Function46() {};
	virtual void Function47() {};
	virtual Sexy::SexyString* GetTypeName() {};
	virtual void OnSpawn() {};
};

class BoardEntityStat
{
public:
	int Type;
	int Value;
};