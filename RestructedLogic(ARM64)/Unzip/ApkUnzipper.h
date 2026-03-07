#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

extern "C" {
#include "miniz.h"
}

class ApkUnzipper {
public:

    static bool extract_asset(const std::string& apk_path,
        const std::string& asset_internal_path,
        const std::string& out_path)
    {
        mz_zip_archive zip{};

        // 1. 打开APK(zip)
        if (!mz_zip_reader_init_file(&zip, apk_path.c_str(), 0)) {
            LOGI("Failed to open apk: %s",apk_path.c_str());
            return false;
        }

        //测试时用，看apk里面有什么文件
        /*mz_uint file_count = mz_zip_reader_get_num_files(&zip);

        LOGI("Zip file count: %d", file_count);

        for (mz_uint i = 0; i < file_count; i++) {
            mz_zip_archive_file_stat stat{};
            mz_zip_reader_file_stat(&zip, i, &stat);

            LOGI("file[%d] = %s", i, stat.m_filename);
        }*/

        // 2. 找到文件index
        int file_index = mz_zip_reader_locate_file(&zip,
            asset_internal_path.c_str(),
            nullptr,
            0);

        if (file_index < 0) {
            LOGI("File not found in apk: %s", asset_internal_path.c_str());

            mz_zip_reader_end(&zip);
            return false;
        }

        // 3. 解压到内存
        size_t file_size = 0;
        void* file_data = mz_zip_reader_extract_to_heap(
            &zip,
            file_index,
            &file_size,
            0
        );

        if (!file_data) {
            LOGI("Failed to extract file");
            mz_zip_reader_end(&zip);
            return false;
        }

        // 4. 写入磁盘
        std::ofstream out_file(out_path, std::ios::binary);
        if (!out_file.is_open()) {
            LOGI("Failed to open output file: %s", out_path.c_str());

            mz_free(file_data);
            mz_zip_reader_end(&zip);
            return false;
        }

        out_file.write(reinterpret_cast<char*>(file_data), file_size);
        out_file.close();

        // 5. 释放资源
        mz_free(file_data);
        mz_zip_reader_end(&zip);

        return true;
    }
    static bool extract_to_memory(
        const std::string& apk_path,
        const std::string& internal_path,
        std::vector<uint8_t>& out)
    {
        mz_zip_archive zip{};

        if (!mz_zip_reader_init_file(&zip, apk_path.c_str(), 0)) {
            LOGI("Failed to open apk.");
            return false;
        }

        int file_index = mz_zip_reader_locate_file(
            &zip,
            internal_path.c_str(),
            nullptr,
            0
        );

        if (file_index < 0) {
            LOGI("File not found: %s",internal_path.c_str());
            mz_zip_reader_end(&zip);
            return false;
        }

        size_t file_size = 0;

        void* data = mz_zip_reader_extract_to_heap(
            &zip,
            file_index,
            &file_size,
            0
        );

        if (!data) {
            std::cerr << "Extract failed\n";
            mz_zip_reader_end(&zip);
            return false;
        }

        out.resize(file_size);
        memcpy(out.data(), data, file_size);

        mz_free(data);
        mz_zip_reader_end(&zip);

        return true;
    }
};