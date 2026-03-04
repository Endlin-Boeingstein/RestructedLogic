#include "RestructedLogic_ARM64_.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unistd.h>
#include "memUtils.h"
#include "SexyTypes.h"
#include "./PvZ2/Board.h"
#include "VersionAddresses.h"
#include "./PvZ2/WorldMap.h"
#include <mutex>
#include <fstream>
#include <sys/stat.h>
#include "Decrypt/picosha2.h"
#include "Decrypt/aes.h"
#include <thread>
#include <vector>
#include <fcntl.h>
#include "VersionRtonIDs.h"

//友情提示：该ARM64工程所有功能均未测试，据估计应当全部重写（以支持64位指针），故劳烦修好后再进行测试，尤其是数据包载入，谢谢！

namespace fs = std::filesystem;

/**
 * 递归创建目录 (模拟 mkdir -p)
 * @param path 目标绝对路径
 * @return 是否创建成功或目录已存在
 */
bool makePath(const std::string& path) {
    std::string tmp_path = path;

    // 确保路径以斜杠结尾，方便统一逻辑处理
    if (tmp_path.empty()) return false;
    if (tmp_path.back() != '/') {
        tmp_path += '/';
    }

    size_t pos = 0;
    // 找到每一个 '/' 的位置并逐层创建
    // 从 pos+1 开始，跳过根目录的第一个 '/'
    while ((pos = tmp_path.find('/', pos + 1)) != std::string::npos) {
        std::string dir = tmp_path.substr(0, pos);

        // 尝试创建目录
        if (mkdir(dir.c_str(), 0777) != 0) {
            // 如果错误原因不是“目录已存在”，则返回失败
            if (errno != EEXIST) {
                return false;
            }
        }
    }
    return true;
}



#pragma region Alias to ID

class ZombieAlmanac
{
public:
    void* vftable;
    std::map<Sexy::SexyString, uint> m_aliasToId;
};

class PlantNameMapper
{
public:
    void* vftable;
    std::map<Sexy::SexyString, uint> m_aliasToId;
};

#define FIRST_FREE_ZOMBIE_ID 441
#define FIRST_FREE_PLANT_ID firstFreePlantID

std::vector<Sexy::SexyString> g_modPlantTypenames;
std::vector<Sexy::SexyString> g_modZombieTypenames;

#define REGISTER_PLANT_TYPENAME(typename) \
    g_modPlantTypenames.push_back(typename); \

#define REGISTER_ZOMBIE_TYPENAME(typename) \
    g_modZombieTypenames.push_back(typename); \

typedef ZombieAlmanac* (*ZombieAlmanacCtor)(ZombieAlmanac*);
ZombieAlmanacCtor oZombieAlmanacCtor = NULL;

void* hkCreateZombieTypenameMap(ZombieAlmanac* a1)
{
    // Let the game create the original alias->id map
    oZombieAlmanacCtor(a1);
    // Now add our own zombie aliases to it 
    // (mod aliases can be registered with the REGISTER_ZOMBIE_TYPENAME macro)
    g_modZombieTypenames.clear();
    //循环加入
    for (int i = 0; i < 109; i++) {
        REGISTER_ZOMBIE_TYPENAME("new_added_zombie_" + i);
    }
    LOGI("Extra zombie typenames = %d", g_modZombieTypenames.size());
    for (int iter = 0; iter < g_modZombieTypenames.size(); iter++)
    {
        LOGI("Registering extra zombie typename %s", g_modZombieTypenames[iter].c_str());
        a1->m_aliasToId[g_modZombieTypenames[iter]] = FIRST_FREE_ZOMBIE_ID + iter;
    }

    return a1;
}

typedef PlantNameMapper* (*PlantNameMapperCtor)(PlantNameMapper*);
PlantNameMapperCtor oPlantNameMapperCtor = NULL;

void* hkCreatePlantNameMapper(PlantNameMapper* self)
{
    // Same deal with the ZombieAlamanc::ctor hook
    oPlantNameMapperCtor(self);
    g_modPlantTypenames.clear();
    for (int i = 0; i < 109; i++) {
        REGISTER_PLANT_TYPENAME(("new_added_plant_" + i));
    }
    LOGI("Extra typenames size = %d", g_modPlantTypenames.size());
    for (int iter = 0; iter < g_modPlantTypenames.size(); iter++)
    {
        LOGI("Registering plant %s", g_modPlantTypenames[iter].c_str());
        self->m_aliasToId[g_modPlantTypenames[iter]] = FIRST_FREE_PLANT_ID + iter;
    }

    return self;
}

#pragma endregion

#pragma region Mummy Memory Fix

// The original function is broken for some reason. We don't need it
uint oCamelZombieFunc = NULL;

typedef void(*camelMinigameModuleFunc)(int, int, int);
camelMinigameModuleFunc cmmFunc = (camelMinigameModuleFunc)getActualOffset(camelMinigameModuleFuncAddr);

void hkCamelZombieFunc(int a1, int a2, int a3)
{
    // Redirect call to some function in CamelMinigameModule
    // This fixes the crash when camels are rising from the ground
    cmmFunc(a1, a2, a3);
}

#pragma endregion

#pragma region Piano Zombie List

typedef bool (*initZombiePianoList)(int, int);
initZombiePianoList oInitZombiePianoList = NULL;

std::vector<Sexy::SexyString>* g_pianoList = NULL;
bool g_pianoListInitialized = false;

bool hkInitZombiePianoList(int a1, int a2)
{
    // This function is called every frame when a piano zombie is on screen
    // So this global bool is needed to prevent wasting a massive amount of cpu time
    if (!g_pianoListInitialized)
    {
        bool orig = oInitZombiePianoList(a1, a2);

        uint ptrAddr = getActualOffset(ZombiePianoListAddr); // address of piano zombie's list in memory
        g_pianoList = reinterpret_cast<std::vector<Sexy::SexyString>*>(ptrAddr);

        // @todo: add this to piano zombie's props instead?
        g_pianoList->clear();
        g_pianoList->push_back("cowboy");
        g_pianoList->push_back("cowboy_armor1");
        g_pianoList->push_back("cowboy_armor2");
        g_pianoList->push_back("cowboy_armor4");
        g_pianoList->push_back("pirate_gargantuar");

        LOGI("Initialized global piano list");
        g_pianoListInitialized = true;
    }
    return oInitZombiePianoList(a1, a2);
}

#pragma endregion

#pragma region Vertical World Map Scrolling
//我不得不骂两句了，好一个O3优化，好一个内联函数！
//10.0以后的版本中，该部分函数直接被遗弃了，保留了函数但是删除了引用
//而引用它们的函数则直接通过内联把逻辑塞自己函数里了
//所以目前为止使用新版本的改版并没有出现能使用地图垂直移动的先例
//那我就写个新旧通用的函数，造福一下大众吧！

//本来我完全可以让你们每个版本都去找通用的三个偏移的，但是为了你们旧版本的，我采用条件调用了
//旧版只需要找一个偏移，而新版则需要找三个

//新版需要hook三个函数，而且由于该死的内联，不能把函数全反编译了，所以直接暴力扩边界让它们强行切到垂直移动判定
//拖动函数:
typedef int (*worldMapScroll)(uintptr_t, int, int);
worldMapScroll oworldMapScroll = NULL;
int hkworldMapScroll(uintptr_t a1, int a2, int a3) {
    *(int32_t*)(a1 + 312) = -1000000000;
    *(int32_t*)(a1 + 316) = -1000000000;
    *(int32_t*)(a1 + 320) = 2000000000;
    *(int32_t*)(a1 + 324) = 2000000000;
    int result = oworldMapScroll(a1, a2, a3);
    return result;
}
//居中函数：
typedef int (*KeepCenter)(uintptr_t, uint*, bool);
KeepCenter oKeepCenter = NULL;
int hkKeepCenter(uintptr_t a1, uint* a2, bool a3) {
    *(int32_t*)(a1 + 312) = -1000000000;
    *(int32_t*)(a1 + 316) = -1000000000;
    *(int32_t*)(a1 + 320) = 2000000000;
    *(int32_t*)(a1 + 324) = 2000000000;
    int result = oKeepCenter(a1, a2, 1);
    return result;
}
//惯性函数：
typedef int (*ScrollInertance)(uintptr_t);
ScrollInertance oScrollInertance = NULL;
int hkScrollInertance(uintptr_t a1) {
    *(int32_t*)(a1 + 312) = -1000000000;
    *(int32_t*)(a1 + 316) = -1000000000;
    *(int32_t*)(a1 + 320) = 2000000000;
    *(int32_t*)(a1 + 324) = 2000000000;
    int result = oScrollInertance(a1);
    return result;
}


//旧函数（10.0版本前有效）
typedef int (*worldMapDoMovement)(void*, float, float, bool);
worldMapDoMovement oWorldMapDoMovement = NULL;

//是否移动
bool g_allowVerticalMovement = true;
//要你有何用？
//移动处理函数
//int worldMapBoundaryMovement(WorldMap* self, float fX, float fY, bool allowVerticalMovement)
//{
//    if (allowVerticalMovement) {
//        //地图垂直移动修复
//        self->m_posX = fX;
//        self->m_posY = fY;
//    }
//    else {
//        if (fX <= self->m_boundaryX)
//        {
//            fX = self->m_boundaryX;
//        }
//
//        if (fX >= self->m_boundaryX + self->m_boundaryWidth)
//        {
//            fX = self->m_boundaryX + self->m_boundaryWidth;
//        }
//
//        if (fY <= self->m_boundaryY)
//        {
//            fY = self->m_boundaryY;
//        }
//
//        if (fY >= self->m_boundaryY + self->m_boundaryHeight)
//        {
//            fY = self->m_boundaryY + self->m_boundaryHeight;
//        }
//    }
//    return 1;
//}

//回归本源
int hkWorldMapDoMovement(void* map, float fX, float fY, bool allowVerticalMovement)
{
    LOGI("Doing map movement: fX - %d, fY - %d", fX, fY);
    return oWorldMapDoMovement(map, fX, fY, g_allowVerticalMovement);
}
#pragma endregion

#pragma region Dumb Hardcoded Immunities (Healer/Magician)

// we don't need to save a pointer to the original functions
uint dispose;

void hkMagicianHealerConditionFunc(int a1, int condition)
{
    // Hardcoded immunity checks would go here
    return;
}

bool hkMagicianHealerImmuneToShrink(int a1)
{
    // true = immune to shrinking
    return false;
}

bool hkMagicianInitializeFamilyImmunities(int a1, int64_t a2)
{
    typedef bool(*zFamilyFunc)(int);
    zFamilyFunc func = (zFamilyFunc)getActualOffset(zFamilyFuncAddr); // function 93 in Zombie's vftable 
    return func(a1);
}

#pragma endregion

#pragma region PrimeGlyphCacheLimitationDescription
//此代码为融小宝对RestructedLogic工程的私有化改造功能之一，并未根据RestructedLogic的GPL-3.0协议进行公开，我已拥有相关证据，你不守规矩，就别怪我强制公开了，并且我也没用你的写法，自己写的
//也不是啥秘密，按照一般查找流程都能找到
//再不济你去https://www.bilibili.com/opus/657868413102718978一路大佬的帖子，打开IDA PRO就知道怎么找了
//实际上我是先去找RSB读取函数，然后再找这里的，一路大佬的帖子有一个地方会卡住人（实际上是你不会确认位置），所以使用RSB主读取函数寻找法就能找到了。
//你要是恼羞成怒，还以为我偷别人的抢别人的，那好，这段的伪C代码（10.3版本）我贴在这了
//int __fastcall sub_1697E88(_DWORD* a1, int a2)
//{
//    int v4; // r7
//    int* v5; // r6
//    int v6; // r1
//    int v7; // r3
//    int v8; // r0
//    int v9; // r0
//    int v10; // r0
//    int v11; // r0
//    int v12; // r5
//    int v13; // r0
//    int v14; // r0
//    __int64 v15; // r0
//    __int64 v16; // r0
//    int v17; // r7
//    int v18; // r5
//    int v20[2]; // [sp+10h] [bp-2F8h] BYREF
//    void* v21; // [sp+18h] [bp-2F0h]
//    char v22[16]; // [sp+20h] [bp-2E8h] BYREF
//    char v23[536]; // [sp+30h] [bp-2D8h] BYREF
//    int v24; // [sp+248h] [bp-C0h]
//    int v25; // [sp+2A4h] [bp-64h]
//    int v26; // [sp+2ECh] [bp-1Ch]
//
//    sub_1716838(sub_169B238, sub_169B248, j_realloc);
//    v4 = *(_DWORD*)(a2 + 1304);
//    if (*(_DWORD*)(a2 + 1300) < v4)
//        v4 = *(_DWORD*)(a2 + 1300);
//    v5 = (int*)operator new(0x130u);
//    v6 = ((int (*)(void))sub_169B258)();
//    v7 = 2048;
//    if (v4 <= 1024)
//        v7 = 1024;
//    if (v4 <= 640)
//        v7 = 512;
//    sub_177ECF4(v5, v6, a2, v7);
//    a1[1] = v5;
//    v8 = *v5;
//    v5[59] = 1;
//    v9 = (*(int(__fastcall**)(int*, int, int))(v8 + 12))(v5, 1, 1);
//    v10 = sub_169B258(v9);
//    v11 = sub_16CF03C(v10);
//    sub_16CF08C(v11);
//    v12 = operator new(0xB500u);
//    v13 = sub_16D901C(v12, 0);
//    *a1 = v12;
//    v14 = sub_169B258(v13);
//    sub_16DA6F8(v12, v14);
//    sub_16CF418(*a1);
//    (*(void(__fastcall**)(_DWORD))(*(_DWORD*)*a1 + 8))(*a1);
//    v21 = 0;
//    v20[1] = 0;
//    v20[0] = 0;
//    sub_2F06A8((int)v20, (wchar_t*)&off_20381A8, 8u);
//    v15 = sub_14E138C(v22, 1);
//    sub_1698158(v23, HIDWORD(v15), v20, 7, v15);
//    if ((v20[0] & 1) != 0)
//        operator delete(v21);
//    v16 = sub_14E138C(v20, 0);
//    v25 = sub_14E1548(v16, HIDWORD(v16));
//    v24 = 1;
//    v17 = (*(int(__fastcall**)(_DWORD, char*, _DWORD, _DWORD, int, int, int))(*(_DWORD*)*a1 + 32))(
//        *a1,
//        v23,
//        0,
//        0,
//        0xFFFF,
//        -1,
//        1);
//    v18 = operator new(0x2C8u);
//    sub_1694728(v18, v17, v23);
//    a1[2] = v18;
//    a1[3] = v18;
//    return _stack_chk_guard - v26;
//}
//还有这个，这个就是最终的地址，看看，看看，是不是和下面实装的代码很像？
//我半年来我就看看，这破圈子把在国内打破so代码垄断的人赶走后，会发展成什么样
//结果呢？维护垄断并攻击技术开放的人成了最大受益者，甚至RestructedLogic都变成了某些人私有的玩物！！！！！
//这大半年来国内已经非常落后了！有些人都投奔国外了！国内的人都开始为这些垄断付费了！
//故特实装该代码以大白于天下，勿忘开源之精神，与垄断者抗争到底！！！！！
//_DWORD* __fastcall sub_177ECF4(_DWORD* a1, int a2, int a3, int a4)
//{
//    _DWORD* result; // r0
//
//    sub_17A97BC();
//    *a1 = off_21E8698;
//    memset(a1 + 66, 0, 0x24u);
//    result = a1;
//    a1[22] = a4;
//    a1[75] = a3;
//    return result;
//}
#pragma endregion

#pragma region PrimeGlyphCacheLimitation
//无语了，连Limitation都能打成Limination，还得我去修正
typedef uint* (*PrimeGlyphCacheLimitation)(uint*, int, int, int);
PrimeGlyphCacheLimitation oPrimeGlyphCacheLimitation = NULL;

//一路：高端设备缓冲大小为2048，中端设备为1024，低端设备为512。经过测试，缓冲大小最大只能设为2048，设为更高值，会导致进入游戏后文字渲染全为空白，这与设为0的效果一致。
uint* hkPrimeGlyphCacheLimitation(uint* a1, int a2, int a3, int a4)
{
    //typedef int(*Func1)(int a1, int a2);
    //Func1 func = (Func1)getActualOffset(0x141D75C);
    //func((uint)a1, a2);
    //*a1 = getActualOffset(0x1DDB7B8);
    //memset(a1 + 66, 0, 0x24u);
    //a1[22] = 2048; //缓冲区大小
    //a1[75] = a3;
    //return a1;
    //你知不知道，你这样做是非常垃圾的做法？还是看我这个RL的创始人怎么改的吧！学着点！
    uint* result = oPrimeGlyphCacheLimitation(a1, a2, a3, a4);
    a1[22] = 2048;
    LOGI("Hooked sub_177ECF4: Modified a1[22] to %d", a1[22]);
    return result;

}

#pragma endregion

//已探明RSB读取入口（废了老大劲拿IDA PRO搁那推），先进行测试（目前为XOR加密未测试）
#pragma region RSB Decrypt
//// RSB decryption function (replace with your actual decryption algorithm)
//void decrypt_rsb(uint8_t* buffer, size_t size) {
//    const uint8_t key = 0x5A; // Example XOR key, replace with your decryption logic (e.g., AES)
//    for (size_t i = 0; i < size; i++) {
//        buffer[i] ^= key;
//    }
//    LOGI("Decrypted %zu bytes", size);
//    if (size >= 4) {
//        LOGI("First 4 bytes after decryption: %02x %02x %02x %02x",
//            buffer[0], buffer[1], buffer[2], buffer[3]);
//    }
//}
//
//// Hook function for RSBRead (completely replace original)
//void* hkRSBRead(int a1, unsigned int* a2, char* a3, int a4) {
//    void* v7 = nullptr;
//    int v16[513]; // Buffer for first 2048 bytes
//    unsigned int v12 = 0; // Data size
//
//    *a2 = 0;
//    *a3 = 0; // Default to invalid, set to 1 on success
//
//    // Read first 2048 bytes (encrypted)
//    int (*readFunc)(int, int*, int, int) = *(int (**)(int, int*, int, int))(*(int*)a1 + 40);
//    int readBytes = readFunc(a1, v16, 2048, 0);
//    LOGI("readFunc called, a1=%p, v16=%p, size=2048, offset=0, readBytes=%d",
//        (void*)a1, v16, readBytes);
//
//    if (readBytes <= 0) {
//        LOGI("Failed to read RSB data: readBytes=%d", readBytes);
//        return nullptr;
//    }
//
//    // Decrypt v16
//    decrypt_rsb((uint8_t*)v16, readBytes);
//
//    // Verify header (optional, for debugging)
//    if (*(int*)v16 != 0x72736230) { // "rsb0"
//        LOGI("Invalid RSB header after decryption: %08x", *(int*)v16);
//        return nullptr;
//    }
//
//    // Set header validity
//    *a3 = 1;
//
//    // Get data size (mimic original logic)
//    int v11 = 27;
//    if (a4 || v16[1] < 4) {
//        v11 = 3;
//    }
//    v12 = v16[v11];
//    LOGI("RSB data size (v12): %u bytes", v12);
//
//    // Allocate v7
//    v7 = operator new[](v12);
//    if (!v7) {
//        LOGI("Failed to allocate v7: size=%u", v12);
//        *a3 = 0;
//        return nullptr;
//    }
//
//    // Copy decrypted v16 to v7
//    if (v12 <= 2048) {
//        memcpy(v7, v16, v12);
//    }
//    else {
//        memcpy(v7, v16, 2048);
//        // Read and decrypt remaining data
//        readBytes = readFunc(a1, (int*)((char*)v7 + 2048), v12 - 2048, 2048);
//        LOGI("readFunc called, a1=%p, v7+2048=%p, size=%u, offset=2048, readBytes=%d",
//            (void*)a1, (char*)v7 + 2048, v12 - 2048, readBytes);
//
//        if (readBytes != (int)(v12 - 2048)) {
//            LOGI("Failed to read remaining RSB data: readBytes=%d, expected=%u",
//                readBytes, v12 - 2048);
//            operator delete[](v7);
//            *a3 = 0;
//            return nullptr;
//        }
//
//        // Decrypt remaining data
//        decrypt_rsb((uint8_t*)((char*)v7 + 2048), readBytes);
//    }
//
//    // Set output size
//    *a2 = v12;
//
//    return v7;
//}
#pragma endregion

//真正的RSB解密函数
#pragma region RSBPathChangeAndDecryptRSB


// ==========================================
// C++11 兼容的编译期字符串混淆
// ==========================================
template <size_t... Is> struct index_sequence {};
template <size_t N, size_t... Is> struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...> {};
template <size_t... Is> struct make_index_sequence<0, Is...> : index_sequence<Is...> {};

template <int XorKey, size_t N>
struct ObfuscatedString {
    char encrypted[N];
    template <size_t... Is>
    constexpr ObfuscatedString(const char* str, index_sequence<Is...>)
        : encrypted{ static_cast<char>(str[Is] ^ (XorKey + Is))... } {}

    inline std::string decrypt() const {
        std::string s; s.resize(N - 1);
        for (size_t i = 0; i < N - 1; ++i) s[i] = encrypted[i] ^ (XorKey + i);
        return s;
    }
};
#define HIDE_STR(s) (ObfuscatedString<(0x55 + __LINE__), sizeof(s)>(s, make_index_sequence<sizeof(s)>()).decrypt())


// 临时文件路径列表
static std::vector<std::string> g_tempFiles;
// 解密函数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//你的解密函数放在这里！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
void decrypt_rsb(uint8_t* data, size_t size) {
    // 基础检查：不仅要够头部的 20 字节，还得确保能放下至少 1 个加密块
    if (size < 36) return;

    // 1. 安全拦截：如果头已经是 "1bsr" (0x31 0x62 0x73 0x72)，说明已经解密过了
    // 这样可以防止二次解密导致数据彻底损坏
    if (data[0] == 0x31 && data[1] == 0x62 && data[2] == 0x73 && data[3] == 0x72) {
        return;
    }
    //检测到EBRL则跳过解密
    if (data[0] == 0x45 && data[1] == 0x42 && data[2] == 0x52 && data[3] == 0x4C) {
        return;
    }

    // 2. 校验 Magic (RSB2)
    if (memcmp(data, "RSB2", 4) != 0) return;

    // 3. 准备 Key (SHA256)
    std::string pwd = HIDE_STR("RestructedLogic_Encrypt_V0");
    uint8_t key[32];
    picosha2::hash256_one_by_one hasher;
    hasher.process(pwd.begin(), pwd.end());
    hasher.finish();
    hasher.get_hash_bytes(key, key + 32);

    uint8_t* ciphertext_start = data + 20;
    uint32_t total_cipher_len = (uint32_t)(size - 20);
    uint32_t num_blocks = total_cipher_len / 16;

    // 4. 多线程并行解密设置
    // 获取 CPU 核心数，通常 Android 手机返回 8
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;

    uint32_t blocks_per_thread = num_blocks / num_threads;
    std::vector<std::thread> threads;

    for (unsigned int t = 0; t < num_threads; ++t) {
        uint32_t start_block = t * blocks_per_thread;
        uint32_t end_block = (t == num_threads - 1) ? num_blocks : (t + 1) * blocks_per_thread;

        threads.emplace_back([=]() {
            uint32_t current_offset = start_block * 16;
            uint32_t thread_len = (end_block - start_block) * 16;
            if (thread_len == 0) return;

            struct AES_ctx ctx;
            uint8_t thread_iv[16];

            // CBC 解密的精髓：每一段的 IV 就是它前一个密文块
            if (start_block == 0) {
                // 第一段使用文件内置的初始 IV
                memcpy(thread_iv, data + 4, 16);
            }
            else {
                // 其他段使用前一个密文块作为其解密的初始 IV
                memcpy(thread_iv, ciphertext_start + current_offset - 16, 16);
            }

            AES_init_ctx_iv(&ctx, key, thread_iv);
            AES_CBC_decrypt_buffer(&ctx, ciphertext_start + current_offset, thread_len);
            });
    }

    // 等待所有线程完成
    for (auto& th : threads) th.join();

    // 5. 移除 Padding 并原地移动内存
    uint8_t pad = ciphertext_start[total_cipher_len - 1];
    if (pad > 0 && pad <= 16) {
        uint32_t plain_len = total_cipher_len - pad;
        // 核心移动：把明文覆盖到 data 最开头
        memmove(data, ciphertext_start, plain_len);
        // 清理末尾，确保“进化统计数据”逻辑读到的是干净数据
        memset(data + plain_len, 0, size - plain_len);
    }
}

//将文件头部替换为可识别四字节
bool maskFileHeader(const std::string& filePath, std::string tagstr) {
    // 1. 以读写模式打开文件 (注意不要加 O_TRUNC，否则文件会被清空！)
    int fd = open(filePath.c_str(), O_RDWR);
    if (fd < 0) return false;

    // 2. 准备新的 4 字节头
    const char* tag = tagstr.c_str();

    // 3. 使用 pwrite 直接覆盖偏移量为 0 的位置
    // 这一步是原子操作，只改动磁盘上最开始的 4 个字节
    ssize_t bytes = pwrite(fd, tag, 4, 0);

    // 4. 强制将修改刷入磁盘（防止断电丢失）
    fdatasync(fd);
    close(fd);

    return bytes == 4;
}

//检测是否ROOT
bool isRooted() {
    // 检查常见的 Root 路径和文件
    const char* paths[] = { "/system/app/Superuser.apk", "/sbin/su", "/system/bin/su", "/system/xbin/su" };
    for (auto path : paths) {
        if (access(path, F_OK) == 0) return true;
    }
    return false;
}

// 清理临时文件
void cleanupTempFiles() {
    for (const auto& path : g_tempFiles) {
        if (unlink(path.c_str()) == 0) {
            LOGI("Deleted temp file: %s", path.c_str());
        }
        else {
            LOGI("Failed to delete temp file: %s, errno=%d", path.c_str(), errno);
        }
    }
    g_tempFiles.clear();
}

//// 进程退出时清理
//__attribute__((destructor))
//void lib_cleanup() {
//    LOGI("Cleaning up temp files");
//    cleanupTempFiles();
//}

// 修改函数指针类型
typedef int (*RSBPathRecorder)(uintptr_t* a1);
RSBPathRecorder oRSBPathRecorder = nullptr;

int hkRSBPathRecorder(uintptr_t* a1) {
    LOGI("Hooking RSBPathRecorder");

    // 检查输入
    if (!oRSBPathRecorder) {
        LOGI("RSBPathRecorder: Original function is null");
        return 0;
    }
    if (!a1) {
        LOGI("RSBPathRecorder: a1 is null");
        return oRSBPathRecorder(a1);
    }

    // 调用原始函数
    int result = oRSBPathRecorder(a1);
    LOGI("RSBPathRecorder: Original function returned %d, a1[0]=0x%x, a1[1]=0x%x, a1[2]=0x%x",
        result, a1[0], a1[1], a1[2]);

    // 提取路径 - 使用安全的指针转换
    char* path_ptr = nullptr;
    if (a1[0] & 1) {
        path_ptr = reinterpret_cast<char*>(a1[2]);
    }
    else {
        path_ptr = reinterpret_cast<char*>(a1[1]);
    }

    // 检查指针有效性
    if (!path_ptr || reinterpret_cast<uintptr_t>(path_ptr) < 0x1000) {
        LOGI("RSBPathRecorder: Invalid path pointer %p, a1[0]=0x%",(void*)path_ptr, a1[0]);
        return result;
    }
    std::string original_path;
    size_t i;
    for (i = 0; i < 1024; ++i) {
        if (path_ptr[i] == '\0') {
            original_path = std::string(path_ptr, i);
            break;
        }
        if (i == 1023) {
            LOGI("RSBPathRecorder: Path too long or invalid");
            return result;
        }
    }
    if (original_path.empty()) {
        LOGI("RSBPathRecorder: Path is empty");
        return result;
    }
    LOGI("RSBPathRecorder: Original path=%s", original_path.c_str());

    //C++17新增优化
    fs::path fsOriPath = original_path;
    std::vector<std::string> path_components;
    //存入路径上各文件夹名称
    for (const auto& part : fsOriPath) {
        if (!part.empty() && part != "/") {
            path_components.push_back(part.string());
        }
    }
    //获取包名
    std::string pack_name = path_components[path_components.size() - 2];
    //获取数据包名
    std::string rsb_name = path_components[path_components.size() - 1];

    // 验证预期路径
    std::string expected_path = "/storage/emulated/0/Android/obb/" + pack_name + "/" + rsb_name;
    if (original_path != expected_path) {
        LOGI("RSBPathRecorder: Path mismatch, expected %s", expected_path.c_str());
        // 继续处理，允许非预期路径
    }

    //定义临时路径
    // 创建缓存目录/data/user/0/com.ea.game.pvz2_改版名/files
    std::string cache_dir = "/data/user/0/"+pack_name+"/files";///storage/emulated/0/Android/data/com.ea.game.pvz2_na/cache
    if (mkdir(cache_dir.c_str(), 0777) != 0 && errno != EEXIST) {
        LOGI("RSBPathRecorder: Failed to create %s, errno=%d", cache_dir.c_str(), errno);
        return result;
    }
    std::string temp_path = cache_dir + "/.cache_data_file";
    std::ofstream out_file(temp_path.c_str(), std::ios::binary);
    if (!out_file.is_open()) {
        LOGI("RSBPathRecorder: Failed to create %s, errno=%d", temp_path.c_str(), errno);
        return result;
    }
    // 读取 RSB 文件，读不到文件直接切到temp_path
    std::ifstream in_file(original_path.c_str(), std::ios::binary | std::ios::ate);
    if (!in_file.is_open()) {
        LOGI("RSBPathRecorder: Failed to open %s, errno=%d", original_path.c_str(), errno);
        /*return result;*/
    }
    else {
        std::streamsize file_size = in_file.tellg();
        in_file.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(file_size);
        in_file.read(reinterpret_cast<char*>(buffer.data()), file_size);
        if (!in_file) {
            LOGI("RSBPathRecorder: Failed to read %s, errno=%d", original_path.c_str(), errno);
            in_file.close();
            return result;
        }
        in_file.close();
        LOGI("RSBPathRecorder: Read %lld bytes", static_cast<long long>(file_size));
        if (buffer.data()[0] == 0x45 && buffer.data()[1] == 0x42 && buffer.data()[2] == 0x52 && buffer.data()[3] == 0x4C && isRooted()) {
            //是ROOT重写数据包头
            if (!maskFileHeader(original_path.c_str(), "RSB2")) {
                //重写失败报错
                LOGI("RSB_TRACE: RSB2 overrides failed.");
                return result;
            }
            else LOGI("RSB_TRACE: RSB2 overrides succeed.");
        }
        //检测到EBRL，跳过转移文件
        if (buffer.data()[0] == 0x45 && buffer.data()[1] == 0x42 && buffer.data()[2] == 0x52 && buffer.data()[3] == 0x4C) {
            LOGI("RSBPathRecorder: Detecting EBRL, using temp_path.");
        }
        else {
            // 解密
            decrypt_rsb(buffer.data(), static_cast<size_t>(file_size));


            out_file.write(reinterpret_cast<char*>(buffer.data()), file_size);
            if (!out_file) {
                LOGI("RSBPathRecorder: Failed to write %s, errno=%d", temp_path.c_str(), errno);
                out_file.close();
                return result;
            }
            out_file.close();
            LOGI("RSBPathRecorder: Saved to %s", temp_path.c_str());
            //没必要清理临时数据了，因为现在的临时通道作为隐藏通道来使用，而加密数据包会被干掉，做到一次解密终生秒进
                /*g_tempFiles.push_back(temp_path);*/
                //新增功能，清理加密数据包
                /*g_tempFiles.push_back(original_path);*/
                /*cleanupTempFiles();*/
                //不需要了，我直接重写
            //这个也不需要了，直接把头重写就行了
            /*int rl_fd = open(original_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (rl_fd >= 0) {
                write(rl_fd, "EBRL", 4);
                close(rl_fd);
            }*/
            //重写数据包头部为EBRL
            if (!isRooted()) {
                //没ROOT重写数据包头
                if (!maskFileHeader(original_path.c_str(), "EBRL")) {
                    //重写失败报错
                    LOGI("RSB_TRACE: EBRL overrides failed.");
                    return result;
                }
                else LOGI("RSB_TRACE: EBRL overrides succeed.");
            }
            //ROOT警报
            else {
                //记录需要删除的解密数据包（因为需要防ROOT）
                g_tempFiles.push_back(temp_path);
                LOGI("RSB_TRACE: Warning! Device rooted.");
            }
        }
        
    }
    

    // 替换路径 - 安全存储指针
    char* new_path = strdup(temp_path.c_str());
    if (!new_path) {
        LOGI("RSBPathRecorder: Failed to allocate new_path");
        return result;
    }
    /*if (a1[0] & 1) {
        a1[2] = reinterpret_cast<uintptr_t>(new_path);
    }
    else {
        a1[1] = reinterpret_cast<uintptr_t>(new_path);
    }*/
    size_t new_path_len = strlen(new_path);
    if (a1[0] & 1) {
        // 动态分配
        if (a1[2]) {
            free((void*)a1[2]); // 释放原始路径
        }
        unsigned int v10 = new_path_len > 20 ? new_path_len : 20;
        unsigned int v8 = (v10 + 16) & 0xFFFFFFF0; // 分配大小
        a1[0] = v8 | 1; // a1[0] = 65 (0x41)
        a1[1] = new_path_len; // a1[1] = 47 (0x2F)
        a1[2] = reinterpret_cast<uintptr_t>(new_path); // 新路径指针
    }
    else {
        // 非动态分配
        a1[0] = 2 * new_path_len; // a1[0] = 2 * 路径长度
        a1[1] = reinterpret_cast<uintptr_t>(new_path); // a1[1] = 新路径指针
    }
    LOGI("RSBPathRecorder: Replaced path with %s (ptr=%p)",
        temp_path.c_str(), (void*)new_path);

    return result;
}


#pragma endregion

//强制1536
#pragma region ForceResources1536
//此代码自主查找并转译得来
//声明原始函数指针
typedef int (*ForceResources1536)(int);
ForceResources1536 oForceResources1536 = NULL;
int hkForceResources1536(int a1)
{
    // 调用原始函数
    int result = oForceResources1536(a1);
    //强制1536
    result = 1536;

    // 强制返回 1536 (0x600, 对应 0205BCEC)
    LOGI("Hooked sub_6E4224: Original result=%d, Forcing result=1536", result);
    return result;
}
#pragma endregion

//在此感谢CZ的技术专栏分享，我将变量名和一些方式进行了小小的改变，但依旧需要对其为技术的分享表达感谢！！！！！
#pragma region CDNExpansion
typedef int (*CDNExpand)(int* a1, const Sexy::SexyString& rtonName, int rtonTable, int a4);
CDNExpand oCDNLoad = NULL;

std::atomic<bool> executed(false);

void hkCDNLoad(int* a1, const Sexy::SexyString& rtonName, int rtonTable, int a4)

{

    if (!oCDNLoad)
    {
        LOGI("Rton Table IDs Old Load failed.");
        return;
    }
    //至于这个偏移怎么查.........很简单，HEX搜products.rton
    //然后根据products.rton的"p"的偏移地址，用ida pro跳转到该地址
    //你会发现一堆的rton（绿色）右侧都用同一个DATA XREF地址跳转（引用偏移地址）
    //双击那个地址，你就会到达CZ讲的那个大函数，跳转后按F5，然后向下翻就能看到
    //那些rton下面都有同一个函数，就是那个函数需要hook
    //然后原理CZ讲过了，我也是直接拿来用，没啥丢脸的，有公开的好东西不用才是固执嘛......
    //不过，CZ拿64位演示，推荐的bb2和jay krow的32位工程，对于一些萌新来说可不友好哦......
    //原理很简单（如果这都要拿AI去查什么意思的话，那我可要数落你了啊）
    //executed一开始为false，我们在塞入rton之前的第一步就是检测executed是否为true
    //executed你可以比喻为一个罐子，打开了就是true，没打开就是false，我们只需要打开一次就不需要打开了
    //所以第一次我们打开之前，罐子是未开封状态，打开了就是开封状态
    //未开封状态我们要打开罐子拿出东西塞别的里面去，我们塞过之后就不需要再塞重复的了
    //所以一看到开封的状态我们就知道不需要在这个罐子里面拿东西了
    //所以executed在我们塞rton之前是false，塞rton时候就已经变true了，就不需要再塞了
    if (!executed.exchange(true))
    {
        //载入各版本RtonTableID
        if (rtonTableIDsLoader()) {
            LOGI("Rton Table IDs Load succeed.");
            // 遍历载入
            for (const auto& rtonfile : rtonTableIDs) {
                oCDNLoad(a1, rtonfile.first, rtonfile.second, 1);
                LOGI("%s:%d is loaded", (rtonfile.first).c_str(), rtonfile.second);
            }
        }
        else LOGI("Rton Table IDs Load failed.");
    }
    LOGI("%s:%d is loaded", rtonName.c_str(), rtonTable);
    oCDNLoad(a1, rtonName, rtonTable, a4);
}
#pragma endregion

#pragma region LoaderTest
//探测开启游戏时到底载入了哪些函数
typedef int (*MainLoadFunc)(int, int, int);
MainLoadFunc oMainLoadFunc = NULL;
int hkMainLoadFunc(int a1, int a2, int a3) {
    LOGI("Hooking MainLoadFunc 6F00A0");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata = oMainLoadFunc(a1, a2, a3);
    LOGI("Hooking MainLoadFunc 6F00A0");
    return backdata;
}

typedef int (*ResourceManagerFunc)(int, int, int);
ResourceManagerFunc oResourceManagerFunc = NULL;
int hkResourceManagerFunc(int a1, int a2, int a3) {
    LOGI("Hooking ResourcesManagerFunc 6EE218");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata = oResourceManagerFunc(a1, a2, a3);
    LOGI("Hooking ResourcesManagerFunc 6EE218 End");
    LOGI("Cleaning up temp files");
    //如果检测到ROOT，则进入秒删模式
    if (isRooted()) cleanupTempFiles();
    return backdata;
}

typedef int (*ResourceReadFunc)(
    uint*,
    int,
    int,
    uint8_t*,
    uint8_t*,
    int,
    void*,
    int,
    int,
    int,
    void*);
ResourceReadFunc oResourceReadFunc = NULL;
int hkResourceReadFunc(
    uint* a1,
    int a2,
    int a3,
    uint8_t* a4,
    uint8_t* a5,
    int a6,
    void* a7,
    int a8,
    int a9,
    int a10,
    void* a11) {
    LOGI("Hooking ResourceReadFunc 16228F0");
    int backdata = oResourceReadFunc(
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        a8,
        a9,
        a10,
        a11);
    LOGI("Hooking ResourceReadFunc 16228F0 End");
    return backdata;
}
typedef int (*RSBTestAndReadFunc)(uint*, int*);
RSBTestAndReadFunc oRSBTestAndReadFunc = NULL;
int hkRSBTestAndReadFunc(uint* a1, int* a2) {
    LOGI("Hooking RSBTestAndReadFunc 16303BC");
    LOGI("a1=%p, a2=%p", (void*)a1, (void*)a2);
    int backdata = oRSBTestAndReadFunc(a1, a2);
    LOGI("return %d", backdata);
    LOGI("Hello?");
    LOGI("Hooking RSBTestAndReadFunc 16303BC End");
    return backdata;
}
typedef int (*ManifestChecker)(
    void*,
    int,
    int,
    int,
    int,
    int,
    void*,
    int,
    int,
    int,
    void*,
    int);
ManifestChecker oManifestChecker = NULL;
int hkManifestChecker(
    void* a1,
    int a2,
    int a3,
    int a4,
    int a5,
    int a6,
    void* a7,
    int a8,
    int a9,
    int a10,
    void* a11,
    int a12) {
    LOGI("Hooking ManifestChecker 16229C8");

    int backdata = oManifestChecker(
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        a8,
        a9,
        a10,
        a11,
        a12);
    LOGI("return %d", backdata);
    LOGI("Hooking ManifestChecker 16229C8 End");
    return backdata;
}
#pragma endregion


#pragma region LogOutputHook



typedef int (*LogOutputFunc)(char*, ...);
LogOutputFunc oLogOutputFunc = NULL;
std::mutex g_logMutex;

int hkLogOutputFunc(char* format, ...) {
    if (!oLogOutputFunc) {
        LOGI("LogOutputFunc: Original function pointer is null");
        return -1;
    }

    std::lock_guard<std::mutex> lock(g_logMutex);

    va_list va, va_copy;
    va_start(va, format);
    va_copy(va_copy, va);

    // 计算所需长度
    char temp[1];
    int len = vsnprintf(temp, 0, format, va);
    va_end(va);

    va_start(va, format);
    char* buffer;
    if (len >= 0 && len < 1024) {
        buffer = new char[1024];
        len = vsnprintf(buffer, 1024, format, va);
        buffer[len] = '\0';
        LOGI("LogOutputFunc: %s", buffer);
    }
    else if (len >= 0) {
        buffer = new char[len + 1];
        len = vsnprintf(buffer, len + 1, format, va);
        buffer[len] = '\0';
        LOGI("LogOutputFunc: %s", buffer);
    }
    else {
        LOGI("LogOutputFunc: Failed to format, format=%s, len=%d", format ? format : "null", len);
    }

    int result = oLogOutputFunc(format, va_copy);
    va_end(va_copy);
    va_end(va);
    delete[] buffer;
    return result;
}

#pragma endregion

#pragma region LogOutputHook_Simple

typedef int (*LogOutputFunc_Simple)(const char*);
LogOutputFunc_Simple oLogOutputFunc_Simple = NULL;
std::mutex g_logMutex_Simple;

int hkLogOutputFunc_Simple(const char* text) {
    if (!oLogOutputFunc_Simple) {
        LOGI("LogOutputFunc_Simple: Original function pointer is null");
        return -1;
    }

    // 预检逻辑（模仿 IDA 中的 if(!v2)）
    if (text && *text != '\0') {
        std::lock_guard<std::mutex> lock(g_logMutex_Simple);

        // 直接打印传入的字符串，无需 vsnprintf，因为这不是可变参数函数
        LOGI("LogOutputFunc_Simple [PvZ2Debug]: %s", text);
    }

    // 调用原函数
    return oLogOutputFunc_Simple(text);
}

#pragma endregion

#pragma region LogOutputHook_Struct

// 参数是 int (寄存器 r0)，在 Hook 中我们定义为 void* 或 long
typedef int (*LogOutputFunc_Struct)(void*);
LogOutputFunc_Struct oLogOutputFunc_Struct = NULL;
std::mutex g_logMutex_Struct;

int hkLogOutputFunc_Struct(void* result) {
    if (!oLogOutputFunc_Struct) {
        LOGI("LogOutputFunc_Struct: Original function pointer is null");
        return -1;
    }

    if (result) {
        const char* v1 = NULL;
        // 模仿 IDA 逻辑：检查标志位
        // 如果 (*(unsigned char*)result & 1) != 0
        if ((*((unsigned char*)result) & 1) != 0) {
            // 长字符串逻辑：从偏移 8 处取指针
            v1 = *(const char**)((uintptr_t)result + 8);
        }
        else {
            // 短字符串逻辑：从偏移 1 处取内容
            v1 = (const char*)((uintptr_t)result + 1);
        }

        // 如果指针不为空且内容不为空字符串
        if (v1 && *v1 != '\0') {
            std::lock_guard<std::mutex> lock(g_logMutex_Struct);
            LOGI("LogOutputFunc_Struct: %s", v1);
        }
    }

    // 调用原函数并返回其结果
    return oLogOutputFunc_Struct(result);
}

#pragma endregion

#pragma region LogOutputHook_v2

typedef int (*LogOutputFunc_v2)(int a1, ...);
LogOutputFunc_v2 oLogOutputFunc_v2 = NULL;
std::mutex g_logMutex_v2;

int hkLogOutputFunc_v2(int a1, ...) {
    if (!oLogOutputFunc_v2) {
        LOGI("LogOutputFunc_v2: Original function pointer is null");
        return -1;
    }

    std::lock_guard<std::mutex> lock(g_logMutex_v2);

    va_list va, va_copy;
    va_start(va, a1);
    va_copy(va_copy, va);

    // 1. 尝试格式化字符串用于拦截打印
    // 注意：a1 在这里通常是 format 字符串的指针
    const char* format = (const char*)a1;

    char* buffer = nullptr;
    // 计算所需长度
    char temp[1];
    int len = vsnprintf(temp, 0, format, va);
    va_end(va);

    if (len >= 0) {
        // 分配内存并格式化
        int buf_size = (len < 1024) ? 1024 : (len + 1);
        buffer = new char[buf_size];

        va_start(va, a1);
        vsnprintf(buffer, buf_size, format, va);
        va_end(va);

        // 输出到我们的日志
        LOGI("LogOutputFunc_v2: %s", buffer);
    }
    else {
        LOGI("LogOutputFunc_v2: Failed to format, a1=%p", (void*)a1);
    }

    // 2. 调用原始函数
    // 同样注意：C语言中无法直接将 va_list 传给 ...，这里取决于你的 Hook 框架支持
    // 如果是 Dobby/Substrate，通常建议转发参数
    int result = oLogOutputFunc_v2(a1, va_copy);

    va_end(va_copy);
    if (buffer) delete[] buffer;

    return result;
}

#pragma endregion


#pragma region Board Zoom Test

//typedef int (*UIWidgetScale)(int a1, int a2);
//UIWidgetScale oUIWidgetScale = NULL;
//
//// 假设这些变量在你的全局上下文或 LawnApp 中可以获取
//extern int realPhysicalHeight=1220; // 实际屏幕物理像素高度
//
//int hkUIWidgetScale(int a1, int a2) {
//    if (!oUIWidgetScale) {
//        LOGI("UIWidgetScalingHook: Original function pointer is null");
//        return 0;
//    }
//
//    // 1. 调用原始函数完成基础注册逻辑
//    // 必须先让原函数运行，因为它会先执行序列化和内存初始化
//    int result = oUIWidgetScale(a1, a2);
//
//    // 2. 检查 a2 指针有效性
//    if (a2 == 0) return result;
//
//    // --- 仿照 LogOutputHook 风格的拦截修正逻辑 ---
//
//    // A. 修正“免疫设备缩放” (Offset 137)
//    // 逻辑：强制设为 0 (false)，允许 UI 随屏幕高度拉伸
//    *(unsigned char*)(a2 + 137) = 0;
//
//    // B. 修正“忽略安全区” (Offset 168)
//    // 逻辑：强制设为 1 (true)，允许渲染延伸至刘海屏/挖孔区域
//    *(unsigned char*)(a2 + 168) = 1;
//
//    // C. 动态计算缩放比例
//    // 基于你提到的 600 逻辑高度基准
//    float logicBaseHeight = 1536.0f;
//    float deviceScale = (float)realPhysicalHeight / logicBaseHeight;
//
//    // D. 修正虚拟高度 (VirtualHeight Offset 78)
//    // 根据 sub_FB0288 的 STRH 指令，这里是 2 字节存储
//    unsigned short* pVirtualHeight = (unsigned short*)(a2 + 78);
//    unsigned short oldVHeight = *pVirtualHeight;
//    *pVirtualHeight = (unsigned short)((float)oldVHeight * deviceScale);
//
//    // E. 修正棋盘虚拟宽度 (BoardScaledVirtualWidth Offset 126)
//    // 这是你最关心的棋盘拉伸关键位
//    unsigned short* pBoardVWidth = (unsigned short*)(a2 + 126);
//    if (*pBoardVWidth > 0) {
//        *pBoardVWidth = (unsigned short)((float)(*pBoardVWidth) * deviceScale);
//    }
//
//    // F. 修正虚拟宽度 (VirtualWidth Offset 76)
//    // 保持纵横比一致，同步缩放宽度
//    unsigned short* pVirtualWidth = (unsigned short*)(a2 + 76);
//    *pVirtualWidth = (unsigned short)((float)(*pVirtualWidth) * deviceScale);
//
//    // 3. 拦截打印（可选，方便在 logcat 确认是否生效）
//    // LOGI("UIWidgetHook: a2=%p, BaseScale=%.2f, VHeight:%d->%d", 
//    //      (void*)a2, deviceScale, oldVHeight, *pVirtualHeight);
//
//    return result;
//}



////部分钱袋钻石叶绿素UI缩放
//#pragma region UniversalZoomHook
//
//// 定义原函数原型
//typedef float (*UniversalZoom)();
//UniversalZoom oUniversalZoom = nullptr;
//
//// 你的 Hook 函数
//float hkUniversalZoom() {
//    if (!oUniversalZoom) {
//        return 1.0f; // 安全退路
//    }
//
//    // 1. 获取原版的缩放比例
//    float originalZoom = oUniversalZoom();
//
//    // 2. 1.0倍缩放
//    // 这样既保留了游戏原本的自适应比例，又整体放大了
//    float finalZoom = originalZoom * 1.0f;
//
//    // 调试日志（可选，按你提供的样式）
//    LOGI("LawnZoom: Original=%f, Modified=%f", originalZoom, finalZoom);
//
//    return finalZoom;
//}
//
//
//// 定义原函数原型
//typedef int (*UniversalZoom1)(int a1,int a2);
//UniversalZoom1 oUniversalZoom1 = nullptr;
//
//// 你的 Hook 函数
//int hkUniversalZoom1(int a1,int a2) {
//    if (!oUniversalZoom1) {
//        return 1; // 安全退路
//    }
//
//    // 1. 获取原版的缩放比例
//    int originalZoom = oUniversalZoom1(a1,a2);
//
//    // 2. 1.5倍缩放
//    // 这样既保留了游戏原本的自适应比例，又整体放大了
//    int finalZoom = originalZoom * 1.0f;
//
//    // 调试日志（可选，按你提供的样式）
//    LOGI("LawnZoom: Original=%d, Modified=%d", originalZoom, finalZoom);
//
//    return finalZoom;
//}


//获取设备分辨率和结果分辨率
// 原函数签名
typedef int (*LawnAppScreenWidthHeight)(float* a1, int a2);
LawnAppScreenWidthHeight oLawnAppScreenWidthHeight = nullptr;

//设备分辨率 根据 sub_1482320: 1448字节 = 偏移362, 1452字节 = 偏移363
int mOrigScreenWidth;
int mOrigScreenHeight;

//游戏分辨率 根据 sub_6E4030 反汇编:
int mWidth;
int mHeight;

//缩放后结果 float 成员
float m_contentResWidth;
float m_contentResHeight;

float zoomScale;

int hkLawnAppScreenWidthHeight(float* a1, int a2) {
    // 1. 先执行原函数，让内部逻辑完成内存写入
    int result = oLawnAppScreenWidthHeight(a1, a2);

    if (a1 == nullptr) return result;

    // 2. 根据偏移直接提取数据
    // 注意：a1 是 float*，偏移计算需小心转换
    int* iPtr = (int*)a1;

    // 根据 sub_1482320: 1448字节 = 偏移362, 1452字节 = 偏移363
    mOrigScreenWidth = iPtr[362];
    mOrigScreenHeight = iPtr[363];

    // 根据 sub_6E4030 反汇编:
    mWidth = iPtr[25];
    mHeight = iPtr[26];

    // float 成员
    m_contentResWidth = a1[394];
    m_contentResHeight = a1[395];

    // 3. 仿照你的 LogOutputFunc 风格进行输出
    // 使用 snprintf 格式化到局部 buffer
    char buffer[512];
    int len = snprintf(buffer, sizeof(buffer),
        "\n--- LawnApp::SetWidthHeight Hook ---\n"
        "mOrigSize: %d x %d\n"
        "mSize:     %d x %d\n"
        "mContent:  %.2f x %.2f\n"
        "Result:    %d",
        mOrigScreenWidth, mOrigScreenHeight,
        mWidth, mHeight,
        m_contentResWidth, m_contentResHeight,
        result);

    if (len > 0) {
        LOGI("%s", buffer);
    }
    zoomScale = ((float)mOrigScreenHeight / m_contentResHeight);
    return result;
}




// 定义原函数的函数原型 (32位 ARM 中 __fastcall 通常对应 r0, r1...)
typedef int (*OrigBoardZoom)(uintptr_t a1);
OrigBoardZoom oBoardZoom = nullptr;

int hkBoardZoom(uintptr_t a1) {
    //集体注释（没用了，用了会起反作用）
    {
        ////缩放系数
        //float zoom = *(float*)(a1 + 860);
        ////乘宽高系数从而达到缩放目的
        //*(float*)(a1 + 860) = (float)zoom * zoomScale;
        //// 2. 取出原函数辛苦算出来的总宽度 (v11 + v12)
        //int32_t total_width = *(int32_t*)(a1 + 44);
        //*(int32_t*)(a1 + 44) = total_width * zoomScale;


        ////解释：board于屏幕右下角为原点生成，所以运算基于该原点
        ////起始位置坐标
        //int32_t texture_left = *(int32_t*)(a1 + 872);
        //*(int32_t*)(a1 + 872) = (int32_t)(texture_left * zoomScale);

        ////选卡后向左滑动后停留的左侧坐标（0为距离屏幕左侧一个texture_left*自制缩放率开始的原点）
        //int32_t board_x = *(int32_t*)(a1 + 876);
        //*(int32_t*)(a1 + 876) = (total_width - mOrigScreenWidth) * zoomScale;
        //// 4. 选卡前向右滑动的偏移（地图总长-屏幕总宽）
        //int32_t board_block = *(int32_t*)(a1 + 884);
        //*(int32_t*)(a1 + 884) = (int32_t)(total_width * zoomScale - mOrigScreenWidth);
        ////选卡前向左滑动的距离
        ///**(int32_t*)(a1 + 880) = (int32_t)( (* (int32_t*)(a1 + 880)+ mOrigScreenWidth -board_x )* zoomScale- mOrigScreenWidth+ board_x * zoomScale);*/
    }
    // 1. 先跑原函数
    int result = oBoardZoom(a1);

    //改变选卡时向左滑动距离
    *(int32_t*)(a1 + 880) = -(*(int32_t*)(a1 + 840)) + 20 + 64 * 3; /*-(*(int32_t*)(a1 + 832));*///前面这个也是可以的//-(*(int32_t*)(a1 + 840))+20选卡时候会完全靠左边，部分设备选卡会看不到出怪
    //高度无法调整，只能靠缩放
    return result;
}

// 定义原函数的函数原型 (32位 ARM 中 __fastcall 通常对应 r0, r1...)
typedef int (*OrigBoardZoom2)(uintptr_t a1);
OrigBoardZoom2 oBoardZoom2 = nullptr;

int hkBoardZoom2(uintptr_t a1) {



    int result = oBoardZoom2(a1);
    //缩放系数
    float zoom = *(float*)(a1 + 860);
    LOGI("zoom= %f", zoom);
    *(float*)(a1 + 860) = 1.0f;

    //俩半逻辑宽度
    int32_t logicalA = *(int32_t*)(a1 + 832);
    int32_t logicalB = *(int32_t*)(a1 + 840);
    //改变左侧偏移(因为误差20像素，所以补上)
    *(int32_t*)(a1 + 824) = (int32_t)logicalB - 20;/**(int32_t*)(a1 + 44)-mOrigScreenWidth;*///注释的是刘海屏留存的数值



    //顶部基准线
    *(int32_t*)(a1 + 868) = (int32_t)mOrigScreenHeight;

    //右边界屏幕坐标
    int32_t board_right = *(int32_t*)(a1 + 864);
    /**(int32_t*)(a1 + 864) = board_right*zoomScale;*/
    //高度无法调整，只能靠缩放
    return result;
}

//防手机刘海（似乎没有用，已被注释掉）
typedef int (*IgnoreSafeArea)(int a1, int a2);
IgnoreSafeArea oIgnoreSafeArea = NULL;
int hkIgnoreSafeArea(int a1, int a2) {
    int result = oIgnoreSafeArea(a1, a2);
    // A. 强制关闭“免疫缩放” (Offset 137)
    // 这样 UI 才会跟随底层的缩放矩阵变动
    /**(uint8_t*)(a2 + 137) = 0; */// ImmuneToDeviceScaling = false

    // B. 强制修正“忽略安全区” (Offset 168) 
    // 视情况开启，确保 UI 能填满刘海屏区域
    *(uint8_t*)(a2 + 168) = 1; // IgnoreSafeArea = true
    return result;
}

#pragma endregion













//友情提示：该ARM64工程所有功能均未测试，据估计应当全部重写（以支持64位指针），故劳烦修好后在进行测试，尤其是数据包载入，谢谢！

__attribute__((constructor))
// This is automatically executed when the lib is loaded
// Run your initialization code here
void libRestructedLogic_ARM64__main()
{
    LOGI("Initializing %s", LIB_TAG);
    //根据版本修改偏移——已经不需要了
    /*AddressesChangedByVersion();*/
    // New, easier to manage way of adding typenames to the plant/zombie name mapper
    REGISTER_PLANT_TYPENAME("funny_tomato");
    for (int i = 0; i < 109; i++) {
        REGISTER_PLANT_TYPENAME(("newadd_" + i));
    }

    // New, easier to manage way of adding typenames to the plant/zombie name mapper
    //No need to use///REGISTER_ZOMBIE_TYPENAME("steam");

    // Function hooks
    //部分偏移由某神秘大佬查找得来，但是由于v7a和v8a函数结构不同，还有新的库的未知什么导致的闪退问题，故v8a方案已废弃
    //PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
    //PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
    //PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
    //PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");
    //PVZ2HookFunction(ReinitForSurfaceChangedAddr, (void*)HkReinitForSurfaceChange, (void**)&oRFSC, "ReinitForSurfaceChanged");
    //PVZ2HookFunction(BoardAddr, (void*)hkBoardCtor, (void**)&oBoardCtor, "Board::Board");
    //PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
    //PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
    //PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
    //PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
    //PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");
    

    /*if (version_code < v10_3) {*/
    if (GAME_VERSION < 1030) {
        /*PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
        PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
        PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
        PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");

        PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
        PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
        PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");*/
        PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");
    }
    else {
        PVZ2HookFunction(worldMapScrollAddr, (void*)hkworldMapScroll, (void**)&oworldMapScroll, "WorldMap::worldMapScroll");
        //居中函数
        PVZ2HookFunction(KeepCenterAddr, (void*)hkKeepCenter, (void**)&oKeepCenter, "WorldMap::KeepCenter");
        //惯性函数
        PVZ2HookFunction(ScrollInertanceAddr, (void*)hkScrollInertance, (void**)&oScrollInertance, "WorldMap::worldMapScroll");
    }
    //输出简要日志
    PVZ2HookFunction(LogOutputFuncAddrSimpleAddr, (void*)hkLogOutputFunc_Simple, (void**)&oLogOutputFunc_Simple, "LogOutputFunc_Simple");
    //输出日志
    PVZ2HookFunction(LogOutputFuncAddr, (void*)hkLogOutputFunc, (void**)&oLogOutputFunc, "LogOutputFunc");
    //输出结构日志
    PVZ2HookFunction(LogOutputFuncAddr_Struct, (void*)hkLogOutputFunc_Struct, (void**)&oLogOutputFunc_Struct, "LogOutputFunc_Struct");
    //输出v2日志
    PVZ2HookFunction(LogOutputFuncAddr_v2, (void*)hkLogOutputFunc_v2, (void**)&oLogOutputFunc_v2, "LogOutputFunc_v2");
    PVZ2HookFunction(MainLoadFuncAddr, (void*)hkMainLoadFunc, (void**)&oMainLoadFunc, "ResourceManager::MainLoadFunc");
    PVZ2HookFunction(ResourceManagerFuncAddr, (void*)hkResourceManagerFunc, (void**)&oResourceManagerFunc, "ResourceManager::ResourceManagerFunc");
    PVZ2HookFunction(ResourceReadFuncAddr, (void*)hkResourceReadFunc, (void**)&oResourceReadFunc, "ResourceManager::ResourceReadFunc");
    PVZ2HookFunction(RSBTestAndReadFuncAddr, (void*)hkRSBTestAndReadFunc, (void**)&oRSBTestAndReadFunc, "ResourceManager::RSBTestAndReadFunc");
    //自主开发强制1536
    PVZ2HookFunction(ForceResources1536Addr, (void*)hkForceResources1536, (void**)&oForceResources1536, "ForceResources1536");

    //CDN读取rton，感谢CZ技术专栏分享技术！！！
    PVZ2HookFunction(CDNLoadAddr, (void*)hkCDNLoad, (void**)&oCDNLoad, "CDNLoadExpansion");
    //得到缩放前后尺寸
    PVZ2HookFunction(LawnAppScreenWidthHeightAddr, (void*)hkLawnAppScreenWidthHeight, (void**)&oLawnAppScreenWidthHeight, "LawnApp:SetScreenWidthHeight");
    //控制屏幕缩放
    PVZ2HookFunction(BoardZoomAddr, (void*)hkBoardZoom, (void**)&oBoardZoom, "BoardZoom");
    PVZ2HookFunction(BoardZoom2Addr, (void*)hkBoardZoom2, (void**)&oBoardZoom2, "BoardZoom2");
    //防手机刘海（似乎没有用）
    /*PVZ2HookFunction(0xFB0288, (void*)hkIgnoreSafeArea, (void**)&oIgnoreSafeArea, "IgnoreSafeArea");*/
    // Hook RSBRead (replace original)
    //禁用禁用PVZ2HookFunction(RSBReadAddr, (void*)hkRSBRead, nullptr, "ResourceManager::Init");
    //RSB解密
    PVZ2HookFunction(RSBPathRecorderAddr, (void*)hkRSBPathRecorder, (void**)&oRSBPathRecorder, "ResourceManager::RSBPathRecorder");
    //此代码为融小宝对RestructedLogic工程的私有化改造功能之一，并未根据RestructedLogic的GPL-3.0协议进行公开，我已拥有相关证据，你不守规矩，就别怪我强制公开了，并且我也没用你的写法，自己写的
    PVZ2HookFunction(PrimeGlyphCacheAddr, (void*)hkPrimeGlyphCacheLimitation, (void**)&oPrimeGlyphCacheLimitation, "PrimeGlyphCache::PrimeGlyphCacheLimitation");

    /*PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");*/
    LOGI("Finished initializing");
}
