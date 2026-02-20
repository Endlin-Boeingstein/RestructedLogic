#pragma once
#include "RtObject.h"
#include "../Reflection/RClass.h"
#include "../memUtils.h"
#include "../VersionAddresses.h"

#define RTOBJECT_GETTYPE_INDEX 0
#define RTOBJECT_FUNC1_INDEX 1
#define RTOBJECT_CONSTRUCT_INDEX 2
#define RTOBJECT_DESTRUCT_INDEX 3
#define RTOBJECT_ISTYPE_INDEX 4
#define RTOBJECT_FUNC5_INDEX 5
#define RTOBJECT_FUNC6_INDEX 6

typedef void* (*ParameterlessConstructorFunc)();

namespace Sexy
{
    class RtClass : public RtObject
    {
    public:
        const char* TypeName;
        class RtClass* m_parentType;
        void* m_fConstructor;
        char pad_0010[20]; //0x0010
        class Reflection::RClass* m_rclass; //0x0024

        RtClass()
        {
            typedef void(*rtClassCtorFunc)(void*);
            //寻找该偏移方法：
            //使用Hex搜索System.RtClasses，直到出现诸如"System.RtClasses.super"字样时
            //把鼠标单击System.RtClasses.super的"S"上面，然后根据该偏移让ida pro跳转
            //这个时候，如下所示：
            /*.rodata:01B51E97 53 79 73 74 65 6D 2E 52 74 43 + aSystemRtclasse DCB "System.RtClasses", 0
                .rodata : 01B51E97 6C 61 73 73 65 73 00; DATA XREF : sub_1250518 + E4↑o
                .rodata : 01B51E97; sub_1250518 + E8↑o
                .rodata:01B51E97;.text:off_125072C↑o*/

            //其中示例中DATA XREF: sub_1250518+E4↑o位置的sub_1250518就是这个偏移的位置
            rtClassCtorFunc pFunc = (rtClassCtorFunc)getActualOffset(RtClass_rtClassCtorFuncAddr);
            pFunc(this);
        }

        void SetRClass(Reflection::RClass* rclass);

        virtual RtClass* GetType() {};
        virtual bool Function1() {};
        virtual void Destruct1() {};
        virtual void Destruct2() {};
        virtual bool IsType(RtClass* type) {};
        virtual bool Function5() {};
        virtual void Function6() {};
        virtual void Function7() {};
        virtual void* RegisterClass(RtClass* rtclass, const char* typeName, RtClass* parentType, ParameterlessConstructorFunc ctor) {};
    };
}

typedef Sexy::RtClass* (*rtClassCtorFunc)();
typedef Sexy::RtClass* (*rtClassGetClassFunc)();
typedef void(*rtClassSetRClassFunc)(Sexy::RtClass*, Reflection::RClass*);