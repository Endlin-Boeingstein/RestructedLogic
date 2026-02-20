#pragma once
#include "../../PvZ2/Projectile.h"
class GridItemRaiserProjectile : public Projectile
{
	DECLARE_STATIC_RT_CLASS_MEMBERS(GridItemRaiserProjectile);
	//接着GridItemRaiserProjectile.cpp的子弹虚表找法：
	//最右上角的偏移引用部分
	//其中DATA XREF: sub_907508+28↑o或sub_907508+30↑o的sub_907508即DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(GridItemRaiserProjectile, 填入);
	DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(GridItemRaiserProjectile, Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_BEGINAddr);
	DEFINE_RT_CLASS_CONSTRUCT_FUNCTION_END();

	RT_CLASS_BUILD_SYMBOLS_BEGIN(GridItemRaiserProjectile, Projectile);
	RT_CLASS_BUILD_SYMBOLS_END();

	DEFINE_RT_CLASS_REGISTER_CLASS_FUNCTION(GridItemRaiserProjectile);
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

	//其中sub_9059B0即DEFINE_RT_CLASS_GET_CLASS_FUNCTION(GridItemRaiserProjectile, 填入);
	DEFINE_RT_CLASS_GET_CLASS_FUNCTION(GridItemRaiserProjectile, Customize_Projectile_GridItemRaiserProjectile_DEFINE_RT_CLASS_GET_CLASS_FUNCTIONAddr);
};