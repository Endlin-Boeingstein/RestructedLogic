#include "memUtils.h"
#include "Logging.h"

#include "x64/jni/include/Utils.h"
#include "x64/jni/libs/64InlineHook/And64InlineHook.hpp"

size_t g_libAddress = NULL;

size_t getLibraryAddress(const char *libName) {
  return get_libBase(libName);
}

size_t getActualOffset(size_t offset) {
  return getRealOffset(offset);
}

size_t getOriginalOffset(size_t actualOffset) {
  return getOriOffset(actualOffset);
}

void PVZ2HookFunction(size_t offset, void *replace, void **result, const char *funcName) {
  A64HookFunction((void *)getActualOffset(offset), replace, result);
  LOGI("Hooked %s", funcName);
}

void *copyVFTable(size_t vftableAddr, int numVFuncs) {
  int size = numVFuncs * sizeof(int);
  void *vftableCopy = malloc(size);
  memcpy(vftableCopy, (const void *)vftableAddr, size);
  return vftableCopy;
}

void patchVFTable(void *vftable, void *funcAddr, int index) {
  ((reinterpret_cast<void **>(vftable))[index]) = funcAddr;
}

void copyVFTable(void *dest, size_t vftableAddr, int numVFuncsToCopy) {
  int size = numVFuncsToCopy * sizeof(int);
  memcpy(dest, (const void *)vftableAddr, size);
}

void *createChildVFTable(int vFuncsCount, int parentVftable, int nuMVFuncsToCopy) {
  int size = vFuncsCount * sizeof(int);
  void *childVftable = malloc(size);
  copyVFTable(childVftable, parentVftable, nuMVFuncsToCopy);

  return childVftable;
}

void setVFTable(void *obj, size_t newVftablePtr) {
  *reinterpret_cast<int *>(size_t(obj)) = newVftablePtr;
}

void *GetVirtualFunc(void *obj, int index) {
  void **vtable = *reinterpret_cast<void ***>(obj);
  return vtable[index];
}