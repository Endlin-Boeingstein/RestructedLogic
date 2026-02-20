#pragma once
#include <vector>

#include "ObjectTypeDescriptor.h"
#include "ZombiePropertySheet.h"
#include "../Sexy/RtWeakPtr.h"


//寻找该偏移方法：
//HEX搜索文本ObjectTypeDirectory
//然后比如你跳转到了诸如"19ObjectTypeDirectoryI10ZombieTypeE"字样时候(注意了是ZombieTypeE！！！！！)
//把鼠标单击ObjectTypeDirectory的"O"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B8F210; `typeinfo name for'ObjectTypeDirectory<ZombieType>
//.rodata:01B8F210 31 39 4F 62 6A 65 63 74 54 79 + _ZTS19ObjectTypeDirectoryI10ZombieTypeE DCB "19ObjectTypeDirectoryI10ZombieTypeE", 0
//.rodata : 01B8F210 70 65 44 69 72 65 63 74 6F 72 + ; DATA XREF : .data.rel.ro : 01C5DDB8↓o
//.rodata : 01B8F210 79 49 31 30 5A 6F 6D 62 69 65 + ; type descriptor name

//双击示例位置的DATA XREF: .data.rel.ro:01C5DDB8↓o
//跳转到该类的虚表，向上翻页，如下：
//.data.rel.ro:01C5DD9C; `vtable for'ObjectTypeDirectory<ZombieType>
//.data.rel.ro:01C5DD9C 00 00 00 00                   _ZTV19ObjectTypeDirectoryI10ZombieTypeE DCD 0
//.data.rel.ro : 01C5DD9C; DATA XREF : sub_281008 + 28↑o
//.data.rel.ro : 01C5DD9C; sub_281008 + 38↑o
//.data.rel.ro:01C5DD9C;.text:off_281078↑o
//.data.rel.ro : 01C5DD9C; sub_285ED8 + C↑o
//.data.rel.ro:01C5DD9C; sub_285ED8 + 10↑o
//.data.rel.ro:01C5DD9C;.text:off_285F2C↑o
//.data.rel.ro : 01C5DD9C; sub_285F38 + C↑o
//.data.rel.ro:01C5DD9C; sub_285F38 + 10↑o
//.data.rel.ro:01C5DD9C;.text:off_285F90↑o
//.data.rel.ro : 01C5DD9C; offset to this
//.data.rel.ro:01C5DDA0 B4 DD C5 01                   DCD _ZTI19ObjectTypeDirectoryI10ZombieTypeE; `typeinfo for'ObjectTypeDirectory<ZombieType>
//.data.rel.ro:01C5DDA4 D8 5E 28 00                   off_1C5DDA4 DCD sub_285ED8
//.data.rel.ro : 01C5DDA8 38 5F 28 00                   DCD sub_285F38
//.data.rel.ro : 01C5DDAC; public Sexy::LazySingleton<ObjectTypeDirectory<ZombieType>>
//.data.rel.ro:01C5DDAC; `typeinfo for'Sexy::LazySingleton<ObjectTypeDirectory<ZombieType>>
//.data.rel.ro:01C5DDAC D4 74 DF 01                   _ZTIN4Sexy13LazySingletonI19ObjectTypeDirectoryI10ZombieTypeEEE DCD _ZTVN10__cxxabiv117__class_type_infoE + 8
//.data.rel.ro : 01C5DDAC; DATA XREF : .data.rel.ro : 01C5DDBC↓o
//.data.rel.ro : 01C5DDAC;.data.rel.ro:01C5DDC4↓o
//.data.rel.ro : 01C5DDAC; reference to RTTI's type class
//.data.rel.ro:01C5DDB0 40 F2 B8 01                   DCD _ZTSN4Sexy13LazySingletonI19ObjectTypeDirectoryI10ZombieTypeEEE; reference to type's name
//.data.rel.ro:01C5DDB4; public ObjectTypeDirectory<ZombieType> :
//.data.rel.ro : 01C5DDB4;   public /* offset 0x0 */ Sexy::LazySingleton<ObjectTypeDirectory<ZombieType>>
//.data.rel.ro:01C5DDB4; `typeinfo for'ObjectTypeDirectory<ZombieType>
//.data.rel.ro:01C5DDB4 D8 74 DF 01                   _ZTI19ObjectTypeDirectoryI10ZombieTypeE DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C5DDB4; DATA XREF : .data.rel.ro : 01C5DDA0↑o
//.data.rel.ro : 01C5DDB4; reference to RTTI's type class
//.data.rel.ro:01C5DDB8 10 F2 B8 01                   DCD _ZTS19ObjectTypeDirectoryI10ZombieTypeE; reference to type's name

//其中最右上角的偏移引用部分
//DATA XREF: sub_281008+28↑o或sub_281008+38↑o的sub_281008为ZOMBIETYPEDIRECTORY_GET
#define ZOMBIETYPEDIRECTORY_GET ZombieType_ZOMBIETYPEDIRECTORY_GETAddr

//寻找该偏移方法：
//HEX搜索文本UI_MainMenuLogo
//然后比如你跳转到了诸如"UI_MainMenuLogo.IntroCinema"字样时候(注意了是ZombieTypeE！！！！！)
//把鼠标单击UI_MainMenuLogo的"U"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AE70E8 55 49 5F 4D 61 69 6E 4D 65 6E + aUiMainmenulogo DCB "UI_MainMenuLogo", 0; DATA XREF : sub_415C10 + 29C↑o
//.rodata : 01AE70E8 75 4C 6F 67 6F 00; sub_415C10 + 2B4↑o
//.rodata:01AE70E8;.text:off_416460↑o
//.rodata : 01AE70E8; sub_5D0830 + 3C4↑o
//.rodata:01AE70E8; sub_5D0830 + 3DC↑o
//.rodata:01AE70E8; sub_5D0830 + 42C↑o
//.rodata:01AE70E8; sub_5D0830 + 444↑o
//.rodata:01AE70E8; sub_5D0830:off_5D0D90↑o
//.rodata : 01AE70E8; sub_5D0830:off_5D0D94↑o
//.rodata : 01AE70E8; sub_6288B0 + 88↑o
//.rodata:01AE70E8; sub_6288B0 + A0↑o
//.rodata:01AE70E8;.text:off_628A90↑o
//.rodata : 01AE70E8; sub_628A9C + D8↑o
//.rodata:01AE70E8; sub_628A9C + F0↑o
//.rodata:01AE70E8;.text:off_628C70↑o ...

//双击示例中DATA XREF: sub_415C10+29C↑o或sub_415C10+2B4↑o位置
//跳转后按F5，所得如下：
//int __fastcall sub_415C10(int a1, int a2)
//{
//    char v2; // r0
//    char v3; // r0
//    char v4; // r0
//    char v5; // r0
//    int v6; // r5
//    int i; // r8
//    int v8; // r0
//    int v9; // r0
//    int* v10; // r7
//    int v11; // r6
//    int v12; // r0
//    int v13; // r0
//    int v14; // r5
//    int j; // r8
//    int v16; // r0
//    int* v17; // r6
//    int v18; // r4
//    int v19; // r0
//    int v20; // r0
//    char* v22; // r4
//    char* v23; // r4
//    unsigned int v25[3]; // [sp+8h] [bp-40h] BYREF
//    int v26; // [sp+14h] [bp-34h] BYREF
//    int v27; // [sp+18h] [bp-30h]
//    void* v28; // [sp+1Ch] [bp-2Ch]
//    __int64 v29; // [sp+20h] [bp-28h] BYREF
//    int v30; // [sp+28h] [bp-20h]
//
//    sub_DF1E6C();
//    v2 = byte_1D7F888;
//    __dmb(0xBu);
//    if ((v2 & 1) == 0 && _cxa_guard_acquire((__guard*)&byte_1D7F888))
//    {
//        byte_1D7F828 = 20;
//        strcpy(byte_1D7F829, "peashooter");
//        dword_1D7F834 = 18;
//        BYTE1(dword_1D7F83C) = 0;
//        HIWORD(dword_1D7F83C) = 0;
//        strcpy((char*)&dword_1D7F834 + 1, "sunflow");
//        dword_1D7F840 = 14;
//        strcpy((char*)&dword_1D7F840 + 1, "wallnut");
//        dword_1D7F848 = 0;
//        byte_1D7F84C = 20;
//        strcpy(byte_1D7F84D, "bloomerang");
//        dword_1D7F860 = 0;
//        *(int*)((char*)&dword_1D7F85C + 1) = 2037344355;
//        dword_1D7F858 = 16;
//        *(int*)((char*)&dword_1D7F858 + 1) = 1802399586;
//        dword_1D7F864 = 14;
//        strcpy((char*)&dword_1D7F864 + 1, "iceburg");
//        dword_1D7F86C = 0;
//        byte_1D7F870 = 20;
//        strcpy(byte_1D7F871, "potatomine");
//        BYTE1(dword_1D7F884) = 0;
//        HIWORD(dword_1D7F884) = 0;
//        dword_1D7F87C = 18;
//        strcpy((char*)&dword_1D7F87C + 1, "torchwo");
//        _cxa_atexit((void(__fastcall*)(void*))sub_211A0C, 0, &off_1D2A000);
//        _cxa_guard_release((__guard*)&byte_1D7F888);
//    }
//    v3 = byte_1D7F898;
//    __dmb(0xBu);
//    if ((v3 & 1) == 0 && _cxa_guard_acquire((__guard*)&byte_1D7F898))
//    {
//        sub_27BC1C(dword_1D7F88C, &byte_1D7F828, &byte_1D7F888);
//        _cxa_atexit((void(__fastcall*)(void*))sub_24DB98, dword_1D7F88C, &off_1D2A000);
//        _cxa_guard_release((__guard*)&byte_1D7F898);
//    }
//    v4 = byte_1D7F8F4;
//    __dmb(0xBu);
//    if ((v4 & 1) == 0 && _cxa_guard_acquire((__guard*)&byte_1D7F8F4))
//    {
//        *(_DWORD*)((char*)&qword_1D7F8B9 + 7) = 0;
//        unk_1D7F8B8 = 16;
//        dword_1D7F8B4 = 0;
//        dword_1D7F8B0 = 0;
//        dword_1D7F8A0 = 10;
//        dword_1D7F8A4 = 30976;
//        dword_1D7F8A8 = 0;
//        byte_1D7F8AC = 4;
//        strcpy((char*)&word_1D7F8AD, "ra");
//        qword_1D7F8B9 = 0x7265726F6C707865LL;
//        *(int*)((char*)&dword_1D7F8A0 + 1) = 1835890029;
//        dword_1D7F8C4 = 10;
//        dword_1D7F8CC = 0;
//        dword_1D7F8C8 = 30976;
//        *(int*)((char*)&dword_1D7F8C4 + 1) = 1835890029;
//        dword_1D7F8D0 = 0;
//        dword_1D7F8D4 = 0;
//        dword_1D7F8D8 = 0;
//        v22 = (char*)operator new(0x10u);
//        dword_1D7F8D0 = 17;
//        dword_1D7F8D4 = 12;
//        dword_1D7F8D8 = (int)v22;
//        strcpy(v22, "mummy_armor1");
//        dword_1D7F8DC = 0;
//        dword_1D7F8E0 = 0;
//        dword_1D7F8E4 = 0;
//        v23 = (char*)operator new(0x10u);
//        dword_1D7F8DC = 17;
//        dword_1D7F8E0 = 12;
//        dword_1D7F8E4 = (int)v23;
//        strcpy(v23, "mummy_armor2");
//        dword_1D7F8E8 = 14;
//        strcpy((char*)&dword_1D7F8E8 + 1, "pharaoh");
//        dword_1D7F8F0 = 0;
//        _cxa_atexit((void(__fastcall*)(void*))sub_211A5C, 0, &off_1D2A000);
//        _cxa_guard_release((__guard*)&byte_1D7F8F4);
//    }
//    v5 = byte_1D7F904;
//    __dmb(0xBu);
//    if ((v5 & 1) == 0 && _cxa_guard_acquire((__guard*)&byte_1D7F904))
//    {
//        sub_27BC1C(dword_1D7F8F8, &dword_1D7F8A0, &byte_1D7F8F4);
//        _cxa_atexit((void(__fastcall*)(void*))sub_24DB98, dword_1D7F8F8, &off_1D2A000);
//        _cxa_guard_release((__guard*)&byte_1D7F904);
//    }
//    v6 = dword_1D7F88C[0];
//    for (i = dword_1D7F88C[1]; i != v6; v6 += 12)
//    {
//        v8 = sub_24CFAC(&v26, v6);
//        v9 = sub_25B8B4(v8);
//        sub_25B928(v25, v9, &v26);
//        v10 = sub_10D99A4();
//        sub_10DFA5C(&v29, (int)v10, v25);
//        v11 = 0;
//        if (!sub_10C8C60(&v29))
//        {
//            v12 = sub_10C8B64((int)&v29);
//            v13 = sub_10DF644(v10, v12);
//            if (v13)
//                v11 = sub_10DB9C0(v13, (int)&v29);
//        }
//        sub_10C8B38((unsigned int*)&v29);
//        (*(void(__fastcall**)(int, int))(*(_DWORD*)v11 + 28))(v11, a2);
//        sub_10C8B38(v25);
//        if ((v26 & 1) != 0)
//            operator delete(v28);
//    }
//    v14 = dword_1D7F8F8[0];
//    for (j = dword_1D7F8F8[1]; j != v14; v14 += 12)
//    {
//        sub_24CFAC(&v26, v14);
//        v16 = sub_281008();
//        sub_28107C(v25, v16, (int)&v26);
//        v17 = sub_10D99A4();
//        sub_10DFA5C(&v29, (int)v17, v25);
//        v18 = 0;
//        if (!sub_10C8C60(&v29))
//        {
//            v19 = sub_10C8B64((int)&v29);
//            v20 = sub_10DF644(v17, v19);
//            if (v20)
//                v18 = sub_10DB9C0(v20, (int)&v29);
//        }
//        sub_10C8B38((unsigned int*)&v29);
//        sub_CA63AC(v18, a2);
//        sub_10C8B38(v25);
//        if ((v26 & 1) != 0)
//            operator delete(v28);
//    }
//    v28 = (void*)operator new(0x20u);
//    v26 = 33;
//    v27 = 16;
//    strcpy((char*)v28, "Grass_Transition");
//    sub_29E270(&v29, a2, &v26, &v26);
//    if ((v26 & 1) != 0)
//        operator delete(v28);
//    v28 = (void*)operator new(0x10u);
//    v26 = 17;
//    v27 = 15;
//    strcpy((char*)v28, "UI_MainMenuLogo");
//    sub_29E270(&v29, a2, &v26, &v26);
//    if ((v26 & 1) != 0)
//        operator delete(v28);
//    return _stack_chk_guard - v30;
//}




//其函数名称sub_28107C即为ZOMBIETYPEDIRECTORY_GETTYPE
#define ZOMBIETYPEDIRECTORY_GETTYPE ZombieType_ZOMBIETYPEDIRECTORY_GETTYPEAddr

enum ZombieFlagType {
	noflag = 0,
	flag_normal = 1,
	flag_veteran = 2
};

class ZombieType : public ObjectTypeDescriptor
{
public:
	Sexy::SexyString ZombieClass;
	Sexy::SexyString HomeWorld;
	Sexy::SexyString DisplayTypeName;
	Sexy::SexyString AlmanacBackdropName;
	Sexy::SexyString PopAnim;
	Sexy::SexyString AnimRigClass;
	std::vector<Sexy::SexyString> ResourceGroups;
	std::vector<Sexy::SexyString> AudioGroups;
	Sexy::RtWeakPtr<ZombiePropertySheet> Properties;
	bool Placeable;
	bool HastyOnStart;
	bool IsBasicZombie;
	bool IsFemaleZombie;
	bool HideFromAlmanac;
	ZombieFlagType FlagType;
	int unk;

	// new field
	int IntegerID = 0;

	static Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc oZombieTypeBuildSymbols;
	static Reflection::CRefManualSymbolBuilder::ConstructFunc oZombieTypeConstruct;

	static void* construct(ZombieType* self)
	{
		oZombieTypeConstruct(self);

		self->IntegerID = 0;

		return self;
	}

	static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
	{
		oZombieTypeBuildSymbols(builder, rclass);
		REGISTER_STANDARD_PROPERTY(builder, rclass, ZombieType, IntegerID);
	}

	static void GetFromName(Sexy::RtWeakPtr<ZombieType>* res, Sexy::SexyString zombieName);
};

static_assert(sizeof(ZombieType) == 0x8C);
static_assert(offsetof(ZombieType, AudioGroups) == 0x64);
static_assert(offsetof(ZombieType, FlagType) == 0x80);