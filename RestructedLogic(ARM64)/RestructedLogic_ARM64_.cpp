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
#ifdef _DEBUG
  mOrigScreenWidth = *(unsigned int *)(a1 + 1860);
#endif
  mOrigScreenHeight = *(unsigned int *)(a1 + 1864);

  mWidth = *(unsigned int *)(a1 + 244);
#ifdef _DEBUG
  mHeight = *(unsigned int *)(a1 + 248);
#endif

  // 3. 输出日志
  LOGI(R"(
--- LawnApp::SetWidthHeight Hook ---
mOrigWidth: %d, mOrigHeight: %d
mWidth: %d, mHeight: %d
result: %lld)",
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

#endif

typedef int64_t (*OrigBoardZoom)(int64_t a1);
OrigBoardZoom oBoardZoom = nullptr;

int64_t hkBoardZoom(int64_t a1) {
  // 先跑原函数
  int64_t result = oBoardZoom(a1);
  // 改变选卡时视野左边缘与棋盘左边缘的距离
  *(int32_t *)(a1 + 1140) = preGameRightLine - mWidth;
  // 高度无法调整，只能靠缩放
  return result;
}

typedef void (*OrigBoardZoom2)(int64_t a1);
OrigBoardZoom2 oBoardZoom2 = nullptr;

void hkBoardZoom2(int64_t a1) {
  oBoardZoom2(a1);
  // 缩放系数
  *(float *)(a1 + 1120) = 1.0f;
  // 改变视野左边缘与棋盘左边缘的距离
  *(int32_t *)(a1 + 1080) = -(gameStartRightLine - mWidth);
  // 顶部基准线
  *(int32_t *)(a1 + 1128) = (int32_t)mOrigScreenHeight;
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
