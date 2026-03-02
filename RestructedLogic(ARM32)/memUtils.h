#pragma once
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include "Logging.h"

#define LOG_RETURN_ADDRESS(level) \
  LOGI("%p", (size_tPTR)__builtin_return_address(level) - g_libAddress);

extern size_t g_libAddress;
// Get base address of a library (.so) loaded in memory.
size_t getLibraryAddress(const char *libName);
// Get actual offset of address inside libPVZ2.so
size_t getActualOffset(size_t offset);
// Get offset within libPVZ2.so from a running program
size_t getOriginalOffset(size_t actualOffset);
// Hook a function in libPVZ2
void PVZ2HookFunction(size_t offset, void *replace, void **result, const char *funcName);

void *copyVFTable(size_t vftableAddr, int numVFuncs);

void patchVFTable(void *vftable, void *funcAddr, int index);

void copyVFTable(void *dest, size_t vftableAddr, int numVFuncsToCopy);

void *createChildVFTable(int vFuncsCount, int parentVftable, int nuMVFuncsToCopy);

void setVFTable(void *obj, size_t newVftablePtr);

void *GetVirtualFunc(void *obj, int index);

template <typename R, typename... Args>
R CallVirtualFunc(void *obj, int index, Args... args) {
  void *func = GetVirtualFunc(obj, index);
  auto castedFunc = reinterpret_cast<R (*)(Args...)>(func);
  return castedFunc(args...);
}