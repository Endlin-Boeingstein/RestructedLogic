#pragma once
#include "../memUtils.h"
#include "../VersionAddresses.h"
//寻找该偏移方法：
//使用Hex搜索imitater，直到出现诸如"imitater.Incorrect Plant Count Found Vs Level Preset List."字样时
//把鼠标单击imitater的"i"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B3CC86 69 6D 69 74 61 74 65 72 00    aImitater_0 DCB "imitater", 0; DATA XREF : sub_3E6928 + 98↑o
//.rodata : 01B3CC86; sub_3E6928 + 9C↑o
//.rodata:01B3CC86;.text:off_3E6E00↑o
//.rodata : 01B3CC86; sub_4ECA3C + 834↑o
//.rodata:01B3CC86; sub_4ECA3C + 83C↑o
//.rodata:01B3CC86;.text:off_4ED7C4↑o
//.rodata : 01B3CC86; sub_59634C + 1B8↑o
//.rodata:01B3CC86; sub_59634C + 1C0↑o
//.rodata:01B3CC86;.text:off_596D00↑o
//.rodata : 01B3CC86; sub_6057E0 + 138↑o
//.rodata:01B3CC86; sub_6057E0 + 14C↑o
//.rodata:01B3CC86;.text:off_6065F0↑o
//.rodata : 01B3CC86; sub_609CC8 + 224↑o
//.rodata:01B3CC86; sub_609CC8 + 22C↑o
//.rodata:01B3CC86;.text:off_60A19C↑o ...

//双击从下往上数的第三个.text:的上方俩同名函数其中之一（sub_59634C+1B8↑o或sub_59634C+1C0↑o）
//跳转后向下翻（不能按F5反编译，因为这个函数不同版本不一样）
//直到你翻到：
//.text:005965EC;   try {
//	.text:005965EC 05 00 A0 E1                   MOV             R0, R5
//		.text : 005965F0 01 10 A0 E3                   MOV             R1, #1
//		.text:005965F4 01 20 A0 E3                   MOV             R2, #1
//		.text:005965F8 04 80 8D E5                   STR             R8, [SP, #0x98 + var_94]
//		.text:005965FC 6E D9 F2 EB                   BL              sub_24CBBC
//		.text:005965FC
//		.text:00596600 00 90 A0 E1                   MOV             R9, R0
//		.text:00596604 00 00 99 E5                   LDR             R0, [R9]
//		.text:00596608 80 80 90 E5                   LDR             R8, [R0, #0x80]
//		.text:0059660C 48 00 8D E2                   ADD             R0, SP, #0x98 + var_50
//		.text:00596610 00 20 A0 E3                   MOV             R2, #0
//		.text:00596614 00 30 A0 E3                   MOV             R3, #0
//		.text:00596618 00 60 A0 E3                   MOV             R6, #0
//		.text:0059661C 08 C9 2C EB                   BL              sub_10C8A44
//		.text:0059661C;
//} // starts at 5965EC
//.text:0059661C
//.text:00596620 D0 06 9F E5                   LDR             R0, =(_ZTVN4Sexy9Delegate3IRKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_iEE - 0x596630); `vtable for'Sexy::Delegate3<std::string const&,std::string const&,int>
//.text:00596624 58 60 8D E5                   STR             R6, [SP, #0x98 + var_40]
//.text:00596628 00 00 8F E0                   ADD             R0, PC, R0; `vtable for'Sexy::Delegate3<std::string const&,std::string const&,int>

//那么双击示例中的BL              sub_24CBBC位置（看清楚是哪个BL，别看错了！！！）
//你就会发现，大多数我们要找的偏移函数都在那里面
//整体示例如下：
//int __fastcall sub_24CBBC(int a1, int a2, int a3)
//{
//	char* v4; // r0
//	int v5; // r5
//	int* v6; // r8
//	int v7; // r4
//	int v8; // r0
//	int v9; // r0
//	int v10; // r5
//	int(__fastcall * v11)(int, int); // r4
//	int v12; // r0
//	void(__fastcall * v13)(int, _DWORD); // r4
//	int v14; // r0
//	void(__fastcall * v15)(int, char*); // r4
//	int v16; // r0
//	int v17; // r4
//	void* v18; // r6
//	int v19; // r6
//	int v20; // r0
//	int v23; // [sp+8h] [bp-58h] BYREF
//	int v24; // [sp+Ch] [bp-54h]
//	void* v25; // [sp+10h] [bp-50h]
//	char v26[8]; // [sp+18h] [bp-48h] BYREF
//	char v27[12]; // [sp+20h] [bp-40h] BYREF
//	char v28[8]; // [sp+2Ch] [bp-34h] BYREF
//	void* v29; // [sp+34h] [bp-2Ch]
//	char v30[8]; // [sp+38h] [bp-28h] BYREF
//
//	if (a2)
//		sub_9493D8(a1 + 88);
//	if ((*(_BYTE*)(a1 + 76) & 1) != 0)
//		v4 = *(char**)(a1 + 84);
//	else
//		v4 = (char*)(a1 + 77);
//	v5 = sub_1250938(v4);
//	sub_C9B7D4(v30, a1 + 64);
//	v6 = (int*)sub_10D99A4();
//	sub_10DFA5C(&v23, v6, v30);
//	v7 = 0;
//	if (!sub_10C8C60(&v23))
//	{
//		v8 = sub_10C8B64(&v23);
//		v9 = sub_10DF644(v6, v8);
//		if (v9)
//			v7 = sub_10DB9C0(v9, &v23);
//	}
//	sub_10C8B38(&v23);
//	v10 = sub_65A0C8(v7, v5);
//	if (v10)
//	{
//		v11 = *(int(__fastcall**)(int, int))(*(_DWORD*)v10 + 16);
//		v12 = sub_F57DC0();
//		if (v11(v10, v12))
//		{
//			v13 = *(void(__fastcall**)(int, _DWORD))(*(_DWORD*)v10 + 268);
//			v14 = sub_24CF10(a1, 1);
//			v13(v10, *(_DWORD*)(v14 + 108));
//			(*(void(__fastcall**)(int, _DWORD))(*(_DWORD*)v10 + 200))(v10, *(_DWORD*)(a1 + 128));
//			sub_24CFAC(v28, a1 + 76);
//			sub_56B5E8(v10, v28);
//			if ((v28[0] & 1) != 0)
//				operator delete(v29);
//			v15 = *(void(__fastcall**)(int, char*))(*(_DWORD*)v10 + 208);
//			v16 = sub_24CF10(a1, 1);
//			sub_24D058(v27, v16 + 280);
//			v15(v10, v27);
//			sub_24D0C0(v27);
//		}
//	}
//	v17 = sub_24CF10(a1, 1);
//	sub_56AEC8(v10, v17 + 232);
//	sub_56AED8(v10);
//	if (a3)
//	{
//		v25 = 0;
//		v24 = 0;
//		v23 = 0;
//		v18 = (void*)operator new(0x20u);
//		v23 = 33;
//		v25 = v18;
//		v24 = 19;
//		strcpy((char*)v18, "POPANIM_MISSING_PAM");
//		sub_C9B7D4(v26, &v23);
//		v19 = sub_24D110(v30, v26);
//		sub_10C8B38(v26);
//		if ((v23 & 1) != 0)
//			operator delete(v25);
//		if (v19)
//			sub_65FC34(v10, 1);
//	}
//	v20 = sub_109B0F4(
//		*(float*)(v17 + 40) - (float)(*(float*)(v17 + 40) * *(float*)(v17 + 44)),
//		*(float*)(v17 + 40) + (float)(*(float*)(v17 + 40) * *(float*)(v17 + 44)));
//	sub_56B034(v10, v20);
//	sub_10C8B38(v30);
//	return v10;
//}

//然后你就知道接下来按照示例的函数位置你会去找什么了(但凡知道偏移是啥都不会把sub_填上去)
//sub_10D99A4是OFFSET_RTWEAKPTR_GETREGISTRY
#define OFFSET_RTWEAKPTR_GETREGISTRY RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY
//sub_10DFA5C是OFFSET_RTWEAKPTR_COPYWEAKPTR
#define OFFSET_RTWEAKPTR_COPYWEAKPTR RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR
//sub_10DF644是OFFSET_RTWEAKPTR_GETTABLEOFTYPE
#define OFFSET_RTWEAKPTR_GETTABLEOFTYPE RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE
//sub_24D110是OFFSET_RTWEAKPTR_EQUALS
#define OFFSET_RTWEAKPTR_EQUALS RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS
//接下来几个还需要继续找
//使用Hex搜索UIWorldMapBackButton，直到出现诸如"UIWorldMapBackButton....UIWorldMapAlmanacButton"字样时
//把鼠标单击UIWorldMapBackButton的"U"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AE4048 55 49 57 6F 72 6C 64 4D 61 70 + aUiworldmapback DCB "UIWorldMapBackButton", 0
//.rodata : 01AE4048 42 61 63 6B 42 75 74 74 6F 6E + ; DATA XREF : sub_3AA074 + 58↑o
//.rodata : 01AE4048 00; sub_3AA074 + 74↑o
//.rodata:01AE4048;.text:off_3AA498↑o
//.rodata : 01AE4048; sub_42F33C + 28↑o
//.rodata:01AE4048; sub_42F33C + 40↑o
//.rodata:01AE4048;.text:off_42F400↑o
//.rodata : 01AE4048; sub_42F408 + 28↑o
//.rodata:01AE4048; sub_42F408 + 40↑o
//.rodata:01AE4048;.text:off_42F4CC↑o
//.rodata : 01AE4048; sub_42F668 + 3A0↑o
//.rodata:01AE4048; sub_42F668 + 3B8↑o
//.rodata:01AE4048;.text:off_42FB10↑o
//.rodata : 01AE4048; sub_441418 + C0↑o
//.rodata:01AE4048; sub_441418 + D8↑o
//.rodata:01AE4048; sub_441418 + 1D8↑o ...

//双击示例中的sub_441418+C0↑o或sub_441418+D8↑o或sub_441418+1D8↑o位置
//跳转后按F5，所得如下：
//int __fastcall sub_441418(int a1)
//{
//	_BYTE* v2; // r0
//	int v3; // r5
//	int v4; // r6
//	int* v5; // r0
//	int v6; // r6
//	int v7; // r0
//	int v8; // r0
//	int v10; // r0
//	bool v11; // zf
//	_BYTE* v12; // r0
//	int v13; // r4
//	int v14; // r0
//	int v15; // r2
//	_DWORD v16[2]; // [sp+0h] [bp-30h] BYREF
//	int v17[2]; // [sp+8h] [bp-28h] BYREF
//	int v18; // [sp+10h] [bp-20h] BYREF
//	int v19; // [sp+14h] [bp-1Ch]
//	void* v20; // [sp+18h] [bp-18h]
//
//	if (*(float*)(a1 + 696) != 3.4028e38)
//	{
//		v2 = (_BYTE*)(a1 + 545);
//		goto LABEL_3;
//	}
//	v2 = (_BYTE*)(a1 + 545);
//	if (!*(_BYTE*)(a1 + 531))
//	{
//	LABEL_3:
//		v3 = 1;
//		if (!*v2)
//		{
//			v4 = operator new(8u);
//			sub_1250128((_DWORD*)v4);
//			*(_WORD*)(v4 + 4) = 0;
//			v18 = v4;
//			*(_DWORD*)v4 = off_1C5D138;
//			v5 = *(int**)(a1 + 536);
//			if ((unsigned int)v5 >= *(_DWORD*)(a1 + 540))
//			{
//				sub_4523C8(a1 + 532, &v18);
//			}
//			else
//			{
//				*v5 = v4;
//				*(_DWORD*)(a1 + 536) += 4;
//			}
//		}
//		return v3;
//	}
//	v6 = 0;
//	*v2 = 0;
//	v20 = (void*)operator new(0x20u);
//	v18 = 33;
//	v19 = 20;
//	strcpy((char*)v20, "UIWorldMapBackButton");
//	v7 = sub_2614E8(&v18);
//	if ((*(_BYTE*)(v7 + 100) & 4) != 0)
//		v6 = sub_1079B7C(v7 + 20) ^ 1;
//	if ((v18 & 1) != 0)
//		operator delete(v20);
//	v3 = 1;
//	if (v6)
//	{
//		if (*(_BYTE*)(*(_DWORD*)(a1 + 404) + 64))
//		{
//			v8 = sub_2580B8();
//			sub_DAC748(*(_DWORD*)(v8 + 88));
//			sub_438AAC(*(_DWORD*)(a1 + 404));
//		}
//		else
//		{
//			v10 = *(_DWORD*)(a1 + 276);
//			v11 = v10 == 0;
//			if (v10)
//				v11 = *(_BYTE*)(v10 + 80) == 0;
//			if (v11 || !sub_279278())
//			{
//				if (!sub_3876C0(*(_DWORD*)(a1 + 408)))
//				{
//					v12 = *(_BYTE**)(a1 + 412);
//					if (!v12[88] || !(*(int(__fastcall**)(_BYTE*))(*(_DWORD*)v12 + 56))(v12))
//					{
//						v20 = (void*)operator new(0x20u);
//						v18 = 33;
//						v19 = 20;
//						strcpy((char*)v20, "UIWorldMapBackButton");
//						v13 = sub_2614E8(&v18);
//						if ((v18 & 1) != 0)
//							operator delete(v20);
//						return (*(int(__fastcall**)(int))(*(_DWORD*)v13 + 192))(v13);
//					}
//				}
//			}
//			else
//			{
//				v14 = *(_DWORD*)(a1 + 276);
//				v17[1] = 0;
//				v17[0] = 0;
//				v3 = 1;
//				v15 = *(_DWORD*)(a1 + 40);
//				v16[0] = *(_DWORD*)(a1 + 36);
//				v16[1] = v15;
//				sub_277224(v14, v17, v16, 1);
//			}
//		}
//	}
//	return v3;
//}

//找到其中对应sub_277224的函数，双击进入
//所得如下所示：
//int __fastcall sub_277224(int a1, _DWORD* a2, _DWORD* a3, int a4)
//{
//	int v7; // r0
//	bool v8; // zf
//	int v10; // r4
//	int v11; // r5
//	int v12; // r8
//	int* v13; // r5
//	int v14; // r7
//	int v15; // r0
//	int v16; // r0
//	int v17; // r5
//	int v18; // r8
//	int* v19; // r5
//	int v20; // r7
//	int v21; // r0
//	int v22; // r0
//	int(__fastcall * v23)(int, int); // r5
//	int v24; // r0
//	int v25; // r5
//	int v26; // r5
//	int v27; // r0
//	int* v28; // r1
//	int v29; // r3
//	int v30; // r2
//	int v31; // r5
//	int v32; // r8
//	int v33; // r4
//	int v34; // r0
//	int v35[2]; // [sp+0h] [bp-60h] BYREF
//	char v36[8]; // [sp+8h] [bp-58h] BYREF
//	void* v37; // [sp+10h] [bp-50h]
//	char v38[8]; // [sp+14h] [bp-4Ch] BYREF
//	void* v39; // [sp+1Ch] [bp-44h]
//	char v40[8]; // [sp+20h] [bp-40h] BYREF
//	void* v41; // [sp+28h] [bp-38h]
//	char v42[8]; // [sp+30h] [bp-30h] BYREF
//	char v43[8]; // [sp+38h] [bp-28h] BYREF
//	int v44; // [sp+40h] [bp-20h]
//
//	v7 = *(_DWORD*)(a1 + 220);
//	if (v7)
//	{
//		v8 = *(_BYTE*)(v7 + 64) == 0;
//		if (!*(_BYTE*)(v7 + 64))
//			v8 = a4 == 0;
//		if (!v8)
//			return sub_438AAC(v7);
//		sub_277868(v43);
//		v10 = 6;
//		if (sub_279198(v43))
//		{
//			v11 = sub_9CDA38();
//			v12 = sub_9CE5C8(v11, 28);
//			sub_10C8A34(v42);
//			sub_10C8BF8(v42, v11 + 72);
//			v13 = (int*)sub_10D99A4();
//			sub_10DFA5C((int)v40, (int)v13, (int)v42);
//			v14 = 0;
//			if (!sub_10C8C60(v40))
//			{
//				v15 = sub_10C8B64(v40);
//				v16 = sub_10DF644(v13, v15);
//				if (v16)
//					v14 = sub_10DB9C0(v16, v40);
//			}
//			sub_10C8B38(v40);
//			v17 = sub_3DAB10(v14, v12);
//			sub_10C8B38(v42);
//			v18 = sub_16FE3E0(1440, 0, *(_DWORD*)(v17 + 20), *(int*)(v17 + 20) >> 31);
//			v19 = (int*)sub_10D99A4();
//			sub_10DFA5C((int)v40, (int)v19, (int)v43);
//			v20 = 0;
//			if (!sub_10C8C60(v40))
//			{
//				v21 = sub_10C8B64(v40);
//				v22 = sub_10DF644(v19, v21);
//				if (v22)
//					v20 = sub_10DB9C0(v22, v40);
//			}
//			sub_10C8B38(v40);
//			if (v20)
//			{
//				v23 = *(int(__fastcall**)(int, int))(*(_DWORD*)v20 + 16);
//				v24 = sub_30CFC8();
//				if (v23(v20, v24))
//					v10 = sub_30E31C(v20) * v18;
//			}
//		}
//		sub_438AE8(*(_DWORD*)(a1 + 220), 2);
//		v25 = *(_DWORD*)(a1 + 220);
//		sub_109A024(v40, &unk_1B6C9DC);
//		sub_27B448(v25 + 128, v40);
//		if ((v40[0] & 1) != 0)
//			operator delete(v41);
//		sub_109A024(v40, &unk_1B6CA4C);
//		sub_10C5ED0(v36, &off_1B6C918, v10);
//		sub_109BB68(v38, v40, &unk_1B6C8F4, v36);
//		if ((v36[0] & 1) != 0)
//			operator delete(v37);
//		sub_27B448(*(_DWORD*)(a1 + 220) + 140, v38);
//		sub_4392B4(*(_DWORD*)(a1 + 220));
//		v26 = *(_DWORD*)(a1 + 36);
//		v27 = sub_36A1E0(dword_1D9CA24, 10);
//		v28 = *(int**)(a1 + 220);
//		v29 = *v28;
//		v30 = *(_DWORD*)(dword_1D92A94 + 1312);
//		v28[9] = 0;
//		v28[10] = 0;
//		v28[11] = v26 - v27;
//		v28[12] = v30;
//		(*(void(__fastcall**)(int*))(v29 + 28))(v28);
//		v31 = *(_DWORD*)(a1 + 220);
//		*(_DWORD*)(v31 + 8) = 1;
//		v32 = a3[1];
//		v33 = a2[1];
//		v35[0] = *a3 + *a2;
//		v35[1] = v32 + v33 + sub_36A1E0(dword_1D9CA24, 50);
//		sub_438AB8(v31, v35);
//		v34 = *(_DWORD*)(dword_1D92A94 + 1884);
//		if (v34)
//			sub_43EC0C(v34);
//		sub_438AD4(*(_DWORD*)(a1 + 220));
//		if ((v38[0] & 1) != 0)
//			operator delete(v39);
//		if ((v40[0] & 1) != 0)
//			operator delete(v41);
//		sub_10C8B38(v43);
//	}
//	return _stack_chk_guard - v44;
//}

//sub_279198是OFFSET_RTWEAKPTR_ISVALIDPTR
#define OFFSET_RTWEAKPTR_ISVALIDPTR RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR
//sub_10DB9C0是OFFSET_RTWEAKPTR_RESOLVE
#define OFFSET_RTWEAKPTR_RESOLVE RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE

//使用Hex搜索Play_UI_Menu_Buy_Coins_Press，直到出现诸如"Play_UI_Menu_Buy_Coins_Press....Play_UI_Menu_Buy_Coins_Release"字样时
//把鼠标单击Play_UI_Menu_Buy_Coins_Press的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AD9E90 50 6C 61 79 5F 55 49 5F 4D 65 + aPlayUiMenuBuyC DCB "Play_UI_Menu_Buy_Coins_Press", 0
//.rodata : 01AD9E90 6E 75 5F 42 75 79 5F 43 6F 69 + ; DATA XREF : sub_255DBC + 9C↑o
//.rodata : 01AD9E90 6E 73 5F 50 72 65 73 73 00; sub_255DBC + B0↑o
//.rodata:01AD9E90;.text:off_255FC0↑o
//.rodata : 01AD9E90; sub_255FCC + 7A0↑o
//.rodata:01AD9E90; sub_255FCC + 7A4↑o
//.rodata:01AD9E90; sub_255FCC:loc_256794↑o
//.rodata : 01AD9E90; sub_255FCC + 7CC↑o
//.rodata:01AD9E90;.text:off_256A1C↑o
//.rodata : 01AD9E90;.text:off_256A24↑o
//.rodata : 01AD9E90; sub_2573EC + B8↑o
//.rodata:01AD9E90; sub_2573EC + C0↑o
//.rodata:01AD9E90;.text:off_2577C0↑o

//双击示例中的DATA XREF: sub_255DBC+9C↑o或sub_255DBC+B0↑o位置
//跳转后按F5，所得如下：
//int __fastcall sub_255DBC(int a1)
//{
//	char* v2; // r6
//	char* v3; // r6
//	__int64 v5; // [sp+0h] [bp-28h] BYREF
//
//	sub_257B48(&v5, &unk_1D7C318);
//	sub_10C8A34((_DWORD*)a1);
//	sub_10C8BF8((unsigned int*)a1, &v5);
//	sub_10C8B38((unsigned int*)&v5);
//	sub_257B48(&v5, &unk_1D7C330);
//	sub_10C8A34((_DWORD*)(a1 + 8));
//	sub_10C8BF8((unsigned int*)(a1 + 8), &v5);
//	sub_10C8B38((unsigned int*)&v5);
//	*(_DWORD*)(a1 + 16) = 0;
//	*(_DWORD*)(a1 + 20) = 0;
//	*(_DWORD*)(a1 + 24) = 0;
//	v2 = (char*)operator new(0x20u);
//	*(_DWORD*)(a1 + 16) = 33;
//	*(_DWORD*)(a1 + 20) = 28;
//	*(_DWORD*)(a1 + 24) = v2;
//	strcpy(v2, "Play_UI_Menu_Buy_Coins_Press");
//	*(_DWORD*)(a1 + 28) = 0;
//	*(_DWORD*)(a1 + 32) = 0;
//	*(_DWORD*)(a1 + 36) = 0;
//	v3 = (char*)operator new(0x20u);
//	*(_DWORD*)(a1 + 28) = 33;
//	*(_DWORD*)(a1 + 32) = 30;
//	*(_DWORD*)(a1 + 36) = v3;
//	strcpy(v3, "Play_UI_Menu_Buy_Coins_Release");
//	*(_DWORD*)(a1 + 44) = 0;
//	*(_BYTE*)(a1 + 40) = 0;
//	*(_DWORD*)(a1 + 48) = 0;
//	*(_DWORD*)(a1 + 52) = 0;
//	sub_10C8A34((_DWORD*)(a1 + 56));
//	return a1;
//}

//其中sub_10C8BF8是OFFSET_RTWEAKPTR_FROMOTHER
#define OFFSET_RTWEAKPTR_FROMOTHER RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER
//使用Hex搜索IMAGE_MISSING_IMAGE，直到出现诸如"IMAGE_MISSING_IMAGE.....Play_UI_Menu_Buy_Coins_Press"字样时
//把鼠标单击IMAGE_MISSING_IMAGE的"I"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AD9E78 49 4D 41 47 45 5F 4D 49 53 53 + aImageMissingIm DCB "IMAGE_MISSING_IMAGE", 0
//.rodata : 01AD9E78 49 4E 47 5F 49 4D 41 47 45 00; DATA XREF : sub_255A48 + 180↑o
//.rodata : 01AD9E78; sub_255A48 + 198↑o
//.rodata:01AD9E78;.text:off_255CF0↑o
//.rodata : 01AD9E78; sub_257CB4 + 58↑o
//.rodata:01AD9E78; sub_257CB4 + 70↑o
//.rodata:01AD9E78;.text:off_257DD4↑o
//.rodata : 01AD9E78; sub_69B38C + 1C4↑o
//.rodata:01AD9E78; sub_69B38C + 1DC↑o
//.rodata:01AD9E78;.text:off_69BBF0↑o
//.rodata : 01AD9E78; sub_C9B4AC + 6C↑o
//.rodata:01AD9E78; sub_C9B4AC + 84↑o
//.rodata:01AD9E78;.text:off_C9B5F0↑o
//.rodata : 01AD9E78; sub_C9B5FC + C8↑o
//.rodata:01AD9E78; sub_C9B5FC + E0↑o
//.rodata:01AD9E78;.text:off_C9B7C8↑o

//双击示例中那个DATA XREF: sub_255A48+180↑o位置的函数
//按F5，你会发现整体长这样：
//int __fastcall sub_255A48(_QWORD* a1, unsigned __int8* a2)
//{
//	int v4; // r1
//	unsigned __int8* v5; // r9
//	unsigned int v6; // r0
//	unsigned __int8* v7; // r4
//	unsigned __int8* v8; // r0
//	unsigned __int8* v9; // r0
//	unsigned __int8* v10; // r7
//	bool v11; // zf
//	int* v12; // r6
//	int v13; // r5
//	int v14; // r0
//	int v15; // r0
//	int v16; // r5
//	void* v17; // r6
//	int v19; // [sp+0h] [bp-38h] BYREF
//	int v20; // [sp+4h] [bp-34h]
//	void* v21; // [sp+8h] [bp-30h]
//	char v22[12]; // [sp+10h] [bp-28h] BYREF
//	int v23; // [sp+1Ch] [bp-1Ch]
//
//	sub_10C8A34(a1);
//	v4 = *((_DWORD*)a2 + 1);
//	v5 = (unsigned __int8*)*((_DWORD*)a2 + 2);
//	v6 = *a2;
//	if ((v6 & 1) == 0)
//	{
//		v5 = a2 + 1;
//		v4 = v6 >> 1;
//	}
//	if (v4 >= 9)
//	{
//		v7 = &v5[v4];
//		v8 = v5;
//		do
//		{
//			v9 = (unsigned __int8*)memchr(v8, 73, v4 - 8);
//			v10 = v9;
//			if (!v9)
//				break;
//			if (!memcmp(v9, "IMAGE_UI_", 9u))
//			{
//				v11 = v10 == v7;
//				if (v10 != v7)
//					v11 = v10 - v5 == -1;
//				if (!v11)
//				{
//					sub_5DC47C(&v19, dword_1D92A94, a2);
//					sub_10C8BB0(a1, (int)&v19);
//					goto LABEL_14;
//				}
//				break;
//			}
//			v8 = v10 + 1;
//			v4 = v7 - (v10 + 1);
//		} while (v4 >= 9);
//	}
//	sub_5DC38C(&v19, dword_1D92A94, a2, 0);
//	sub_10C8BB0(a1, (int)&v19);
//LABEL_14:
//	sub_10C8B38((int)&v19);
//	if (!sub_10C8C50(a1))
//		goto LABEL_19;
//	v12 = (int*)sub_10D99A4();
//	sub_10DFA5C((int)&v19, (int)v12, (int)a1);
//	v13 = 0;
//	if (!sub_10C8C60(&v19))
//	{
//		v14 = sub_10C8B64(&v19);
//		v15 = sub_10DF644(v12, v14);
//		if (v15)
//			v13 = sub_10DB9C0(v15, &v19);
//	}
//	sub_10C8B38((int)&v19);
//	if (!v13)
//	{
//	LABEL_19:
//		v21 = 0;
//		v20 = 0;
//		v19 = 0;
//		v16 = dword_1D92A94;
//		v17 = (void*)operator new(0x20u);
//		v19 = 33;
//		v21 = v17;
//		v20 = 19;
//		strcpy((char*)v17, "IMAGE_MISSING_IMAGE");
//		sub_5DC38C(v22, v16, &v19, 0);
//		sub_10C8BB0(a1, (int)v22);
//		sub_10C8B38((int)v22);
//		if ((v19 & 1) != 0)
//			operator delete(v21);
//	}
//	return _stack_chk_guard - v23;
//}

//根据这个函数，可以找到sub_10C8BB0是OFFSET_RTWEAKPTR_MOVE
#define OFFSET_RTWEAKPTR_MOVE RtWeakPtr_OFFSET_RTWEAKPTR_MOVE
//然后双击进入sub_10C8BB0，发现sub_10C88C8是OFFSET_RTWEAKPTR_SETWEAKPTR
#define OFFSET_RTWEAKPTR_SETWEAKPTR RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR

namespace Sexy
{
	template <typename T>
	class RtWeakPtr
	{
	public:

		RtWeakPtr()
		{
			data1 = NULL;
			data2 = NULL;
		}

		~RtWeakPtr()
		{
			typedef void(*func)(RtWeakPtr*, int64_t);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_SETWEAKPTR);
			pSetValue(this, 0LL);
		}

		RtWeakPtr(RtWeakPtr* other) {
			data1 = NULL;
			data2 = NULL;

			this->FromOther(other);
		}

		RtWeakPtr(RtWeakPtr&& other) {
			data1 = NULL;
			data2 = NULL;

			typedef void(*func)(RtWeakPtr*, RtWeakPtr*);
			func pFunc = (func)getActualOffset(OFFSET_RTWEAKPTR_MOVE);
			pFunc(this, &other);
		}

		RtWeakPtr(const RtWeakPtr& other) {
			data1 = NULL;
			data2 = NULL;

			typedef void(*func)(RtWeakPtr*, const RtWeakPtr&);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);
		}

		bool operator==(const RtWeakPtr<T>& other) const
		{
			typedef bool(*eqOp)(RtWeakPtr<T>*, RtWeakPtr<T>*);
			eqOp pEqOp = (eqOp)getActualOffset(OFFSET_RTWEAKPTR_EQUALS);
			return pEqOp(this, &other);
		}

		bool operator==(RtWeakPtr<T>& other)
		{
			typedef bool(*eqOp)(RtWeakPtr<T>*, RtWeakPtr<T>*);
			eqOp pEqOp = (eqOp)getActualOffset(OFFSET_RTWEAKPTR_EQUALS);
			return pEqOp(this, &other);
		}


		RtWeakPtr<T>& operator=(const RtWeakPtr<T>& other)
		{
			typedef void(*func)(RtWeakPtr*, const RtWeakPtr&);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);

			// This is how I've been using the assignment operator so far
			data1 = other.data1;
			data2 = other.data2;

			return *this;
		}

		RtWeakPtr<T>& operator=(RtWeakPtr<T>& other)
		{
			typedef void(*func)(RtWeakPtr*, RtWeakPtr&);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);
		}

		RtWeakPtr<T>& operator=(RtWeakPtr<T>* other)
		{
			typedef void(*func)(RtWeakPtr*, RtWeakPtr*);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);
		}

		RtWeakPtr<T>& operator=(const RtWeakPtr<T>* other)
		{
			typedef void(*func)(RtWeakPtr*, RtWeakPtr*);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);
		}

		bool Equals(RtWeakPtr<T>* other) {
			typedef bool(*eqOp)(RtWeakPtr<T>*, RtWeakPtr<T>*);
			eqOp pEqOp = (eqOp)getActualOffset(OFFSET_RTWEAKPTR_EQUALS);
			return pEqOp(this, other);
		}

		bool IsInvalid()
		{
			return data1 == NULL;
		}

		bool IsValid()
		{
			typedef bool(*func)(RtWeakPtr<T>*);
			func pFunc = (func)getActualOffset(OFFSET_RTWEAKPTR_ISVALIDPTR);
			return pFunc(this);
		}

		int TypeID()
		{
			return (this->data2 >> 0x11) & 0x3FFF;
		}

		int GetSomething()
		{
			return this->data2 >> 0x1F;
		}

		void FromOther(RtWeakPtr* other)
		{
			typedef void(*func)(RtWeakPtr*, RtWeakPtr*);
			func pSetValue = (func)getActualOffset(OFFSET_RTWEAKPTR_FROMOTHER);
			pSetValue(this, other);
		}

		// Get the object this points to, if valid.
		T* Get()
		{
			typedef void* (*getV8)();
			getV8 pGetRegistry = (getV8)getActualOffset(OFFSET_RTWEAKPTR_GETREGISTRY);

			void* registry = pGetRegistry();

			typedef void (*sub10CC81C)(RtWeakPtr*, void*, RtWeakPtr*);
			sub10CC81C pSub10CC81C = (sub10CC81C)getActualOffset(OFFSET_RTWEAKPTR_COPYWEAKPTR);

			RtWeakPtr<T> temp;
			pSub10CC81C(&temp, registry, this);

			T* retVal = NULL;
			if (!temp.IsInvalid())
			{

				int typeId = temp.TypeID();

				typedef void* (*sub10CC404)(void*, int);
				sub10CC404 pSub10CC404 = (sub10CC404)getActualOffset(OFFSET_RTWEAKPTR_GETTABLEOFTYPE);

				void* v11 = pSub10CC404(registry, typeId);
				if (v11)
				{
					// LOGI("Valid and is correct type");
					typedef T* (*sub10C8780)(void*, RtWeakPtr*);
					sub10C8780 pResolveWeakPtr = (sub10C8780)getActualOffset(OFFSET_RTWEAKPTR_RESOLVE);
					retVal = pResolveWeakPtr(v11, &temp);
				}
			}
			return retVal;
		}

	private:
		int data1;
		int data2;
	};
}

int getWeakPtr(int addr);