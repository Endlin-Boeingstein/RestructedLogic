#include "RestructedLogic_ARM32_.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unistd.h>
#include "memUtils.h"
#include <mutex>
#include <fstream>
#include <sys/stat.h>
#include "Decrypt/picosha2.h"
#include "Decrypt/aes.h"
#include <thread>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include "VersionSwitcher.h"

#if GAME_VERSION < 1031

namespace AliasToID {
class PlantNameMapper {
 public:
  void *vftable;
  std::map<Sexy::SexyString, uint> m_aliasToId;
};
std::vector<Sexy::SexyString> g_modPlantTypenames;

#define REGISTER_PLANT_TYPENAME(typename) g_modPlantTypenames.push_back(typename);

typedef PlantNameMapper *(*PlantNameMapperCtor)(PlantNameMapper *);
PlantNameMapperCtor oPlantNameMapperCtor = NULL;

void *hkCreatePlantNameMapper(PlantNameMapper *self) {
  oPlantNameMapperCtor(self);
  g_modPlantTypenames.clear();
  for (int i = 1; i <= 100; i++) {
    REGISTER_PLANT_TYPENAME(("custom_plant_" + std::to_string(i)));
  }
  LOGI("Extra typenames size = %d", g_modPlantTypenames.size());
  for (int iter = 0; iter < g_modPlantTypenames.size(); iter++) {
    LOGI("Registering plant %s", g_modPlantTypenames[iter].c_str());
    self->m_aliasToId[g_modPlantTypenames[iter]] = firstFreePlantID + iter;
  }
  return self;
}

inline void process() {
  PVZ2HookFunction(PlantNameMapperAddr, (void *)hkCreatePlantNameMapper,
                   (void **)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
}
#undef REGISTER_PLANT_TYPENAME
}  // namespace AliasToID

#endif

namespace PrimeGlyphCacheLimitation {
typedef uint *(*PrimeGlyphCacheLimitation)(uint *, int, int, int);
PrimeGlyphCacheLimitation oPrimeGlyphCacheLimitation = NULL;

// 一路：高端设备缓冲大小为2048，中端设备为1024，低端设备为512。经过测试，缓冲大小最大只能设为2048，设为更高值，会导致进入游戏后文字渲染全为空白，这与设为0的效果一致。
uint *hkPrimeGlyphCacheLimitation(uint *a1, int a2, int a3, int a4) {
  uint *result = oPrimeGlyphCacheLimitation(a1, a2, a3, a4);
  a1[22] = 2048;
  LOGI("Hooked sub_177ECF4: Modified a1[22] to %d", a1[22]);
  return result;
}

inline void process() {
  PVZ2HookFunction(PrimeGlyphCacheAddr, (void *)hkPrimeGlyphCacheLimitation,
                   (void **)&oPrimeGlyphCacheLimitation,
                   "PrimeGlyphCache::PrimeGlyphCacheLimitation");
}
}  // namespace PrimeGlyphCacheLimitation

namespace RSBPathChangeAndDecryptRSB {
// C++11 兼容的编译期字符串混淆
template <size_t... Is>
struct index_sequence {};
template <size_t N, size_t... Is>
struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...> {};
template <size_t... Is>
struct make_index_sequence<0, Is...> : index_sequence<Is...> {};

template <int XorKey, size_t N>
struct ObfuscatedString {
  char encrypted[N];
  template <size_t... Is>
  constexpr ObfuscatedString(const char *str, index_sequence<Is...>)
      : encrypted{static_cast<char>(str[Is] ^ (XorKey + Is))...} {}

  inline std::string decrypt() const {
    std::string s;
    s.resize(N - 1);
    for (size_t i = 0; i < N - 1; ++i)
      s[i] = encrypted[i] ^ (XorKey + i);
    return s;
  }
};
#define HIDE_STR(s) \
  (ObfuscatedString<(0x55 + __LINE__), sizeof(s)>(s, make_index_sequence<sizeof(s)>()).decrypt())

/**
 * 递归创建目录 (模拟 mkdir -p)
 * @param path 目标绝对路径
 * @return 是否创建成功或目录已存在
 */
bool makePath(const std::string &path) {
  std::string tmp_path = path;
  // 确保路径以斜杠结尾，方便统一逻辑处理
  if (tmp_path.empty())
    return false;
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

/**
 * 纯解密核心：专门适配分块映射。
 * 只做解密，不移动内存，不检测 Header。
 * 核心解密：纯计算，不检测 Magic，不移动内存
 * 确保 decrypt_pure_cbc_internal 接收 key
 */
void decrypt_pure_cbc_internal(uint8_t *data, size_t size, const uint8_t *start_iv,
                               const uint8_t *key) {
  uint32_t num_blocks = (uint32_t)(size / 16);
  unsigned int num_threads = std::thread::hardware_concurrency();
  if (num_threads == 0)
    num_threads = 4;

  uint32_t blocks_per_thread = num_blocks / num_threads;
  std::vector<std::thread> threads;

  for (unsigned int t = 0; t < num_threads; ++t) {
    uint32_t start_block = t * blocks_per_thread;
    uint32_t end_block = (t == num_threads - 1) ? num_blocks : (t + 1) * blocks_per_thread;

    threads.emplace_back([=, &key, &start_iv]() {
      uint32_t t_offset = start_block * 16;
      uint32_t t_len = (end_block - start_block) * 16;
      if (t_len == 0)
        return;

      struct AES_ctx ctx;
      uint8_t thread_iv[16];

      if (start_block == 0) {
        memcpy(thread_iv, start_iv, 16);
      } else {
        memcpy(thread_iv, data + t_offset - 16, 16);
      }

      AES_init_ctx_iv(&ctx, key, thread_iv);
      AES_CBC_decrypt_buffer(&ctx, data + t_offset, t_len);
    });
  }
  for (auto &th : threads)
    th.join();
}

// 将文件头部替换为可识别四字节
bool maskFileHeader(const std::string &filePath, std::string tagstr) {
  // 1. 以读写模式打开文件 (注意不要加 O_TRUNC，否则文件会被清空！)
  int fd = open(filePath.c_str(), O_RDWR);
  if (fd < 0)
    return false;
  // 2. 准备新的 4 字节头
  const char *tag = tagstr.c_str();
  // 3. 使用 pwrite 直接覆盖偏移量为 0 的位置
  // 这一步是原子操作，只改动磁盘上最开始的 4 个字节
  ssize_t bytes = pwrite(fd, tag, 4, 0);
  // 4. 强制将修改刷入磁盘（防止断电丢失）
  fdatasync(fd);
  close(fd);

  return bytes == 4;
}

// 检测是否ROOT
bool isRooted() {
  // 检查常见的 Root 路径和文件
  const char *paths[] = {"/system/app/Superuser.apk", "/sbin/su", "/system/bin/su",
                         "/system/xbin/su"};
  for (auto path : paths) {
    if (access(path, F_OK) == 0)
      return true;
  }
  return false;
}

// 临时文件路径列表
static std::vector<std::string> g_tempFiles;
void cleanupTempFiles() {
  for (const auto &path : g_tempFiles) {
    if (unlink(path.c_str()) == 0) {
      LOGI("Deleted temp file: %s", path.c_str());
    } else {
      LOGI("Failed to delete temp file: %s, errno=%d", path.c_str(), errno);
    }
  }
  g_tempFiles.clear();
}

// Hook 函数
typedef int (*RSBPathRecorder)(uint *a1);
RSBPathRecorder oRSBPathRecorder = nullptr;

int hkRSBPathRecorder(uint *a1) {
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
  LOGI("RSBPathRecorder: Original function returned %d, a1[0]=0x%x, a1[1]=0x%x, a1[2]=0x%x", result,
       a1[0], a1[1], a1[2]);

  // 提取路径
  char *path_ptr = nullptr;
  if (a1[0] & 1) {
    path_ptr = (char *)a1[2];  // 动态分配，路径在 a1[2]
  } else {
    path_ptr = (char *)a1[1];  // 非动态分配，路径在 a1[1]
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
  std::string expected_path =
      "/storage/emulated/0/Android/obb/com.ea.game.pvz2_na/main.763.com.ea.game.pvz2_na.obb";
  if (original_path != expected_path) {
    LOGI("RSBPathRecorder: Path mismatch, expected %s", expected_path.c_str());
    // 继续处理，允许非预期路径
  }

  LOGI("RSB_TRACE: Starting Hybrid Mmap-Stream Process...");

  // 一定要改！！！！！把你的地址改成/data/user/0/com.ea.game.pvz2_改版名/files！！！！！
  std::string cache_dir =
      "/data/user/0/com.ea.game.pvz2_row/files";  /// storage/emulated/0/Android/data/com.ea.game.pvz2_row/cache
  makePath(cache_dir);
  // 这个地方可以随意写，这样别人就认不出来了
  std::string temp_path = cache_dir + "/.cache_data_file";

  // 2. 检测 1bsr (保持不变)
  int src_fd = open(original_path.c_str(), O_RDONLY);
  // 读不到文件直接切到temp_path
  if (src_fd >= 0) {
    uint8_t magic[4];
    read(src_fd, magic, 4);
    if (memcmp(magic, "1bsr", 4) == 0) {
      LOGI("RSB_TRACE: Detected 1bsr, skipping...");
      // 原逻辑是把未加密数据包也放临时路径，目前看来已经不必要
      // 毕竟只有改版作者才拥有未加密数据包，再迁移不仅浪费时间还让作者得不到出问题的是哪个包（被隐藏了）
      return result;
    }
    if (memcmp(magic, "EBRL", 4) == 0 && isRooted()) {
      // 是ROOT重写数据包头
      if (!maskFileHeader(original_path.c_str(), "RSB2")) {
        // 重写失败报错
        LOGI("RSB_TRACE: RSB2 overrides failed.");
        return result;
      } else
        LOGI("RSB_TRACE: RSB2 overrides succeed.");
    }
    if (memcmp(magic, "EBRL", 4) == 0) {
      LOGI("RSB_TRACE: Detected EBRL, using temp_path...");
    } else {
      // 3. 准备 IV 和 Key (使用你的 HIDE_STR)
      uint8_t iv_from_header[16];
      read(src_fd, iv_from_header, 16);

      uint8_t key[32];
      {
        // 此处填写密钥!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string pwd = HIDE_STR("rl_key");
        picosha2::hash256_one_by_one hasher;
        hasher.process(pwd.begin(), pwd.end());
        hasher.finish();
        hasher.get_hash_bytes(key, key + 32);
      }

      // 4. 关键：利用内核 sendfile 完成第一次全量物理拷贝 (这是目前最快的读写方式)
      struct stat st;
      fstat(src_fd, &st);
      size_t file_size = st.st_size;
      int dst_fd = open(temp_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
      lseek(src_fd, 0, SEEK_SET);
      sendfile(dst_fd, src_fd, nullptr, file_size);
      close(src_fd);

      // 5. 分块映射解密 + 即时覆盖平移
      LOGI("RSB_TRACE: Phase: Mmap Decrypt + Immediate In-place Pwrite...");

      const size_t CHUNK_SIZE = 256 * 1024 * 1024;  // 256MB，平衡 32 位内存压力与效率
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
        decrypt_len &= ~0xF;  // 16字节对齐
        if (decrypt_len == 0)
          break;

        size_t map_size = decrypt_len + in_map_offset;
        void *ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, map_offset);
        if (ptr == MAP_FAILED) {
          LOGI("RSB_TRACE: mmap failed, errno=%d", errno);
          break;
        }

        uint8_t *cipher_ptr = (uint8_t *)ptr + in_map_offset;

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
          if (pad > 0 && pad <= 16)
            block_write_len -= pad;
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
      fdatasync(dst_fd);  // 确保元数据和数据写回
      close(dst_fd);

      LOGI("RSB_TRACE: All Done. Optimized Path Taken.");
      // 没必要清理临时数据了，因为现在的临时通道作为隐藏通道来使用，而加密数据包会被干掉，做到一次解密终生秒进
      // 重写数据包头部为EBRL
      if (!isRooted()) {
        // 没ROOT重写数据包头
        if (!maskFileHeader(original_path.c_str(), "EBRL")) {
          // 重写失败报错
          LOGI("RSB_TRACE: EBRL overrides failed.");
          return result;
        } else
          LOGI("RSB_TRACE: EBRL overrides succeed.");
      }
      // ROOT警报
      else {
        // 记录需要删除的解密数据包（因为需要防ROOT）
        g_tempFiles.push_back(temp_path);
        LOGI("RSB_TRACE: Warning! Device rooted.");
      }
    }
  } else {
    /*return result;*/
  }

  // 替换路径
  char *new_path = strdup(temp_path.c_str());
  if (!new_path) {
    LOGI("RSBPathRecorder: Failed to allocate new_path");
    return result;
  }
  size_t new_path_len = strlen(new_path);
  // if (a1[0] & 1) {
  //     a1[2] = (uint)new_path; // 动态分配，替换 a1[2]
  // }
  // else {
  //     a1[1] = (uint)new_path; // 非动态分配，替换 a1[1]
  // }
  if (a1[0] & 1) {
    // 动态分配
    if (a1[2]) {
      free((void *)a1[2]);  // 释放原始路径
    }
    unsigned int v10 = new_path_len > 20 ? new_path_len : 20;
    unsigned int v8 = (v10 + 16) & 0xFFFFFFF0;  // 分配大小
    a1[0] = v8 | 1;                             // a1[0] = 65 (0x41)
    a1[1] = new_path_len;                       // a1[1] = 47 (0x2F)
    a1[2] = (uint)new_path;                     // 新路径指针
  } else {
    // 非动态分配
    a1[0] = 2 * new_path_len;  // a1[0] = 2 * 路径长度
    a1[1] = (uint)new_path;    // a1[1] = 新路径指针
  }
  LOGI("RSBPathRecorder: Replaced path with %s", temp_path.c_str());

  return result;
}

// ROOT 检测
typedef int (*ResourceManagerFunc)(int, int, int);
ResourceManagerFunc oResourceManagerFunc = NULL;
int hkResourceManagerFunc(int a1, int a2, int a3) {
  LOGI("Hooking ResourcesManagerFunc 6EE218");
  LOGI("a1=%d, a2=%d, a3=%d", a1, a2, a3);
  int backdata = oResourceManagerFunc(a1, a2, a3);
  LOGI("Hooking ResourcesManagerFunc 6EE218 End");
  // 如果检测到ROOT，则进入秒删模式
  if (isRooted()) {
    LOGI("Cleaning up temp files");
    cleanupTempFiles();
  }
  return backdata;
}

inline void process() {
  // Hook RSB 读取函数
  PVZ2HookFunction(RSBPathRecorderAddr, (void *)hkRSBPathRecorder, (void **)&oRSBPathRecorder,
                   "ResourceManager::RSBPathRecorder");
  // ROOT 检测
  PVZ2HookFunction(ResourceManagerFuncAddr, (void *)hkResourceManagerFunc,
                   (void **)&oResourceManagerFunc, "ResourceManager::ResourceManagerFunc");
}
}  // namespace RSBPathChangeAndDecryptRSB

namespace CDNExpansion {
// 在此感谢CZ的技术专栏分享，我将变量名和一些方式进行了小小的改变，但依旧需要对其为技术的分享表达感谢！！！！！
typedef int (*CDNExpand)(int *a1, const Sexy::SexyString &rtonName, int rtonTable, int a4);
CDNExpand oCDNLoad = NULL;

std::atomic<bool> executed(false);

void hkCDNLoad(int *a1, const Sexy::SexyString &rtonName, int rtonTable, int a4) {
  if (!oCDNLoad) {
    LOGI("Rton Table IDs Old Load failed.");
    return;
  }
  // 至于这个偏移怎么查.........很简单，HEX搜products.rton
  // 然后根据products.rton的"p"的偏移地址，用ida pro跳转到该地址
  // 你会发现一堆的rton（绿色）右侧都用同一个DATA XREF地址跳转（引用偏移地址）
  // 双击那个地址，你就会到达CZ讲的那个大函数，跳转后按F5，然后向下翻就能看到
  // 那些rton下面都有同一个函数，就是那个函数需要hook
  // 然后原理CZ讲过了，我也是直接拿来用，没啥丢脸的，有公开的好东西不用才是固执嘛......
  // 不过，CZ拿64位演示，推荐的bb2和jay krow的32位工程，对于一些萌新来说可不友好哦......
  // 原理很简单（如果这都要拿AI去查什么意思的话，那我可要数落你了啊）
  // executed一开始为false，我们在塞入rton之前的第一步就是检测executed是否为true
  // executed你可以比喻为一个罐子，打开了就是true，没打开就是false，我们只需要打开一次就不需要打开了
  // 所以第一次我们打开之前，罐子是未开封状态，打开了就是开封状态
  // 未开封状态我们要打开罐子拿出东西塞别的里面去，我们塞过之后就不需要再塞重复的了
  // 所以一看到开封的状态我们就知道不需要在这个罐子里面拿东西了
  // 所以executed在我们塞rton之前是false，塞rton时候就已经变true了，就不需要再塞了
  if (!executed.exchange(true)) {
    // 载入各版本RtonTableID
    rtonTableIDsLoader();
    LOGI("Rton Table IDs Load succeed.");
    // 遍历载入
    for (const auto &rtonfile : rtonTableIDs) {
      oCDNLoad(a1, rtonfile.first, rtonfile.second, 1);
      LOGI("%s:%d is loaded", (rtonfile.first).c_str(), rtonfile.second);
    }
  }
  LOGI("%s:%d is loaded", rtonName.c_str(), rtonTable);
  oCDNLoad(a1, rtonName, rtonTable, a4);
}

inline void process() {
  // CDN读取rton，感谢CZ技术专栏分享技术！！！
  PVZ2HookFunction(CDNLoadAddr, (void *)hkCDNLoad, (void **)&oCDNLoad, "CDNLoadExpansion");
}
}  // namespace CDNExpansion

namespace LogOutput {
typedef int (*LogOutputFunc)(char *, ...);
LogOutputFunc oLogOutputFunc = NULL;
std::mutex g_logMutex;

int hkLogOutputFunc(char *format, ...) {
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
  char *buffer;
  if (len >= 0 && len < 1024) {
    buffer = new char[1024];
    len = vsnprintf(buffer, 1024, format, va);
    buffer[len] = '\0';
    LOGI("LogOutputFunc: %s", buffer);
  } else if (len >= 0) {
    buffer = new char[len + 1];
    len = vsnprintf(buffer, len + 1, format, va);
    buffer[len] = '\0';
    LOGI("LogOutputFunc: %s", buffer);
  } else {
    LOGI("LogOutputFunc: Failed to format, format=%s, len=%d", format ? format : "null", len);
    return -1;
  }

  int result = oLogOutputFunc(format, va_copy);
  va_end(va_copy);
  va_end(va);
  delete[] buffer;
  return result;
}

typedef int (*LogOutputFunc_Simple)(const char *);
LogOutputFunc_Simple oLogOutputFunc_Simple = NULL;
std::mutex g_logMutex_Simple;

int hkLogOutputFunc_Simple(const char *text) {
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

// 参数是 int (寄存器 r0)，在 Hook 中我们定义为 void* 或 long
typedef int (*LogOutputFunc_Struct)(void *);
LogOutputFunc_Struct oLogOutputFunc_Struct = NULL;
std::mutex g_logMutex_Struct;

int hkLogOutputFunc_Struct(void *result) {
  if (!oLogOutputFunc_Struct) {
    LOGI("LogOutputFunc_Struct: Original function pointer is null");
    return -1;
  }

  if (result) {
    const char *v1 = NULL;
    // 模仿 IDA 逻辑：检查标志位
    // 如果 (*(unsigned char*)result & 1) != 0
    if ((*((unsigned char *)result) & 1) != 0) {
      // 长字符串逻辑：从偏移 8 处取指针
      v1 = *(const char **)((uint)result + 8);
    } else {
      // 短字符串逻辑：从偏移 1 处取内容
      v1 = (const char *)((uint)result + 1);
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
  const char *format = (const char *)a1;
  char *buffer = nullptr;
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
  } else {
    LOGI("LogOutputFunc_v2: Failed to format, a1=%p", (void *)a1);
  }

  // 2. 调用原始函数
  // 同样注意：C语言中无法直接将 va_list 传给 ...，这里取决于你的 Hook 框架支持
  // 如果是 Dobby/Substrate，通常建议转发参数
  int result = oLogOutputFunc_v2(a1, va_copy);

  va_end(va_copy);
  if (buffer)
    delete[] buffer;

  return result;
}

void process() {
  // 输出简要日志
  PVZ2HookFunction(LogOutputFuncAddr_Simple, (void *)hkLogOutputFunc_Simple,
                   (void **)&oLogOutputFunc_Simple, "LogOutputFunc_Simple");
  // 输出主日志
  PVZ2HookFunction(LogOutputFuncAddr, (void *)hkLogOutputFunc, (void **)&oLogOutputFunc,
                   "LogOutputFunc");
  // 输出结构日志
  PVZ2HookFunction(LogOutputFuncAddr_Struct, (void *)hkLogOutputFunc_Struct,
                   (void **)&oLogOutputFunc_Struct, "LogOutputFunc_Struct");
  // 输出v2日志
  PVZ2HookFunction(LogOutputFuncAddr_v2, (void *)hkLogOutputFunc_v2, (void **)&oLogOutputFunc_v2,
                   "LogOutputFunc_v2");
}
}  // namespace LogOutput

namespace MaxZoom {

constexpr int TEXTURE_WIDTH = 2048, TEXTURE_LEFT_WIDTH = 556, TEXTURE_RIGHT_WIDTH = 1345;
constexpr int stageRightLine = TEXTURE_WIDTH + TEXTURE_RIGHT_WIDTH;

// 选卡界面与正式游戏视野右边缘（相对于棋盘左侧边缘的距离）
int gameStartRightLine, preGameRightLine;

// 设备分辨率
#ifdef _DEBUG
int mOrigScreenWidth;
#endif
int mOrigScreenHeight;

// 游戏分辨率
int mWidth;
#ifdef _DEBUG
int mHeight;
#endif

// LawnAppScreenWidthHeight 的原函数会随版本变化。目前只知道 8.7.3 和 10.3.1
// 的写法。其他版本欢迎补充。
#if GAME_VERSION == 873

typedef int (*LawnAppScreenWidthHeight)(int a1, int a2);
LawnAppScreenWidthHeight oLawnAppScreenWidthHeight = nullptr;

int hkLawnAppScreenWidthHeight(int a1, int a2) {
  // 1. 先执行原函数，让内部逻辑完成内存写入
  int result = oLawnAppScreenWidthHeight(a1, a2);

  if (a1 == NULL)
    return result;

  // 2. 根据偏移直接提取数据
  // 根据 sub_FFE7D0
#ifdef _DEBUG
  mOrigScreenWidth = *(int32_t *)(a1 + 1512);
#endif
  mOrigScreenHeight = *(int32_t *)(a1 + 1516);

  // 根据自身
  mWidth = *(int32_t *)(a1 + 136);
#ifdef _DEBUG
  mHeight = *(int32_t *)(a1 + 140);
#endif

  // 3. 输出日志
  LOGI(R"(
--- LawnApp::SetWidthHeight Hook ---
mOrigWidth: %d, mOrigHeight: %d
mWidth: %d, mHeight: %d
result: %d)",
       mOrigScreenWidth, mOrigScreenHeight, mWidth, mHeight, result);

  // 若游戏分辨率宽度大于棋盘和左侧的总宽度（足以让左侧全部显示），则使偏移与左侧宽度相同
  // 否则使偏移等于游戏分辨率宽度减去棋盘宽度（即让右侧边缘与屏幕右侧对齐）
  gameStartRightLine = (mWidth >= TEXTURE_WIDTH + TEXTURE_LEFT_WIDTH)
                           ? (mWidth - TEXTURE_LEFT_WIDTH)
                           : TEXTURE_WIDTH;
  gameStartRightLine = std::min(gameStartRightLine, stageRightLine);
  preGameRightLine = (gameStartRightLine + stageRightLine) / 2;
  preGameRightLine = std::min(preGameRightLine, stageRightLine);

  return result;
}

#elif GAME_VERSION == 1031

typedef int (*LawnAppScreenWidthHeight)(float *a1, int a2);
LawnAppScreenWidthHeight oLawnAppScreenWidthHeight = nullptr;

int hkLawnAppScreenWidthHeight(float *a1, int a2) {
  // 1. 先执行原函数，让内部逻辑完成内存写入
  int result = oLawnAppScreenWidthHeight(a1, a2);

  if (a1 == nullptr)
    return result;

  // 2. 根据偏移直接提取数据
  // 注意：a1 是 float*，偏移计算需小心转换
  int *iPtr = (int *)a1;

  // 根据 sub_1482320: 1448字节 = 偏移362, 1452字节 = 偏移363
#ifdef _DEBUG
  mOrigScreenWidth = iPtr[362];
#endif
  mOrigScreenHeight = iPtr[363];

  // 根据自身
  mWidth = iPtr[25];
#ifdef _DEBUG
  mHeight = iPtr[26];
#endif

  // 3. 输出日志
  LOGI(R"(
--- LawnApp::SetWidthHeight Hook ---
mOrigWidth: %d, mOrigHeight: %d
mWidth: %d, mHeight: %d
result: %d)",
       mOrigScreenWidth, mOrigScreenHeight, mWidth, mHeight, result);

  // 若游戏分辨率宽度大于棋盘和左侧的总宽度（足以让左侧全部显示），则使偏移与左侧宽度相同
  // 否则使偏移等于游戏分辨率宽度减去棋盘宽度（即让右侧边缘与屏幕右侧对齐）
  gameStartRightLine = (mWidth >= TEXTURE_WIDTH + TEXTURE_LEFT_WIDTH)
                           ? (mWidth - TEXTURE_LEFT_WIDTH)
                           : TEXTURE_WIDTH;
  gameStartRightLine = std::min(gameStartRightLine, stageRightLine);
  preGameRightLine = (gameStartRightLine + stageRightLine) / 2;
  preGameRightLine = std::min(preGameRightLine, stageRightLine);

  return result;
}

#else

#error \
    "Unsupported game version for LawnAppScreenWidthHeight hook. You may try the above 2 versions."

#endif

// 定义原函数的函数原型
typedef int (*OrigBoardZoom)(int a1);
OrigBoardZoom oBoardZoom = nullptr;

int hkBoardZoom(int a1) {
  // 先跑原函数
  int result = oBoardZoom(a1);
  // 改变选卡时视野左边缘与棋盘左边缘的距离
  *(int32_t *)(a1 + 880) = preGameRightLine - mWidth;
  // 高度无法调整，只能靠缩放
  return result;
}

// 定义原函数的函数原型
typedef int (*OrigBoardZoom2)(int a1);
OrigBoardZoom2 oBoardZoom2 = nullptr;

int hkBoardZoom2(int a1) {
  int result = oBoardZoom2(a1);
  // 缩放系数
  *(float *)(a1 + 860) = 1.0f;
  // 改变视野左边缘与棋盘左边缘的距离
  *(int32_t *)(a1 + 824) = -(gameStartRightLine - mWidth);
  // 顶部基准线
  *(int32_t *)(a1 + 868) = (int32_t)mOrigScreenHeight;
  return result;
}

inline void process() {
  // 得到缩放前后尺寸
  PVZ2HookFunction(LawnAppScreenWidthHeightAddr, (void *)hkLawnAppScreenWidthHeight,
                   (void **)&oLawnAppScreenWidthHeight, "LawnApp:SetScreenWidthHeight");
  // 控制屏幕缩放
  PVZ2HookFunction(BoardZoomAddr, (void *)hkBoardZoom, (void **)&oBoardZoom, "BoardZoom");
  PVZ2HookFunction(BoardZoom2Addr, (void *)hkBoardZoom2, (void **)&oBoardZoom2, "BoardZoom2");
}
}  // namespace MaxZoom

__attribute__((constructor)) void libRestructedLogic_ARM32__main() {
  LOGI("Initializing %s", LIB_TAG);

#if GAME_VERSION < 1031
  AliasToID::process();  // 添加植物 ID（疑似无效）
#endif
#ifdef _DEBUG
  LogOutput::process();     // 输出日志
  CDNExpansion::process();  // 自定义 CDN 列表
#endif
  PrimeGlyphCacheLimitation::process();   // 修改字符缓冲区大小
  RSBPathChangeAndDecryptRSB::process();  // RSB 加密
  MaxZoom::process();                     // 高视角

  LOGI("Finished initializing");
}
