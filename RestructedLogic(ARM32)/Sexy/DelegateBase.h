#pragma once
#include "../VersionAddresses.h"
//寻找该偏移方法：
//HEX搜索文本Delegate0
//然后比如你跳转到了诸如"N4Sexy9Delegate0E.7TimeMgr......"字样时候
//把鼠标单击N4Sexy9Delegate0E的"N"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B8E630                               ; `typeinfo name for'Sexy::Delegate0
//.rodata:01B8E630 4E 34 53 65 78 79 39 44 65 6C + _ZTSN4Sexy9Delegate0E DCB "N4Sexy9Delegate0E", 0
//.rodata : 01B8E630 65 67 61 74 65 30 45 00; DATA XREF : sub_4700B8↑o
//.rodata : 01B8E630; sub_4700B8 + C↑o
//.rodata:01B8E630;.text:off_4700D8↑o
//.rodata : 01B8E630;.data.rel.ro:01C5C76C↓o
//.rodata : 01B8E630; type descriptor name

//双击示例那个data.rel.ro:01C5C76C↓o位置的函数
//界面朝上一点，你会发现这块整体长这样：
//.data.rel.ro:01C5C754 68 C7 C5 01                   DCD _ZTIN4Sexy9Delegate0E               ; `typeinfo for'Sexy::Delegate0
//.data.rel.ro:01C5C758 1C C8 25 00                   DCD sub_25C81C
//.data.rel.ro : 01C5C75C EC DF 24 00                   DCD sub_24DFEC
//.data.rel.ro : 01C5C760 38 DA 24 00                   DCD nullsub_295
//.data.rel.ro : 01C5C764 48 C8 25 00                   DCD j__ZdlPv_5; operator delete(void*)
//.data.rel.ro:01C5C768; public Sexy::Delegate0 :
//.data.rel.ro : 01C5C768;   public /* offset 0x0 */ Sexy::DelegateBase
//.data.rel.ro:01C5C768; `typeinfo for'Sexy::Delegate0
//.data.rel.ro:01C5C768 D8 74 DF 01                   _ZTIN4Sexy9Delegate0E DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C5C768; DATA XREF : sub_4700DC↑o
//.data.rel.ro : 01C5C768; sub_4700DC + 4↑o
//.data.rel.ro:01C5C768;.text:off_4700E8↑o
//.data.rel.ro : 01C5C768;.data.rel.ro:01C5C754↑o
//.data.rel.ro : 01C5C768; reference to RTTI's type class
//.data.rel.ro:01C5C76C 30 E6 B8 01                   DCD _ZTSN4Sexy9Delegate0E; reference to type's name
//.data.rel.ro:01C5C770 58 C0 C5 01                   DCD _ZTIN4Sexy12DelegateBaseE; reference to parent's type name

//看到第一行那个DCD _ZTIN4Sexy9Delegate0E了吗？
//它下面那个函数的最左侧显示的偏移就是我们要找的偏移SEXYDELEGATE_VTBL
#define SEXYDELEGATE_VTBL DelegateBase_SEXYDELEGATE_VTBLAddr

namespace Sexy {
	class DelegateBase
	{
	public:
		uint callbackFunc;
		int useOwnerVtable;
		uint callbackOwner;
		int unk0x10;
		uint executeCallbackFunction;

		virtual void Function0() {};
		virtual void Function1() {};
		virtual void Function2() {};
		virtual void Delete() {};
	};
}

Sexy::DelegateBase CreateEmptyDelegate(uint vftableAddr);

Sexy::DelegateBase CreateDelegate(
	uint vftableAddr,
	uint callbackFunc,
	bool useOwnerVtable,
	uint callbackOwner,
	int unk0x10,
	uint executeCallbackFunction
);

Sexy::DelegateBase CreateDelegate(
	uint callbackFunc,
	bool useOwnerVtable,
	uint callbackOwner,
	int unk0x10,
	uint executeCallbackFunction
);