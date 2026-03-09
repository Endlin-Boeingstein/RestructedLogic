#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
extern "C" {
#include "miniz.h"
#include "../XXHash/xxhash.h"
}

namespace fs = std::filesystem;

class HashComparer {
public:
    // 针对 32 位优化的文件哈希计算
    static uint32_t compute_file_hash_32(const fs::path& filePath) {
        if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
            return 0;
        }

        std::ifstream file(filePath, std::ios::binary);
        if (!file) return 0;

        // 1. 初始化 32 位状态 (State)
        XXH32_state_t* state = XXH32_createState();
        XXH32_reset(state, 0); // 0 是种子 Seed

        // 2. 分块读取
        std::vector<char> buffer(64 * 1024);
        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            // 使用 32 位更新接口
            XXH32_update(state, buffer.data(), file.gcount());
        }

        // 3. 生成结果 (uint32_t)
        uint32_t hash = XXH32_digest(state);
        XXH32_freeState(state);
        return hash;
    }

    // 根据路径对比函数
    static bool are_files_identical_32(const fs::path& p1, const fs::path& p2) {
        // 基础优化：比大小
        if (fs::file_size(p1) != fs::file_size(p2)) return false;

        // 哈希校验
        return compute_file_hash_32(p1) == compute_file_hash_32(p2);
    }
    
    //根据哈希值对比32位
    static bool are_hashes_identical_32(const uint32_t p1, const uint32_t p2) {
        return p1 == p2;
    }

    // 辅助函数：计算单个文件的哈希值
    static XXH64_hash_t compute_file_hash(const fs::path& filePath) {
        // 基础检查：文件是否存在且是常规文件
        if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
            return 0;
        }

        std::ifstream file(filePath, std::ios::binary);
        if (!file) return 0;

        // 使用 XXH3 的流式处理（State），防止大文件撑爆内存
        XXH3_state_t* state = XXH3_createState();
        XXH3_64bits_reset(state);

        // 64KB 缓冲区对 L1/L2 缓存友好
        std::vector<char> buffer(64 * 1024);
        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            XXH3_64bits_update(state, buffer.data(), file.gcount());
        }

        XXH64_hash_t hash = XXH3_64bits_digest(state);
        XXH3_freeState(state);
        return hash;
    }

    // 根据路径32位64位通用对比函数
    static bool are_files_identical(const fs::path& p1, const fs::path& p2) {
        // 优化 1：先比大小。如果大小不等，内容绝对不等，没必要算哈希。
        if (fs::file_size(p1) != fs::file_size(p2)) {
            return false;
        }

        // 优化 2：计算并对比哈希
        return compute_file_hash(p1) == compute_file_hash(p2);
    }

    //根据哈希值对比64位
    static bool are_hashes_identical_64(const uint64_t p1, const uint64_t p2) {
        return p1 == p2;
    }

    // 回调函数：miniz 每解压出一块数据就传给 xxHash 处理
    static size_t hash_update_callback(void* pUser_data, mz_uint64 file_ofs, const void* pBuffer, size_t n) {
        XXH32_state_t* state = static_cast<XXH32_state_t*>(pUser_data);
        // 将解压出的原始数据（pBuffer）喂给哈希状态机
        if (XXH32_update(state, pBuffer, n) == XXH_OK) {
            return n;
        }
        return 0; // 如果更新失败，返回 0 告知 miniz 停止解压
    }

    static uint32_t get_asset_hash_32(const std::string& apk_path,
        const std::string& asset_internal_path)
    {
        mz_zip_archive zip{};

        // 1. 初始化并打开 APK
        if (!mz_zip_reader_init_file(&zip, apk_path.c_str(), 0)) {
            LOGI("Failed to open apk: %s", apk_path.c_str());
            return 0;
        }

        // 2. 定位目标文件索引
        int file_index = mz_zip_reader_locate_file(
            &zip,
            asset_internal_path.c_str(),
            nullptr,
            0
        );

        if (file_index < 0) {
            LOGI("File not found in apk: %s", asset_internal_path.c_str());
            mz_zip_reader_end(&zip);
            return 0;
        }

        // 3. 准备 xxHash 32位状态机
        XXH32_state_t* state = XXH32_createState();
        if (!state) {
            mz_zip_reader_end(&zip);
            return 0;
        }
        XXH32_reset(state, 0); // 种子设为 0

        // 4. 流式解压：直接将数据流导入回调函数
        // 这种方式最省内存，数据块解压完并更新哈希后会立即被丢弃
        if (!mz_zip_reader_extract_to_callback(
            &zip,
            (mz_uint)file_index,
            hash_update_callback,
            state,
            0))
        {
            LOGI("Extract to callback failed for: %s", asset_internal_path.c_str());
            XXH32_freeState(state);
            mz_zip_reader_end(&zip);
            return 0;
        }

        // 5. 获取最终哈希结果
        uint32_t final_hash = XXH32_digest(state);

        // 6. 清理资源
        XXH32_freeState(state);
        mz_zip_reader_end(&zip);

        return final_hash;
    }

    // 64 位回调函数：适配 XXH3
    static size_t hash_update_callback_64(void* pUser_data, mz_uint64 file_ofs, const void* pBuffer, size_t n) {
        XXH3_state_t* state = static_cast<XXH3_state_t*>(pUser_data);
        // XXH3 的更新接口是 XXH3_64bits_update
        if (XXH3_64bits_update(state, pBuffer, n) == XXH_OK) {
            return n;
        }
        return 0;
    }

    static uint64_t get_asset_hash_64(const std::string& apk_path,
        const std::string& asset_internal_path)
    {
        mz_zip_archive zip{};

        // 1. 初始化并打开 APK
        if (!mz_zip_reader_init_file(&zip, apk_path.c_str(), 0)) {
            // LOGI("Failed to open apk: %s", apk_path.c_str());
            return 0;
        }

        // 2. 定位目标文件
        int file_index = mz_zip_reader_locate_file(
            &zip,
            asset_internal_path.c_str(),
            nullptr,
            0
        );

        if (file_index < 0) {
            mz_zip_reader_end(&zip);
            return 0;
        }

        // 3. 准备 XXH3 64位状态机
        XXH3_state_t* state = XXH3_createState();
        if (!state) {
            mz_zip_reader_end(&zip);
            return 0;
        }
        // 重置状态机（XXH3 特有 API）
        XXH3_64bits_reset(state);

        // 4. 流式解压
        if (!mz_zip_reader_extract_to_callback(
            &zip,
            (mz_uint)file_index,
            hash_update_callback_64,
            state,
            0))
        {
            XXH3_freeState(state);
            mz_zip_reader_end(&zip);
            return 0;
        }

        // 5. 生成 64 位摘要
        uint64_t final_hash = XXH3_64bits_digest(state);

        // 6. 清理
        XXH3_freeState(state);
        mz_zip_reader_end(&zip);

        return final_hash;
    }

    //读取预存的哈希值32位
    static uint32_t read_hash_after_header_32(const char* path) {
        FILE* fp = fopen(path, "rb");
        if (!fp) return 0;

        uint32_t hash_val = 0;

        // 1. 跳过前 4 个字节的头部
        if (fseek(fp, 4, SEEK_SET) == 0) {
            // 2. 读取紧随其后的 4 字节哈希值
            if (fread(&hash_val, sizeof(uint32_t), 1, fp) != 1) {
                hash_val = 0; // 读取失败重置为 0
            }
        }

        fclose(fp);
        return hash_val;
    }
    //读取预存的哈希值64位
    static uint64_t read_hash_after_header_64(const char* path) {
        FILE* fp = fopen(path, "rb");
        if (!fp) return 0;

        uint64_t hash_val = 0;

        // 1. 直接跳到偏移量为 4 的位置
        if (fseek(fp, 4, SEEK_SET) == 0) {
            // 2. 读取 8 字节的 64 位哈希
            if (fread(&hash_val, sizeof(uint64_t), 1, fp) != 1) {
                hash_val = 0;
            }
        }

        fclose(fp);
        return hash_val;
    }

    /**
 * @brief 生成指纹文件
 * @param targetFilePath 要计算哈希的原始文件路径
 * @param outputHashPath 生成的指纹文件保存路径
 * @param header 4字节的头部字符串
 */
    //32位哈希值文件生成函数
    static bool generate_hash_file_with_header_32(const fs::path& targetFilePath,
        const fs::path& outputHashPath,
        const char* header)
    {
        // 1. 计算原始文件的哈希值
        uint32_t hashResult = compute_file_hash_32(targetFilePath);
        if (hashResult == 0) return false;

        // 2. 以二进制覆盖模式打开输出文件
        std::ofstream outFile(outputHashPath, std::ios::binary | std::ios::out | std::ios::trunc);
        if (!outFile) return false;

        // 3. 写入 4 字节头部
        // 注意：这里直接写入 header 指针指向的前 4 个字符
        outFile.write(header, 4);

        // 4. 写入 4 字节哈希值 (uint32_t)
        // 强制转换为 char* 以便按字节流写入内存中的 4 个字节
        outFile.write(reinterpret_cast<const char*>(&hashResult), sizeof(uint32_t));

        outFile.close();
        return true;
    }

    //64位版本
    static bool generate_hash_file_with_header_64(const fs::path& targetFilePath,
        const fs::path& outputHashPath,
        const char* header)
    {
        // 1. 计算 64 位哈希
        XXH64_hash_t hashResult = compute_file_hash(targetFilePath);
        if (hashResult == 0) return false;

        // 2. 二进制写入模式打开
        std::ofstream outFile(outputHashPath, std::ios::binary | std::ios::trunc);
        if (!outFile) return false;

        // 3. 写入 4 字节头部
        outFile.write(header, 4);

        // 4. 写入 8 字节哈希值 (uint64_t / XXH64_hash_t)
        // 在 64 位系统下，这能极大降低哈希碰撞的概率
        outFile.write(reinterpret_cast<const char*>(&hashResult), sizeof(XXH64_hash_t));

        outFile.close();
        return true;
    }
};