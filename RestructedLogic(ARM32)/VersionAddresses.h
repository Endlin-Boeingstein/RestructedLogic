#include <map>
#include <string>

#define GAME_VERSION 1031
// 填入版本号，为去掉小数点的版本号
// NULL 表示暂未知偏移。

#if GAME_VERSION == 941

constexpr size_t PlantNameMapperAddr = 0xD994B8;
constexpr size_t PrimeGlyphCacheAddr = NULL;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 185;

#endif

#if GAME_VERSION == 961

constexpr size_t PlantNameMapperAddr = 0xDA5C58;
constexpr size_t PrimeGlyphCacheAddr = NULL;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 188;

#endif

#if GAME_VERSION == 981

constexpr size_t PlantNameMapperAddr = 0xDFC008;
constexpr size_t PrimeGlyphCacheAddr = 0x13FBA38;
constexpr size_t RSBPathRecorderAddr = NULL;
constexpr size_t ResourceManagerFuncAddr = NULL;
constexpr size_t CDNLoadAddr = NULL;
constexpr size_t LogOutputFuncAddr_Simple = NULL;
constexpr size_t LogOutputFuncAddr = NULL;
constexpr size_t LogOutputFuncAddr_Struct = NULL;
constexpr size_t LogOutputFuncAddr_v2 = NULL;
constexpr size_t LawnAppScreenWidthHeightAddr = NULL;
constexpr size_t BoardZoomAddr = NULL;
constexpr size_t BoardZoom2Addr = NULL;
constexpr int firstFreePlantID = 191;

#endif

#if GAME_VERSION == 1031

constexpr size_t PlantNameMapperAddr = NULL;
constexpr size_t PrimeGlyphCacheAddr = 0x177ECF4;
constexpr size_t RSBPathRecorderAddr = 0x16431A8;
constexpr size_t ResourceManagerFuncAddr = 0x6EE218;
constexpr size_t CDNLoadAddr = 0x876CB0;
constexpr size_t LogOutputFuncAddr_Simple = 0x146E160;
constexpr size_t LogOutputFuncAddr = 0x146DE24;
constexpr size_t LogOutputFuncAddr_Struct = 0x146DFE4;
constexpr size_t LogOutputFuncAddr_v2 = 0x146E028;
constexpr size_t LawnAppScreenWidthHeightAddr = 0x6E4030;
constexpr size_t BoardZoomAddr = 0x88D3EC;
constexpr size_t BoardZoom2Addr = 0x88D670;
constexpr int firstFreePlantID = 0;  // 10.3 不需要

#endif

// 在此仿照如上格式再续写所需版本号偏移分类
