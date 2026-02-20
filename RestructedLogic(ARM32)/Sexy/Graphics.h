#pragma once
#include "Color.h"
#include "../memUtils.h"
#include "../VersionAddresses.h"

//寻找该偏移方法：
//HEX搜索文本*default*
//然后比如你跳转到了诸如"*default*.$.path.$."字样时候
//把鼠标单击*default*的"*"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B5052D 2A 64 65 66 61 75 6C 74 2A 00 aDefault_3 DCB "*default*", 0; DATA XREF : sub_5D0830 + 5C8↑o
//.rodata : 01B5052D; sub_1123AFC + 5C↑o
//.rodata:01B5052D; sub_1123D20 + 48↑o
//.rodata:01B5052D;.data:off_1D6B404↓o

//双击示例中.data:off_1D6B404↓o位置，跳转到如下所示：
//.data:01D6B404 2D 05 B5 01                   off_1D6B404 DCD aDefault_3; DATA XREF : sub_5D0830 + 5C0↑o
//.data : 01D6B404; sub_5D0830 + 5C8↑r
//.data:01D6B404; sub_1123AFC:loc_1123B54↑o
//.data : 01D6B404; sub_1123AFC + 5C↑r
//.data:01D6B404;.text:off_1123C68↑o
//.data : 01D6B404; sub_1123D20 + 34↑o
//.data:01D6B404; sub_1123D20 + 48↑r
//.data:01D6B404;.text:off_1123F2C↑o
//.data : 01D6B404;.got:off_1D24798↑o
//.data : 01D6B404; "*default*"
//.data:01D6B408 14                            unk_1D6B408 DCB 0x14; DATA XREF : sub_1122AD8 + F4↑o
//.data : 01D6B408; sub_1122AD8 + F8↑o
//.data:01D6B408;.text:off_1123A70↑o
//.data : 01D6B409 00                            DCB    0
//.data : 01D6B40A 00                            DCB    0
//.data : 01D6B40B 00                            DCB    0
//.data : 01D6B40C 00                            DCB    0
//.data : 01D6B40D 00                            DCB    0
//.data : 01D6B40E 00                            DCB    0
//.data : 01D6B40F 00                            DCB    0
//.data : 01D6B410 55 4E 4B 4E 4F 57 4E 00       aUnknown_10 DCB "UNKNOWN", 0; DATA XREF : sub_11324A0:loc_113252C↑o
//.data : 01D6B410; sub_11324A0 + 98↑o
//.data:01D6B410;.text:off_1132598↑o
//.data : 01D6B410; sub_11325A0:loc_1132670↑o
//.data : 01D6B410; sub_11325A0 + D4↑o
//.data:01D6B410;.text:off_11327D4↑o

//双击示例中sub_1123D20+34↑o或者sub_1123D20+48↑r位置
//跳转后按F5，选择工具栏的视图->打开子视图->邻近浏览器
//找到其最顶端的父函数，双击后有“噔噔”声后按空格恢复至反编译界面
//所得如下所示：
//int sub_11246AC()
//{
//	int v0; // r0
//	int* v1; // r5
//	bool v2; // zf
//	int v3; // r1
//	int* v4; // t1
//	int* v6; // [sp+0h] [bp-18h] BYREF
//	int v7[5]; // [sp+4h] [bp-14h] BYREF
//
//	v7[1] = 0;
//	v7[0] = 0;
//	v6 = v7;
//	v0 = sub_1123D20();
//	v1 = v7;
//	while (v1 != v7)
//	{
//		sub_112460C(v0, (_DWORD*)v1[7]);
//		v0 = v1[1];
//		if (v0)
//		{
//			do
//			{
//				v1 = (int*)v0;
//				v0 = *(_DWORD*)v0;
//			} while (v0);
//		}
//		else
//		{
//			v0 = (int)(v1 + 2);
//			v2 = *(_DWORD*)v1[2] == (_DWORD)v1;
//			v1 = (int*)v1[2];
//			if (!v2)
//			{
//				do
//				{
//					v3 = *(_DWORD*)v0;
//					v4 = *(int**)(*(_DWORD*)v0 + 8);
//					v0 = *(_DWORD*)v0 + 8;
//					v1 = v4;
//				} while (*v4 != v3);
//			}
//		}
//	}
//	sub_112654C(&v6, v7[0]);
//	return _stack_chk_guard - v7[2];
//}


//关闭其余的反编译窗口防止干扰，按Tab键返回反编译界面，如下所示：
//.text:011246AC; int __fastcall sub_11246AC(int)
//.text:011246AC                               sub_11246AC
//.text : 011246AC
//.text : 011246AC                               var_18 = -0x18
//.text : 011246AC                               var_14 = -0x14
//.text : 011246AC                               var_10 = -0x10
//.text : 011246AC                               var_C = -0xC
//.text : 011246AC
//.text : 011246AC; __unwind{ // __gxx_personality_v0
//.text:011246AC 30 48 2D E9                   PUSH            {R4,R5,R11,LR}
//.text : 011246B0 08 B0 8D E2                   ADD             R11, SP, #8
//.text:011246B4 10 D0 4D E2                   SUB             SP, SP, #0x10
//.text:011246B8 D4 10 9F E5                   LDR             R1, =(__stack_chk_guard_ptr - 0x11246C4)
//.text : 011246BC 01 10 9F E7                   LDR             R1,[PC,R1]; __stack_chk_guard
//.text:011246C0 00 10 91 E5                   LDR             R1,[R1]
//.text : 011246C4 0C 10 8D E5                   STR             R1,[SP,#0x18 + var_C]
//.text : 011246C8 00 10 A0 E3                   MOV             R1, #0
//.text:011246CC 08 10 8D E5                   STR             R1,[SP,#0x18 + var_10]
//.text:011246D0 04 10 8D E5                   STR             R1,[SP,#0x18 + var_14]
//.text : 011246D4 0D 10 A0 E1                   MOV             R1, SP
//.text : 011246D8 04 40 81 E2                   ADD             R4, R1, #4
//.text:011246DC 00 40 8D E5                   STR             R4,[SP,#0x18 + var_18]
//.text : 011246E0;   try {
//.text:011246E0 8E FD FF EB                   BL              sub_1123D20
//.text : 011246E0;
//   } // starts at 11246E0
//.text:011246E0
//.text : 011246E4 00 50 9D E5                   LDR             R5,[SP,#0x18 + var_18]
//.text : 011246E8 15 00 00 EA                   B               loc_1124744
//.text : 011246E8
//.text : 011246EC; -------------------------------------------------------------------------- -
//.text:011246EC
//.text : 011246EC                               loc_11246EC; CODE XREF : sub_11246AC + 9C↓j
//.text : 011246EC 1C 10 95 E5                   LDR             R1,[R5,#0x1C]
//.text : 011246F0;   try {
//.text:011246F0 C5 FF FF EB                   BL              sub_112460C
//.text : 011246F0;
//   } // starts at 11246F0
//.text:011246F0
//.text : 011246F4 04 00 95 E5                   LDR             R0,[R5,#4]
//.text : 011246F8 00 00 50 E3                   CMP             R0, #0
//.text:011246FC 04 00 00 0A                   BEQ             loc_1124714
//.text : 011246FC
//.text : 01124700
//.text : 01124700                               loc_1124700; CODE XREF : sub_11246AC + 60↓j
//.text : 01124700 00 50 A0 E1                   MOV             R5, R0
//.text : 01124704 00 00 95 E5                   LDR             R0,[R5]
//.text : 01124708 00 00 50 E3                   CMP             R0, #0
//.text:0112470C FB FF FF 1A                   BNE             loc_1124700
//.text : 0112470C
//.text : 01124710 0B 00 00 EA                   B               loc_1124744
//.text:01124710
//.text : 01124714; -------------------------------------------------------------------------- -
//.text:01124714
//.text : 01124714                               loc_1124714; CODE XREF : sub_11246AC + 50↑j
//.text : 01124714 05 00 A0 E1                   MOV             R0, R5
//.text : 01124718 08 10 B0 E5                   LDR             R1,[R0,#8]!
//.text:0112471C 00 20 91 E5                   LDR             R2,[R1]
//.text : 01124720 05 00 52 E1                   CMP             R2, R5
//.text : 01124724 01 50 A0 E1                   MOV             R5, R1
//.text : 01124728 05 00 00 0A                   BEQ             loc_1124744
//.text:01124728
//.text:0112472C
//.text : 0112472C                               loc_112472C; CODE XREF : sub_11246AC + 94↓j
//.text : 0112472C 00 10 90 E5                   LDR             R1,[R0]
//.text : 01124730 01 00 A0 E1                   MOV             R0, R1
//.text : 01124734 08 50 B0 E5                   LDR             R5,[R0,#8]!
//.text:01124738 00 20 95 E5                   LDR             R2,[R5]
//.text:0112473C 01 00 52 E1                   CMP             R2, R1
//.text : 01124740 F9 FF FF 1A                   BNE             loc_112472C
//.text : 01124740
//.text : 01124744
//.text : 01124744                               loc_1124744; CODE XREF : sub_11246AC + 3C↑j
//.text : 01124744; sub_11246AC + 64↑j
//.text:01124744; sub_11246AC + 7C↑j
//.text:01124744 04 00 55 E1                   CMP             R5, R4
//.text : 01124748 E7 FF FF 1A                   BNE             loc_11246EC
//.text:01124748
//.text:0112474C 04 10 9D E5                   LDR             R1,[SP,#0x18 + var_14]
//.text : 01124750 0D 00 A0 E1                   MOV             R0, SP
//.text : 01124754 7C 07 00 EB                   BL              sub_112654C
//.text : 01124754
//.text : 01124758 38 00 9F E5                   LDR             R0, =(__stack_chk_guard_ptr - 0x1124768)
//.text:0112475C 0C 10 9D E5                   LDR             R1,[SP,#0x18 + var_C]
//.text : 01124760 00 00 9F E7                   LDR             R0,[PC,R0]; __stack_chk_guard
//.text:01124764 00 00 90 E5                   LDR             R0,[R0]
//.text : 01124768 01 00 50 E0                   SUBS            R0, R0, R1
//.text:0112476C 08 D0 4B 02                   SUBEQ           SP, R11, #8
//.text:01124770 30 88 BD 08                   POPEQ           {R4,R5,R11,PC}
//.text:01124770
//.text : 01124774 BB 5E C3 EB                   BL              __stack_chk_fail
//.text : 01124774
//.text : 01124778; -------------------------------------------------------------------------- -
//.text:01124778
//.text:01124778                               loc_1124778
//.text:01124778;   cleanup() // owned by 11246E0
//.text:01124778 FF FF FF EA                   B               loc_112477C
//.text:01124778
//.text:0112477C; -------------------------------------------------------------------------- -
//.text:0112477C
//.text : 0112477C                               loc_112477C; CODE XREF : sub_11246AC:loc_1124778↑j
//.text : 0112477C;   cleanup() // owned by 11246F0
//.text:0112477C 04 10 9D E5                   LDR             R1,[SP,#0x18 + var_14]
//.text : 01124780 00 40 A0 E1                   MOV             R4, R0
//.text:01124784 0D 00 A0 E1                   MOV             R0, SP
//.text:01124788 6F 07 00 EB                   BL              sub_112654C
//.text:01124788
//.text:0112478C 04 00 A0 E1                   MOV             R0, R4
//.text:01124790 E3 5E 17 FA                   BLX             sub_16FC324
//.text:01124790
//.text:01124790; End of function sub_11246AC

//找到示例最后的; End of function sub_11246AC这句话位置，然后向上找倒数第一个;   cleanup() // owned by 11246F0
//其中往下数的最靠近BL的MOV             R0, SP（最靠近BL且在BL上面的那个）的左侧显示偏移则为UNK_GRAPHICSFUNC2
#define UNK_GRAPHICSFUNC2 Graphics_UNK_GRAPHICSFUNC2Addr

//再次按F5进入伪C代码界面
//双击示例中的sub_112460C位置函数
//进入函数后，关闭其余的反编译窗口防止干扰，按Tab键返回反编译界面，如下所示：
//.text:0112460C 70 4C 2D E9                   PUSH{ R4 - R6,R10,R11,LR }
//.text : 01124610 10 B0 8D E2                   ADD             R11, SP, #0x10
//.text:01124614 01 40 A0 E1                   MOV             R4, R1
//.text : 01124618 08 00 00 EA                   B               loc_1124640
//.text:01124618
//.text:0112461C; -------------------------------------------------------------------------- -
//.text:0112461C
//.text : 0112461C                               loc_112461C; CODE XREF : sub_112460C + 3C↓j
//.text : 0112461C 00 00 94 E5                   LDR             R0, [R4]
//.text : 01124620 01 10 A0 E3                   MOV             R1, #1
//.text:01124624 08 50 80 E2                   ADD             R5, R0, #8
//.text:01124628 05 00 A0 E1                   MOV             R0, R5
//.text:0112462C EF F4 FF EB                   BL              sub_11219F0
//.text : 0112462C
//.text : 01124630 05 00 A0 E1                   MOV             R0, R5
//.text : 01124634 9E F4 FF EB                   BL              sub_11218B4
//.text : 01124634
//.text : 01124638 04 00 A0 E1                   MOV             R0, R4
//.text:0112463C F8 00 00 EB                   BL              sub_1124A24
//.text : 0112463C
//.text : 01124640
//.text : 01124640                               loc_1124640; CODE XREF : sub_112460C + C↑j
//.text : 01124640 08 00 94 E5                   LDR             R0, [R4, #8]
//.text:01124644 00 00 50 E3                   CMP             R0, #0
//.text:01124648 F3 FF FF 1A                   BNE             loc_112461C
//.text:01124648
//.text:0112464C 0C 60 94 E5                   LDR             R6, [R4, #0xC]
//.text : 01124650 10 00 94 E5                   LDR             R0, [R4, #0x10]
//.text : 01124654 11 00 00 EA                   B               loc_11246A0
//.text : 01124654
//.text : 01124658; -------------------------------------------------------------------------- -
//.text:01124658
//.text:01124658                               loc_1124658; CODE XREF : sub_112460C + 98↓j
//.text : 01124658 04 50 86 E2                   ADD             R5, R6, #4
//.text:0112465C 05 00 A0 E1                   MOV             R0, R5
//.text : 01124660 FC F4 FF EB                   BL              sub_1121A58
//.text : 01124660
//.text : 01124664 01 00 40 E2                   SUB             R0, R0, #1
//.text:01124668 02 00 50 E3                   CMP             R0, #2
//.text:0112466C 02 00 00 3A                   BCC             loc_112467C
//.text : 0112466C
//.text : 01124670 04 00 96 E5                   LDR             R0, [R6, #4]
//.text : 01124674 00 00 50 E3                   CMP             R0, #0
//.text:01124678 06 00 00 0A                   BEQ             loc_1124698
//.text:01124678
//.text:0112467C
//.text : 0112467C                               loc_112467C; CODE XREF : sub_112460C + 60↑j
//.text : 0112467C 05 00 A0 E1                   MOV             R0, R5
//.text : 01124680 01 10 A0 E3                   MOV             R1, #1
//.text:01124684 D9 F4 FF EB                   BL              sub_11219F0
//.text:01124684
//.text:01124688 30 00 D6 E5                   LDRB            R0, [R6, #0x30]
//.text:0112468C 00 00 50 E3                   CMP             R0, #0
//.text:01124690 05 00 A0 01                   MOVEQ           R0, R5
//.text:01124694 86 F4 FF 0B                   BLEQ            sub_11218B4
//.text:01124694
//.text:01124698
//.text:01124698                               loc_1124698; CODE XREF : sub_112460C + 6C↑j
//.text : 01124698 10 00 94 E5                   LDR             R0, [R4, #0x10]
//.text:0112469C 84 60 86 E2                   ADD             R6, R6, #0x84
//.text:0112469C
//.text:011246A0
//.text : 011246A0                               loc_11246A0; CODE XREF : sub_112460C + 48↑j
//.text : 011246A0 00 00 56 E1                   CMP             R6, R0
//.text : 011246A4 EB FF FF 1A                   BNE             loc_1124658
//.text : 011246A4
//.text : 011246A8 70 8C BD E8                   POP{ R4 - R6,R10,R11,PC }
//.text : 011246A8; } // starts at 112460C
//.text:011246A8
//.text : 011246A8; End of function sub_112460C

//其中第一行的; __unwind {下面的数行后的MOV             R4, R1最左侧对应的偏移就是你要找的UNK_GRAPHICSFUNC
#define UNK_GRAPHICSFUNC Graphics_UNK_GRAPHICSFUNCAddr


namespace Sexy
{
	class Graphics
	{
	public:
		int unk1;
		int unk2;
		float mTransX;
		float mTransY;
		float mScaleX;
		float mScaleY;
		float mScaleOrigX;
		float mScaleOrigY;
		Rect mClipRect;
		Color mColor;
		int mFont; // Sexy::Font type
		int mDrawMode;
		bool mColorizeImages;
		bool mFastStretch;
		bool mWriteColoredString;
		bool mLinearBlend;
		bool mIs3D;
		int mRenderDevice; // AndroidRenderDevice*
		int mRenderContext;
		int mGraphics3D;
		// there are still at least 4 more unknown fields

		void UnkFunc() {
			typedef void (*unkFunc)(Graphics*);
			((unkFunc)getActualOffset(UNK_GRAPHICSFUNC))(this);
		}

		void UnkFunc2() {
			typedef void (*unkFunc)(Graphics*);
			((unkFunc)getActualOffset(UNK_GRAPHICSFUNC2))(this);
		}
	};

	static_assert(offsetof(Graphics, mRenderDevice) == 0x50);
	static_assert(offsetof(Graphics, mIs3D) == 0x4C);
}