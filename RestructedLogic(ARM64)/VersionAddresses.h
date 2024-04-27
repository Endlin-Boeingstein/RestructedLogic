/*
 *  @date   : 2024/04/20
 *  @author : Endlin Boeingstein
 */
#include <map>
#include <string>
#ifndef VERSIONADDRESSES_H
#define VERSIONADDRESSES_H

uint ZombieAlmanacAddr;
uint PlantNameMapperAddr;
uint CamelZombieAddr;
uint camelMinigameModuleFuncAddr;
uint WorldMapDoMovementAddr;
uint ZombiePianoAddr;
uint ZombiePianoListAddr;
uint ReinitForSurfaceChangedAddr;
uint BoardAddr;
uint ZombieCarnieMagician__IsImmuneToShrinkAddr;
uint ZombieRomanHealer__IsImmuneToShrinkAddr;
uint ZombieCarnieMagician__ConditionFuncAddr;
uint ZombieRomanHealer__ConditionFuncAddr;
uint ZombieRomanHealer__InitializeFamilyImmunitiesAddr;
uint zFamilyFuncAddr;

//第一个自定义的植物ID
uint firstFreePlantID;

enum VersionOfGame
{
    v9_4,
    v9_6,
    v9_8
    //仿照上面添加版本号
};

#pragma region Auto Select Addresses
void AddressesChangedByVersion() {
    switch (v9_4)//在此处修改版本号
    {
    case v9_4:
    {
        //部分偏移由某神秘大佬查找得来，但是由于v7a和v8a函数结构不同，还有新的库的未知什么导致的闪退问题，故v8a方案已废弃
        ZombieAlmanacAddr = 0x00;
        PlantNameMapperAddr = 0x1157778;//
        CamelZombieAddr = 0x00;
        camelMinigameModuleFuncAddr = 0x00;
        WorldMapDoMovementAddr = 0x00;
        ZombiePianoAddr = 0x00;
        ZombiePianoListAddr = 0x00;
        ReinitForSurfaceChangedAddr = 0x164C580;
        BoardAddr = 0xA94604;//
        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
        zFamilyFuncAddr = 0x00;

        firstFreePlantID = 185;
        break;
    }
    case v9_6:
    {
        ZombieAlmanacAddr = 0x00;
        PlantNameMapperAddr = 0x00;//
        CamelZombieAddr = 0x00;
        camelMinigameModuleFuncAddr = 0x00;
        WorldMapDoMovementAddr = 0x00;
        ZombiePianoAddr = 0x00;
        ZombiePianoListAddr = 0x00;
        ReinitForSurfaceChangedAddr = 0x00;
        BoardAddr = 0x00;//
        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
        zFamilyFuncAddr = 0x00;

        firstFreePlantID = 188;
        break;
    }
    case v9_8:
    {
        ZombieAlmanacAddr = 0x00;
        PlantNameMapperAddr = 0x00;//
        CamelZombieAddr = 0x00;
        camelMinigameModuleFuncAddr = 0x00;
        WorldMapDoMovementAddr = 0x00;
        ZombiePianoAddr = 0x00;
        ZombiePianoListAddr = 0x00;
        ReinitForSurfaceChangedAddr = 0x00;
        BoardAddr = 0x00;//
        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__ConditionFuncAddr = 0x00;
        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
        zFamilyFuncAddr = 0x00;

        firstFreePlantID = 191;
        break;
    }
    //仿照上述case添加版本偏移
    default:
    {
        break;
    }
    }
}
#pragma endregion

#pragma region DeleteRegion
//std::map<std::string, uint> getFuncAddress(double ver)
//{
//    uint ZombieAlmanac;
//    uint PlantNameMapper;
//    uint CamelZombie;
//    uint camelMinigameModuleFunc;
//    uint WorldMapDoMovement;
//    uint ZombiePiano;
//    uint ZombiePianoList;
//    uint ReinitForSurfaceChanged;
//    uint Board;
//    uint ZombieCarnieMagician__IsImmuneToShrink;
//    uint ZombieRomanHealer__IsImmuneToShrink;
//    uint ZombieCarnieMagician__ConditionFunc;
//    uint ZombieRomanHealer__ConditionFunc;
//    uint ZombieRomanHealer__InitializeFamilyImmunities;
//    uint zFamilyFunc;
//
//    std::map<std::string, uint> funcaddress;
//    {
//        /*
//        std::pair<std::string,uint>("ZombieAlmanac",0),
//        std::pair<std::string,uint>("PlantNameMapper",0),
//        std::pair<std::string,uint>("CamelZombie",0),
//        std::pair<std::string,uint>("camelMinigameModuleFunc",0),
//        std::pair<std::string,uint>("WorldMapDoMovement",0),
//        std::pair<std::string,uint>("ZombiePiano",0),
//        std::pair<std::string,uint>("ZombiePianoList",0),
//        std::pair<std::string,uint>("ReinitForSurfaceChanged",0),
//        std::pair<std::string,uint>("Board",0),
//        std::pair<std::string,uint>("ZombieCarnieMagician__IsImmuneToShrink",0),
//        std::pair<std::string,uint>("ZombieRomanHealer__IsImmuneToShrink",0),
//        std::pair<std::string,uint>("ZombieCarnieMagician__ConditionFunc",0),
//        std::pair<std::string,uint>("ZombieRomanHealer__ConditionFunc",0),
//        std::pair<std::string,uint>("ZombieRomanHealer__InitializeFamilyImmunities",0),
//        std::pair<std::string,uint>("zFamilyFunc",0)
//        */
//    };
//
//    if (ver == 9.4)
//    {
//        ZombieAlmanac = 0x105123C;
//        PlantNameMapper = 0xD994B8;
//        CamelZombie = 0x7942BC;
//        camelMinigameModuleFunc = 0x797494;
//        WorldMapDoMovement = 0x44E604;
//        ZombiePiano = 0x890108;
//        ZombiePianoList = 0x1CE922C;
//        ReinitForSurfaceChanged = 0x127415C;
//        Board = 0x71A004;
//        ZombieCarnieMagician__IsImmuneToShrink = 0x884B6C;
//        ZombieRomanHealer__IsImmuneToShrink = 0x881C4C;
//        ZombieCarnieMagician__ConditionFunc = 0x86CCAC;
//        ZombieRomanHealer__ConditionFunc = 0x84EAA0;
//        ZombieRomanHealer__InitializeFamilyImmunities = 0x86CCC0;
//        zFamilyFunc = 0x8C70A0;
//    }
//    else if (ver == 9.6)
//    {
//        ZombieAlmanac = 0x10643E0;
//        PlantNameMapper = 0xDA5C58;
//        CamelZombie = 0x789DC8;
//        camelMinigameModuleFunc = 0x78CFA0;
//        WorldMapDoMovement = 0x441068;
//        ZombiePiano = 0x885F80;
//        ZombiePianoList = 0x1D890F4;
//        ReinitForSurfaceChanged = 0x1287430;
//        Board = 0x70F63C;
//        ZombieCarnieMagician__IsImmuneToShrink = 0x87A9E4;
//        ZombieRomanHealer__IsImmuneToShrink = 0x877AC4;
//        ZombieCarnieMagician__ConditionFunc = 0x8628B0;
//        ZombieRomanHealer__ConditionFunc = 0x8446A8;
//        ZombieRomanHealer__InitializeFamilyImmunities = 0x8628C4;
//        zFamilyFunc = 0x8BD2C0;
//    }
//    else if (ver == 9.8)
//    {
//        ZombieAlmanac = 0x10C0800;
//        PlantNameMapper = 0xDFC008;
//        CamelZombie = 0x7D1BD0;
//        camelMinigameModuleFunc = 0x7D4DA8;
//        WorldMapDoMovement = 0x483504;
//        ZombiePiano = 0x8CDC60;
//        ZombiePianoList = 0x1E5429C;
//        ReinitForSurfaceChanged = 0x12EE3AC;
//        Board = 0x75743C;
//        ZombieCarnieMagician__IsImmuneToShrink = 0x8C26C4;
//        ZombieRomanHealer__IsImmuneToShrink = 0x8BF7A4;
//        ZombieCarnieMagician__ConditionFunc = 0x8AA588;
//        ZombieRomanHealer__ConditionFunc = 0x88C290;
//        ZombieRomanHealer__InitializeFamilyImmunities = 0x8AA59C;
//        zFamilyFunc = 0x905110;
//    }
//    //在此处添加新的版本偏移
//    else {}
//    //加入map以供调用
//    funcaddress.insert(std::pair<std::string, uint>("ZombieAlmanac", ZombieAlmanac));
//    funcaddress.insert(std::pair<std::string, uint>("PlantNameMapper", PlantNameMapper));
//    funcaddress.insert(std::pair<std::string, uint>("CamelZombie", CamelZombie));
//    funcaddress.insert(std::pair<std::string, uint>("camelMinigameModuleFunc", camelMinigameModuleFunc));
//    funcaddress.insert(std::pair<std::string, uint>("WorldMapDoMovement", WorldMapDoMovement));
//    funcaddress.insert(std::pair<std::string, uint>("ZombiePiano", ZombiePiano));
//    funcaddress.insert(std::pair<std::string, uint>("ZombiePianoList", ZombiePianoList));
//    funcaddress.insert(std::pair<std::string, uint>("ReinitForSurfaceChanged", ReinitForSurfaceChanged));
//    funcaddress.insert(std::pair<std::string, uint>("Board", Board));
//    funcaddress.insert(std::pair<std::string, uint>("ZombieCarnieMagician__IsImmuneToShrink", ZombieCarnieMagician__IsImmuneToShrink));
//    funcaddress.insert(std::pair<std::string, uint>("ZombieRomanHealer__IsImmuneToShrink", ZombieRomanHealer__IsImmuneToShrink));
//    funcaddress.insert(std::pair<std::string, uint>("ZombieCarnieMagician__ConditionFunc", ZombieCarnieMagician__ConditionFunc));
//    funcaddress.insert(std::pair<std::string, uint>("ZombieRomanHealer__ConditionFunc", ZombieRomanHealer__ConditionFunc));
//    funcaddress.insert(std::pair<std::string, uint>("ZombieRomanHealer__InitializeFamilyImmunities", ZombieRomanHealer__InitializeFamilyImmunities));
//    funcaddress.insert(std::pair<std::string, uint>("zFamilyFunc", zFamilyFunc));
//    return funcaddress;
//}
#pragma endregion


#endif