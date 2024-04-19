/*
 *  @date   : 2024/04/16
 *  @author : Endlin Boeingstein
 */
#include "Gloss.h"
using namespace Gloss::Inst;

uintptr_t GlossGetLibInfo(const char* lib_name, pid_t pid, char* lib_path, size_t* lib_mem_len)
{
    return uintptr_t();
}

gloss_lib GlossOpen(const char* lib_name)
{
    return gloss_lib();
}

int GlossClose(gloss_lib handle, bool is_dlclose)
{
    return 0;
}

uintptr_t GlossGetLibBias(const char* lib_name)
{
    return uintptr_t();
}

uintptr_t GlossGetLibBiasEx(gloss_lib handle)
{
    return uintptr_t();
}

const char* GlossGetLibPath(gloss_lib handle)
{
    return nullptr;
}

bool GlossGetLibPathEx(uintptr_t lib_addr, char* path)
{
    return false;
}

size_t GlossGetLibFileSize(const char* lib_name)
{
    return size_t();
}

uintptr_t GlossSymbol(gloss_lib handle, const char* name, size_t* sym_size)
{
    return uintptr_t();
}

uintptr_t GlossSymbolEx(uintptr_t lib_addr, const char* name, size_t* sym_size)
{
    return uintptr_t();
}

bool GlossAddr(uintptr_t lib_addr, uintptr_t* sym_addr, size_t* sym_size, char* sym_name)
{
    return false;
}

const char* GlossGetLibMachine(const char* libName)
{
    return nullptr;
}

const int GlossGetLibBit(const char* libName)
{
    return 0;
}

uintptr_t GlossGetLibSection(const char* libName, const char* sec_name, size_t* sec_size)
{
    return uintptr_t();
}

uintptr_t GlossGetLibSegment(const char* libName, unsigned int seg_type, size_t* seg_size)
{
    return uintptr_t();
}

bool SetMemoryPermission(uintptr_t addr, size_t len, p_flag* type)
{
    return false;
}

bool GetMemoryPermission(uintptr_t addr, p_flag* type, pid_t pid, const char* lib_name)
{
    return false;
}

void WriteMemory(void* addr, void* data, size_t size, bool vp)
{
}

void* ReadMemory(void* addr, void* data, size_t size, bool vp)
{
    return nullptr;
}

void MemoryFill(void* addr, uint8_t value, size_t size, bool vp)
{
}

void* GlossHook(void* sym_addr, void* new_func, void** old_func)
{
    return nullptr;
}

void* GlossHookAddr(void* func_addr, void* new_func, void** old_func, bool is_4_byte_hook, i_set mode)
{
    return nullptr;
}

void* GlossHookBranchB(void* branch_addr, void* new_func, void** old_func, i_set mode)
{
    return nullptr;
}

void* GlossHookBranchBL(void* branch_addr, void* new_func, void** old_func, i_set mode)
{
    return nullptr;
}

void* GlossHookBranchBLX(void* branch_addr, void* new_func, void** old_func, i_set mode)
{
    return nullptr;
}

void* GlossHookInternal(void* addr, GlossHookInternalCallback new_func, bool is_4_byte_hook, i_set mode)
{
    return nullptr;
}

void* GlossHookRedirect(void* redirect_addr, void* new_addr, bool is_4_byte_hook, i_set mode)
{
    return nullptr;
}

void* GlossGotHook(void* got_addr, void* new_func, void** old_func)
{
    return nullptr;
}

bool GlossLinkerHook(const char* dlfunc, GlossLinkerFuncProxy new_dlfunc, void** hook, void** hook2)
{
    return false;
}

void* GlossHookEx(const char* lib_name, const char* sym_name, void* new_func, void** old_func, GlossHookCallback call_back_func)
{
    return nullptr;
}

void* GlossGotHookEx(const char* lib_name, const char* sym_name, void* new_func, void** old_func, GlossHookCallback call_back_func)
{
    return nullptr;
}

void* GlossHookConstructor(const char* lib_name, void* offset_addr, void* new_func, void** old_func, bool is_4_byte_hook, i_set mode, GlossHookCallback call_back_func)
{
    return nullptr;
}

void GlossHookDisable(void* hook)
{
}

void GlossHookEnable(void* hook)
{
}

void GlossHookDelete(void* hook)
{
}

void GlossHookDisableAll(void* addr, i_set mode)
{
}

void GlossHookEnableAll(void* addr, i_set mode)
{
}

void GlossHookDeleteAll(void* addr, i_set mode)
{
}

int GlossHookGetCount(void* hook)
{
    return 0;
}

int GlossHookGetTotalCount(void* addr, i_set mode)
{
    return 0;
}

void* GlossHookGetPtr(void* addr, i_set mode)
{
    return nullptr;
}

void* GlossHookGetPtrEx(void* addr, int count, i_set mode)
{
    return nullptr;
}

int GlossHookGetStatus(void* hook)
{
    return 0;
}

void* GlossHookGetPrev(void* hook)
{
    return nullptr;
}

void* GlossHookGetNext(void* hook)
{
    return nullptr;
}

void GlossHookSetNewFunc(void* hook, void* new_func)
{
}

const int Gloss::Inst::CheckAbsoluteJump(uintptr_t addr)
{
    return 0;
}

const int Gloss::Inst::CheckRelativeJump(uintptr_t addr)
{
    return 0;
}

const branchs Gloss::Inst::GetBranch(uintptr_t addr, i_set mode)
{
    return branchs();
}

bool Gloss::Inst::IsThumb32(uint32_t addr)
{
    return false;
}

void Gloss::Inst::MakeThumb16NOP(uint32_t addr, size_t size)
{
}

void Gloss::Inst::MakeThumb32NOP(uint32_t addr, size_t size)
{
}

void Gloss::Inst::MakeThumbRET(uint32_t addr, uint8_t type)
{
}

const uint16_t Gloss::Inst::MakeThumb16B(uint32_t addr, uint32_t dest)
{
    return 0;
}

const uint16_t Gloss::Inst::MakeThumb16BCond(uint32_t addr, uint32_t dest, conds cond)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumb32B(uint32_t addr, uint32_t dest)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumb32BCond(uint32_t addr, uint32_t dest, conds cond)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumbBL(uint32_t addr, uint32_t func)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumbBL_W(uint32_t addr, uint32_t func)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumbBLX(uint32_t addr, uint32_t func)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeThumbBLX_W(uint32_t addr, uint32_t func)
{
    return 0;
}

const uint16_t Gloss::Inst::MakeThumbCB(uint32_t addr, uint32_t dest, gloss_reg::e_reg reg, bool is_cbnz)
{
    return 0;
}

int8_t Gloss::Inst::MakeThumbAbsoluteJump(uint32_t addr, uint32_t dest)
{
    return 0;
}

uint32_t Gloss::Inst::GetThumb16BranchDestination(uint32_t addr)
{
    return 0;
}

uint32_t Gloss::Inst::GetThumb32BranchDestination(uint32_t addr)
{
    return 0;
}

void Gloss::Inst::MakeArmNOP(uint32_t addr, size_t size)
{
}

void Gloss::Inst::MakeArmRET(uint32_t addr, uint8_t type)
{
}

const uint32_t Gloss::Inst::MakeArmB(uint32_t addr, uint32_t dest, conds cond)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeArmBL(uint32_t addr, uint32_t func, conds cond)
{
    return 0;
}

const uint32_t Gloss::Inst::MakeArmBLX(uint32_t addr, uint32_t func)
{
    return 0;
}

int8_t Gloss::Inst::MakeArmAbsoluteJump(uint32_t addr, uint32_t dest)
{
    return 0;
}

uint32_t Gloss::Inst::GetArmBranchDestination(uint32_t addr)
{
    return 0;
}

void MakeArm64NOP(uint64_t addr, size_t size)
{
}

void MakeArm64RET(uint64_t addr, uint8_t type)
{
}

const uint32_t MakeArm64B(uint64_t addr, uint64_t dest)
{
    return 0;
}

const uint32_t MakeArm64BCond(uint64_t addr, uint64_t dest, conds cond)
{
    return 0;
}

const uint32_t MakeArm64BL(uint64_t addr, uint64_t func)
{
    return 0;
}

const uint32_t MakeArm64CB(uint64_t addr, uint64_t dest, uint8_t reg, bool is_cbnz, bool is64)
{
    return 0;
}

int8_t MakeArm64AbsoluteJump(uint64_t addr, uint64_t dest, gloss_reg::e_reg reg)
{
    return 0;
}

int8_t MakeArm64AbsoluteJump32(uint64_t addr, uint64_t dest, gloss_reg::e_reg reg)
{
    return 0;
}

int8_t MakeArm64AbsoluteJumpRet(uint64_t addr, uint64_t dest, gloss_reg::e_reg reg)
{
    return 0;
}

uint64_t GetArm64BranchDestination(uint64_t addr)
{
    return 0;
}

const int Gloss::Inst::WriteByte(uintptr_t addr, void(*inst_func)(), size_t len)
{
    return 0;
}
