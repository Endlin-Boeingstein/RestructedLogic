#pragma once
#include "GameObject.h"

#define PROPSHEETBASE_VFTABLE_FUNC_COUNT 14
//寻找该偏移方法：
//HEX搜索文本PropertySheetBase
//然后比如你跳转到了诸如"27AdaptorSimpleTutorialDialog...17PropertySheetBase"字样时候
//把鼠标单击PropertySheetBase的"P"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01BA5D60; `typeinfo name for'PropertySheetBase
//.rodata:01BA5D60 31 37 50 72 6F 70 65 72 74 79 + _ZTS17PropertySheetBase DCB "17PropertySheetBase", 0
//.rodata : 01BA5D60 53 68 65 65 74 42 61 73 65 00; DATA XREF : .data.rel.ro : 01CB3AE4↓o
//.rodata : 01BA5D60; type descriptor name

//双击示例中的DATA XREF: .data.rel.ro:01CB3AE4↓o位置
//跳转到该类虚表，向上翻页，整体如下所示：
//.data.rel.ro:01CB3AA0; `vtable for'PropertySheetBase
//.data.rel.ro:01CB3AA0 00 00 00 00                   _ZTV17PropertySheetBase DCD 0; DATA XREF : sub_253C50 + 70↑o
//.data.rel.ro : 01CB3AA0; sub_253CE8 + 70↑o
//.data.rel.ro:01CB3AA0; sub_255264 + 10↑o
//.data.rel.ro:01CB3AA0; sub_255298 + 10↑o
//.data.rel.ro:01CB3AA0; sub_271BC0 + 98↑o
//.data.rel.ro:01CB3AA0; sub_27DF6C + CC↑o
//.data.rel.ro:01CB3AA0; sub_27FAB4 + F0↑o
//.data.rel.ro:01CB3AA0; sub_283EDC + 7C↑o
//.data.rel.ro:01CB3AA0; sub_284108 + 7C↑o
//.data.rel.ro:01CB3AA0; sub_2841B0 + 7C↑o
//.data.rel.ro:01CB3AA0; sub_2843CC + A8↑o
//.data.rel.ro:01CB3AA0; sub_284588 + 6C↑o
//.data.rel.ro:01CB3AA0; sub_284620 + 6C↑o
//.data.rel.ro:01CB3AA0; sub_2846C0 + 48↑o
//.data.rel.ro:01CB3AA0; sub_284730 + 48↑o ...
//.data.rel.ro:01CB3AA0; offset to this
//.data.rel.ro:01CB3AA4 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; `typeinfo for'PropertySheetBase
//.data.rel.ro:01CB3AA8 E8 0F 98 00                   DCD sub_980FE8
//.data.rel.ro : 01CB3AAC 40 11 98 00                   DCD sub_981140
//.data.rel.ro : 01CB3AB0 64 52 25 00                   DCD sub_255264
//.data.rel.ro : 01CB3AB4 A4 15 98 00                   DCD sub_9815A4
//.data.rel.ro : 01CB3AB8 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01CB3ABC 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01CB3AC0 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01CB3AC4 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01CB3AC8 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01CB3ACC 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01CB3AD0 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01CB3AD4 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01CB3AD8 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01CB3ADC 98 3D 25 00                   DCD nullsub_345
//.data.rel.ro : 01CB3AE0; public PropertySheetBase :
//.data.rel.ro : 01CB3AE0;   public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01CB3AE0;     public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01CB3AE0; `typeinfo for'PropertySheetBase
//.data.rel.ro:01CB3AE0 D8 74 DF 01                   _ZTI17PropertySheetBase DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01CB3AE0; DATA XREF : .data.rel.ro : 01C5C49C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C5DD2C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C5E188↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C5EE4C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C5F740↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C5F78C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C62EF0↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C63410↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C695E4↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C69630↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C6A28C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C6A2D8↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C6A44C↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C6A498↑o
//.data.rel.ro : 01CB3AE0;.data.rel.ro:01C6B5BC↑o ...
//.data.rel.ro : 01CB3AE0; reference to RTTI's type class
//.data.rel.ro:01CB3AE4 60 5D BA 01                   DCD _ZTS17PropertySheetBase; reference to type's name
//.data.rel.ro:01CB3AE8 F8 54 C7 01                   DCD _ZTI10GameObject; reference to parent's type name

//看最右上角的偏移引用
//其中DATA XREF: sub_253C50+70↑o的sub_253C50为PROPSHEETBASE_CTOR和PROPSHEETBASE_DTOR
#define PROPSHEETBASE_CTOR PropertySheetBase_PROPSHEETBASE_CTORAddr
#define PROPSHEETBASE_DTOR PropertySheetBase_PROPSHEETBASE_DTORAddr
//sub_253CE8+70↑o中的sub_253CE8为PROPSHEETBASE_Destructor
#define PROPSHEETBASE_Destructor PropertySheetBase_PROPSHEETBASE_DestructorAddr

//接着是：
//.data.rel.ro:01CB3AA4 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; `typeinfo for'PropertySheetBase
//.data.rel.ro:01CB3AA8 E8 0F 98 00                   DCD sub_980FE8

//其中，.data.rel.ro:01CB3AA8的01CB3AA8为PROPSHEETBASE_VFTABLE
#define PROPSHEETBASE_VFTABLE PropertySheetBase_PROPSHEETBASE_VFTABLEAddr
//双击示例中DCD sub_980FE8位置
//跳转后如下：
//.text:00980FE8
//.text:00980FE8; ============== = S U B R O U T I N E ====================================== =
//.text:00980FE8
//.text:00980FE8; Attributes: thunk
//.text : 00980FE8
//.text:00980FE8                               sub_980FE8; DATA XREF : .data.rel.ro : 01CB3AA8↓o
//.text : 00980FE8; __unwind{
//.text:00980FE8 E1 FF FF EA                   B               sub_980F74
//.text:00980FE8; } // starts at 980FE8
//.text:00980FE8
//.text:00980FE8; End of function sub_980FE8
//.text:00980FE8
//.text:00980FEC

//其中sub_980F74为PROPSHEETBASE_GETTYPE
#define PROPSHEETBASE_GETTYPE PropertySheetBase_PROPSHEETBASE_GETTYPEAddr


class BoardEntityScaledPropsEntry
{
public:
	Sexy::SexyString Key;
	int Formula;
	float Arg1;
	float Arg2;
};

class PropertySheetBase : public GameObject
{
public:
	PropertySheetBase() {}
	~PropertySheetBase()
	{
		typedef void(*propertySheetBaseDtor)(PropertySheetBase*);
		propertySheetBaseDtor destructor = (propertySheetBaseDtor)getActualOffset(PROPSHEETBASE_Destructor);
		destructor(this);
	}

	std::vector<BoardEntityScaledPropsEntry> ScaledProps;

	virtual void Function13() {}
	virtual void Function14() {}
	virtual void Function15() {}
};