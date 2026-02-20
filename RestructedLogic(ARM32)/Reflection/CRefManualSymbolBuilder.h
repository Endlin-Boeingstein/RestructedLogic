#pragma once
#include "RClass.h"
#include "RClassRef.h"

#include "../Sexy/DelegateBase.h"
#include "../Logging.h"

//寻找该偏移方法：
//HEX搜索文本CRefManualTypeBuilder::GetInnerTemplateTypeName: e
//然后比如你跳转到了诸如"CRefManualTypeBuilder::GetInnerTemplateTypeName: empty type name, probably resulting from a GetType<T>() without an inTypeName argument"字样时候
//把鼠标单击CRefManualTypeBuilder::GetInnerTemplateTypeName: e的"C"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01B51365 79 70 65 4E 61 6D 65 3A 20 65 + DCB "tType<T>() without an inTypeName argument", 0
//.rodata : 01B513ED 43 52 65 66 4D 61 6E 75 61 6C + aCrefmanualtype DCB "CRefManualTypeBuilder::GetInnerTemplateTypeName: empty type name, probably resulting from a Ge"
//.rodata : 01B513ED 54 79 70 65 42 75 69 6C 64 65 + ; DATA XREF : sub_1232B84:loc_1232C44↑o
//.rodata : 01B513ED 72 3A 3A 47 65 74 49 6E 6E 65 + ; sub_1232B84 + C4↑o
//.rodata:01B513ED 72 54 65 6D 70 6C 61 74 65 54 + ;.text:off_1232D04↑o
//.rodata : 01B513ED 79 70 65 4E 61 6D 65 3A 20 65 + DCB "tType<T>() without an inTypeName argument", 0
//.rodata : 01B51475 43 52 65 66 4D 61 6E 75 61 6C + aCrefmanualtype_2 DCB "CRefManualTypeBuilder::GetMapInnerTemplateTypeName: empty type name, probably resulting from a"
//.rodata : 01B51475 54 79 70 65 42 75 69 6C 64 65 + ; DATA XREF : sub_1232D0C:loc_1232DF4↑o
//.rodata : 01B51475 72 3A 3A 47 65 74 4D 61 70 49 + ; sub_1232D0C + EC↑o
//.rodata:01B51475 6E 6E 65 72 54 65 6D 70 6C 61 + ;.text:off_1232F74↑o
//.rodata : 01B51475 74 65 54 79 70 65 4E 61 6D 65 + DCB " GetType<T>() without an inTypeName argument", 0
//.rodata : 01B51500 52 54 5F 43 4F 4D 4D 41 00    aRtComma DCB "RT_COMMA", 0; DATA XREF : sub_1232D0C + 90↑o
//.rodata : 01B51500; sub_1232D0C + 98↑o
//.rodata:01B51500;.text:off_1232F68↑o
//.rodata : 01B51500; sub_1232F7C + 60↑o
//.rodata:01B51500; sub_1232F7C + 64↑o
//.rodata:01B51500;.text:off_1233184↑o

//这个时候就已经可以根据绿色字符串得知两个偏移需要填什么了
//sub_1232B84对应OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAME
#define OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAME CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAMEAddr
//sub_1232D0C对应OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAME
#define OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAME CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAMEAddr

namespace Reflection
{
    class CRefManualSymbolBuilder
    {
    public:
        typedef void(*BuildSymbolsFunc)(CRefManualSymbolBuilder*, RClass*);
        typedef void* (*ConstructFunc)(void*);

        void GetInnerTemplateTypeName(const Sexy::SexyString& typeName)
        {
            typedef void(*func)(Sexy::SexyString&, const Sexy::SexyString&);
            func pFunc = (func)getActualOffset(OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAME);
            Sexy::SexyString outStr;
            pFunc(outStr, typeName);
            LOGI("Out inner typename: %s", outStr.c_str());
        }

        void GetMapInnerTemplateTypeName(const Sexy::SexyString& typeName)
        {
            typedef void(*func)(Sexy::SexyString&, const Sexy::SexyString&);
            func pFunc = (func)getActualOffset(OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAME);
            Sexy::SexyString outStr;
            pFunc(outStr, typeName);
            LOGI("Out inner typename: %s", outStr.c_str());
        }

        virtual void Function0() {};
        virtual void Function1() {};
        virtual void Function2() {};
        virtual void Function3() {};
        virtual void Function4() {};
        virtual void RegisterClassWithProperties(const Sexy::SexyString& className, BuildSymbolsFunc buildPropsFunc, uint classSize, int unk) {};
        virtual void Function6() {};
        virtual void* GetPropertyOfType(ReflectionFieldType type, uint size) {};
        virtual void Function8() {};
        virtual void Function9() {};
        virtual void* RegisterPointerProperty(int, void*, void*) {};
        virtual RClassRef* GetClassRef(const Sexy::SexyString& className) {};
        virtual void SetRClassWithParent(void*, void*, int) {};
        virtual void RegisterProperty(void* rClass, const Sexy::SexyString& name, uint offset, void* type) {};
        virtual void Function14() {};
        virtual void RegisterCallback(void* rClass, const Sexy::SexyString& eventName, Sexy::DelegateBase* delegate, int unk, int unk2) {};
    };
}