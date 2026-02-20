#pragma once
#include "../../PvZ2/Projectile.h"
class GridItemRaiserProjectileProps : public Projectile
{
	DECLARE_STATIC_RT_CLASS_MEMBERS(GridItemRaiserProjectileProps);
	//设定新属性：定义子弹生成的障碍物
	Sexy::SexyString GridItemType = "gravestone_egypt";
	//接着GridItemRaiserProjectileProps.cpp的子弹虚表找法：
	//最右上角的偏移引用部分
	//其中DATA XREF: sub_907508+28↑o或sub_907508+30↑o的sub_907508即DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(GridItemRaiserProjectileProps, 填入);
	/*DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(GridItemRaiserProjectileProps, Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr);
	DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_END();*/
	DEFINE_RT_CLASS_CONSTRUCT_FUNCTION(GridItemRaiserProjectileProps, Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr);

	RT_CLASS_BUILD_SYMBOLS_BEGIN(GridItemRaiserProjectileProps, Projectile);
	// 这里利用宏展开后的 builder 指针，塞入你的新属性
	void* prop_GridItemType = (builder)->GetPropertyOfType(Reflection::Type_Char, sizeof(char));
	void* regProp_GridItemType = (builder)->RegisterPointerProperty(0, prop_GridItemType, __null);
	//注册新属性
	(builder)->RegisterProperty(rclass, "GridItemType", __builtin_offsetof(GridItemRaiserProjectileProps, GridItemType), regProp_GridItemType);
	RT_CLASS_BUILD_SYMBOLS_END();

	DEFINE_RT_CLASS_REGISTER_CLASS_FUNCTION(GridItemRaiserProjectileProps);
	//接下来为：
	/*.data.rel.ro:01CB00D4 C4 01 CB 01                   DCD _ZTI10Projectile; `typeinfo for'Projectile
		.data.rel.ro:01CB00D8 24 5A 90 00                   off_1CB00D8 DCD sub_905A24*/

	//双击示例中的DCD sub_905A24
	//跳转后可得：
	//.text:00905A24; ============== = S U B R O U T I N E ====================================== =
	//	.text:00905A24
	//	.text:00905A24; Attributes: thunk
	//	.text : 00905A24
	//	.text:00905A24                               sub_905A24; DATA XREF : .data.rel.ro : off_1CB00D8↓o
	//	.text : 00905A24; __unwind{
	//	.text:00905A24 E1 FF FF EA                   B               sub_9059B0
	//	.text:00905A24; } // starts at 905A24
	//	.text:00905A24
	//	.text:00905A24; End of function sub_905A24
	//	.text:00905A24
	//	.text:00905A28

	//其中sub_9059B0即DEFINE_RT_CLASS_GET_CLASS_FUNCTION(GridItemRaiserProjectileProps, 填入);
	DEFINE_RT_CLASS_GET_CLASS_FUNCTION(GridItemRaiserProjectileProps, Customize_Projectile_GridItemRaiserProjectileProps_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr);




	
};