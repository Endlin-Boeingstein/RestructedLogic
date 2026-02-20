#pragma once
#include "../Sexy/RtWeakPtr.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class Plant : public BoardEntity
{
public:
	PlantFramework* m_plantFramework;
	ValueRange m_initialLaunchInterval;
	ValueRange m_launchInterval;
	float m_baseScale;
	uint32_t m_state;
	int32_t m_plantFlags;
	float m_PlantHealth;
	float m_overrideMinimumMaxHealth;
	float m_speedModifier;
	int32_t m_lastDamageType;
	int m_unk0x94;
	int32_t m_row;
	int32_t m_column;
	bool m_isOnBoard;
	bool m_isShooter;
	bool m_mirror;
	bool m_isDead;
	float m_disappearTime;
	float m_doSpecialTime;
	float m_stateEndTime;
	float m_launchTime;
	float m_plantFoodEndtime;
	float m_timeTillNextDamageFlash;
	float m_fadeInDuration;
	float m_fadeInEndTime;
	float m_sproutScalingDuration;
	float m_sproutScalingEndTime;
	char pad_00CC[8];
	int32_t m_damageStates;
	int32_t m_currentDamageState;
	int32_t m_currentPlantActionIdx;
	Sexy::RtWeakPtr<void> m_type;
	Sexy::RtWeakPtr<int> m_animRig;
	Sexy::RtWeakPtr<int> m_plantFoodShine;
	bool m_isInPlantFoodState;
	bool m_protectedFromShovel;
	bool m_isDuplicate;
	char pad_00FB[1];
	int32_t m_level;
	int32_t m_masteryLevel;
	int32_t m_powerUpFlags;
	Sexy::RtWeakPtr<PlantPropertySheet> m_propertySheet;
	int32_t m_multiPlantGridLayer;
	int32_t m_multiPlantDrawLayer;
	bool m_relocating;
	char pad_0119[3];
	float m_relocateFromX;
	float m_relocateFromY;
	float m_relocateToX;
	float m_relocateToY;
	float m_relocateApexHeight;
	struct Sexy::SexyVector2 m_relocationOffsetFromDestination;
	float m_relocateStartTime;
	float m_relocateEndTime;
	int32_t m_relocationType;
	char pad_0144[4];
	int32_t m_groundEffect;
	char pad_014C[20];
	char m_conditionTracker[104];
	int32_t m_attachedBoardEntities;
	char pad_01CC[12];
	int32_t m_attachedEffects;
	char m_attachedEffectsVec[12];

	template <typename T>
	T* GetProps()
	{
		Sexy::RtWeakPtr<PlantPropertySheet> propSheetPtr = m_propertySheet;

		T* props = reinterpret_cast<T*>(propSheetPtr.Get());
		return props;
	}
};

static_assert(offsetof(Plant, m_type) == 0xE0);
static_assert(offsetof(Plant, m_conditionTracker) == 0x160);
static_assert(sizeof(Plant) == 0x1E8);

class PlantGroup : public BoardEntity
{
public:
	int m_gridX; // 0x64
	int m_gridY; // 0x68
	bool m_isOnBoard; // 0x6C
	bool m_groupPlantfoodRender;
	std::vector<Sexy::RtWeakPtr<Plant>> m_plants;
};