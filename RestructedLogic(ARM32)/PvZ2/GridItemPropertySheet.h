#pragma once
#pragma once
#include "PropertySheetBase.h"
#include "StringRestrictionSet.h"

class GridItemPropertySheet : public PropertySheetBase
{
public:
	float Hitpoints;
	int HitRectOffsetX;
	int HitRectOffsetWidth;
	int Height;
	bool CanBeMowed;
	PlantingRestrictionSet PlantingRestrictions;
	GridItemRestrictionSet GridItemsOverride;
};