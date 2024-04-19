#pragma once

// Useful for filtering logcat
#define LIB_TAG "RestructedLogic_ARM64_"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LIB_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LIB_TAG, __VA_ARGS__))
