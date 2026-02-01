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

//友情提示：该ARM64工程所有功能均未测试，据估计应当全部重写（以支持64位指针），故劳烦修好后在进行测试，尤其是数据包载入，谢谢！

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
// 解密函数（基于你的 XOR 0x5A）
void decrypt_rsb(uint8_t* data, size_t size) {
    if (size < 20) return;

    // 1. 校验 Magic (现在顺序固定了)
    if (memcmp(data, "RSB2", 4) != 0) return;

    // 2. 提取 IV (直接从 data+4 拷贝)
    uint8_t iv[16];
    memcpy(iv, data + 4, 16);

    // 3. 还原 Key
    std::string pwd = HIDE_STR("RestructedLogic_Encrypt_V0");
    uint8_t key[32];
    picosha2::hash256_one_by_one hasher;
    hasher.process(pwd.begin(), pwd.end());
    hasher.finish();
    hasher.get_hash_bytes(key, key + 32);

    // 4. 原地解密
    uint8_t* ciphertext = data + 20;
    uint32_t ciphertext_len = (uint32_t)(size - 20);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, ciphertext, ciphertext_len);

    // 5. 移除 Padding 并覆盖 Header
    uint8_t pad = ciphertext[ciphertext_len - 1];
    if (pad > 0 && pad <= 16) {
        uint32_t plain_len = ciphertext_len - pad;
        memmove(data, ciphertext, plain_len);
        memset(data + plain_len, 0, size - plain_len);
        // 此时 data[0] 就是解密后的原始第一个字节
    }
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

    // 验证预期路径
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

    // 创建缓存目录
    std::string cache_dir = "/storage/emulated/0/Android/data/com.ea.game.pvz2_na/cache";
    if (mkdir(cache_dir.c_str(), 0777) != 0 && errno != EEXIST) {
        LOGI("RSBPathRecorder: Failed to create %s, errno=%d", cache_dir.c_str(), errno);
        return result;
    }
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


//友情提示：该ARM64工程所有功能均未测试，据估计应当全部重写（以支持64位指针），故劳烦修好后在进行测试，尤其是数据包载入，谢谢！

__attribute__((constructor))
// This is automatically executed when the lib is loaded
// Run your initialization code here
void libRestructedLogic_ARM64__main()
{
    LOGI("Initializing %s", LIB_TAG);
    //根据版本修改偏移
    AddressesChangedByVersion();
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
    //PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");

    if (version_code < v10_3) {
        /*PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
        PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
        PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
        PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");

        PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
        PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
        PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");*/
    }
    //输出日志
    PVZ2HookFunction(LogOutputFuncAddr, (void*)hkLogOutputFunc, (void**)&oLogOutputFunc, "LogOutputFunc");
    PVZ2HookFunction(MainLoadFuncAddr, (void*)hkMainLoadFunc, (void**)&oMainLoadFunc, "ResourceManager::MainLoadFunc");
    PVZ2HookFunction(ResourceManagerFuncAddr, (void*)hkResourceManagerFunc, (void**)&oResourceManagerFunc, "ResourceManager::ResourceManagerFunc");
    PVZ2HookFunction(ResourceReadFuncAddr, (void*)hkResourceReadFunc, (void**)&oResourceReadFunc, "ResourceManager::ResourceReadFunc");
    PVZ2HookFunction(RSBTestAndReadFuncAddr, (void*)hkRSBTestAndReadFunc, (void**)&oRSBTestAndReadFunc, "ResourceManager::RSBTestAndReadFunc");
    //自主开发强制1536
    PVZ2HookFunction(ForceResources1536Addr, (void*)hkForceResources1536, (void**)&oForceResources1536, "ForceResources1536");
    // Hook RSBRead (replace original)
    //禁用禁用PVZ2HookFunction(RSBReadAddr, (void*)hkRSBRead, nullptr, "ResourceManager::Init");
    //RSB解密
    PVZ2HookFunction(RSBPathRecorderAddr, (void*)hkRSBPathRecorder, (void**)&oRSBPathRecorder, "ResourceManager::RSBPathRecorder");
    /*PVZ2HookFunction(ReinitForSurfaceChangedAddr, (void*)HkReinitForSurfaceChange, (void**)&oRFSC, "ReinitForSurfaceChanged");
    PVZ2HookFunction(BoardAddr, (void*)hkBoardCtor, (void**)&oBoardCtor, "Board::Board");*/

    /*PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");*/
    LOGI("Finished initializing");
}
