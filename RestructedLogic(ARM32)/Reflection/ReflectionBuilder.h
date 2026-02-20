#pragma once
#include <vector>
#include <map>
#include <string>

#include "../Sexy/RtClass.h"
#include "CRefManualSymbolBuilder.h"
#include "RCustomType/TStdVectorManipulator.h"

//寻找该偏移方法：
//HEX搜索文本AdaptorMultiPurchase
//然后比如你跳转到了诸如"POPANIM_MISSING_PAM.....AdaptorMultiPurchase"字样时候
//把鼠标单击AdaptorMultiPurchase的"A"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AD9B68 41 64 61 70 74 6F 72 4D 75 6C + aAdaptormultipu_0 DCB "AdaptorMultiPurchase", 0
//.rodata : 01AD9B68 74 69 50 75 72 63 68 61 73 65 + ; DATA XREF : sub_24F2E8 + 40↑o
//.rodata : 01AD9B68 00; sub_24F2E8 + 48↑o
//.rodata:01AD9B68;.text:off_24F354↑o
//.rodata : 01AD9B68; sub_24F428 + 4C↑o
//.rodata:01AD9B68; sub_24F428 + 64↑o
//.rodata:01AD9B68;.text:off_24F518↑o
//.rodata : 01AD9B68; sub_D009BC + 4C↑o
//.rodata:01AD9B68; sub_D009BC + 64↑o
//.rodata:01AD9B68;.text:off_D00AC8↑o

//这个时候双击示例中sub_24F428+4C↑o或者sub_24F428+64↑o位置
//跳转后按F5，所得如下：
//int sub_24F428()
//{
//    int v0; // r0
//    int v1; // r0
//    int v2; // r4
//    void(__fastcall * v3)(int, int*, int (*)(), int, _DWORD); // r6
//    int v5[2]; // [sp+8h] [bp-20h] BYREF
//    void* v6; // [sp+10h] [bp-18h]
//    int v7; // [sp+14h] [bp-14h]
//
//    v0 = sub_123B308();
//    if (v0)
//    {
//        v1 = sub_123B35C(v0);
//        v2 = v1;
//        if (v1)
//        {
//            v3 = *(void(__fastcall**)(int, int*, int (*)(), int, _DWORD))(*(_DWORD*)v1 + 20);
//            v6 = (void*)operator new(0x20u);
//            v5[0] = 33;
//            v5[1] = 20;
//            strcpy((char*)v6, "AdaptorMultiPurchase");
//            v3(v2, v5, sub_24F52C, 264, 0);
//            if ((v5[0] & 1) != 0)
//                operator delete(v6);
//        }
//    }
//    return _stack_chk_guard - v7;
//}

//sub_123B308对应RT_BUILDER_REGISTERCLASS_FUNC1
#define RT_BUILDER_REGISTERCLASS_FUNC1 ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC1Addr
//sub_123B35C对应RT_BUILDER_REGISTERCLASS_FUNC2
#define RT_BUILDER_REGISTERCLASS_FUNC2 ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC2Addr


template <typename T>
using RTMap = std::map<Sexy::SexyString, T>;

template <typename T>
inline Reflection::ReflectionFieldType GetPropertyType()
{
    if (std::is_same<T, bool>::value)
    {
        return Reflection::Type_Bool;
    }
    if (std::is_same<T, int>::value || std::is_same<T, long>::value)
    {
        return Reflection::Type_IntType;
    }
    else if (std::is_same<T, uint>::value || std::is_same<T, Sexy::ulong>::value)
    {
        return Reflection::Type_UIntType;
    }
    else if (std::is_same<T, float>::value || std::is_same<T, double>::value)
    {
        return Reflection::Type_FloatType;
    }
    else if (std::is_same<T, Sexy::SexyString>::value)
    {
        return Reflection::Type_Char;
    }
}

void ForceRTClassRebuild(uint classPtr, uint getClassFunc);
void ReplaceRTClassPtr(uint classPtr, Sexy::RtClass* newClassPtr);

#define GET_SIZE(className, memberName) \
    sizeof(decltype(std::declval<className>().memberName)) \

#define GET_TYPE(className, memberName) \
    GetPropertyType<decltype(std::declval<className>().memberName)>()

// Registers a standard type property (int, float, bool...) ONLY use with standard properties. Templated properties have their own macro.
#define REGISTER_STANDARD_PROPERTY(builder, rClass, className, name) \
    void* prop_##name = (builder)->GetPropertyOfType(GET_TYPE(className, name), GET_SIZE(className, name)); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), prop_##name); \

#define REGISTER_INT_PROPERTY(builder, rClass, className, name) \
    void* prop_##name = (builder)->GetPropertyOfType(Reflection::Type_IntType, sizeof(int)); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), prop_##name); \

#define REGISTER_STANDARD_VECTOR_PROPERTY(builder, rClass, className, name, elementType) \
    void* prop_##name = (builder)->GetPropertyOfType(GetPropertyType<elementType>(), sizeof(elementType)); \
    Reflection::RCustomType::TStdVectorManipulator<elementType>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<elementType>(); \
    void* regProp_##name = (builder)->RegisterPointerProperty(2, prop_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_STANDARD_MAP_PROPERTY(builder, rClass, className, name, valueType) \
    void* prop_##name = (builder)->GetPropertyOfType(GetPropertyType<valueType>(), sizeof(valueType)); \
    Reflection::RCustomType::TStdVectorManipulator<int>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<int>(); \
    void* regProp_##name = (builder)->RegisterPointerProperty(6, prop_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_CLASS_PROPERTY(builder, rClass, className, classRefName, name) \
    void* prop_##name = (builder)->GetClassRef(#classRefName); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), prop_##name); \

#define REGISTER_CLASS_VECTOR_PROPERTY(builder, rClass, className, name, elementType) \
    void* prop_##name = (builder)->GetClassRef(#elementType); \
    Reflection::RCustomType::TStdVectorManipulator<elementType>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<elementType>(); \
    void* regProp_##name = (builder)->RegisterPointerProperty(2, prop_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_CLASS_MAP_PROPERTY(builder, rClass, className, name, valueType) \
    void* prop_##name = (builder)->GetClassRef(#valueType); \
    Reflection::RCustomType::TStdVectorManipulator<int>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<int>(); \
    void* regProp_##name = (builder)->RegisterPointerProperty(6, prop_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_CLASS_RTWEAKPTR_PROPERTY(builder, rClass, className, name, valueType) \
    void* prop_##name = (builder)->GetClassRef(#valueType); \
    void* regProp_##name = (builder)->RegisterPointerProperty(3, prop_##name, 0); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_RTWEAKPTR_VECTOR_PROPERTY(builder, rClass, className, name, valueType) \
    void* prop_##name = (builder)->GetClassRef(#valueType); \
    void* rtWeakPtrProp_##name = (builder)->RegisterPointerProperty(3, prop_##name, 0); \
    Reflection::RCustomType::TStdVectorManipulator<Sexy::RtWeakPtr<valueType>>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<Sexy::RtWeakPtr<valueType>>(); \
    void* vecProp_##name = (builder)->RegisterPointerProperty(2, rtWeakPtrProp_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), vecProp_##name); \

// Registers a Sexy::SexyString class property. ONLY use with Sexy::SexyString, not any other type of string.
#define REGISTER_STRING_PROPERTY(builder, rClass, className, name) \
    void* prop_##name = (builder)->GetPropertyOfType(Reflection::Type_Char, sizeof(char)); \
    void* regProp_##name = (builder)->RegisterPointerProperty(0, prop_##name, NULL); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name); \

#define REGISTER_STRING_VECTOR_PROPERTY(builder, rClass, className, name) \
    void* prop_##name = (builder)->GetPropertyOfType(Reflection::Type_Char, sizeof(char)); \
    Reflection::RCustomType::TStdVectorManipulator<Sexy::SexyString>* manip_##name = new Reflection::RCustomType::TStdVectorManipulator<Sexy::SexyString>(); \
    void* strProp_##name = (builder)->RegisterPointerProperty(0, prop_##name, NULL); \
    void* regProp_##name = (builder)->RegisterPointerProperty(2, strProp_##name, manip_##name); \
    (builder)->RegisterProperty(rClass, #name, offsetof(className, name), regProp_##name);

#define REGISTER_CLASS_WITH_PROPERTIES(builder, className) \
    (builder)->RegisterClassWithProperties(#className, className::buildSymbols, sizeof(className), 0); \

#define DECLARE_STATIC_RT_CLASS_MEMBERS(className) \
    public: \
        static void* vftable; \
        static Sexy::RtClass* s_rtClass; \
        static void modInit();

#define DECLARE_STATIC_RT_CLASS_MEMBERS_NO_VFTABLE_PATCH(className) \
    public: \
        static Sexy::RtClass* s_rtClass; \
        static void modInit();

#define DEFINE_STATIC_RT_CLASS_MEMBERS(className) \
    void* className::vftable = nullptr; \
    Sexy::RtClass* className::s_rtClass = nullptr;

#define DEFINE_STATIC_RT_CLASS_MEMBERS_NO_VFTABLE_PATCH(className) \
    Sexy::RtClass* className::s_rtClass = nullptr;

#define RT_CLASS_BUILD_SYMBOLS() \
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass) \

#define DEFINE_RT_CLASS_BUILD_SYMBOLS_WITHOUT_CLASS_PROPERTIES(className, parentClassName) \
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass) \
    { \
        Sexy::RtClass* rtClass = getRtClass(); \
        rtClass->SetRClass(rclass); \
        rclass->m_rtclass = rtClass; \
        Reflection::RClassRef* ref = builder->GetClassRef(#parentClassName); \
        Reflection::RClass* parent = ref->GetRClass(); \
        builder->SetRClassWithParent(rclass, parent, 0); \
    } \

#define DEFINE_RT_CLASS_NAME_MACRO(className)

#define RT_CLASS_BUILD_SYMBOLS_BEGIN(className, parentClassName) \
    static void buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass) \
    { \
        Sexy::RtClass* rtClass = getRtClass(); \
        rtClass->SetRClass(rclass); \
        rclass->m_rtclass = rtClass; \
        Reflection::RClassRef* ref = builder->GetClassRef(#parentClassName); \
        Reflection::RClass* parent = ref->GetRClass(); \

#define RT_CLASS_BUILD_SYMBOLS_END() \
        builder->SetRClassWithParent(rclass, parent, 0); \
    } \

#define RT_CLASS_STANDARD_PROPERTY(className, name) \
    REGISTER_STANDARD_PROPERTY(builder, rclass, className, name);

#define RT_CLASS_CLASS_PROPERTY(className, propClassName, name) \
    REGISTER_CLASS_PROPERTY(builder, rclass, className, propClassName, name);

#define DEFINE_RT_CLASS_REGISTER_CLASS_FUNCTION(className) \
    static void registerClass() \
    { \
        typedef void* (*func123B308)(); \
        func123B308 func_0x123B308 = (func123B308)getActualOffset(RT_BUILDER_REGISTERCLASS_FUNC1); \
        void* v0 = (void*)func_0x123B308(); \
        if (v0) \
        { \
            typedef void* (*func123B35C)(void*); \
            func123B35C func_0x123B35C = (func123B35C)getActualOffset(RT_BUILDER_REGISTERCLASS_FUNC2); \
            auto* builder = (Reflection::CRefManualSymbolBuilder*)func_0x123B35C(v0); \
            if (builder) \
            { \
                REGISTER_CLASS_WITH_PROPERTIES(builder, className); \
            } \
        } \
    }

#define DEFINE_RT_CLASS_REGISTER_CLASS_AND_STATES_FUNCTION(className) \
    static void registerClass() \
    { \
        typedef void* (*func123B308)(); \
        func123B308 func_0x123B308 = (func123B308)getActualOffset(RT_BUILDER_REGISTERCLASS_FUNC1); \
        void* v0 = (void*)func_0x123B308(); \
        if (v0) \
        { \
            typedef void* (*func123B35C)(void*); \
            func123B35C func_0x123B35C = (func123B35C)getActualOffset(RT_BUILDER_REGISTERCLASS_FUNC2); \
            auto* builder = (Reflection::CRefManualSymbolBuilder*)func_0x123B35C(v0); \
            if (builder) \
            { \
                REGISTER_CLASS_WITH_PROPERTIES(builder, className); \
            } \
        } \
        buildStates(); \
    }*/

#define DEFINE_RT_CLASS_CONSTRUCT_FUNCTION(className, baseCtorAddr) \
	static void* construct() \
	{ \
		auto* instance = new className(); \
		typedef void* (*ctorWithThisPtr)(void*); \
		ctorWithThisPtr baseCtor = (ctorWithThisPtr)getActualOffset(baseCtorAddr); \
		baseCtor(instance); \
		setVFTable(instance, (uintptr_t)vftable); \
		return instance; \
	};

#define DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_WITH_TI(className, baseCtorAddr, typeInfoAddr) \
    static void* construct() \
    { \
        auto* instance = new className(); \
        typedef void* (*ctorWithThisPtr)(void*); \
        ctorWithThisPtr baseCtor = (ctorWithThisPtr)getActualOffset(baseCtorAddr); \
        baseCtor(instance); \
        setVFTable(instance, (uintptr_t)vftable); \
        ((int*)instance)[4] = getActualOffset(typeInfoAddr); \
        return instance; \
    }

#define DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_NO_VFTABLE_PATCH(className) \
    static void* construct() \
    { \
		return new className(); \
    }

#define DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(className, baseCtorAddr) \
	static void* construct() \
	{ \
		auto* instance = new className(); \
		typedef void* (*ctorWithThisPtr)(void*); \
		ctorWithThisPtr baseCtor = (ctorWithThisPtr)getActualOffset(baseCtorAddr);

#define DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_END() \
		baseCtor(instance); \
		setVFTable(instance, (uintptr_t)vftable); \
		return instance; \
	};


//寻找该偏移方法：
//HEX搜索文本AdaptorMultiPurchase
//然后比如你跳转到了诸如"POPANIM_MISSING_PAM.....AdaptorMultiPurchase"字样时候
//把鼠标单击AdaptorMultiPurchase的"A"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01AD9B68 41 64 61 70 74 6F 72 4D 75 6C + aAdaptormultipu_0 DCB "AdaptorMultiPurchase", 0
//.rodata : 01AD9B68 74 69 50 75 72 63 68 61 73 65 + ; DATA XREF : sub_24F2E8 + 40↑o
//.rodata : 01AD9B68 00; sub_24F2E8 + 48↑o
//.rodata:01AD9B68;.text:off_24F354↑o
//.rodata : 01AD9B68; sub_24F428 + 4C↑o
//.rodata:01AD9B68; sub_24F428 + 64↑o
//.rodata:01AD9B68;.text:off_24F518↑o
//.rodata : 01AD9B68; sub_D009BC + 4C↑o
//.rodata:01AD9B68; sub_D009BC + 64↑o
//.rodata:01AD9B68;.text:off_D00AC8↑o

//双击示例位置的DATA XREF : sub_24F2E8 + 40↑o
//跳转后按F5，所得如下：
//int sub_24F2E8()
//{
//    int result; // r0
//    int v1; // r4
//    void(__fastcall * v2)(int, const char*, int, int (*)()); // r6
//    int v3; // r0
//
//    result = dword_1D7C24C;
//    if (!dword_1D7C24C)
//    {
//        v1 = sub_12501AC();
//        dword_1D7C24C = v1;
//        v2 = *(void(__fastcall**)(int, const char*, int, int (*)()))(*(_DWORD*)v1 + 32);
//        v3 = sub_4ADFDC();
//        v2(v1, "AdaptorMultiPurchase", v3, sub_24F360);
//        sub_24F428();
//        return dword_1D7C24C;
//    }
//    return result;
//}

//其中sub_12501AC则Sexy::RtClass* rtClass = ((initRtClass)getActualOffset(填入))();
#define DEFINE_RT_CLASS_GET_CLASS_FUNCTION(className, parentGetTypeAddr) \
    static Sexy::RtClass* getRtClass() \
    { \
        if (s_rtClass) \
            return s_rtClass; \
        \
        typedef Sexy::RtClass* (*initRtClass)(); \
        Sexy::RtClass* rtClass = ((initRtClass)getActualOffset(ReflectionBuilder_rtClassGetClassFuncAddr))(); \
        s_rtClass = rtClass; \
        \
        rtClassGetClassFunc parentGetType = (rtClassGetClassFunc)getActualOffset(parentGetTypeAddr); \
        int parent = (int)parentGetType(); \
        \
        typedef int (*rtClassRegisterClass)(void*, const char*, int, ParameterlessConstructorFunc); \
        rtClassRegisterClass regrtclass = *(rtClassRegisterClass*)(*(uintptr_t*)rtClass + 0x20); \
        regrtclass(rtClass, #className, (int)parent, className::construct); \
        \
        className::registerClass(); \
        return s_rtClass; \
    }

#define DEFINE_RT_CLASS_GET_CLASS_OVERRIDE(className, parentGetTypeAddr, existingGetTypeAddr, existingTypeAddr) \
    static Sexy::RtClass* getRtClass() \
    { \
        if (!s_rtClass) \
        { \
            Sexy::RtClass* rtClass = new Sexy::RtClass(); \
            s_rtClass = rtClass; \
            rtClassGetClassFunc parentGetType = (rtClassGetClassFunc)getActualOffset(parentGetTypeAddr); \
            Sexy::RtClass* parent = parentGetType(); \
            rtClass->RegisterClass(#className, parent, className::construct); \
            registerClass(); \
            uint dummy; \
            MSHookFunction((void*)getActualOffset(existingGetTypeAddr), (void*)className::getRTClass, (void**)&dummy); \
            ReplaceRTClassPtr(getActualOffset(existingTypeAddr), rtClass); \
            LOGI("Override...");    \
        } \
        return s_rtClass; \
    }


#define DEFINE_RT_CLASS_GET_CLASS_WRAPPER(getTypeAddr) \
    static Sexy::RtClass* getRtClass() \
    { \
        typedef Sexy::RtClass* (*getType)(); \
        getType pGetType = (getType)getActualOffset(getTypeAddr); \
        return pGetType(); \
    } 

#define DEFINE_RT_CLASS_GET_CLASS_NO_PROPERTIES_FUNCTION(className, parentGetTypeAddr) \
    static Sexy::RtClass* getRtClass() \
    { \
        if (!s_rtClass) \
        { \
            Sexy::RtClass* rtClass = new Sexy::RtClass(); \
            s_rtClass = rtClass; \
            rtClassGetClassFunc parentGetType = (rtClassGetClassFunc)getActualOffset(parentGetTypeAddr); \
            Sexy::RtClass* parent = parentGetType(); \
            rtClass->RegisterClass(#className, parent, className::construct); \
        } \
        return s_rtClass; \
    }

#define DEFINE_RTOBJECT_OVERRIDE_GETTYPE(className) \
    Sexy::RtClass* GetType() override { return className::getRtClass(); }

#define DECLARE_RTOBJECT_DTORS(className) \
    static void* Destroy(className* self); \
    static void DestroyAndDealloc(className* self) { \
        auto ptr = Destroy(self); \
        operator delete(ptr); \
    }