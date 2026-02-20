#pragma once
#include "PropertySheetBase.h"

#define LEVELMODULEPROPS_VTBL_NFUNC 18

#define LEVELMODULEPROPS_GETMODULETYPE_INDEX 14

//在此介绍在这些实现基类中如何寻找一堆偏移的方法（根据找之前那堆偏移得出的经验）
//HEX搜索对应类名的文本
//然后就一直搜索，直到到了一个二位数加上这个名称（不多不少）的地方
//这个地方有一堆二位数加名字
//这二位数+名称的偏移位置就是这个类的vtable所在位置
//根据这个虚表，则会知晓一堆所需偏移

//寻找该偏移方法：
//HEX搜索文本LevelModuleProperties
//然后比如你跳转到了诸如"28LevelModuleDifficultyUIProps..21LevelModuleProperties"字样时候
//把鼠标单击LevelModuleProperties的"L"上面，然后根据该偏移让ida pro跳转
//这个时候，如下所示：
//.rodata:01BB2F70; `typeinfo name for'LevelModuleProperties
//.rodata:01BB2F70 32 31 4C 65 76 65 6C 4D 6F 64 + _ZTS21LevelModuleProperties DCB "21LevelModuleProperties", 0
//.rodata : 01BB2F70 75 6C 65 50 72 6F 70 65 72 74 + ; DATA XREF : .data.rel.ro : 01CF07BC↓o
//.rodata : 01BB2F70 69 65 73 00; type descriptor name

//双击示例中DATA XREF: .data.rel.ro:01CF07BC↓o位置
//跳转后即为该类虚表
//往上翻翻则会看到整个虚表如下所示：
//.data.rel.ro:01CF0768; `vtable for'LevelModuleProperties
//.data.rel.ro:01CF0768 00 00 00 00                   _ZTV21LevelModuleProperties DCD 0; DATA XREF : sub_28DAF0 + 2C↑o
//.data.rel.ro : 01CF0768; sub_294E7C + 14↑o
//.data.rel.ro:01CF0768; sub_294EFC + 14↑o
//.data.rel.ro:01CF0768; sub_2A951C + 2C↑o
//.data.rel.ro:01CF0768; sub_2AA64C + 38↑o
//.data.rel.ro:01CF0768; sub_2AA6F4 + 38↑o
//.data.rel.ro:01CF0768; sub_2D9C60 + 2C↑o
//.data.rel.ro:01CF0768; sub_2DA75C + 2C↑o
//.data.rel.ro:01CF0768; sub_2DA7F8 + 2C↑o
//.data.rel.ro:01CF0768; sub_2DF028 + 2C↑o
//.data.rel.ro:01CF0768; sub_2DF424 + 14↑o
//.data.rel.ro:01CF0768; sub_2F464C + 2C↑o
//.data.rel.ro:01CF0768; sub_2F5860 + 14↑o
//.data.rel.ro:01CF0768; sub_31CCAC + 2C↑o
//.data.rel.ro:01CF0768; sub_31D2D8 + 14↑o ...
//.data.rel.ro:01CF0768; offset to this
//.data.rel.ro:01CF076C B8 07 CF 01                   DCD _ZTI21LevelModuleProperties; `typeinfo for'LevelModuleProperties
//.data.rel.ro:01CF0770 D4 18 DF 00                   DCD sub_DF18D4
//.data.rel.ro : 01CF0774 88 1A DF 00                   DCD sub_DF1A88
//.data.rel.ro : 01CF0778 7C 4E 29 00                   DCD sub_294E7C
//.data.rel.ro : 01CF077C 58 27 DF 00                   DCD sub_DF2758
//.data.rel.ro : 01CF0780 F0 01 25 01                   DCD sub_12501F0
//.data.rel.ro : 01CF0784 1C 02 25 01                   DCD sub_125021C
//.data.rel.ro : 01CF0788 20 F2 53 00                   DCD sub_53F220
//.data.rel.ro : 01CF078C 84 3D 25 00                   DCD nullsub_339
//.data.rel.ro : 01CF0790 88 3D 25 00                   DCD nullsub_340
//.data.rel.ro : 01CF0794 8C 3D 25 00                   DCD nullsub_341
//.data.rel.ro : 01CF0798 B8 22 25 00                   DCD nullsub_342
//.data.rel.ro : 01CF079C 90 3D 25 00                   DCD nullsub_343
//.data.rel.ro : 01CF07A0 94 3D 25 00                   DCD nullsub_344
//.data.rel.ro : 01CF07A4 6C 1E DF 00                   DCD sub_DF1E6C
//.data.rel.ro : 01CF07A8 DC 27 DF 00                   DCD sub_DF27DC
//.data.rel.ro : 01CF07AC 84 4F 29 00                   DCD sub_294F84
//.data.rel.ro : 01CF07B0 B4 4F 29 00                   DCD sub_294FB4
//.data.rel.ro : 01CF07B4 94 20 DF 00                   DCD sub_DF2094
//.data.rel.ro : 01CF07B8; public LevelModuleProperties :
//.data.rel.ro : 01CF07B8;   public /* offset 0x0 */ PropertySheetBase :
//.data.rel.ro : 01CF07B8;     public /* offset 0x0 */ GameObject :
//.data.rel.ro : 01CF07B8;       public /* offset 0x0 */ Sexy::RtObject
//.data.rel.ro:01CF07B8; `typeinfo for'LevelModuleProperties
//.data.rel.ro:01CF07B8 D8 74 DF 01                   _ZTI21LevelModuleProperties DCD _ZTVN10__cxxabiv120__si_class_type_infoE + 8
//.data.rel.ro : 01CF07B8; DATA XREF : .data.rel.ro : 01C5F12C↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C60CD4↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C61114↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C63054↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C65090↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C67114↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C677F0↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C683F8↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C684B4↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C68570↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C6862C↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C686E8↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C687A4↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C68860↑o
//.data.rel.ro : 01CF07B8;.data.rel.ro:01C6891C↑o ...
//.data.rel.ro : 01CF07B8; reference to RTTI's type class
//.data.rel.ro:01CF07BC 70 2F BB 01                   DCD _ZTS21LevelModuleProperties; reference to type's name
//.data.rel.ro:01CF07C0 E0 3A CB 01                   DCD _ZTI17PropertySheetBase; reference to parent's type name

//其中最右上的偏移引用
//DATA XREF: sub_28DAF0+2C↑o的sub_28DAF0则为LEVELMODULEPROPS_CTOR_ADDR
//高版本该函数似乎被阉割了，所以按照虚表查找流程查找VictoryOutroProperties虚表，然后找其第一个偏移引用即可
#define LEVELMODULEPROPS_CTOR_ADDR LevelModuleProperties_LEVELMODULEPROPS_CTOR_ADDRAddr
//sub_294E7C+14↑o或者sub_294EFC+14↑o则为LEVELMODULEPROPS_DTOR_ADDR
#define LEVELMODULEPROPS_DTOR_ADDR LevelModuleProperties_LEVELMODULEPROPS_DTOR_ADDRAddr
//偏移引用之后是
//.data.rel.ro:01CF076C B8 07 CF 01                   DCD _ZTI21LevelModuleProperties         ; `typeinfo for'LevelModuleProperties
//.data.rel.ro:01CF0770 D4 18 DF 00                   DCD sub_DF18D4
//其中.data.rel.ro:01CF0770的01CF0770为LEVELMODULEPROPS_VTBL
#define LEVELMODULEPROPS_VTBL LevelModuleProperties_LEVELMODULEPROPS_VTBLAddr
//双击示例中LEVELMODULEPROPS_VTBL位置
//跳转后则无需F5即刻看到
//.text:00DF18D4
//.text : 00DF18D4; ============== = S U B R O U T I N E ====================================== =
//.text:00DF18D4
//.text : 00DF18D4; Attributes: thunk
//.text : 00DF18D4
//.text : 00DF18D4                               sub_DF18D4; DATA XREF : .data.rel.ro : 01CF0770↓o
//.text : 00DF18D4; __unwind{
//.text:00DF18D4 E1 FF FF EA                   B               sub_DF1860
//.text : 00DF18D4; } // starts at DF18D4
//.text:00DF18D4
//.text : 00DF18D4; End of function sub_DF18D4
//.text:00DF18D4

//其中示例中sub_DF1860位置即LEVELMODULEPROPS_GETCLASS_ADDR
#define LEVELMODULEPROPS_GETCLASS_ADDR LevelModuleProperties_LEVELMODULEPROPS_GETCLASS_ADDRAddr


class LevelModuleProperties : public PropertySheetBase
{
public:
	std::vector<Sexy::SexyString> ResourceGroupNames;
	Sexy::RtWeakPtr<void> DifficultyProps;
	Sexy::SexyString IconImage;
	Sexy::SexyString IconText;
};

static_assert(sizeof(LevelModuleProperties) == 0x48); // 0x50 is the true size