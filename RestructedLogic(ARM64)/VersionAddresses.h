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
#define ZombieAlmanacAddr  0x00
#define PlantNameMapperAddr  0x1157778//
#define CamelZombieAddr  0x00
#define camelMinigameModuleFuncAddr  0x00
#define WorldMapDoMovementAddr  0x00
#define ZombiePianoAddr  0x00
#define ZombiePianoListAddr  0x00
#define ReinitForSurfaceChangedAddr  0x164C580
#define BoardAddr  0xA94604//
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x00
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x00
#define ZombieCarnieMagician__ConditionFuncAddr  0x00
#define ZombieRomanHealer__ConditionFuncAddr  0x00
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x00
#define zFamilyFuncAddr  0x00
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
 /*#define RSBReadAddr  NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
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





#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_ProjectileVFTableAddr NULL






#define firstFreePlantID  185

#endif

#if GAME_VERSION==960
#define ZombieAlmanacAddr  0x00
#define PlantNameMapperAddr  0x00//
#define CamelZombieAddr  0x00
#define camelMinigameModuleFuncAddr  0x00
#define WorldMapDoMovementAddr  0x00
#define ZombiePianoAddr  0x00
#define ZombiePianoListAddr  0x00
#define ReinitForSurfaceChangedAddr  0x00
#define BoardAddr  0x00//
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x00
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x00
#define ZombieCarnieMagician__ConditionFuncAddr  0x00
#define ZombieRomanHealer__ConditionFuncAddr  0x00
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x00
#define zFamilyFuncAddr  0x00
#define LawnAppAddr  0x2593760
#define SexyAppAddr  0x25A4618
/*#define RSBReadAddr  NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
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





#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_ProjectileVFTableAddr NULL






#define firstFreePlantID  188

#endif

#if GAME_VERSION==980
#define ZombieAlmanacAddr  0x00
#define PlantNameMapperAddr  0x00//
#define CamelZombieAddr  0x00
#define camelMinigameModuleFuncAddr  0x00
#define WorldMapDoMovementAddr  0x00
#define ZombiePianoAddr  0x00
#define ZombiePianoListAddr  0x00
#define ReinitForSurfaceChangedAddr  0x00
#define BoardAddr  0x00//
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  0x00
#define ZombieRomanHealer__IsImmuneToShrinkAddr  0x00
#define ZombieCarnieMagician__ConditionFuncAddr  0x00
#define ZombieRomanHealer__ConditionFuncAddr  0x00
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  0x00
#define zFamilyFuncAddr  0x00
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
/*#define RSBReadAddr  NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
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





#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_ProjectileVFTableAddr NULL












#define firstFreePlantID  191

#endif

#if GAME_VERSION==1030
#define ZombieAlmanacAddr  NULL  // NULL means I don't know what it is.
#define PlantNameMapperAddr  NULL  // 10.3 Don't need it.
#define CamelZombieAddr  NULL
#define camelMinigameModuleFuncAddr  NULL
#define WorldMapDoMovementAddr  NULL
#define ZombiePianoAddr  NULL
#define ZombiePianoListAddr  NULL
#define ReinitForSurfaceChangedAddr  NULL
#define BoardAddr  NULL
#define ZombieCarnieMagician__IsImmuneToShrinkAddr  NULL
#define ZombieRomanHealer__IsImmuneToShrinkAddr  NULL
#define ZombieCarnieMagician__ConditionFuncAddr  NULL
#define ZombieRomanHealer__ConditionFuncAddr  NULL
#define ZombieRomanHealer__InitializeFamilyImmunitiesAddr  NULL
#define zFamilyFuncAddr  NULL
#define LawnAppAddr  NULL
#define SexyAppAddr  NULL
/*#define RSBReadAddr  NULL*/
#define RSBPathRecorderAddr  NULL
#define PrimeGlyphCacheAddr  NULL
#define ForceResources1536Addr  NULL
#define LogOutputFuncAddrSimpleAddr NULL
#define LogOutputFuncAddr  NULL
#define MainLoadFuncAddr  NULL
#define ResourceManagerFuncAddr  NULL
#define ResourceReadFuncAddr  NULL
#define RSBTestAndReadFuncAddr  NULL
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





#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_GetBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SpawnGridItemOnBoardAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_SetTeamFlagAddr NULL
#define Customize_Projectile_GridItemRaiserProjectile_ProjectileVFTableAddr NULL





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
////禁用
////uint RSBReadAddr;
//uint ForceResources1536Addr;
//uint LogOutputFuncAddr;
//uint RSBPathRecorderAddr;
//uint MainLoadFuncAddr;
//uint ResourceManagerFuncAddr;
//uint ResourceReadFuncAddr;
//uint RSBTestAndReadFuncAddr;
//
////第一个自定义的植物ID
//uint firstFreePlantID;

//enum VersionOfGame
//{
//    v9_4 = 940,
//    v9_6 = 960,
//    v9_8 = 980,
//    v10_3 = 1030
//    //仿照上面添加版本号
//};
//
//#pragma region Auto Select Addresses
//int version_code = v10_3;//在此处修改版本号
//void AddressesChangedByVersion() {
//    switch (version_code)
//    {
//    case v9_4:
//    {
//        //部分偏移由某神秘大佬查找得来，但是由于v7a和v8a函数结构不同，还有新的库的未知什么导致的闪退问题，故v8a方案已废弃
//        ZombieAlmanacAddr = 0x00;
//        PlantNameMapperAddr = 0x1157778;//
//        CamelZombieAddr = 0x00;
//        camelMinigameModuleFuncAddr = 0x00;
//        WorldMapDoMovementAddr = 0x00;
//        ZombiePianoAddr = 0x00;
//        ZombiePianoListAddr = 0x00;
//        ReinitForSurfaceChangedAddr = 0x164C580;
//        BoardAddr = 0xA94604;//
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
//        zFamilyFuncAddr = 0x00;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr = NULL;*/
//        RSBPathRecorderAddr = NULL;
//        ForceResources1536Addr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
//
//        firstFreePlantID = 185;
//        break;
//    }
//    case v9_6:
//    {
//        ZombieAlmanacAddr = 0x00;
//        PlantNameMapperAddr = 0x00;//
//        CamelZombieAddr = 0x00;
//        camelMinigameModuleFuncAddr = 0x00;
//        WorldMapDoMovementAddr = 0x00;
//        ZombiePianoAddr = 0x00;
//        ZombiePianoListAddr = 0x00;
//        ReinitForSurfaceChangedAddr = 0x00;
//        BoardAddr = 0x00;//
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
//        zFamilyFuncAddr = 0x00;
//        LawnAppAddr = 0x2593760;
//        SexyAppAddr = 0x25A4618;
//        /*RSBReadAddr = NULL;*/
//        RSBPathRecorderAddr = NULL;
//        ForceResources1536Addr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
//
//        firstFreePlantID = 188;
//        break;
//    }
//    case v9_8:
//    {
//        ZombieAlmanacAddr = 0x00;
//        PlantNameMapperAddr = 0x00;//
//        CamelZombieAddr = 0x00;
//        camelMinigameModuleFuncAddr = 0x00;
//        WorldMapDoMovementAddr = 0x00;
//        ZombiePianoAddr = 0x00;
//        ZombiePianoListAddr = 0x00;
//        ReinitForSurfaceChangedAddr = 0x00;
//        BoardAddr = 0x00;//
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = 0x00;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = 0x00;
//        ZombieCarnieMagician__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__ConditionFuncAddr = 0x00;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = 0x00;
//        zFamilyFuncAddr = 0x00;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr = NULL;*/
//        RSBPathRecorderAddr = NULL;
//        ForceResources1536Addr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
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
//        WorldMapDoMovementAddr = NULL;
//        ZombiePianoAddr = NULL;
//        ZombiePianoListAddr = NULL;
//        ReinitForSurfaceChangedAddr = NULL;
//        BoardAddr = NULL;
//        ZombieCarnieMagician__IsImmuneToShrinkAddr = NULL;
//        ZombieRomanHealer__IsImmuneToShrinkAddr = NULL;
//        ZombieCarnieMagician__ConditionFuncAddr = NULL;
//        ZombieRomanHealer__ConditionFuncAddr = NULL;
//        ZombieRomanHealer__InitializeFamilyImmunitiesAddr = NULL;
//        zFamilyFuncAddr = NULL;
//        LawnAppAddr = NULL;
//        SexyAppAddr = NULL;
//        /*RSBReadAddr = NULL;*/
//        RSBPathRecorderAddr = NULL;
//        ForceResources1536Addr = NULL;
//        LogOutputFuncAddr = NULL;
//        MainLoadFuncAddr = NULL;
//        ResourceManagerFuncAddr = NULL;
//        ResourceReadFuncAddr = NULL;
//        RSBTestAndReadFuncAddr = NULL;
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