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

uint_t getOriginalOffset(uint_t actualOffset) {
    return getOriginalOffset(actualOffset);
}

void PVZ2HookFunction(uint offset, void* replace, void** result, const char* funcName) 
{
    A64HookFunction((void*)getActualOffset(offset), replace, result);
    LOGI("Hooked %s", funcName);
}

void* copyVFTable(int vftableAddr, int numVFuncs)
{
    int size = numVFuncs * sizeof(int);
    void* vftableCopy = malloc(size);
    memcpy(vftableCopy, (const void*)vftableAddr, size);
    return vftableCopy;
}

void patchVFTable(void* vftable, void* funcAddr, int index)
{
    ((reinterpret_cast<void**>(vftable))[index]) = funcAddr;
}

void copyVFTable(void* dest, int vftableAddr, int numVFuncsToCopy) {
    int size = numVFuncsToCopy * sizeof(int);
    memcpy(dest, (const void*)vftableAddr, size);
}

void* createChildVFTable(int vFuncsCount, int parentVftable, int nuMVFuncsToCopy) {
    int size = vFuncsCount * sizeof(int);
    void* childVftable = malloc(size);
    copyVFTable(childVftable, parentVftable, nuMVFuncsToCopy);

    return childVftable;
}

void setVFTable(void* obj, uintptr_t newVftablePtr)
{
    *reinterpret_cast<int*>(uintptr_t(obj)) = newVftablePtr;
}

void* GetVirtualFunc(void* obj, int index) {
    void** vtable = *reinterpret_cast<void***>(obj);
    return vtable[index];
}