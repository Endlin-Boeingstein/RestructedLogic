#include "memUtils.h"
#include "Logging.h"

#include "x64/jni/include/Utils.h"
#include "x64/jni/libs/64InlineHook/And64InlineHook.hpp"

uint g_libAddress = NULL;

uint getLibraryAddress(const char* libName) {
    return get_libBase(libName);
}

uint getActualOffset(uint offset)
{
    return getRealOffset(offset);
}

void PVZ2HookFunction(uint offset, void* replace, void** result, const char* funcName) 
{
    A64HookFunction((void*)getActualOffset(offset), replace, result);
    LOGI("Hooked %s", funcName);
}