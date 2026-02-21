#pragma once
#include "../Reflection/ReflectionBuilder.h"


//寻找该偏移方法：
//HEX搜索文本GameObject
//然后比如你跳转到了诸如"18BananaTargetCursor.10GameObject"字样时候
//把鼠标单击GameObject的"G"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B98665; `typeinfo name for'GameObject
//.rodata:01B98665 31 30 47 61 6D 65 4F 62 6A 65 + _ZTS10GameObject DCB "10GameObject", 0; DATA XREF : .data.rel.ro : 01C754FC↓o
//.rodata : 01B98665 63 74 00; type descriptor name

//双击示例DATA XREF: .data.rel.ro:01C754FC↓o位置，进行跳转
//界面朝上一点，你会发现这块整体长这样：
//.data.rel.ro:01C754BC; `vtable for'GameObject
//.data.rel.ro:01C754BC 00 00 00 00                   _ZTV10GameObject DCD 0; DATA XREF : sub_53C830 + 1C↑o
//.data.rel.ro : 01C754BC; sub_53EF3C + 10↑o
//.data.rel.ro:01C754BC; sub_53EF3C + 14↑o
//.data.rel.ro:01C754BC;.text:off_53EF80↑o
//.data.rel.ro : 01C754BC; sub_53EF84 + 10↑o
//.data.rel.ro:01C754BC; sub_53EF84 + 18↑o
//.data.rel.ro:01C754BC;.text:off_53EFE8↑o
//.data.rel.ro : 01C754BC; sub_696B34 + 1C↑o
//.data.rel.ro:01C754BC; sub_6F1388 + 18↑o
//.data.rel.ro:01C754BC; sub_978BF4 + 44↑o
//.data.rel.ro:01C754BC; sub_978BF4 + AC↑o
//.data.rel.ro:01C754BC; sub_978ED4 + 28↑o
//.data.rel.ro:01C754BC; sub_978ED4 + A0↑o
//.data.rel.ro:01C754BC; sub_9790F8 + 44↑o
//.data.rel.ro:01C754BC; sub_9790F8 + AC↑o ...
//.data.rel.ro:01C754BC; offset to this
//.data.rel.ro:01C754C0 F8 54 C7 01                   DCD _ZTI10GameObject; `typeinfo for'GameObject
//.data.rel.ro:01C754C4 80 EA 53 00                   off_1C754C4 DCD sub_53EA80
//.data.rel.ro : 01C754C8 3C EC 53 00                   DCD sub_53EC3C
//.data.rel.ro : 01C754CC 84 EF 53 00                   DCD sub_53EF84
//.data.rel.ro : 01C754D0 EC EF 53 00                   DCD sub_53EFEC
//.data.rel.ro : 01C754D4 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01C754D8 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01C754DC 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01C754E0 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01C754E4 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01C754E8 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01C754EC B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01C754F0 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01C754F4 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01C754F8; public GameObject :
//.data.rel.ro : 01C754F8;   public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01C754F8; `typeinfo for'GameObject
//.data.rel.ro:01C754F8 D8 74 DF 01                   _ZTI10GameObject DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01C754F8; DATA XREF : .data.rel.ro : 01C5C900↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C5EBA8↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C60FBC↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C61280↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C62364↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C671BC↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C69780↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C6E790↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C711F8↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C754C0↑o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C7605C↓o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C7EAE0↓o
//.data.rel.ro : 01C754F8;.data.rel.ro:01C85D7C↓o
//.data.rel.ro : 01C754F8;.data.rel.ro:01CB3AE8↓o
//.data.rel.ro : 01C754F8;.data.rel.ro:01CB5460↓o ...
//.data.rel.ro : 01C754F8; reference to RTTI's type class
//.data.rel.ro:01C754FC 65 86 B9 01                   DCD _ZTS10GameObject; reference to type's name
//.data.rel.ro:01C75500 BC DA D0 01                   DCD _ZTIN4Sexy8RtObjectE; reference to parent's type name

//其中sub_53EF3C+10↑o或者sub_53EF3C+14↑o的sub_53EF3C是GAMEOBJECT_CONSTRUCTOR_OFFSET
#define GAMEOBJECT_CONSTRUCTOR_OFFSET GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr
//寻找该偏移方法：
//HEX搜索文本UIWidget
//然后比如你跳转到了诸如"CalendarWidgetEntryEvent7.UIWidget"字样时候
//把鼠标单击UIWidget的"U"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B39C67 55 49 57 69 64 67 65 74 00    aUiwidget DCB "UIWidget", 0; DATA XREF : sub_25DBD0 + 40↑o
//.rodata : 01B39C67; sub_25DBD0 + 48↑o
//.rodata:01B39C67;.text:off_25DC3C↑o
//.rodata : 01B39C67; sub_CF7704 + BC↑o
//.rodata:01B39C67; sub_CF7704 + CC↑o
//.rodata:01B39C67;.text:off_CF79B0↑o

//双击示例中DATA XREF: sub_25DBD0+40↑o位置
//跳转后按F5，所得如下：
//int sub_25DBD0()
//{
//    int result; // r0
//    int v1; // r4
//    int(__fastcall * v2)(int, const char*, int, int (*)()); // r6
//    int v3; // r0
//    int v4; // r0
//
//    result = dword_1D7C410;
//    if (!dword_1D7C410)
//    {
//        v1 = sub_12501AC();
//        dword_1D7C410 = v1;
//        v2 = *(int(__fastcall**)(int, const char*, int, int (*)()))(*(_DWORD*)v1 + 32);
//        v3 = sub_53EA0C();
//        v4 = v2(v1, "UIWidget", v3, sub_25DC48);
//        sub_25DC7C(v4);
//        return dword_1D7C410;
//    }
//    return result;
//}

//其中sub_53EA0C即GAMEOBJECT_GETTYPE_OFFSET
#define GAMEOBJECT_GETTYPE_OFFSET GameObject_GAMEOBJECT_GETTYPE_OFFSETAddr
//你玩我呢？这不就是BoardEntity的OFFSET_BOARDENTITY_DIE吗？？？？？
#define GAMEOBJECT_FUNCTION_DIE_OFFSET GameObject_GAMEOBJECT_FUNCTION_DIE_OFFSETAddr

class Renderable
{
public:
    virtual ~Renderable() {};
    virtual void Draw(void* g) {};
    virtual int GetRenderOrder() {};
};

class GameObject : public Sexy::RtObject
{
public:
    DEFINE_RT_CLASS_GET_CLASS_WRAPPER(GAMEOBJECT_GETTYPE_OFFSET);

    int unk_0x4;
    Sexy::RtWeakPtr<Sexy::RtObject> m_thisPtr;

    void Die()
    {
        typedef void(*func)(void*);
        func pFunc = (func)getActualOffset(GAMEOBJECT_FUNCTION_DIE_OFFSET);
        pFunc(this);
    }

    // Called when the object is serialized from a JSON
    virtual void RegisterForEvents() {};
    virtual void Function8() {};
    virtual void Function9() {};
    virtual void Function10() {};
    virtual void Function11() {};
    virtual void Destroy() {};
};