#pragma once
#include "../Sexy/RtObject.h"
#include "../Sexy/RtWeakPtr.h"

class GameObjectDictionary : public Sexy::RtObject
{};

class AttachedGameObjectNode
{
public:
	Sexy::SexyString m_name;
	Sexy::RtWeakPtr<Sexy::RtObject> m_object;
};

class AttachedEffect : public AttachedGameObjectNode
{
public:
	int m_updateMethod;
	Sexy::SexyString m_loopAnimName;
	ValueRange m_loopDelayRange;
	float m_loopDelay;
	float m_staticScale;
	float m_dynamicScale;
};

class AttachedEffectManager : public GameObjectDictionary
{
public:

	std::vector<AttachedEffect> m_nodes;
};
static_assert(sizeof(AttachedEffectManager) == 0x10);