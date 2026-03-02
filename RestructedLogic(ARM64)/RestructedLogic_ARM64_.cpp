#include "RestructedLogic_ARM64_.h"
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

namespace MaxZoom {

// 设备分辨率
// int mOrigScreenWidth;
int mOrigScreenHeight;

// LawnAppScreenWidthHeight 的原函数会随版本变化。目前只知道 8.7.3 的写法。其他版本欢迎补充。
#if GAME_VERSION == 873

typedef int64_t (*LawnAppScreenWidthHeight)(int64_t a1, int a2);
LawnAppScreenWidthHeight oLawnAppScreenWidthHeight = nullptr;

int64_t hkLawnAppScreenWidthHeight(int64_t a1, int a2) {
  // 1. 先执行原函数，让内部逻辑完成内存写入
  int64_t result = oLawnAppScreenWidthHeight(a1, a2);

  if (a1 == NULL)
    return result;

  // 2. 根据偏移直接提取数据
  // 根据 sub_FFE7D0
  // mOrigScreenWidth = *(unsigned int *)(a1 + 1860);
  mOrigScreenHeight = *(unsigned int *)(a1 + 1864);

  // 3. 输出日志
  LOGI(R"(
--- LawnApp::SetWidthHeight Hook ---
mOrigHeight: %d, result: %lld)",
       mOrigScreenHeight, result);

  return result;
}

#endif

typedef int64_t (*OrigBoardZoom)(int64_t a1);
OrigBoardZoom oBoardZoom = nullptr;

int64_t hkBoardZoom(int64_t a1) {
  // 先跑原函数
  int64_t result = oBoardZoom(a1);
  // 改变选卡时向左滑动距离
  *(int32_t *)(a1 + 1140) = -(*(int32_t *)(a1 + 1088)) + 20;
  // 高度无法调整，只能靠缩放
  return result;
}

typedef void (*OrigBoardZoom2)(int64_t a1);
OrigBoardZoom2 oBoardZoom2 = nullptr;

void hkBoardZoom2(int64_t a1) {
  oBoardZoom2(a1);
  // 缩放系数
  *(float *)(a1 + 1120) = 1.0f;
  // 逻辑宽度 B
  int32_t logicalB = *(int32_t *)(a1 + 1096);
  // 改变左侧偏移(因为误差20像素，所以补上)
  *(int32_t *)(a1 + 1080) = (int32_t)logicalB - 20;
  // 顶部基准线
  *(int32_t *)(a1 + 1128) = (int32_t)mOrigScreenHeight;
  // 右边界屏幕坐标
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

__attribute__((constructor)) void libRestructedLogic_ARM64__main() {
  LOGI("Initializing %s", LIB_TAG);

  MaxZoom::process();  // 高视角

  LOGI("Finished initializing");
}
