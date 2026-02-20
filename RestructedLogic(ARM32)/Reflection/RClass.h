#pragma once
#include <vector>
#include "RField.h"

namespace Sexy
{
    class RtClass;
}

namespace Reflection
{
    class RClass
    {
    public:
        char pad_0000[52]; //0x0000
        uint32_t m_classSize; //0x0034
        char pad_0038[32]; //0x0038
        class Sexy::RtClass* m_rtclass; //0x0058
        class std::vector<RField*> m_fields; //0x005C

        // void DumpFields(bool dumpBase);
    };
}