/*
 *  @date   : 2024/04/20
 *  @author : Endlin Boeingstein
 */
#include <map>
#include <string>
#ifndef VERSIONADDRESSES_H
#define VERSIONADDRESSES_H

#define GAME_VERSION 1030//填入版本号，为去掉小数点的版本号

#if GAME_VERSION==940
#define ZombieAlmanacAddr  0x105123C
#define PlantNameMapperAddr  0xD994B8
#define CamelZombieAddr  0x7942BC
#define camelMinigameModuleFuncAddr  0x797494
#define WorldMapDoMovementAddr  0x44E604
#define ZombiePianoAddr  0x890108
#define ZombiePianoListAddr  0x1CE922C
#define ReinitForSurfaceChangedAddr  0x127415C
#define BoardAddr  0x71A004
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x884B6C
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x881C4C
#define ZombieCarnieMagician__ConditionFuncAddr  0x86CCAC
#define ZombieRomanHealer__ConditionFuncAddr  0x84EAA0
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x86CCC0
#define zFamilyFuncAddr  0x8C70A0
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
 /*#define RSBReadAddr NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define ProjectileSpawnZombieAddr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
#define BoardInitAddr  NULL
#define CDNLoadAddr NULL


#define DelegateBase_SEXYDELEGATE_VTBLAddr  NULL
#define Graphics_UNK_GRAPHICSFUNC2Addr  NULL
#define Graphics_UNK_GRAPHICSFUNCAddr  NULL
#define RtClass_rtClassCtorFuncAddr  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_MOVE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR  NULL


#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1Addr NULL
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2Addr NULL
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3Addr NULL
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAMEAddr NULL
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAMEAddr NULL
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC1Addr NULL
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC2Addr NULL
#define ReflectionBuilder_rtClassGetClassFuncAddr NULL



#define BoardEntity_OFFSET_BOARDENTITY_DIEAddr NULL
#define GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr NULL
#define GameObject_GAMEOBJECT_GETTYPE_OFFSETAddr NULL
#define GameObject_GAMEOBJECT_FUNCTION_DIE_OFFSETAddr GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr
#define GridItem_SpawnGridItemAtAddr NULL
#define LevelModule_LEVELMODULE_DTOR_ADDRAddr NULL
#define LevelModule_LEVELMODULE_CTOR_ADDRAddr NULL
#define LevelModule_LEVELMODULE_GETCLASS_ADDRAddr NULL
#define LevelModule_LEVELMODULE_VTBLAddr NULL
#define LevelModuleManager_getModuleAddr NULL
#define LevelModuleManager_AddDelegateAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_CTOR_ADDRAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_DTOR_ADDRAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_VTBLAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_GETCLASS_ADDRAddr NULL
#define PlantFramework_PLANTFRAMEWORK_CTORAddr NULL
#define PlantFramework_PLANTFRAMEWORK_VFTABLEAddr NULL
#define PlantFramework_PLANTFRAMEWORK_GETTYPEAddr NULL
#define PlantPropertySheet_PLANTPROPS_CTORAddr NULL
#define PlantPropertySheet_PLANTPROPS_VFTABLEAddr NULL
#define PlantPropertySheet_PLANTPROPS_GETTYPEAddr NULL
#define Projectile_OFFSET_PROJECTILE_PLAY_IMPACTAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_CTORAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_VFTABLEAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_GETTYPEAddr NULL
#define PropertySheetBase_PROPSHEETBASE_CTORAddr NULL
#define PropertySheetBase_PROPSHEETBASE_DTORAddr PropertySheetBase_PROPSHEETBASE_CTORAddr
#define PropertySheetBase_PROPSHEETBASE_DestructorAddr NULL
#define PropertySheetBase_PROPSHEETBASE_VFTABLEAddr NULL
#define PropertySheetBase_PROPSHEETBASE_GETTYPEAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_CONSTRUCT_ADDRAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_VTBLAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_GETCLASS_ADDRAddr NULL
#define Zombie_ZOMBIE_CTOR_ADDRAddr NULL
#define Zombie_ZOMBIE_DTOR_ADDRAddr NULL
#define Zombie_ZOMBIE_VFTABLE_ADDRAddr NULL
#define Zombie_OFFSET_ZOMBIE_GETTYPEAddr NULL
#define Zombie_ZOMBIE_GET_RTCLASSAddr Zombie_OFFSET_ZOMBIE_GETTYPEAddr
#define Zombie_ZOMBIE_ISDEADORDYING_ADDRAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_CTORAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_VFTABLEAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_GETTYPEAddr NULL
#define ZombieType_ZOMBIETYPEDIRECTORY_GETAddr NULL
#define ZombieType_ZOMBIETYPEDIRECTORY_GETTYPEAddr NULL





#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_ProjectileVFTableAddr NULL



#define firstFreePlantID  185

#endif

#if GAME_VERSION==960
#define ZombieAlmanacAddr  0x10643E0
#define PlantNameMapperAddr  0xDA5C58
#define CamelZombieAddr  0x789DC8
#define camelMinigameModuleFuncAddr  0x78CFA0
#define WorldMapDoMovementAddr  0x441068
#define ZombiePianoAddr  0x885F80
#define ZombiePianoListAddr  0x1D890F4
#define ReinitForSurfaceChangedAddr  0x1287430
#define BoardAddr  0x70F63C
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x87A9E4
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x877AC4
#define ZombieCarnieMagician__ConditionFuncAddr  0x8628B0
#define ZombieRomanHealer__ConditionFuncAddr  0x8446A8
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x8628C4
#define zFamilyFuncAddr  0x8BD2C0
#define LawnAppAddr  0x1D92A94
#define SexyAppAddr  0x1D9CA24
 /*#define RSBReadAddr NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define ProjectileSpawnZombieAddr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
#define BoardInitAddr  NULL
#define CDNLoadAddr NULL

#define DelegateBase_SEXYDELEGATE_VTBLAddr  0x1C5C758
#define Graphics_UNK_GRAPHICSFUNC2Addr  0x1124784
#define Graphics_UNK_GRAPHICSFUNCAddr  0x1124614
#define RtClass_rtClassCtorFuncAddr  0x1250518
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY  0x10D99A4
#define RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR  0x10DFA5C
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE  0x10DF644
#define RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS  0x24D110
#define RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR  0x279198
#define RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE  0x10DB9C0
#define RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER  0x10C8BF8
#define RtWeakPtr_OFFSET_RTWEAKPTR_MOVE  0x10C8BB0
#define RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR  0x10C88C8



#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1Addr 0x254210
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2Addr 0x254104
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3Addr 0x10E5340
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAMEAddr 0x1232B84
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAMEAddr 0x1232D0C
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC1Addr 0x123B308
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC2Addr 0x123B35C
#define ReflectionBuilder_rtClassGetClassFuncAddr 0x12501AC


#define BoardEntity_OFFSET_BOARDENTITY_DIEAddr 0x53F498
#define GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr 0x53EF3C
#define GameObject_GAMEOBJECT_GETTYPE_OFFSETAddr 0x53EA0C
#define GameObject_GAMEOBJECT_FUNCTION_DIE_OFFSETAddr GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr
#define GridItem_SpawnGridItemAtAddr 0x716690
#define LevelModule_LEVELMODULE_DTOR_ADDRAddr 0x2DF3B8
#define LevelModule_LEVELMODULE_CTOR_ADDRAddr 0x28E534
#define LevelModule_LEVELMODULE_GETCLASS_ADDRAddr 0xCF3960
#define LevelModule_LEVELMODULE_VTBLAddr 0x1CE7414
#define LevelModuleManager_getModuleAddr 0x6FBB94
#define LevelModuleManager_AddDelegateAddr 0x295854
#define LevelModuleProperties_LEVELMODULEPROPS_CTOR_ADDRAddr 0x28DAF0
#define LevelModuleProperties_LEVELMODULEPROPS_DTOR_ADDRAddr 0x294E7C
#define LevelModuleProperties_LEVELMODULEPROPS_VTBLAddr 0x1CF0770
#define LevelModuleProperties_LEVELMODULEPROPS_GETCLASS_ADDRAddr 0xDF1860
#define PlantFramework_PLANTFRAMEWORK_CTORAddr 0x45BBB8
#define PlantFramework_PLANTFRAMEWORK_VFTABLEAddr 0x1C6E4A0
#define PlantFramework_PLANTFRAMEWORK_GETTYPEAddr 0x45BB40
#define PlantPropertySheet_PLANTPROPS_CTORAddr 0x2B17D4
#define PlantPropertySheet_PLANTPROPS_VFTABLEAddr 0x1C5F700
#define PlantPropertySheet_PLANTPROPS_GETTYPEAddr 0x2AFF48
#define Projectile_OFFSET_PROJECTILE_PLAY_IMPACTAddr 0x907988
#define ProjectilePropertySheet_PROJECTILEPROPS_CTORAddr 0x29DC10
#define ProjectilePropertySheet_PROJECTILEPROPS_VFTABLEAddr 0x1C62EB0
#define ProjectilePropertySheet_PROJECTILEPROPS_GETTYPEAddr 0x317058
#define PropertySheetBase_PROPSHEETBASE_CTORAddr 0x253C50
#define PropertySheetBase_PROPSHEETBASE_DTORAddr PropertySheetBase_PROPSHEETBASE_CTORAddr
#define PropertySheetBase_PROPSHEETBASE_DestructorAddr 0x253CE8
#define PropertySheetBase_PROPSHEETBASE_VFTABLEAddr 0x1CB3AA8
#define PropertySheetBase_PROPSHEETBASE_GETTYPEAddr 0x980F74
#define StageModuleProperties_STAGEMODULEPROPS_CONSTRUCT_ADDRAddr 0x31DCB8
#define StageModuleProperties_STAGEMODULEPROPS_VTBLAddr 0x1C71840
#define StageModuleProperties_STAGEMODULEPROPS_GETCLASS_ADDRAddr 0x4AF920
#define Zombie_ZOMBIE_CTOR_ADDRAddr 0x8A2834
#define Zombie_ZOMBIE_DTOR_ADDRAddr 0x8A2D98
#define Zombie_ZOMBIE_VFTABLE_ADDRAddr 0x1CAE3B8
#define Zombie_OFFSET_ZOMBIE_GETTYPEAddr 0x89E20C
#define Zombie_ZOMBIE_GET_RTCLASSAddr Zombie_OFFSET_ZOMBIE_GETTYPEAddr
#define Zombie_ZOMBIE_ISDEADORDYING_ADDRAddr 0x0
#define ZombiePropertySheet_ZOMBIEPROPS_CTORAddr 0x87AEF8
#define ZombiePropertySheet_ZOMBIEPROPS_VFTABLEAddr 0x1CB89D0
#define ZombiePropertySheet_ZOMBIEPROPS_GETTYPEAddr 0xA01550
#define ZombieType_ZOMBIETYPEDIRECTORY_GETAddr 0x281008
#define ZombieType_ZOMBIETYPEDIRECTORY_GETTYPEAddr 0x28107C




#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr 0x907508
#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr 0x9059B0
#define Customize_Projectile_GridItemRaiserProjectileProps_GetBoardAddr 0x949EFC
#define Customize_Projectile_GridItemRaiserProjectileProps_SpawnGridItemOnBoardAddr 0x716FA4
#define Customize_Projectile_GridItemRaiserProjectileProps_SetTeamFlagAddr 0xCEB640
#define Customize_Projectile_GridItemRaiserProjectileProps_ProjectileVFTableAddr 0x1CB00D8


#define firstFreePlantID  188

#endif

#if GAME_VERSION==980
#define ZombieAlmanacAddr  0x10C0800
#define PlantNameMapperAddr  0xDFC008
#define CamelZombieAddr  0x7D1BD0
#define camelMinigameModuleFuncAddr  0x7D4DA8
#define WorldMapDoMovementAddr  0x483504
#define ZombiePianoAddr  0x8CDC60
#define ZombiePianoListAddr  0x1E5429C
#define ReinitForSurfaceChangedAddr  0x12EE3AC
#define BoardAddr  0x75743C
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x8C26C4
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x8BF7A4
#define ZombieCarnieMagician__ConditionFuncAddr  0x8AA588
#define ZombieRomanHealer__ConditionFuncAddr  0x88C290
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x8AA59C
#define zFamilyFuncAddr  0x905110
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
/*#define RSBReadAddr NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  0x13FBA38
#define ForceResources1536Addr  NULL
#define ProjectileSpawnZombieAddr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
#define BoardInitAddr  NULL
#define CDNLoadAddr NULL


#define DelegateBase_SEXYDELEGATE_VTBLAddr  NULL
#define Graphics_UNK_GRAPHICSFUNC2Addr  NULL
#define Graphics_UNK_GRAPHICSFUNCAddr  NULL
#define RtClass_rtClassCtorFuncAddr  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_MOVE  NULL
#define RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR  NULL



#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1Addr NULL
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2Addr NULL
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3Addr NULL
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAMEAddr NULL
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAMEAddr NULL
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC1Addr NULL
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC2Addr NULL
#define ReflectionBuilder_rtClassGetClassFuncAddr NULL



#define BoardEntity_OFFSET_BOARDENTITY_DIEAddr NULL
#define GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr NULL
#define GameObject_GAMEOBJECT_GETTYPE_OFFSETAddr NULL
#define GameObject_GAMEOBJECT_FUNCTION_DIE_OFFSETAddr GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr
#define GridItem_SpawnGridItemAtAddr NULL
#define LevelModule_LEVELMODULE_DTOR_ADDRAddr NULL
#define LevelModule_LEVELMODULE_CTOR_ADDRAddr NULL
#define LevelModule_LEVELMODULE_GETCLASS_ADDRAddr NULL
#define LevelModule_LEVELMODULE_VTBLAddr NULL
#define LevelModuleManager_getModuleAddr NULL
#define LevelModuleManager_AddDelegateAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_CTOR_ADDRAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_DTOR_ADDRAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_VTBLAddr NULL
#define LevelModuleProperties_LEVELMODULEPROPS_GETCLASS_ADDRAddr NULL
#define PlantFramework_PLANTFRAMEWORK_CTORAddr NULL
#define PlantFramework_PLANTFRAMEWORK_VFTABLEAddr NULL
#define PlantFramework_PLANTFRAMEWORK_GETTYPEAddr NULL
#define PlantPropertySheet_PLANTPROPS_CTORAddr NULL
#define PlantPropertySheet_PLANTPROPS_VFTABLEAddr NULL
#define PlantPropertySheet_PLANTPROPS_GETTYPEAddr NULL
#define Projectile_OFFSET_PROJECTILE_PLAY_IMPACTAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_CTORAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_VFTABLEAddr NULL
#define ProjectilePropertySheet_PROJECTILEPROPS_GETTYPEAddr NULL
#define PropertySheetBase_PROPSHEETBASE_CTORAddr NULL
#define PropertySheetBase_PROPSHEETBASE_DTORAddr PropertySheetBase_PROPSHEETBASE_CTORAddr
#define PropertySheetBase_PROPSHEETBASE_DestructorAddr NULL
#define PropertySheetBase_PROPSHEETBASE_VFTABLEAddr NULL
#define PropertySheetBase_PROPSHEETBASE_GETTYPEAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_CONSTRUCT_ADDRAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_VTBLAddr NULL
#define StageModuleProperties_STAGEMODULEPROPS_GETCLASS_ADDRAddr NULL
#define Zombie_ZOMBIE_CTOR_ADDRAddr NULL
#define Zombie_ZOMBIE_DTOR_ADDRAddr NULL
#define Zombie_ZOMBIE_VFTABLE_ADDRAddr NULL
#define Zombie_OFFSET_ZOMBIE_GETTYPEAddr NULL
#define Zombie_ZOMBIE_GET_RTCLASSAddr Zombie_OFFSET_ZOMBIE_GETTYPEAddr
#define Zombie_ZOMBIE_ISDEADORDYING_ADDRAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_CTORAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_VFTABLEAddr NULL
#define ZombiePropertySheet_ZOMBIEPROPS_GETTYPEAddr NULL
#define ZombieType_ZOMBIETYPEDIRECTORY_GETAddr NULL
#define ZombieType_ZOMBIETYPEDIRECTORY_GETTYPEAddr NULL



#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectileProps_ProjectileVFTableAddr NULL


#define firstFreePlantID  191

#endif

#if GAME_VERSION==1030
#define ZombieAlmanacAddr  NULL  // NULL means I don't know what it is.
#define PlantNameMapperAddr  NULL  // 10.3 Don't need it.
#define CamelZombieAddr  NULL
#define camelMinigameModuleFuncAddr  NULL
#define WorldMapDoMovementAddr  0x524294
#define ZombiePianoAddr  NULL
#define ZombiePianoListAddr  NULL
#define ReinitForSurfaceChangedAddr  0x164FB80
#define BoardAddr  0x8856B4
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  NULL
#define ZombieRomanHealer__IsImmuneToShrinkAddr  NULL
#define ZombieCarnieMagician__ConditionFuncAddr  NULL
#define ZombieRomanHealer__ConditionFuncAddr  NULL
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  NULL
#define zFamilyFuncAddr  NULL
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
/*#define RSBReadAddr  0x162CEA4*/
#define RSBPathRecorderAddr  0x16431A8
#define PrimeGlyphCacheAddr  0x177ECF4
#define ForceResources1536Addr  0x6E4224
#define ProjectileSpawnZombieAddr  0xE6B880
#define LogOutputFuncAddrSimpleAddr 0x146E160
#define LogOutputFuncAddr  0x146DE24
#define MainLoadFuncAddr  0x6F00A0
#define ResourceManagerFuncAddr  0x6EE218
#define ResourceReadFuncAddr  0x16228F0
#define RSBTestAndReadFuncAddr  0x16303BC
#define BoardInitAddr  0x6E65AC
#define CDNLoadAddr 0x876CB0



#define DelegateBase_SEXYDELEGATE_VTBLAddr  0x21263E8
#define Graphics_UNK_GRAPHICSFUNC2Addr  0x14DE654
#define Graphics_UNK_GRAPHICSFUNCAddr  0x14DE48C
#define RtClass_rtClassCtorFuncAddr  0x16144AC
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY  0x14851A4
#define RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR  0x148EAEC
#define RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE  0x148E140
#define RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS  0x2E3C84
#define RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR  0x3160D4
#define RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE  0x148847C
#define RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER  0x14719FC
#define RtWeakPtr_OFFSET_RTWEAKPTR_MOVE  0x14719B4
#define RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR  0x14710C8



//#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC1Addr NULL
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC2Addr 0x2EC968
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_FUNC3Addr 0x1494124
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tGetHandle 0x2ED038
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tReadFunc 0x149CC2C
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tStackExtend 0x2ED188
#define TStdVectorManipulator_OFFSET_REFLECTION_RCUSTOMTYPE_TSTDVECTORMANIPULATOR_tVecSize 0x149CC70
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEINNERTEMPLATETYPENAMEAddr 0x15F16F0
#define CRefManualSymbolBuilder_OFFSET_REFLECTION_CREFMANUALSYMBOLBUILDER_GEMAPINNERTEMPLATETYPENAMEAddr 0x15F1AB4
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC1Addr 0x15FAE80
#define ReflectionBuilder_RT_BUILDER_REGISTERCLASS_FUNC2Addr 0x15FAFD8
#define ReflectionBuilder_rtClassGetClassFuncAddr 0x16140B4




#define BoardEntity_OFFSET_BOARDENTITY_DIEAddr 0x64A444
#define GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr 0x649C98
#define GameObject_GAMEOBJECT_GETTYPE_OFFSETAddr 0x649620
#define GameObject_GAMEOBJECT_FUNCTION_DIE_OFFSETAddr GameObject_GAMEOBJECT_CONSTRUCTOR_OFFSETAddr
#define GridItem_SpawnGridItemAtAddr 0x88EEBC
#define LevelModule_LEVELMODULE_DTOR_ADDRAddr 0x38F098
#define LevelModule_LEVELMODULE_CTOR_ADDRAddr 0x32DE6C
#define LevelModule_LEVELMODULE_GETCLASS_ADDRAddr 0xFAB198
#define LevelModule_LEVELMODULE_VTBLAddr 0x21B81E4
#define LevelModuleManager_getModuleAddr 0x86DC30
#define LevelModuleManager_AddDelegateAddr 0x2FFFA8
#define LevelModuleProperties_LEVELMODULEPROPS_CTOR_ADDRAddr 0x32D358
#define LevelModuleProperties_LEVELMODULEPROPS_DTOR_ADDRAddr 0x336C28
#define LevelModuleProperties_LEVELMODULEPROPS_VTBLAddr 0x21C1E2C
#define LevelModuleProperties_LEVELMODULEPROPS_GETCLASS_ADDRAddr 0x10D779C
#define PlantFramework_PLANTFRAMEWORK_CTORAddr 0x543390
#define PlantFramework_PLANTFRAMEWORK_VFTABLEAddr 0x2138808
#define PlantFramework_PLANTFRAMEWORK_GETTYPEAddr 0x54331C
#define PlantPropertySheet_PLANTPROPS_CTORAddr 0x355B3C
#define PlantPropertySheet_PLANTPROPS_VFTABLEAddr 0x2129464
#define PlantPropertySheet_PLANTPROPS_GETTYPEAddr 0x353CF0
#define Projectile_OFFSET_PROJECTILE_PLAY_IMPACTAddr 0xAC0B84
#define ProjectilePropertySheet_PROJECTILEPROPS_CTORAddr 0x340578
#define ProjectilePropertySheet_PROJECTILEPROPS_VFTABLEAddr 0x0212CE20
#define ProjectilePropertySheet_PROJECTILEPROPS_GETTYPEAddr 0x3CCCD0
//存疑
#define PropertySheetBase_PROPSHEETBASE_CTORAddr 0x2E6A90
//存疑
#define PropertySheetBase_PROPSHEETBASE_DTORAddr 0x2E7070
//存疑
#define PropertySheetBase_PROPSHEETBASE_DestructorAddr 0x2EC4D0
#define PropertySheetBase_PROPSHEETBASE_VFTABLEAddr 0x2180AD4
#define PropertySheetBase_PROPSHEETBASE_GETTYPEAddr 0xB61098
#define StageModuleProperties_STAGEMODULEPROPS_CONSTRUCT_ADDRAddr 0x3D4378
#define StageModuleProperties_STAGEMODULEPROPS_VTBLAddr 0x213BCD0
#define StageModuleProperties_STAGEMODULEPROPS_GETCLASS_ADDRAddr 0x5A65B0
#define Zombie_ZOMBIE_CTOR_ADDRAddr 0xA47A00
#define Zombie_ZOMBIE_DTOR_ADDRAddr 0xA481FC
#define Zombie_ZOMBIE_VFTABLE_ADDRAddr 0x217A624
#define Zombie_OFFSET_ZOMBIE_GETTYPEAddr 0xA42E2C
#define Zombie_ZOMBIE_GET_RTCLASSAddr Zombie_OFFSET_ZOMBIE_GETTYPEAddr
#define Zombie_ZOMBIE_ISDEADORDYING_ADDRAddr 0x0
#define ZombiePropertySheet_ZOMBIEPROPS_CTORAddr 0xA1AE80
#define ZombiePropertySheet_ZOMBIEPROPS_VFTABLEAddr 0x2186778
#define ZombiePropertySheet_ZOMBIEPROPS_GETTYPEAddr 0xC08550
#define ZombieType_ZOMBIETYPEDIRECTORY_GETAddr 0x31E4F0
#define ZombieType_ZOMBIETYPEDIRECTORY_GETTYPEAddr 0x148EAEC





#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr 0xAC053C
#define Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr 0xABE708
#define Customize_Projectile_GridItemRaiserProjectileProps_GetBoardAddr 0xB1ED58
#define Customize_Projectile_GridItemRaiserProjectileProps_SpawnGridItemOnBoardAddr 0x88FA58
#define Customize_Projectile_GridItemRaiserProjectileProps_SetTeamFlagAddr 0xFA1860
#define Customize_Projectile_GridItemRaiserProjectileProps_ProjectileVFTableAddr 0x217C9C8





#define firstFreePlantID  0  // 10.3 Don't need it.


#endif

//在此仿照如上格式再续写所需版本号偏移分类





#pragma region OldFunctionRegion
//uint ZombieAlmanacAddr;
//uint PlantNameMapperAddr;
//uint CamelZombieAddr;
//uint camelMinigameModuleFuncAddr;
//uint WorldMapDoMovementAddr;
//uint ZombiePianoAddr;
//uint ZombiePianoListAddr;
//uint ReinitForSurfaceChangedAddr;
//uint BoardAddr;
//uint ZombieCarnieMagician__IsImmuneToShrinkAddr;
//uint ZombieRomanHealer__IsImmuneToShrinkAddr;
//uint ZombieCarnieMagician__ConditionFuncAddr;
//uint ZombieRomanHealer__ConditionFuncAddr;
//uint ZombieRomanHealer__InitializeFamilyImmunitiesAddr;
//uint zFamilyFuncAddr;
//uint LawnAppAddr;
//uint SexyAppAddr;
////弃用
////uint RSBReadAddr;
//uint PrimeGlyphCacheAddr;
//uint ForceResources1536Addr;
//uint ProjectileSpawnZombieAddr;
//uint LogOutputFuncAddr;
//uint RSBPathRecorderAddr;
//uint MainLoadFuncAddr;
//uint ResourceManagerFuncAddr;
//uint ResourceReadFuncAddr;
//uint RSBTestAndReadFuncAddr;
//uint BoardInitAddr;
//
//
//
//
//
////Sexy类偏移地址
//#pragma region Sexy
//uint DelegateBase_SEXYDELEGATE_VTBLAddr;
//uint Graphics_UNK_GRAPHICSFUNC2Addr;
//uint Graphics_UNK_GRAPHICSFUNCAddr;
//uint RtClass_rtClassCtorFuncAddr;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_MOVE;
//uint RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR;
//#pragma endregion
//
//
////Reflection类偏移地址
//#pragma region Reflection
//
//#pragma endregion
//
////PvZ2类偏移地址
//#pragma region PvZ2
//
//#pragma endregion
//
////Customize类偏移地址
//#pragma region Customize
//
//#pragma endregion
//
//
//
////第一个自定义的植物ID
//uint firstFreePlantID;

//enum VersionOfGame
//{
//    v9_4=940,
//    v9_6=960,
//    v9_8=980,
//    v10_3=1030
//    //仿照上面添加版本号
//};

//#pragma region Auto Select Addresses
//int version_code = v10_3;//在此处修改版本号
//void AddressesChangedByVersion() {
//    switch (version_code)
//    {
//    case v9_4:
//    {
//        ZombieAlmanacAddr = 0x105123C;
//        PlantNameMapperAddr = 0xD994B8;
//        CamelZombieAddr = 0x7942BC;
//        camelMinigameModuleFuncAddr = 0x797494;
//        WorldMapDoMovementAddr = 0x44E604;
//        ZombiePianoAddr = 0x890108;
//        ZombiePianoListAddr = 0x1CE922C;
//        ReinitForSurfaceChangedAddr = 0x127415C;
//        BoardAddr = 0x71A004;
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x884B6C;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x881C4C;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x86CCAC;
//        ZombieRomanHealer__ConditionFuncAddr = 0x84EAA0;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x86CCC0;
//        zFamilyFuncAddr = 0x8C70A0;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr=NULL;*/
//        RSBPathRecorderAddr = NULL;
//        PrimeGlyphCacheAddr = NULL;
//        ForceResources1536Addr = NULL;
//        ProjectileSpawnZombieAddr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
//        BoardInitAddr = NULL;
//
//
//        DelegateBase_SEXYDELEGATE_VTBLAddr = NULL;
//        Graphics_UNK_GRAPHICSFUNC2Addr = NULL;
//        Graphics_UNK_GRAPHICSFUNCAddr = NULL;
//        RtClass_rtClassCtorFuncAddr = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_MOVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR = NULL;
//
//        firstFreePlantID = 185;
//        break;
//    }
//    case v9_6:
//    {
//        ZombieAlmanacAddr = 0x10643E0;
//        PlantNameMapperAddr = 0xDA5C58;
//        CamelZombieAddr = 0x789DC8;
//        camelMinigameModuleFuncAddr = 0x78CFA0;
//        WorldMapDoMovementAddr = 0x441068;
//        ZombiePianoAddr = 0x885F80;
//        ZombiePianoListAddr = 0x1D890F4;
//        ReinitForSurfaceChangedAddr = 0x1287430;
//        BoardAddr = 0x70F63C;
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x87A9E4;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x877AC4;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x8628B0;
//        ZombieRomanHealer__ConditionFuncAddr = 0x8446A8;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x8628C4;
//        zFamilyFuncAddr = 0x8BD2C0;
//        LawnAppAddr = 0x1D92A94;
//        SexyAppAddr = 0x1D9CA24;
//        /*RSBReadAddr=NULL;*/
//        RSBPathRecorderAddr = NULL;
//        PrimeGlyphCacheAddr = NULL;
//        ForceResources1536Addr = NULL;
//        ProjectileSpawnZombieAddr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
//        BoardInitAddr = NULL;
//
//        DelegateBase_SEXYDELEGATE_VTBLAddr = 0x1C5C758;
//        Graphics_UNK_GRAPHICSFUNC2Addr = 0x1124784;
//        Graphics_UNK_GRAPHICSFUNCAddr = 0x1124614;
//        RtClass_rtClassCtorFuncAddr = 0x1250518;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY = 0x10D99A4;
//        RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR = 0x10DFA5C;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE = 0x10DF644;
//        RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS = 0x24D110;
//        RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR = 0x279198;
//        RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE = 0x10DB9C0;
//        RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER = 0x10C8BF8;
//        RtWeakPtr_OFFSET_RTWEAKPTR_MOVE = 0x10C8BB0;
//        RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR = 0x10C88C8;
//
//
//        firstFreePlantID = 188;
//        break;
//    }
//    case v9_8:
//    {
//        ZombieAlmanacAddr = 0x10C0800;
//        PlantNameMapperAddr = 0xDFC008;
//        CamelZombieAddr = 0x7D1BD0;
//        camelMinigameModuleFuncAddr = 0x7D4DA8;
//        WorldMapDoMovementAddr = 0x483504;
//        ZombiePianoAddr = 0x8CDC60;
//        ZombiePianoListAddr = 0x1E5429C;
//        ReinitForSurfaceChangedAddr = 0x12EE3AC;
//        BoardAddr = 0x75743C;
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x8C26C4;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x8BF7A4;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x8AA588;
//        ZombieRomanHealer__ConditionFuncAddr = 0x88C290;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x8AA59C;
//        zFamilyFuncAddr = 0x905110;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr=NULL;*/
//        RSBPathRecorderAddr = NULL;
//        PrimeGlyphCacheAddr = 0x13FBA38;
//        ForceResources1536Addr = NULL;
//        ProjectileSpawnZombieAddr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
//        BoardInitAddr = NULL;
//
//
//        DelegateBase_SEXYDELEGATE_VTBLAddr = NULL;
//        Graphics_UNK_GRAPHICSFUNC2Addr = NULL;
//        Graphics_UNK_GRAPHICSFUNCAddr = NULL;
//        RtClass_rtClassCtorFuncAddr = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_MOVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR = NULL;
//
//
//
//
//        firstFreePlantID = 191;
//        break;
//    }
//    case v10_3:
//    {
//        ZombieAlmanacAddr = NULL;  // NULL means I don't know what it is.
//        PlantNameMapperAddr = NULL;  // 10.3 Don't need it.
//        CamelZombieAddr = NULL;
//        camelMinigameModuleFuncAddr = NULL;
//        WorldMapDoMovementAddr = 0x524294;
//        ZombiePianoAddr = NULL;
//        ZombiePianoListAddr = NULL;
//        ReinitForSurfaceChangedAddr = 0x164FB80;
//        BoardAddr = 0x8856B4;
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = NULL;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = NULL;
//        ZombieCarnieMagician__ConditionFuncAddr = NULL;
//        ZombieRomanHealer__ConditionFuncAddr = NULL;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = NULL;
//        zFamilyFuncAddr = NULL;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr = 0x162CEA4;*/
//        RSBPathRecorderAddr = 0x16431A8;
//        PrimeGlyphCacheAddr = 0x177ECF4;
//        ForceResources1536Addr = 0x6E4224;
//        ProjectileSpawnZombieAddr = 0xE6B880;
//        LogOutputFuncAddr = 0x146DE24;
//        MainLoadFuncAddr = 0x6F00A0;
//        ResourceManagerFuncAddr = 0x6EE218;
//        ResourceReadFuncAddr = 0x16228F0;
//        RSBTestAndReadFuncAddr = 0x16303BC;
//        BoardInitAddr = 0x6E65AC;
//
//
//
//        DelegateBase_SEXYDELEGATE_VTBLAddr = NULL;
//        Graphics_UNK_GRAPHICSFUNC2Addr = NULL;
//        Graphics_UNK_GRAPHICSFUNCAddr = NULL;
//        RtClass_rtClassCtorFuncAddr = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETREGISTRY = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_COPYWEAKPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_GETTABLEOFTYPE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_EQUALS = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_ISVALIDPTR = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_RESOLVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_FROMOTHER = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_MOVE = NULL;
//        RtWeakPtr_OFFSET_RTWEAKPTR_SETWEAKPTR = NULL;
//
//
//
//
//
//        firstFreePlantID = 0;  // 10.3 Don't need it.
//        break;
//    }
//    //仿照上述case添加版本偏移
//    default:
//    {
//        break;
//    }
//    }
//}
//#pragma endregion

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