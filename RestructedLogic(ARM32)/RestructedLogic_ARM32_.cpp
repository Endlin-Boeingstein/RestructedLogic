﻿#include "RestructedLogic_ARM32_.h"
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
        REGISTER_ZOMBIE_TYPENAME("new_added_zombie_"+i);
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

bool g_allowVerticalMovement = true;

typedef int (*worldMapDoMovement)(WorldMap*, int64_t, int64_t);
worldMapDoMovement oWorldMapDoMovement = NULL;

int hkWorldMapDoMovement(WorldMap* map, int64_t x, int64_t y)
{
    LOGI("Doing map movement: x - %d, y - %d", x, y);
    return oWorldMapDoMovement(map, x, y);
}

inline int worldMapBoundaryMovement(WorldMap* self, float fX, float fY, bool allowVerticalMovement)
{
    if (fX <= self->m_boundaryX)
    {
        fX = self->m_boundaryX;
    }

    if (fX >= self->m_boundaryX + self->m_boundaryWidth)
    {
        fX = self->m_boundaryX + self->m_boundaryWidth;
    }

    if (fY <= self->m_boundaryY)
    {
        fY = self->m_boundaryY;
    }

    if (fY >= self->m_boundaryY + self->m_boundaryHeight)
    {
        fY = self->m_boundaryY + self->m_boundaryHeight;
    }

    return 1;
}

#pragma endregion

#pragma region Board Zoom



int gWidth = 0;
int gHeight = 0;

inline uint_t getLawnApp() {
    return *(uint_t*)getActualOffset(LawnAppAddr);
}

uint_t getSexyApp() {
    return *(uint_t*)getActualOffset(SexyAppAddr);
}

enum AspectRatio
{
    Letterbox,
    Widescreen,
    Ultrawide,
};

//typedef int(*worldMapDoMovement)(void*, float, float, bool);
//worldMapDoMovement oWorldMapDoMovement = NULL;
//
//int hkWorldMapDoMovement(void* self, float fX, float fY, bool allowVerticalMovement)
//{
//    return oWorldMapDoMovement(self, fX, fY, true);
//}

AspectRatio GetAspectRatio()
{
    float ratio = (float)gWidth / (float)gHeight;
    if (ratio <= 1.4f)
    {
        return Letterbox;
    }
    else if (ratio >= 1.41f && ratio <= 1.85f)
    {
        return Widescreen;
    }
    else if (ratio >= 1.86f)
    {
        return Ultrawide;
    }
}

typedef void(*ReinitForSurfaceChange)(int, int, int, int, int);
ReinitForSurfaceChange oRFSC = nullptr;

void HkReinitForSurfaceChange(int thisptr, int a2, int width, int height, int a5)
{
    gWidth = width;//width
    gHeight = height;//height
    return oRFSC(thisptr, a2, width, height, a5);
}

//要搞开关了
bool g_boardZoomOut = true;

typedef void* (*boardCtor)(Board*);
boardCtor oBoardCtor = NULL;

void* hkBoardCtor(Board* board)
{
    oBoardCtor(board);

    LOGI("Board constructor called");
    LOGI("[ Column Count ] x: %d", board->m_columnCount);
    LOGI("[ Row Count ] x: %d", board->m_rowCount);
    LOGI("[ Lawn Rect ] x: %d, y: %d, w: %d, h: %d", board->m_lawnRect.mX, board->m_lawnRect.mY, board->m_lawnRect.mWidth, board->m_lawnRect.mHeight);

    if (g_boardZoomOut)
    {
        board->m_lawnRect.mX = 200; //200
        board->m_lawnRect.mY = 160; //160

        switch (GetAspectRatio())
        {
        case Letterbox:
        {
            LOGI("Aspect Ratio: Letterbox");
            board->m_lawnRect.mWidth = 576; //576
            board->m_lawnRect.mHeight = 500; //380
            break;
        }
        case Widescreen:
        {
            LOGI("Aspect Ratio: Widescreen");
            board->m_lawnRect.mWidth = 576; //576
            board->m_lawnRect.mHeight = 450; //380
            // board->m_lawnRect.mHeight = 540; //380
            break;
        }
        case Ultrawide:
        {
            LOGI("Aspect Ratio: Ultrawide");
            board->m_lawnRect.mX = 450; //450
            board->m_lawnRect.mY = 160;
            board->m_lawnRect.mWidth = 576; //576
            board->m_lawnRect.mHeight = 525; //380
            break;
        }
        }
    }

    return board;
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


//特别提醒：该加密测试已经被我注释掉了，因为目前仅完成了对_MANIFESTGROUP_的解密，离完全完成还很远，但我没心情和时间陪这玩意耗了
//已探明RSB读取入口（废了老大劲拿IDA PRO搁那推），先进行测试（目前为XOR加密未测试）
//自己研究的RSB入口寻找法：用Hex编辑器打开so后文本搜索RSB Initialization failed，找到对应的偏移
//使用IDA PRO跳转到该偏移上，随后对该句右键，选择交叉引用列表，选那个.text类型的（唯一）
//然后你就找到一个语句，这个语句下面一段距离后会有句话// starts at 啥啥啥的
//你IDA PRO窗口代码左侧是偏移，这个starts at后面说的偏移，你去找那个偏移的那句话
//这句话就是RSB的路径分析入口，如果你想找主读取函数，那就对该句右键，选择图标视图
//你会发现它被唯一一个函数引用，那就是RSB主读取函数
//如果你只想看代码，那就按F5，转换成伪C代码，慢慢看吧，借助大模型分析（ChatGPT最佳，Grok也还行），找到那个读取RSB内容的内嵌在里面的函数就行了
#pragma region RSB _MANIFEST_GROUP_ Read

//inline uint32_t bswap32(uint32_t x) {
//    return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24);
//}
//
//void decrypt_rsb(uint8_t* buffer, size_t size) {
//    /*const uint8_t key = 0x5A;
//    for (size_t i = 0; i < size; i++) {
//        buffer[i] ^= key;
//    }
//    LOGI("Decrypted %zu bytes", size);
//    if (size >= 4) {
//        LOGI("First 4 bytes after decryption: %02x %02x %02x %02x",
//            buffer[0], buffer[1], buffer[2], buffer[3]);
//    }*/
//}
//
//
//
//void* hkRSBRead(int a1, uint* a2, char* a3, int a4) {
//    void* v7 = nullptr;
//    int v16[513]; // 匹配原版大小
//    uint v12 = 0;
//    *a2 = 0;
//    *a3 = 1; // 匹配原版初始值
//
//    int (*readFunc)(int, int*, int, int) = *(int (**)(int, int*, int, int))(*(int*)a1 + 40);
//    int (*statusFunc)(int) = *(int (**)(int))(*(int*)a1 + 44);
//    LOGI("readFunc=%p, statusFunc=%p, a1=%p", (void*)readFunc, (void*)statusFunc, (void*)a1);
//
//    if (!a1 || !readFunc || !statusFunc) {
//        LOGI("Invalid parameters: a1=%p, readFunc=%p, statusFunc=%p",
//            (void*)a1, (void*)readFunc, (void*)statusFunc);
//        return nullptr;
//    }
//
//    int readResult = readFunc(a1, v16, 2048, 0);
//    LOGI("readFunc called, a1=%p, v16=%p, size=2048, offset=0, readResult=%d",
//        (void*)a1, v16, readResult);
//    if (readResult <= 0) {
//        LOGI("Failed to read RSB data: readResult=%d", readResult);
//        return nullptr;
//    }
//
//    int status;
//    do {
//        status = statusFunc(a1);
//        LOGI("statusFunc called, a1=%p, status=%d", (void*)a1, status);
//    } while (status == 1);
//    if (status == 2) {
//        LOGI("Invalid status after read: status=%d", status);
//        return nullptr;
//    }
//
//    LOGI("v16 before decrypt: %02x %02x %02x %02x",
//        ((uint8_t*)v16)[0], ((uint8_t*)v16)[1], ((uint8_t*)v16)[2], ((uint8_t*)v16)[3]);
//    decrypt_rsb((uint8_t*)v16, 2048);
//
//    uint32_t header = *(uint32_t*)v16;
//    LOGI("Raw header: %08x", header);
//    char v9 = 0;
//    if (header == 0x72736231) {
//        v9 = 1;
//    }
//    else {
//        header = bswap32(header);
//        LOGI("Header after bswap: %08x", header);
//        if (header != 0x72736231) {
//            LOGI("Invalid RSB header after decryption and bswap: %08x", header);
//            return nullptr;
//        }
//        *(uint32_t*)v16 = header;
//    }
//    *a3 = v9;
//
//    int v11 = 27;
//    if (a4 || v16[1] < 4) v11 = 3;
//    v12 = v16[v11];
//    if (!*a3) v12 = bswap32(v12);
//    LOGI("RSB data size (v12): %u bytes, v11=%d, a4=%d, v16[1]=%d", v12, v11, a4, v16[1]);
//    LOGI("v16[3]=%08x, v16[27]=%08x", v16[3], v16[27]);
//    *a2 = v12;
//
//    v7 = operator new[](v12);
//    if (!v7) {
//        LOGI("Failed to allocate v7: size=%u", v12);
//        *a3 = 0;
//        return nullptr;
//    }
//
//    if (v12 <= 2048) {
//        memcpy(v7, v16, v12);
//        LOGI("Copied %u bytes from v16 to v7", v12);
//    }
//    else {
//        memcpy(v7, v16, 2048);
//        LOGI("Copied 2048 bytes from v16 to v7");
//        readResult = readFunc(a1, (int*)((char*)v7 + 2048), v12 - 2048, 0); // 修正偏移为 0
//        LOGI("readFunc called, a1=%p, v7+2048=%p, size=%u, offset=0, readResult=%d",
//            (void*)a1, (char*)v7 + 2048, v12 - 2048, readResult);
//        if (readResult <= 0) {
//            LOGI("Failed to read remaining RSB data: readResult=%d, expected=%u",
//                readResult, v12 - 2048);
//            operator delete[](v7);
//            *a3 = 0;
//            return nullptr;
//        }
//        do {
//            status = statusFunc(a1);
//            LOGI("statusFunc called, a1=%p, status=%d", (void*)a1, status);
//        } while (status == 1);
//        if (status == 2) {
//            LOGI("Invalid status after second read: status=%d", status);
//            operator delete[](v7);
//            *a3 = 0;
//            return nullptr;
//        }
//        decrypt_rsb((uint8_t*)((char*)v7 + 2048), v12 - 2048);
//    }
//
//    LOGI("v7 fields: v7[0]=%08x, v7[10]=%08x, v7[11]=%08x, v7[12]=%08x, v7[18]=%08x, v7[19]=%08x, v7[20]=%08x",
//        ((uint32_t*)v7)[0], ((uint32_t*)v7)[10], ((uint32_t*)v7)[11], ((uint32_t*)v7)[12],
//        ((uint32_t*)v7)[18], ((uint32_t*)v7)[19], ((uint32_t*)v7)[20]);
//    return v7;
//}
#pragma endregion

//真正的RSB解密函数
//实际上，之前是有直接拦截路径然后解密的想法的，但是被解资源文件分布那里的rsb1头检测迷惑住了
//还以为是把所有的文件都解了，而且还有就是担心解开来没临时路径，如果被人发现解密数据包在哪就完蛋了
//然后就死磕那段代码，终于做好解密时候才发现，它只解了MANIFEST那块！
//气死我了，如果接下来再去一个个把所有的地方都解一遍，我岂不是冤死！
//于是乎，我转向了路径拦截
//这块分析也不顺利，把我气个半死
//最后好在全部解决了，这个函数也不难找，RSB读取函数找到那个读取的字符串Loading main RSB from the path那句前面就找到了
//难的在路径结构分析，不过都解决了
//过程就是，先拦截路径，分析出来之后先根据路径找到RSB去解密，将解密的文件放在某个位置
//然后让RSB读取函数把数据都读完，这个时候数据包就没用了，资源都加载在内存里了
//RSB读取函数就结束使命了，结束前顺手把解密后的RSB删了，就找不到了
//从解密到删除，RSB估计才存在1秒吧，藏在哪人家也不知道
//找到了又能怎的，你还能做到边打开游戏边1秒复制吗？你是超级硬盘？700+的数据包说1秒复制就1秒复制？
//这就是RSB加密的全过程，不知道同行是不是也是这样做的
//文章很长，不想看可以折叠
#pragma region BeforeReading
//但是无所谓了，曾经第一个做出RSB加密的大佬在卖自己加密功能的时候，不少人持反对意见
//我的原话如下：
//“也不要说垄断不垄断的，这玩意算另造引擎，已经超出pvz2修改范围
// 凡事需要付出代价，要么是金钱要么是精力
// 如果你们想要rsb加密宽视野加映射却对他收钱很不爽，你大可以不买。
// 甚至你大可以自己搞一个，你也可以收费。
// 你甚至可以自己搞出来把他饭碗砸了etc.”
//现在，宽视野、加映射、RSB加密我全搞出来了，还开源了，但是又能怎么样呢？
//我搞出来了RestructedLogic，谁会理解我测试上百遍失败才搞出来这个懒人开源工程呢？
//当时做这个工程的时候，群被截图发到了国外，群成员被威胁，群内所有成员都被截图，那时候多苦？
//最后下场是啥？作者被驱逐，别人拿过来改成自己的私人玩物，还说是那个老外做的
//这次的RSB加密估计也是这样吧......我测试了上百遍，终于搞出来了
//但是最终会被所有人使用吗？不会！因为他们会把这个据为己有！
//他们会嫌弃这项工程，向外人表示他们的不齿，因为啥？因为他们为了数据包安全，已经向那位大佬付钱了（笑）！
//我不仅砸了这位大佬的饭碗，我还砸了这群人的饭碗！
//然后他们会根据这个工程去改装，变成自己的私人玩物
//再次开启一段循环
//现在啊，我等了半年，看看他们驱逐了曾经推广so的人，接下来国产so会怎么样？
//结果啊，呵呵呵呵呵，不出所料，有个人，拿我的工程，搞了改渲染缓存的私活
//他知道他注入成功了，但是那个语句有没有被调用？
//他不知道！他只知道不闪退，就是成功！
//他费尽心思把大多数的偏移给找了，但是他真的不知道他的函数实际上就是没用的
//他还拙劣地复刻了那段原函数，实际上没必要，还得多找一段偏移
//然后呢，他们狂欢，攻击被驱逐的人，显得自己赢了
//他们这群废物，连LOGI干啥用的都不知道，ADB怕是也没碰过
//找不出来什么原因，哪里错了？那就对了！
//然后呢？他又做了什么？没了，没别的了
//另外一群人呢？
//他们曾经对被驱逐的人推崇的东西嗤之以鼻
//现在却奉若圭臬，甚至做出了倒退版本的动作！
//但是他们也不只是奉若圭臬啊！拿过来不好用还不忘嘲讽两句，踩两脚
//最后一群人，是啊，和他们同流合污了啊
//但是呢，他因为以前和那群人斗争过，所以他的思想比较先进
//他找到了最初做这类工程的作者，和他合作
//因为同流合污，所以他得到了大量资源和支持
//因为找了国外，所以他得到了高端技术
//这很好，不是吗？
//阿三那样也很好吗？
//那些小作者，为什么要屈服于那群人？
//即使自己改版被骂，也得忍着
//朋友同情他，他却捂着朋友的嘴，还得把朋友出卖以获得那群人的支持
//然后整个圈子都去攻击那个放逐的人，知不知道真相不重要，重要的是要获取那群人支持
//但是，一旦接受支持，那么，你就有了软肋，对方可以撤走在你身上的投入，你未完成的体系直接崩塌！
//所以我再问一句，这很好，不是吗？
//对此，我只能说
//不独立自主，永远找不到出路！
#pragma endregion
#pragma region RSBPathChangeAndDecryptRSB
// 临时文件路径列表
static std::vector<std::string> g_tempFiles;
// 解密函数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//你的解密函数放在这里！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
void decrypt_rsb(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] ^= 0x5A;
    }
    LOGI("Decrypted %zu bytes", size);
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

// Hook 函数
typedef int (*RSBPathRecorder)(uint* a1);
RSBPathRecorder oRSBPathRecorder = nullptr;

int hkRSBPathRecorder(uint* a1) {
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

    // 提取路径
    char* path_ptr = nullptr;
    if (a1[0] & 1) {
        path_ptr = (char*)a1[2]; // 动态分配，路径在 a1[2]
    }
    else {
        path_ptr = (char*)a1[1]; // 非动态分配，路径在 a1[1]
    }
    if (!path_ptr || (uint)path_ptr < 0x1000) {
        LOGI("RSBPathRecorder: Invalid path pointer 0x%x, a1[0]=0x%x", (uint)path_ptr, a1[0]);
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

    // 验证预期路径，可改，改成你的改版路径即可，不改也没影响！！！！！！！！！！！！
    std::string expected_path = "/storage/emulated/0/Android/obb/com.ea.game.pvz2_na/main.763.com.ea.game.pvz2_na.obb";
    if (original_path != expected_path) {
        LOGI("RSBPathRecorder: Path mismatch, expected %s", expected_path.c_str());
        // 继续处理，允许非预期路径
    }

    // 读取 RSB 文件
    std::ifstream in_file(original_path.c_str(), std::ios::binary | std::ios::ate);
    if (!in_file.is_open()) {
        LOGI("RSBPathRecorder: Failed to open %s, errno=%d", original_path.c_str(), errno);
        return result;
    }
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

    // 解密
    decrypt_rsb(buffer.data(), static_cast<size_t>(file_size));

    // 创建缓存目录，必须改！这是你解密文件放的位置，虽然只存在1秒，但务必重视！！！！！！！！！！！！！！！！！！！！！！！！
    // 最好放在你的游戏的data目录（一般为/storage/emulated/0/Android/data/com.ea.game.pvz2_改版名，然后如果深入就加/文件夹）
    std::string cache_dir = "/storage/emulated/0/Android/data/com.ea.game.pvz2_na/cache";
    if (mkdir(cache_dir.c_str(), 0777) != 0 && errno != EEXIST) {
        LOGI("RSBPathRecorder: Failed to create %s, errno=%d", cache_dir.c_str(), errno);
        return result;
    }
    //解密RSB的名称，可以改成别的混淆视听......实际上1秒他能看到个啥，改了之后更认不出来了！！！！！！！！！！！！！！！！！！
    std::string temp_path = cache_dir + "/cache.rsb";
    std::ofstream out_file(temp_path.c_str(), std::ios::binary);
    if (!out_file.is_open()) {
        LOGI("RSBPathRecorder: Failed to create %s, errno=%d", temp_path.c_str(), errno);
        return result;
    }
    out_file.write(reinterpret_cast<char*>(buffer.data()), file_size);
    if (!out_file) {
        LOGI("RSBPathRecorder: Failed to write %s, errno=%d", temp_path.c_str(), errno);
        out_file.close();
        return result;
    }
    out_file.close();
    LOGI("RSBPathRecorder: Saved to %s", temp_path.c_str());
    g_tempFiles.push_back(temp_path);

    // 替换路径
    char* new_path = strdup(temp_path.c_str());
    if (!new_path) {
        LOGI("RSBPathRecorder: Failed to allocate new_path");
        return result;
    }
    if (a1[0] & 1) {
        a1[2] = (uint)new_path; // 动态分配，替换 a1[2]
    }
    else {
        a1[1] = (uint)new_path; // 非动态分配，替换 a1[1]
    }
    LOGI("RSBPathRecorder: Replaced path with %s", temp_path.c_str());

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

//尝试自定义火鸡子弹默认生成类型
#pragma region TurkeypultProjectileSummonCustom
// Hook sub_E6B880 to change hardcoded zombie type
typedef uint* (*ProjectileSpawnZombie)(void);
ProjectileSpawnZombie oProjectileSpawnZombie = NULL;

uint* hkProjectileSpawnZombie() {
    LOGI("Hooking sub_E6B880: Spawning zombie");

    uint* v0 = oProjectileSpawnZombie(); // 调用原始函数

    // 直接替换僵尸类型和数量
    strcpy((char*)v0[82], "turkeypult_turkzilla"); // 修改为你的目标僵尸类型
    v0[83] = 1; // 设置僵尸数量，可根据需要调整

    LOGI("Set zombie type to %s, count = %d", (char*)v0[82], v0[83]);

    return v0;
}
#pragma endregion

#pragma region LoaderTest
//探测开启游戏时到底载入了哪些函数
typedef int (*MainLoadFunc)(int, int, int);
MainLoadFunc oMainLoadFunc = NULL;
int hkMainLoadFunc(int a1, int a2, int a3) {
    LOGI("Hooking MainLoadFunc 6F00A0");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata= oMainLoadFunc(a1, a2, a3);
    LOGI("Hooking MainLoadFunc 6F00A0");
    return backdata;
}

typedef int (*ResourceManagerFunc)(int, int, int);
ResourceManagerFunc oResourceManagerFunc = NULL;
int hkResourceManagerFunc(int a1, int a2, int a3) {
    LOGI("Hooking ResourcesManagerFunc 6EE218");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata= oResourceManagerFunc(a1, a2, a3);
    LOGI("Hooking ResourcesManagerFunc 6EE218 End");
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
    int backdata= oResourceReadFunc(
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
    int backdata= oRSBTestAndReadFunc(a1, a2);
    LOGI("return %d", backdata);
    LOGI("Hello?");
    LOGI("Hooking RSBTestAndReadFunc 16303BC End");
    return backdata;
}

#pragma endregion

//尝试自定义火鸡子弹默认生成类型
#pragma region TurkeypultProjectileSummonCustom
// Hook sub_E6B880 to change hardcoded zombie type
typedef uint* (*ProjectileSpawnZombie)(void);
ProjectileSpawnZombie oProjectileSpawnZombie = NULL;

uint* hkProjectileSpawnZombie() {
    LOGI("Hooking sub_E6B880: Spawning zombie");

    uint* v0 = oProjectileSpawnZombie(); // 调用原始函数

    // 直接替换僵尸类型和数量
    strcpy((char*)v0[82], "turkeypult_turkzilla"); // 修改为你的目标僵尸类型
    v0[83] = 1; // 设置僵尸数量，可根据需要调整

    LOGI("Set zombie type to %s, count = %d", (char*)v0[82], v0[83]);

    return v0;
}
#pragma endregion

#pragma region LoaderTest
//探测开启游戏时到底载入了哪些函数
typedef int (*MainLoadFunc)(int, int, int);
MainLoadFunc oMainLoadFunc = NULL;
int hkMainLoadFunc(int a1, int a2, int a3) {
    LOGI("Hooking MainLoadFunc 6F00A0");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata= oMainLoadFunc(a1, a2, a3);
    LOGI("Hooking MainLoadFunc 6F00A0");
    return backdata;
}

typedef int (*ResourceManagerFunc)(int, int, int);
ResourceManagerFunc oResourceManagerFunc = NULL;
int hkResourceManagerFunc(int a1, int a2, int a3) {
    LOGI("Hooking ResourcesManagerFunc 6EE218");
    LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
    int backdata= oResourceManagerFunc(a1, a2, a3);
    LOGI("Hooking ResourcesManagerFunc 6EE218 End");
    LOGI("Cleaning up temp files");
    cleanupTempFiles();
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
    int backdata= oResourceReadFunc(
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
    int backdata= oRSBTestAndReadFunc(a1, a2);
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




__attribute__((constructor))
// This is automatically executed when the lib is loaded
// Run your initialization code here
void libRestructedLogic_ARM32__main()
{
    LOGI("Initializing %s", LIB_TAG);
    //根据版本修改偏移
    AddressesChangedByVersion();
    
    

    // New, easier to manage way of adding typenames to the plant/zombie name mapper
    //No need to use///REGISTER_ZOMBIE_TYPENAME("steam");

    // Function hooks
    if (version_code < v10_3) {
        //PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
        PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
        PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
        PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");
        
        PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
        PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
        PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");
        
    }
    //输出日志
    PVZ2HookFunction(LogOutputFuncAddr, (void*)hkLogOutputFunc, (void**)&oLogOutputFunc, "LogOutputFunc");
    //Hook主函数、RSB读取函数、资源组读取函数、资源分布读取函数
    PVZ2HookFunction(MainLoadFuncAddr, (void*)hkMainLoadFunc, (void**)&oMainLoadFunc, "ResourceManager::MainLoadFunc");
    PVZ2HookFunction(ResourceManagerFuncAddr, (void*)hkResourceManagerFunc, (void**)&oResourceManagerFunc, "ResourceManager::ResourceManagerFunc");
    PVZ2HookFunction(ResourceReadFuncAddr, (void*)hkResourceReadFunc, (void**)&oResourceReadFunc, "ResourceManager::ResourceReadFunc");
    PVZ2HookFunction(RSBTestAndReadFuncAddr, (void*)hkRSBTestAndReadFunc, (void**)&oRSBTestAndReadFunc, "ResourceManager::RSBTestAndReadFunc");
    //PVZ2HookFunction(0x16229C8, (void*)hkManifestChecker, (void**)&oManifestChecker, "ResourceManager::ManifestChecker");
    //火鸡子弹默认生成类型修改测试
    //PVZ2HookFunction(ProjectileSpawnZombieAddr, (void*)hkProjectileSpawnZombie, (void**)&oProjectileSpawnZombie, "ProjectileSpawnZombie");
    //自主开发强制1536
    PVZ2HookFunction(ForceResources1536Addr, (void*)hkForceResources1536, (void**)&oForceResources1536, "ForceResources1536");
    // Hook RSBRead (replace original)
    //禁用禁用PVZ2HookFunction(RSBReadAddr, (void*)hkRSBRead, nullptr, "ResourceManager::RSBLoadingInit");
    //RSB解密
    PVZ2HookFunction(RSBPathRecorderAddr, (void*)hkRSBPathRecorder, (void**)&oRSBPathRecorder, "ResourceManager::RSBPathRecorder");
    //此代码为融小宝对RestructedLogic工程的私有化改造功能之一，并未根据RestructedLogic的GPL-3.0协议进行公开，我已拥有相关证据，你不守规矩，就别怪我强制公开了，并且我也没用你的写法，自己写的
    PVZ2HookFunction(PrimeGlyphCacheAddr, (void*)hkPrimeGlyphCacheLimitation, (void**)&oPrimeGlyphCacheLimitation, "PrimeGlyphCache::PrimeGlyphCacheLimitation");


    PVZ2HookFunction(ReinitForSurfaceChangedAddr, (void*)HkReinitForSurfaceChange, (void**)&oRFSC, "ReinitForSurfaceChanged");
    PVZ2HookFunction(BoardAddr, (void*)hkBoardCtor, (void**)&oBoardCtor, "Board::Board");

    //PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");
    
    

    LOGI("Finished initializing");
}
