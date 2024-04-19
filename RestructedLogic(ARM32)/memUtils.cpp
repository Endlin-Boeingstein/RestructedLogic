#include "memUtils.h"
#include "Logging.h"

#include "x32/jni/include/Utils.h"
#include "x32/jni/libs/Substrate/SubstrateHook.h"
//#include "x32/jni/libs/GlossHook/Gloss.h"

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
    MSHookFunction((void*)getActualOffset(offset), replace, result);
    //GlossHook((void*)getActualOffset(offset), replace, result);
    LOGI("Hooked %s", funcName);
}