#include "RestructedLogic_ARM32_.h"
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
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include "Customize/Projectile/GridItemRaiserProjectileProps.h"
#include "VersionRtonIDs.h"
#include<jni.h>
//#include "Customize/Projectile/GridItemRaiserProjectile.cpp"

namespace fs = std::filesystem;

//拦截JNI!!!
//JavaVM* g_vm = nullptr;
//JNIEXPORT jint JNICALL JNI_Onload(JavaVM* vm, void* reserved) {
//    g_vm = vm;
//    return JNI_VERSION_1_6;
//}

//jobject get_context(JNIEnv* env) {
//    // 核心逻辑：ActivityThread.currentActivityThread().getApplication()
//    jclass atClass = env->FindClass("android/app/ActivityThread");
//    jmethodID currentATMethod = env->GetStaticMethodID(atClass, "currentActivityThread", "()Landroid/app/ActivityThread;");
//    jobject atInstance = env->CallStaticObjectMethod(atClass, currentATMethod);
//
//    jmethodID getAppMethod = env->GetMethodID(atClass, "getApplication", "()Landroid/app/Application;");
//    return env->CallObjectMethod(atInstance, getAppMethod);
//}
//
////一键搞定目录创建，搬运还是算了
////void auto_move_payload(JNIEnv* env, const std::string& src_path) {
//void auto_move_payload(JNIEnv* env) {
//    jobject context = get_context(env);
//    if (!context) return;
//
//    // 1. 让 Java 帮你把 OBB 文件夹建好（带上正确的 SELinux 标签）
//    jclass contextClass = env->GetObjectClass(context);
//    jmethodID getObbDir = env->GetMethodID(contextClass, "getObbDir", "()Ljava/io/File;");
//    jobject obbFile = env->CallObjectMethod(context, getObbDir);
//
//    //// 2. 获取这个文件夹的绝对路径
//    //jclass fileClass = env->GetObjectClass(obbFile);
//    //jmethodID getPath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
//    //jstring jPath = (jstring)env->CallObjectMethod(obbFile, getPath);
//    //const char* cPath = env->GetStringUTFChars(jPath, nullptr);
//
//    //// 3. 拼接目标全路径并写入
//    //std::string dst_path = std::string(cPath) + "/config.dat";
//
//    //std::ifstream src(src_path, std::ios::binary);
//    //std::ofstream dst(dst_path, std::ios::binary);
//    //dst << src.rdbuf(); // 暴力搬运
//
//    //// 释放资源
//    //env->ReleaseStringUTFChars(jPath, cPath);
//}


//static JavaVM* g_vm = nullptr;
//
//jint JNI_OnLoad(JavaVM* vm, void* reserved) {
//    g_vm = vm;
//    return JNI_VERSION_1_4;
//}
//
//// 获取当前 Application Context 的 getObbDir() 路径
//std::string getObbDirPath() {
//    JNIEnv* env = nullptr;
//    // 获取当前线程的 JNIEnv，若线程未附加，则附加
//    jint ret = g_vm->GetEnv((void**)&env, JNI_VERSION_1_6);
//    if (ret == JNI_EDETACHED) {
//        // 如果当前线程未附加，先附加
//        if (g_vm->AttachCurrentThread(&env, nullptr) != JNI_OK) {
//            LOGI("AttachCurrentThread failed");
//            return "";
//        }
//    }
//    else if (ret != JNI_OK) {
//        LOGI("GetEnv failed");
//        return "";
//    }
//
//    // 1. 获取 ActivityThread 类
//    jclass activityThreadCls = env->FindClass("android/app/ActivityThread");
//    if (activityThreadCls == nullptr) {
//        LOGI("FindClass ActivityThread failed");
//        return "";
//    }
//
//    // 2. 获取 currentApplication() 静态方法
//    jmethodID currentAppMethod = env->GetStaticMethodID(activityThreadCls, "currentApplication", "()Landroid/app/Application;");
//    if (currentAppMethod == nullptr) {
//        LOGI("GetMethodID currentApplication failed");
//        return "";
//    }
//
//    // 3. 调用静态方法获得 Application 对象
//    jobject application = env->CallStaticObjectMethod(activityThreadCls, currentAppMethod);
//    if (application == nullptr) {
//        LOGI("currentApplication returned null");
//        return "";
//    }
//
//    // 4. 获取 Context 类的 getObbDir() 方法
//    jclass contextCls = env->FindClass("android/content/Context");
//    jmethodID getObbDirMethod = env->GetMethodID(contextCls, "getObbDir", "()Ljava/io/File;");
//    if (getObbDirMethod == nullptr) {
//        LOGI("GetMethodID getObbDir failed");
//        return "";
//    }
//
//    // 5. 调用 application.getObbDir() 获得 File 对象
//    jobject obbFile = env->CallObjectMethod(application, getObbDirMethod);
//    if (obbFile == nullptr) {
//        LOGI("getObbDir returned null");
//        return "";
//    }
//
//    // 6. 获取 File 类的 getPath() 方法
//    jclass fileCls = env->FindClass("java/io/File");
//    jmethodID getPathMethod = env->GetMethodID(fileCls, "getPath", "()Ljava/lang/String;");
//    if (getPathMethod == nullptr) {
//        LOGI("GetMethodID getPath failed");
//        return "";
//    }
//
//    // 7. 调用 obbFile.getPath() 获得路径字符串
//    jstring pathStr = (jstring)env->CallObjectMethod(obbFile, getPathMethod);
//    if (pathStr == nullptr) {
//        LOGI("getPath returned null");
//        return "";
//    }
//
//    // 8. 将 Java 字符串转为 C 字符串
//    const char* pathChars = env->GetStringUTFChars(pathStr, nullptr);
//    std::string result(pathChars);
//    env->ReleaseStringUTFChars(pathStr, pathChars);
//
//    // 9. 清理局部引用（可选，但建议）
//    env->DeleteLocalRef(activityThreadCls);
//    env->DeleteLocalRef(application);
//    env->DeleteLocalRef(contextCls);
//    env->DeleteLocalRef(obbFile);
//    env->DeleteLocalRef(fileCls);
//    env->DeleteLocalRef(pathStr);
//
//    // 如果之前附加了线程，记得分离（根据实际情况决定）
//    // 如果你的代码是在一个长期运行的 native 线程中调用，且该线程不会退出，可以考虑不分离，或者在线程结束时分离。
//    // 这里简单起见，暂不分离，但需注意平衡。
//
//    return result;
//}


//直装包专项
#pragma region Direct Install Package Funcs
//RSB迁移是否开始判定
std::atomic<bool> thread_applied(false);

//让主程序延迟防止数据包迁移期间被读取（可放在除了Log输出函数以外的任一hook函数调用旧函数之前）
void dalay_hook() {
    //直装包延迟
    while (thread_applied) {
        //对不起，让你歇一下
        LOGI("RSB first loaded, sleeping......");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


//数据分块
void copy_chunk(const fs::path& src, const fs::path& dst,
    uint64_t offset, uint64_t size)
{
    const size_t BUF_SIZE = 64ull * 1024 * 1024; // 512MB

    std::ifstream in(src, std::ios::binary);
    std::fstream out(dst, std::ios::binary | std::ios::in | std::ios::out);

    in.seekg(offset);
    out.seekp(offset);

    std::vector<char> buffer(std::min<uint64_t>(BUF_SIZE, size));

    uint64_t remaining = size;

    while (remaining > 0)
    {
        size_t to_read = std::min<uint64_t>(buffer.size(), remaining);

        in.read(buffer.data(), to_read);
        out.write(buffer.data(), to_read);

        remaining -= to_read;
    }
}
//分块迁移函数
bool copy_file_parallel(const fs::path& src, const fs::path& dst, int threads)
{
    uint64_t file_size = fs::file_size(src);

    // 预创建目标文件
    {
        std::ofstream out(dst, std::ios::binary | std::ios::trunc);
        out.seekp(file_size - 1);
        out.write("", 1);
    }

    uint64_t chunk = file_size / threads;

    std::vector<std::thread> workers;

    for (int i = 0; i < threads; i++)
    {
        uint64_t offset = i * chunk;
        uint64_t size = (i == threads - 1) ? (file_size - offset) : chunk;

        workers.emplace_back(copy_chunk, src, dst, offset, size);
    }

    for (auto& t : workers)
        t.join();

    return true;
}

//RSB迁移期间防止主线程读取函数（大概率无法一次载入因为res头读取比RSB读取要早..........）
void safe_pipe_copy(const std::string& src_path, const std::string& target_path) {
    // 1. 如果路径已存在普通文件，先删掉，否则没法建管道
    unlink(target_path.c_str());

    // 2. 创建管道 (FIFO)
    if (mkfifo(target_path.c_str(), 0666) != 0) {
        // 如果创建失败（比如权限问题），退回到普通拷贝作为保底
        fs::copy(src_path, target_path, fs::copy_options::overwrite_existing);
        return;
    }

    // 3. 打开管道准备写入 (注意：如果主线程没来读，这里会阻塞)
    // 建议在子线程执行，这样不会卡死你的 Mod 初始化
    int fifo_fd = open(target_path.c_str(), O_WRONLY);
    if (fifo_fd < 0) return;

    // 4. 分块读写数据
    std::ifstream src(src_path, std::ios::binary);
    std::vector<char> buffer(1024 * 1024); // 每次 64KB，正好是典型 Linux 管道的大小

    while (src.read(buffer.data(), buffer.size()) || src.gcount() > 0) {
        ssize_t count = src.gcount();
        // 这一步会根据主线程的读取速度自动“限速”
        if (write(fifo_fd, buffer.data(), count) == -1) break;
    }

    // 5. 关键：关闭管道，主线程才会收到 EOF 并结束读取
    close(fifo_fd);
    src.close();

    // 6. 可选：任务彻底完成后删除管道（或者留着下次用）
    unlink(target_path.c_str()); 
}



//std::atomic<bool> directed_install_executed(false);
//void get_package_name(char* out_name) {
//获取游戏包名
std::string get_package_name() {
    //FILE* fp = fopen("/proc/self/cmdline", "r");
    //if (fp) {
    //    fgets(out_name, 256, fp);//读取进程名
    //    fclose(fp);
    //}
    std::ifstream cmdline("/proc/self/cmdline");
    std::string package_name;
    std::getline(cmdline, package_name, '\0');//cmdline以\0结尾
    return package_name;
}


//获取so所在文件夹
std::string get_so_parent_dir() {
    std::ifstream maps("/proc/self/maps");
    std::string line;
    while (std::getline(maps, line)) {
        if (line.find("libRestructedLogic.so") != std::string::npos) {
            size_t path_start = line.find_last_of(' ') + 1;
            std::string full_path = line.substr(path_start);
            //去掉末尾换行符并返回父目录
            return fs::path(full_path).parent_path().string();
        }
    }
    return "";
}
//OBB文件夹是否存在
bool OBBPathExisted() {
    int app_version = 0;
    std::string ori_rsb_name = "main." + std::to_string(app_version) + "." + get_package_name() + ".obb";
    std::string rsb_path_str = "/storage/emulated/0/Android/obb/" + get_package_name();
    fs::path rsb_real_path = fs::path(rsb_path_str);
    if (fs::exists(rsb_real_path)) return 1;
    return 0;
}
//OBB是否存在
bool OBBExisted() {
    int app_version = 0;
    std::string ori_rsb_name = "main." + std::to_string(app_version) + "." + get_package_name() + ".obb";
    std::string rsb_path_str = "/storage/emulated/0/Android/obb/" + get_package_name();
    std::string rsb_self_path_str = rsb_path_str + "/" + ori_rsb_name;
    fs::path rsb_self_path = fs::path(rsb_self_path_str);
    if (fs::exists(rsb_self_path)) return 1;
    return 0;
}
//直装转移
bool RSBDirectInstall() {
    std::string rsb_name = "libRSB.so";
    int app_version = 0;
    std::string ori_rsb_name = "main."+ std::to_string(app_version) + "." + get_package_name() + ".obb";
    std::string rsb_path_str = "/storage/emulated/0/Android/obb/" + get_package_name();
    std::string rsb_self_path_str = rsb_path_str + "/" + ori_rsb_name;
    //获取lib路径
    std::string so_dir = get_so_parent_dir();
    if (so_dir.empty()) return 0;
    //构造源文件路径
    fs::path src_file = fs::path(so_dir) / rsb_name;
    //构造目标路径
    fs::path target_dir = fs::path("/storage/emulated/0/Android/obb/") / get_package_name();
    //目标数据包前往的路径
    fs::path target_file = target_dir / ori_rsb_name;
    LOGI("src_file:%s\ntarget_dir:%s\ntarget_file:%s", src_file.string().c_str(), target_dir.string().c_str(), target_file.string().c_str());
    if (fs::exists(src_file)) {
        LOGI("file exist.");
        if (!fs::exists(target_dir)) {
            /*fs::create_directories(target_dir);*/
            /*std::string obbPath = getObbDirPath();*/
            /*if (obbPath.empty()) {
                LOGI("错误！");
                return 0;
            }*/
            /*if (mkdir(target_dir.string().c_str(), 0775) == -1) {
                if (errno == EACCES) {
                    LOGI("SELinux或者权限拦截！");
                }
                else if (errno == ENOENT) {
                    LOGI("父目录可能不存在，需要递归创建。");
                }
            }*/
            LOGI("target_dir not created.");
            return 0;
        }
        //拷贝文件。使用update_existing保证文件版本更新
        /*fs::copy(src_file, target_file, fs::copy_options::overwrite_existing);*/
        ////可能内存不够，用分块
        //copy_file_parallel(src_file, target_file, 4);
        //防读取但防不了res检测.........
        safe_pipe_copy(src_file, target_file);
        //权限修复
        fs::permissions(target_file, fs::perms::owner_all | fs::perms::group_read);
        return 1;
    }
    else {
        LOGI("不是直装包");
        return 0;
    }
}

//线程监控OBB路径是否存在，存在则毙掉游戏（因为会卡死在下载界面）//现在不需要毙掉了，直接载入了
void obb_path_monitor() {
    while (true) {
        if (OBBPathExisted()) {
            thread_applied = true;
            LOGI("RSBDirectInstall Start.");
            RSBDirectInstall();
            LOGI("RSBDirectInstall End.");
            if (OBBExisted()) {
                //成功迁移
                thread_applied = false;
            }
            /*kill(getpid(), SIGKILL);*/
            return;
        }
        /*else if(OBBExisted()){
            
        }*/
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

#pragma endregion



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
    *(int32_t*)(a1+312) = -1000000000;
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
    int result=oKeepCenter(a1, a2, 1);
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
int hkWorldMapDoMovement(void* map, float fX, float fY,bool allowVerticalMovement)
{
    LOGI("Doing map movement: fX - %d, fY - %d", fX, fY);
    return oWorldMapDoMovement(map, fX, fY,g_allowVerticalMovement);
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




// 物理平移覆盖头部
//void shift_file_left_20_bytes_precise(int fd, size_t plain_size) {
//    if (plain_size == 0) return;
//
//    // 1. 告诉内核：我们要顺序读取文件，请开启预读模式
//    posix_fadvise(fd, 0, plain_size + 20, POSIX_FADV_SEQUENTIAL);
//    // 同时也告诉内核，这块区域的数据未来不需要常驻缓存（节约内存）
//    posix_fadvise(fd, 0, plain_size + 20, POSIX_FADV_NOREUSE);
//
//    // 2. 增大缓冲区：8MB-16MB 往往是 UFS 闪存吞吐的最佳平衡点
//    const size_t BUF_SIZE = 16 * 1024 * 1024;
//    std::vector<uint8_t> buffer(BUF_SIZE);
//
//    size_t moved = 0;
//    while (moved < plain_size) {
//        size_t chunk = std::min(BUF_SIZE, plain_size - moved);
//
//        // 使用 pread/pwrite 替代 lseek+read/write，减少系统调用消耗并保证原子性
//        ssize_t bytes_read = pread(fd, buffer.data(), chunk, 20 + moved);
//        if (bytes_read <= 0) break;
//
//        pwrite(fd, buffer.data(), bytes_read, moved);
//
//        moved += bytes_read;
//    }
//
//    // 3. 截断并同步
//    ftruncate(fd, plain_size);
//    // 强制内核把文件元数据更新刷入磁盘，避免后续读取时文件长度没同步
//    fdatasync(fd);
//}

/**
 * 纯解密核心：专门适配分块映射。
 * 只做解密，不移动内存，不检测 Header。
 */
 // 核心解密：纯计算，不检测 Magic，不移动内存
// 确保 decrypt_pure_cbc_internal 接收 key
void decrypt_pure_cbc_internal(uint8_t* data, size_t size, const uint8_t* start_iv, const uint8_t* key) {
    uint32_t num_blocks = (uint32_t)(size / 16);
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;

    uint32_t blocks_per_thread = num_blocks / num_threads;
    std::vector<std::thread> threads;

    for (unsigned int t = 0; t < num_threads; ++t) {
        uint32_t start_block = t * blocks_per_thread;
        uint32_t end_block = (t == num_threads - 1) ? num_blocks : (t + 1) * blocks_per_thread;

        threads.emplace_back([=, &key, &start_iv]() {
            uint32_t t_offset = start_block * 16;
            uint32_t t_len = (end_block - start_block) * 16;
            if (t_len == 0) return;

            struct AES_ctx ctx;
            uint8_t thread_iv[16];

            if (start_block == 0) {
                memcpy(thread_iv, start_iv, 16);
            }
            else {
                memcpy(thread_iv, data + t_offset - 16, 16);
            }

            AES_init_ctx_iv(&ctx, key, thread_iv);
            AES_CBC_decrypt_buffer(&ctx, data + t_offset, t_len);
            });
    }
    for (auto& th : threads) th.join();
}


//将文件头部替换为可识别四字节
bool maskFileHeader(const std::string& filePath,std::string tagstr) {
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

// 临时文件路径列表
static std::vector<std::string> g_tempFiles;
//该解密函数已废弃
// 解密函数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//你的解密函数放在这里！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//void decrypt_rsb(uint8_t* data, size_t size) {
//    // 基础检查：不仅要够头部的 20 字节，还得确保能放下至少 1 个加密块
//    if (size < 36) return;
//
//    // 1. 安全拦截：如果头已经是 "1bsr" (0x31 0x62 0x73 0x72)，说明已经解密过了
//    // 这样可以防止二次解密导致数据彻底损坏
//    if (data[0] == 0x31 && data[1] == 0x62 && data[2] == 0x73 && data[3] == 0x72) {
//        return;
//    }
//
//    // 2. 校验 Magic (RSB2)
//    if (memcmp(data, "RSB2", 4) != 0) return;
//
//    // 3. 准备 Key (SHA256)
//    std::string pwd = HIDE_STR("rl_end_presentsoft");
//    uint8_t key[32];
//    picosha2::hash256_one_by_one hasher;
//    hasher.process(pwd.begin(), pwd.end());
//    hasher.finish();
//    hasher.get_hash_bytes(key, key + 32);
//
//    uint8_t* ciphertext_start = data + 20;
//    uint32_t total_cipher_len = (uint32_t)(size - 20);
//    uint32_t num_blocks = total_cipher_len / 16;
//
//    // 4. 多线程并行解密设置
//    // 获取 CPU 核心数，通常 Android 手机返回 8
//    unsigned int num_threads = std::thread::hardware_concurrency();
//    if (num_threads == 0) num_threads = 4;
//
//    uint32_t blocks_per_thread = num_blocks / num_threads;
//    std::vector<std::thread> threads;
//
//    for (unsigned int t = 0; t < num_threads; ++t) {
//        uint32_t start_block = t * blocks_per_thread;
//        uint32_t end_block = (t == num_threads - 1) ? num_blocks : (t + 1) * blocks_per_thread;
//
//        threads.emplace_back([=]() {
//            uint32_t current_offset = start_block * 16;
//            uint32_t thread_len = (end_block - start_block) * 16;
//            if (thread_len == 0) return;
//
//            struct AES_ctx ctx;
//            uint8_t thread_iv[16];
//
//            // CBC 解密的精髓：每一段的 IV 就是它前一个密文块
//            if (start_block == 0) {
//                // 第一段使用文件内置的初始 IV
//                memcpy(thread_iv, data + 4, 16);
//            }
//            else {
//                // 其他段使用前一个密文块作为其解密的初始 IV
//                memcpy(thread_iv, ciphertext_start + current_offset - 16, 16);
//            }
//
//            AES_init_ctx_iv(&ctx, key, thread_iv);
//            AES_CBC_decrypt_buffer(&ctx, ciphertext_start + current_offset, thread_len);
//            });
//    }
//
//    // 等待所有线程完成
//    for (auto& th : threads) th.join();
//
//    // 5. 移除 Padding 并原地移动内存
//    uint8_t pad = ciphertext_start[total_cipher_len - 1];
//    if (pad > 0 && pad <= 16) {
//        uint32_t plain_len = total_cipher_len - pad;
//        // 核心移动：把明文覆盖到 data 最开头
//        memmove(data, ciphertext_start, plain_len);
//        // 清理末尾，确保“进化统计数据”逻辑读到的是干净数据
//        memset(data + plain_len, 0, size - plain_len);
//    }
//}
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



    // 验证预期路径，可改，改成你的改版路径即可，不改也没影响！！！！！！！！！！！！
    std::string expected_path = "/storage/emulated/0/Android/obb/"+pack_name+"/"+rsb_name;
    if (original_path != expected_path) {
        LOGI("RSBPathRecorder: Path mismatch, expected %s", expected_path.c_str());
        // 继续处理，允许非预期路径
    }


    //旧方法
    {
        //// 读取 RSB 文件
        //std::ifstream in_file(original_path.c_str(), std::ios::binary | std::ios::ate);
        //if (!in_file.is_open()) {
        //    LOGI("RSBPathRecorder: Failed to open %s, errno=%d", original_path.c_str(), errno);
        //    return result;
        //}
        //std::streamsize file_size = in_file.tellg();
        //in_file.seekg(0, std::ios::beg);
        //std::vector<uint8_t> buffer(file_size);
        //in_file.read(reinterpret_cast<char*>(buffer.data()), file_size);
        //if (!in_file) {
        //    LOGI("RSBPathRecorder: Failed to read %s, errno=%d", original_path.c_str(), errno);
        //    in_file.close();
        //    return result;
        //}
        //in_file.close();
        //LOGI("RSBPathRecorder: Read %lld bytes", static_cast<long long>(file_size));

        //// 解密
        //decrypt_rsb(buffer.data(), static_cast<size_t>(file_size));

        //// 创建缓存目录，必须改！这是你解密文件放的位置，虽然只存在1秒，但务必重视！！！！！！！！！！！！！！！！！！！！！！！！
        //// 最好放在你的游戏的data目录（一般为/storage/emulated/0/Android/data/com.ea.game.pvz2_改版名，然后如果深入就加/文件夹）
        //std::string cache_dir = "/storage/emulated/0/Android/data/com.ea.game.pvz2_end/cache";
        //if (mkdir(cache_dir.c_str(), 0777) != 0 && errno != EEXIST) {
        //    LOGI("RSBPathRecorder: Failed to create %s, errno=%d", cache_dir.c_str(), errno);
        //    return result;
        //}
        ////解密RSB的名称，可以改成别的混淆视听......实际上1秒他能看到个啥，改了之后更认不出来了！！！！！！！！！！！！！！！！！！
        //std::string temp_path = cache_dir + "/cache.rsb";
        //std::ofstream out_file(temp_path.c_str(), std::ios::binary);
        //if (!out_file.is_open()) {
        //    LOGI("RSBPathRecorder: Failed to create %s, errno=%d", temp_path.c_str(), errno);
        //    return result;
        //}
        //out_file.write(reinterpret_cast<char*>(buffer.data()), file_size);
        //if (!out_file) {
        //    LOGI("RSBPathRecorder: Failed to write %s, errno=%d", temp_path.c_str(), errno);
        //    out_file.close();
        //    return result;
        //}
        //out_file.close();
        //LOGI("RSBPathRecorder: Saved to %s", temp_path.c_str());
        //g_tempFiles.push_back(temp_path);
    }

    //有检测机制的旧方法
    {
        //// --- 阶段 1: 打开与读取 ---
        //LOGI("RSBPathRecorder: [1/6] Opening file: %s", original_path.c_str());
        //std::ifstream in_file(original_path.c_str(), std::ios::binary | std::ios::ate);
        //if (!in_file.is_open()) {
        //    LOGW("RSBPathRecorder: ERROR - Failed to open %s, errno=%d", original_path.c_str(), errno);
        //    return result;
        //}

        //std::streamsize file_size = in_file.tellg();
        //in_file.seekg(0, std::ios::beg);
        //LOGI("RSBPathRecorder: [2/6] File size: %lld bytes. Preparing memory...", static_cast<long long>(file_size));

        //// --- 风险点 1: 内存申请 (不使用 try-catch) ---
        //// 使用 std::nothrow 让 vector 分配失败时不崩溃，而是变为空
        //// 注意：对于 vector 来说，最稳妥的办法是先手动分配原始内存
        //uint8_t* raw_buffer = (uint8_t*)malloc(static_cast<size_t>(file_size));
        //if (raw_buffer == nullptr) {
        //    LOGW("RSBPathRecorder: CRITICAL - Out of memory! Cannot allocate %lld bytes", static_cast<long long>(file_size));
        //    in_file.close();
        //    return result;
        //}
        //LOGI("RSBPathRecorder: Memory allocated successfully at %p", raw_buffer);

        //// 将原始内存包装进 vector 或直接使用
        //in_file.read(reinterpret_cast<char*>(raw_buffer), file_size);
        //if (!in_file) {
        //    LOGW("RSBPathRecorder: ERROR - Failed to read bytes, errno=%d", errno);
        //    free(raw_buffer);
        //    in_file.close();
        //    return result;
        //}
        //in_file.close();
        //LOGI("RSBPathRecorder: [3/6] Read to memory completed.");

        //// --- 阶段 2: 解密 ---
        //LOGI("RSBPathRecorder: [4/6] Starting decryption (MT)...");
        //decrypt_rsb(raw_buffer, static_cast<size_t>(file_size));
        //LOGI("RSBPathRecorder: Decryption finished.");

        //// --- 阶段 3: 目录准备 ---
        //std::string cache_dir = "/storage/emulated/0/Android/data/com.ea.game.pvz2_end/cache";
        //LOGI("RSBPathRecorder: [5/6] Checking directory: %s", cache_dir.c_str());

        //// 建议：如果 mkdir 失败且 errno=2，说明父目录不存在
        //if (mkdir(cache_dir.c_str(), 0777) != 0 && errno != EEXIST) {
        //    LOGW("RSBPathRecorder: ERROR - mkdir failed, errno=%d", errno);
        //    // 如果这里报错 2，意味着 com.ea.game.pvz2_end 这个目录都没建
        //    free(raw_buffer);
        //    return result;
        //}

        //std::string temp_path = cache_dir + "/cache.rsb";

        //// --- 阶段 4: 写入 ---
        //std::ofstream out_file(temp_path.c_str(), std::ios::binary);
        //if (!out_file.is_open()) {
        //    LOGW("RSBPathRecorder: ERROR - Open output failed, errno=%d", errno);
        //    free(raw_buffer);
        //    return result;
        //}

        //LOGI("RSBPathRecorder: [6/6] Writing to disk: %s", temp_path.c_str());
        //out_file.write(reinterpret_cast<char*>(raw_buffer), file_size);

        //if (!out_file) {
        //    LOGW("RSBPathRecorder: ERROR - Write failed, errno=%d", errno);
        //}
        //else {
        //    LOGI("RSBPathRecorder: SUCCESS!");
        //    g_tempFiles.push_back(temp_path);
        //}

        //out_file.close();
        //free(raw_buffer); // 记得手动释放 malloc 的内存
    }
    

    
    LOGI("RSB_TRACE: Starting Hybrid Mmap-Stream Process...");

    // 一定要改！！！！！把你的地址改成/data/user/0/com.ea.game.pvz2_改版名/files！！！！！
    //PS:为了多开用户，改成了/data/data/com.ea.game.pvz2_改版名/files
    std::string cache_dir = "/data/data/"+pack_name+"/files";///storage/emulated/0/Android/data/com.ea.game.pvz2_row/cache
    makePath(cache_dir);
    //这个地方可以随意写，这样别人就认不出来了
    std::string temp_path = cache_dir + "/.cache_data_file";

    // 2. 检测 1bsr (保持不变)
    int src_fd = open(original_path.c_str(), O_RDONLY);
    //读不到文件直接切到temp_path
    if (src_fd >= 0) {
        uint8_t magic[4];
        read(src_fd, magic, 4);
        if (memcmp(magic, "1bsr", 4) == 0) {
            LOGI("RSB_TRACE: Detected 1bsr, skipping...");
            //原逻辑是把未加密数据包也放临时路径，目前看来已经不必要
            //毕竟只有改版作者才拥有未加密数据包，再迁移不仅浪费时间还让作者得不到出问题的是哪个包（被隐藏了）
            /*int dst_fd = open(temp_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
            struct stat st; fstat(src_fd, &st);
            lseek(src_fd, 0, SEEK_SET);
            sendfile(dst_fd, src_fd, nullptr, st.st_size);
            close(dst_fd); close(src_fd);
            g_tempFiles.push_back(temp_path);*/
            return result;
        }
        if (memcmp(magic, "EBRL", 4) == 0 && isRooted()) {
            //是ROOT重写数据包头
            if (!maskFileHeader(original_path.c_str(), "RSB2")) {
                //重写失败报错
                LOGI("RSB_TRACE: RSB2 overrides failed.");
                return result;
            }
            else LOGI("RSB_TRACE: RSB2 overrides succeed.");
        }
        if (memcmp(magic, "EBRL", 4) == 0) {
            LOGI("RSB_TRACE: Detected EBRL, using temp_path...");
        }
        else {
            // 3. 准备 IV 和 Key (使用你的 HIDE_STR)
            uint8_t iv_from_header[16];
            read(src_fd, iv_from_header, 16);

            uint8_t key[32];
            {
                //此处填写密钥!!!!!!!!!!!!!!!!!!!!!!!!!
                std::string pwd = HIDE_STR("rl_key");
                picosha2::hash256_one_by_one hasher;
                hasher.process(pwd.begin(), pwd.end());
                hasher.finish();
                hasher.get_hash_bytes(key, key + 32);
            }

            // 4. 关键：利用内核 sendfile 完成第一次全量物理拷贝 (这是目前最快的读写方式)
            struct stat st; fstat(src_fd, &st);
            size_t file_size = st.st_size;
            int dst_fd = open(temp_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
            lseek(src_fd, 0, SEEK_SET);
            sendfile(dst_fd, src_fd, nullptr, file_size);
            close(src_fd);

            // 5. 分块映射解密 + 即时覆盖平移
            LOGI("RSB_TRACE: Phase: Mmap Decrypt + Immediate In-place Pwrite...");

            const size_t CHUNK_SIZE = 256 * 1024 * 1024; // 256MB，平衡 32 位内存压力与效率
            size_t current_cipher_pos = 20;
            size_t total_plain_written = 0;
            uint8_t active_iv[16];
            memcpy(active_iv, iv_from_header, 16);

            while (current_cipher_pos < file_size) {
                // 计算页对齐的映射偏移
                size_t map_offset = (current_cipher_pos / 4096) * 4096;
                size_t in_map_offset = current_cipher_pos - map_offset;

                size_t remaining = file_size - current_cipher_pos;
                size_t decrypt_len = (remaining > CHUNK_SIZE) ? CHUNK_SIZE : remaining;
                decrypt_len &= ~0xF; // 16字节对齐
                if (decrypt_len == 0) break;

                size_t map_size = decrypt_len + in_map_offset;
                void* ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, map_offset);
                if (ptr == MAP_FAILED) {
                    LOGI("RSB_TRACE: mmap failed, errno=%d", errno);
                    break;
                }

                uint8_t* cipher_ptr = (uint8_t*)ptr + in_map_offset;

                // 备份下一块密文 IV
                uint8_t next_iv_backup[16];
                memcpy(next_iv_backup, cipher_ptr + decrypt_len - 16, 16);

                // 调用多线程解密 (直接操作映射内存，极致速度)
                decrypt_pure_cbc_internal(cipher_ptr, decrypt_len, active_iv, key);

                // 更新当前链的 IV
                memcpy(active_iv, next_iv_backup, 16);

                // 处理 Padding (最后一块)
                size_t block_write_len = decrypt_len;
                if (current_cipher_pos + decrypt_len >= file_size - 16) {
                    uint8_t pad = cipher_ptr[decrypt_len - 1];
                    if (pad > 0 && pad <= 16) block_write_len -= pad;
                }

                // 【提速】利用 pwrite 将解密好的明文直接写回到文件开头的正确位置
                // 因为这块内存就在 Page Cache 里，pwrite 此时基本等同于内存拷贝，极快
                pwrite(dst_fd, cipher_ptr, block_write_len, total_plain_written);

                total_plain_written += block_write_len;
                munmap(ptr, map_size);
                current_cipher_pos += decrypt_len;
            }

            // 6. 最终裁剪：一秒搞定
            ftruncate(dst_fd, total_plain_written);
            fdatasync(dst_fd); // 确保元数据和数据写回
            close(dst_fd);

            LOGI("RSB_TRACE: All Done. Optimized Path Taken.");
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
    else {
        /*return result;*/
    }
    
    









    // 替换路径
    char* new_path = strdup(temp_path.c_str());
    if (!new_path) {
        LOGI("RSBPathRecorder: Failed to allocate new_path");
        return result;
    }
    size_t new_path_len = strlen(new_path);
    //if (a1[0] & 1) {
    //    a1[2] = (uint)new_path; // 动态分配，替换 a1[2]
    //}
    //else {
    //    a1[1] = (uint)new_path; // 非动态分配，替换 a1[1]
    //}
    if (a1[0] & 1) {
        // 动态分配
        if (a1[2]) {
            free((void*)a1[2]); // 释放原始路径
        }
        unsigned int v10 = new_path_len > 20 ? new_path_len : 20;
        unsigned int v8 = (v10 + 16) & 0xFFFFFFF0; // 分配大小
        a1[0] = v8 | 1; // a1[0] = 65 (0x41)
        a1[1] = new_path_len; // a1[1] = 47 (0x2F)
        a1[2] = (uint)new_path; // 新路径指针
    }
    else {
        // 非动态分配
        a1[0] = 2 * new_path_len; // a1[0] = 2 * 路径长度
        a1[1] = (uint)new_path; // a1[1] = 新路径指针
    }
    LOGI("RSBPathRecorder: Replaced path with %s", temp_path.c_str());

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
    //直装包专用：第一次载入RSB时候则延迟做到一次载入，否则只能第一次卡住第二次正常进
    dalay_hook();

    int backdata= oResourceManagerFunc(a1, a2, a3);
    LOGI("Hooking ResourcesManagerFunc 6EE218 End");
    //如果检测到ROOT，则进入秒删模式
    if (isRooted()) {
        LOGI("Cleaning up temp files");
        cleanupTempFiles();
    }
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





#pragma region JNI_OnLoad
// 之前定义的全局 VM 指针
//JavaVM* g_vm = nullptr;

// 封装一个简单的“开路”函数
//void prepare_obb_path(JNIEnv* env) {
//    // 1. 还是套路B：拿到 Application Context
//    jclass atClass = env->FindClass("android/app/ActivityThread");
//    jmethodID currentATMethod = env->GetStaticMethodID(atClass, "currentActivityThread", "()Landroid/app/ActivityThread;");
//    jobject atInstance = env->CallStaticObjectMethod(atClass, currentATMethod);
//    jmethodID getAppMethod = env->GetMethodID(atClass, "getApplication", "()Landroid/app/Application;");
//    jobject context = env->CallObjectMethod(atInstance, getAppMethod);
//
//    if (context) {
//        // 2. 核心：调用 getObbDir。这一步执行完，文件夹就变出来了！
//        jclass contextClass = env->FindClass("android/content/Context");
//        jmethodID getObbDir = env->GetMethodID(contextClass, "getObbDir", "()Ljava/io/File;");
//        jobject obbFile = env->CallObjectMethod(context, getObbDir);
//
//        //// 3. 拿到路径并执行你的 C 语言搬运逻辑
//        //jclass fileClass = env->FindClass("java/io/File");
//        //jmethodID getPath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
//        //jstring jstr = (jstring)env->CallObjectMethod(obbFile, getPath);
//
//        //const char* obbPath = env->GetStringUTFChars(jstr, nullptr);
//
//        //// --- 此时 OBB 文件夹已存在，直接搬运 ---
//        //// move_assets_to_obb(obbPath); 
//
//        //env->ReleaseStringUTFChars(jstr, obbPath);
//    }
//}
//typedef jint (*JNI_OnLoadFunc)(JavaVM* vm, void* reserved);
//JNI_OnLoadFunc oJNI_OnLoad = NULL;
//jint hkJNI_OnLoad(JavaVM* vm, void* reserved) {
//    //辛苦你了，接下来我要搞事情了！
//    if (!directed_install_executed.exchange(true)) {
//        JNIEnv* env = nullptr;
//        if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) == JNI_OK) {
//            // 在这里“借刀杀人”，先让系统把路径建好并搬运数据
//            LOGI("CreateOBBPath Start.");
//            prepare_obb_path(env);
//            LOGI("CreateOBBPath End.");
//            
//        }
//    }
//    return oJNI_OnLoad(vm, reserved);
//}
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
        LOGI("LogOutputFunc_Simple: %s", text);
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


#pragma region _android_log_write

typedef int (*LogWriteFunc)(int, const char*, const char*);
LogWriteFunc oLogWrite = NULL;

int hkLogWrite(int prio, const char* tag, const char* text)
{
    //日志等级prio
    /*ANDROID_LOG_VERBOSE	2
    ANDROID_LOG_DEBUG	3
    ANDROID_LOG_INFO	4
    ANDROID_LOG_WARN	5
    ANDROID_LOG_ERROR	6*/
    /*if (tag && strcmp(tag, "PvZ2Debug") == 0) {*/
    //if (prio == ANDROID_LOG_DEBUG) {
    //    /*LOGI("Forwarded: [%s] %s", tag, text);*/
    //    prio = ANDROID_LOG_INFO;
    //}
    return oLogWrite(prio, tag, text);
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
    LOGI("zoom= %f",zoom);
    *(float*)(a1 + 860) = 1.0f;
    
    //俩半逻辑宽度
    int32_t logicalA = *(int32_t*)(a1 + 832);
    int32_t logicalB = *(int32_t*)(a1 + 840);
    //改变左侧偏移(因为误差20像素，所以补上)
    *(int32_t*)(a1 + 824) = (int32_t)logicalB-20;/**(int32_t*)(a1 + 44)-mOrigScreenWidth;*///注释的是刘海屏留存的数值
    


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









#pragma region Build Symbol Funcs

//Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc PlantType::oPlantTypeBuildSymbols = nullptr;
//Reflection::CRefManualSymbolBuilder::ConstructFunc PlantType::oPlantTypeConstruct = nullptr;
//Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieType::oZombieTypeBuildSymbols = nullptr;
//Reflection::CRefManualSymbolBuilder::ConstructFunc ZombieType::oZombieTypeConstruct = nullptr;

#pragma endregion





__attribute__((constructor))
// This is automatically executed when the lib is loaded
// Run your initialization code here
void libRestructedLogic_ARM32__main()
{
    LOGI("Initializing %s", LIB_TAG);
    //根据版本修改偏移——已经不需要了
    /*AddressesChangedByVersion();*/
    
    /*if (!directed_install_executed.exchange(true)) {
        LOGI("RSBDirectInstall Start.");
        RSBDirectInstall();
        LOGI("RSBDirectInstall End.");
    }*/
    //直装包：数据包不存在则轮询路径是否存在
    if (!OBBExisted()) {
        std::thread(obb_path_monitor).detach();
    }
    

    // New, easier to manage way of adding typenames to the plant/zombie name mapper
    //No need to use///REGISTER_ZOMBIE_TYPENAME("steam");

    // Function hooks
    /*if (version_code < v10_3) {*/
    if (GAME_VERSION < 1000) {
        //PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
        PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
        PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
        PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");
        
        PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
        PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
        PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
        PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");
        PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");
    }
    else {
        //拖动函数
        PVZ2HookFunction(worldMapScrollAddr, (void*)hkworldMapScroll, (void**)&oworldMapScroll, "WorldMap::worldMapScroll");
        //居中函数
        PVZ2HookFunction(KeepCenterAddr, (void*)hkKeepCenter, (void**)&oKeepCenter, "WorldMap::KeepCenter");
        //惯性函数
        PVZ2HookFunction(ScrollInertanceAddr, (void*)hkScrollInertance, (void**)&oScrollInertance, "WorldMap::worldMapScroll");
    }
    ////直装包函数__没啥用
    //PVZ2HookFunction(JNI_OnLoadAddr, (void*)hkJNI_OnLoad, (void**)&oJNI_OnLoad, "JNI_OnLoad");
    ////输出简要日志
    //PVZ2HookFunction(LogOutputFuncAddrSimpleAddr, (void*)hkLogOutputFunc_Simple, (void**)&oLogOutputFunc_Simple, "LogOutputFunc_Simple");
    ////输出日志
    PVZ2HookFunction(LogOutputFuncAddr, (void*)hkLogOutputFunc, (void**)&oLogOutputFunc, "LogOutputFunc");
    ////输出结构日志
    //PVZ2HookFunction(LogOutputFuncAddr_Struct, (void*)hkLogOutputFunc_Struct, (void**)&oLogOutputFunc_Struct, "LogOutputFunc_Struct");
    ////输出v2日志
    //PVZ2HookFunction(LogOutputFuncAddr_v2, (void*)hkLogOutputFunc_v2, (void**)&oLogOutputFunc_v2, "LogOutputFunc_v2");
    


    //直接主log函数__不能用，用了必无限递归
    //PVZ2HookFunction(LogWriteAddr, (void*)hkLogWrite, (void**)&oLogWrite, "LogWrite");

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
    //CDN读取rton，感谢CZ技术专栏分享技术！！！
    PVZ2HookFunction(CDNLoadAddr, (void*)hkCDNLoad, (void**)&oCDNLoad, "CDNLoadExpansion");
    ////控制屏幕缩放
    //PVZ2HookFunction(0x2F9F40, (void*)hkUniversalZoom, (void**)&oUniversalZoom, "UniversalZoom");
    ////控制屏幕缩放
    //PVZ2HookFunction(0x7013C0, (void*)hkUniversalZoom1, (void**)&oUniversalZoom1, "UniversalZoom1");
    //得到缩放前后尺寸
    PVZ2HookFunction(LawnAppScreenWidthHeightAddr, (void*)hkLawnAppScreenWidthHeight, (void**)&oLawnAppScreenWidthHeight, "LawnApp:SetScreenWidthHeight");
    //控制屏幕缩放
    PVZ2HookFunction(BoardZoomAddr, (void*)hkBoardZoom, (void**)&oBoardZoom, "BoardZoom");
    PVZ2HookFunction(BoardZoom2Addr, (void*)hkBoardZoom2, (void**)&oBoardZoom2, "BoardZoom2");
    //防手机刘海（似乎没有用）
    /*PVZ2HookFunction(0xFB0288, (void*)hkIgnoreSafeArea, (void**)&oIgnoreSafeArea, "IgnoreSafeArea");*/
    //弃用，缩放率，没多大用PVZ2HookFunction(0x16460F0, (void*)hkSub_16460F0, (void**)&oSub_16460F0, "Sub_16460F0");
    
    
    







    GridItemRaiserProjectileProps::modInit();

    LOGI("Finished initializing");
}
