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

#pragma region Alias to ID

class ZombieAlmanac
{
public:
    void* vftable;
    std::map<SexyString, uint> m_aliasToId;
};

class PlantNameMapper
{
public:
    void* vftable;
    std::map<SexyString, uint> m_aliasToId;
};

#define FIRST_FREE_ZOMBIE_ID 441
#define FIRST_FREE_PLANT_ID 185

std::vector<SexyString> g_modPlantTypenames;
std::vector<SexyString> g_modZombieTypenames;

#define REGISTER_PLANT_TYPENAME(typename) \
    g_modPlantTypenames.push_back(typename); \

#define REGISTER_ZOMBIE_TYPENAME(typename) \
    g_modZombieTypenames.push_back(typename); \

typedef ZombieAlmanac* (*ZombieAlmanacCtor)(ZombieAlmanac*);
ZombieAlmanacCtor oZombieAlmanacCtor = NULL;

void* hkCreateZombieTypenameMap(ZombieAlmanac* a1)
{
    // Let the game create the original alias->id map
    ZombieAlmanac* obj = oZombieAlmanacCtor(a1);
    // Now add our own zombie aliases to it 
    // (mod aliases can be registered with the REGISTER_ZOMBIE_TYPENAME macro)
    for (int iter = 0; iter < g_modZombieTypenames.size(); iter++)
    {
        obj->m_aliasToId[g_modZombieTypenames[iter]] = FIRST_FREE_ZOMBIE_ID + iter;
    }

    return obj;
}

typedef PlantNameMapper* (*PlantNameMapperCtor)(PlantNameMapper*);
PlantNameMapperCtor oPlantNameMapperCtor = NULL;

void* hkCreatePlantNameMapper(PlantNameMapper* self)
{
    // Same deal with the ZombieAlamanc::ctor hook
    PlantNameMapper* obj = oPlantNameMapperCtor(self);
    for (int iter = 0; iter < g_modPlantTypenames.size(); iter++)
    {
        obj->m_aliasToId[g_modPlantTypenames[iter]] = FIRST_FREE_PLANT_ID + iter;
    }

    return obj;
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

std::vector<SexyString>* g_pianoList = NULL;
bool g_pianoListInitialized = false;

bool hkInitZombiePianoList(int a1, int a2)
{
    // This function is called every frame when a piano zombie is on screen
    // So this global bool is needed to prevent wasting a massive amount of cpu time
    if (!g_pianoListInitialized)
    {
        bool orig = oInitZombiePianoList(a1, a2);

        uint ptrAddr = getActualOffset(ZombiePianoListAddr); // address of piano zombie's list in memory
        g_pianoList = reinterpret_cast<std::vector<SexyString>*>(ptrAddr);

        // @todo: add this to piano zombie's props instead?
        g_pianoList->clear();
        g_pianoList->push_back("cowboy");
        g_pianoList->push_back("cowboy_armor1");
        g_pianoList->push_back("cowboy_armor2");
        g_pianoList->push_back("cowboy_armor4");
        g_pianoList->push_back("pirate_gargantuar");

        g_pianoListInitialized = true;
    }
    return oInitZombiePianoList(a1, a2);
}

#pragma endregion

#pragma region Board Zoom

int gWidth = 0;
int gHeight = 0;

enum AspectRatio
{
    Letterbox,
    Widescreen,
    Ultrawide,
};

typedef int(*worldMapDoMovement)(void*, float, float, bool);
worldMapDoMovement oWorldMapDoMovement = NULL;

int hkWorldMapDoMovement(void* self, float fX, float fY, bool allowVerticalMovement)
{
    return oWorldMapDoMovement(self, fX, fY, true);
}

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
    gWidth = width;
    gHeight = height;
    return oRFSC(thisptr, a2, width, height, a5);
}

typedef void* (*boardCtor)(void*);
boardCtor oBoardCtor = NULL;

void* hkBoardCtor(Board* board)
{
    oBoardCtor(board);

    board->m_lawnRect.mX = 200; //200
    board->m_lawnRect.mY = 160; //160

    switch (GetAspectRatio())
    {
    case Letterbox:
    {
        board->m_lawnRect.mWidth = 576; //576//
        board->m_lawnRect.mHeight = 500; //380//
        break;
    }
    case Widescreen:
    {
        board->m_lawnRect.mWidth = 576; //576//
        board->m_lawnRect.mHeight = 450; //380//
        break;
    }
    case Ultrawide:
    {
        board->m_lawnRect.mX = 200;//450
        board->m_lawnRect.mY = 160;//160
        board->m_lawnRect.mWidth = 776; //576//
        board->m_lawnRect.mHeight = 380; //380//525
        break;
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
    REGISTER_PLANT_TYPENAME("newadd_0");
    REGISTER_PLANT_TYPENAME("newadd_1");
    REGISTER_PLANT_TYPENAME("newadd_2");
    REGISTER_PLANT_TYPENAME("newadd_3");
    REGISTER_PLANT_TYPENAME("newadd_4");
    REGISTER_PLANT_TYPENAME("newadd_5");
    REGISTER_PLANT_TYPENAME("newadd_6");
    REGISTER_PLANT_TYPENAME("newadd_7");
    REGISTER_PLANT_TYPENAME("newadd_8");
    REGISTER_PLANT_TYPENAME("newadd_9");
    REGISTER_PLANT_TYPENAME("newadd_10");
    REGISTER_PLANT_TYPENAME("newadd_11");
    REGISTER_PLANT_TYPENAME("newadd_12");
    REGISTER_PLANT_TYPENAME("newadd_13");
    REGISTER_PLANT_TYPENAME("newadd_14");
    REGISTER_PLANT_TYPENAME("newadd_15");
    REGISTER_PLANT_TYPENAME("newadd_16");
    REGISTER_PLANT_TYPENAME("newadd_17");
    REGISTER_PLANT_TYPENAME("newadd_18");
    REGISTER_PLANT_TYPENAME("newadd_19");
    REGISTER_PLANT_TYPENAME("newadd_20");
    REGISTER_PLANT_TYPENAME("newadd_21");
    REGISTER_PLANT_TYPENAME("newadd_22");
    REGISTER_PLANT_TYPENAME("newadd_23");
    REGISTER_PLANT_TYPENAME("newadd_24");
    REGISTER_PLANT_TYPENAME("newadd_25");
    REGISTER_PLANT_TYPENAME("newadd_26");
    REGISTER_PLANT_TYPENAME("newadd_27");
    REGISTER_PLANT_TYPENAME("newadd_28");
    REGISTER_PLANT_TYPENAME("newadd_29");
    REGISTER_PLANT_TYPENAME("newadd_30");
    REGISTER_PLANT_TYPENAME("newadd_31");
    REGISTER_PLANT_TYPENAME("newadd_32");
    REGISTER_PLANT_TYPENAME("newadd_33");
    REGISTER_PLANT_TYPENAME("newadd_34");
    REGISTER_PLANT_TYPENAME("newadd_35");
    REGISTER_PLANT_TYPENAME("newadd_36");
    REGISTER_PLANT_TYPENAME("newadd_37");
    REGISTER_PLANT_TYPENAME("newadd_38");
    REGISTER_PLANT_TYPENAME("newadd_39");
    REGISTER_PLANT_TYPENAME("newadd_40");
    REGISTER_PLANT_TYPENAME("newadd_41");
    REGISTER_PLANT_TYPENAME("newadd_42");
    REGISTER_PLANT_TYPENAME("newadd_43");
    REGISTER_PLANT_TYPENAME("newadd_44");
    REGISTER_PLANT_TYPENAME("newadd_45");
    REGISTER_PLANT_TYPENAME("newadd_46");
    REGISTER_PLANT_TYPENAME("newadd_47");
    REGISTER_PLANT_TYPENAME("newadd_48");
    REGISTER_PLANT_TYPENAME("newadd_49");
    REGISTER_PLANT_TYPENAME("newadd_50");
    REGISTER_PLANT_TYPENAME("newadd_51");
    REGISTER_PLANT_TYPENAME("newadd_52");
    REGISTER_PLANT_TYPENAME("newadd_53");
    REGISTER_PLANT_TYPENAME("newadd_54");
    REGISTER_PLANT_TYPENAME("newadd_55");
    REGISTER_PLANT_TYPENAME("newadd_56");
    REGISTER_PLANT_TYPENAME("newadd_57");
    REGISTER_PLANT_TYPENAME("newadd_58");
    REGISTER_PLANT_TYPENAME("newadd_59");
    REGISTER_PLANT_TYPENAME("newadd_60");
    REGISTER_PLANT_TYPENAME("newadd_61");
    REGISTER_PLANT_TYPENAME("newadd_62");
    REGISTER_PLANT_TYPENAME("newadd_63");
    REGISTER_PLANT_TYPENAME("newadd_64");
    REGISTER_PLANT_TYPENAME("newadd_65");
    REGISTER_PLANT_TYPENAME("newadd_66");
    REGISTER_PLANT_TYPENAME("newadd_67");
    REGISTER_PLANT_TYPENAME("newadd_68");
    REGISTER_PLANT_TYPENAME("newadd_69");
    REGISTER_PLANT_TYPENAME("newadd_70");
    REGISTER_PLANT_TYPENAME("newadd_71");
    REGISTER_PLANT_TYPENAME("newadd_72");
    REGISTER_PLANT_TYPENAME("newadd_73");
    REGISTER_PLANT_TYPENAME("newadd_74");
    REGISTER_PLANT_TYPENAME("newadd_75");
    REGISTER_PLANT_TYPENAME("newadd_76");
    REGISTER_PLANT_TYPENAME("newadd_77");
    REGISTER_PLANT_TYPENAME("newadd_78");
    REGISTER_PLANT_TYPENAME("newadd_79");
    REGISTER_PLANT_TYPENAME("newadd_80");
    REGISTER_PLANT_TYPENAME("newadd_81");
    REGISTER_PLANT_TYPENAME("newadd_82");
    REGISTER_PLANT_TYPENAME("newadd_83");
    REGISTER_PLANT_TYPENAME("newadd_84");
    REGISTER_PLANT_TYPENAME("newadd_85");
    REGISTER_PLANT_TYPENAME("newadd_86");
    REGISTER_PLANT_TYPENAME("newadd_87");
    REGISTER_PLANT_TYPENAME("newadd_88");
    REGISTER_PLANT_TYPENAME("newadd_89");
    REGISTER_PLANT_TYPENAME("newadd_90");
    REGISTER_PLANT_TYPENAME("newadd_91");
    REGISTER_PLANT_TYPENAME("newadd_92");
    REGISTER_PLANT_TYPENAME("newadd_93");
    REGISTER_PLANT_TYPENAME("newadd_94");
    REGISTER_PLANT_TYPENAME("newadd_95");
    REGISTER_PLANT_TYPENAME("newadd_96");
    REGISTER_PLANT_TYPENAME("newadd_97");
    REGISTER_PLANT_TYPENAME("newadd_98");
    REGISTER_PLANT_TYPENAME("newadd_99");
    REGISTER_PLANT_TYPENAME("newadd_100");
    REGISTER_PLANT_TYPENAME("newadd_101");
    REGISTER_PLANT_TYPENAME("newadd_102");
    REGISTER_PLANT_TYPENAME("newadd_103");
    REGISTER_PLANT_TYPENAME("newadd_104");
    REGISTER_PLANT_TYPENAME("newadd_105");
    REGISTER_PLANT_TYPENAME("newadd_106");
    REGISTER_PLANT_TYPENAME("newadd_107");
    REGISTER_PLANT_TYPENAME("newadd_108");
    REGISTER_PLANT_TYPENAME("newadd_109");

    //No need to use///REGISTER_ZOMBIE_TYPENAME("steam");

    // Function hooks
    PVZ2HookFunction(ZombieAlmanacAddr, (void*)hkCreateZombieTypenameMap, (void**)&oZombieAlmanacCtor, "ZombieAlmanac::ZombieAlamanc");
    PVZ2HookFunction(PlantNameMapperAddr, (void*)hkCreatePlantNameMapper, (void**)&oPlantNameMapperCtor, "PlantNameMapper::PlantNameMapper");
    PVZ2HookFunction(CamelZombieAddr, (void*)hkCamelZombieFunc, (void**)&oCamelZombieFunc, "CamelZombie::vftable_func_0xEC");
    PVZ2HookFunction(ZombiePianoAddr, (void*)hkInitZombiePianoList, (void**)&oInitZombiePianoList, "ZombiePiano::getTypenameList");
    PVZ2HookFunction(ReinitForSurfaceChangedAddr, (void*)HkReinitForSurfaceChange, (void**)&oRFSC, "ReinitForSurfaceChanged");
    PVZ2HookFunction(BoardAddr, (void*)hkBoardCtor, (void**)&oBoardCtor, "Board::Board");
    PVZ2HookFunction(ZombieCarnieMagician__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieCarnieMagician::IsImmuneToShrink");
    PVZ2HookFunction(ZombieRomanHealer__IsImmuneToShrinkAddr, (void*)hkMagicianHealerImmuneToShrink, (void**)&dispose, "ZombieRomanHealer::IsImmuneToShrink");
    PVZ2HookFunction(ZombieCarnieMagician__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieCarnieMagician::ConditionFunc");
    PVZ2HookFunction(ZombieRomanHealer__ConditionFuncAddr, (void*)hkMagicianHealerConditionFunc, (void**)&dispose, "ZombieRomanHealer::ConditionFunc");
    PVZ2HookFunction(ZombieRomanHealer__InitializeFamilyImmunitiesAddr, (void*)hkMagicianInitializeFamilyImmunities, (void**)&dispose, "ZombieRomanHealer::InitializeFamilyImmunities");
    PVZ2HookFunction(WorldMapDoMovementAddr, (void*)hkWorldMapDoMovement, (void**)&oWorldMapDoMovement, "WorldMap::doMovement");

    LOGI("Finished initializing");
}
