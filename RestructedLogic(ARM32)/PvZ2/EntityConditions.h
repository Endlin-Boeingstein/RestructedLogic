#pragma once


struct EntityCondition
{
	float m_startTime;
	float m_endTime;
	float m_eventTime;
	float m_additionalDataValue;
};

// it should be a template with 2 parameters
class EntityConditionTracker
{
public:
	std::vector<uint8_t> m_conditionFlags;
	std::vector<EntityCondition> m_conditions;

public:
	virtual void Function0() {};
	virtual void Function1() {};
	virtual void Function2() {};
	virtual void Function3() {};
};

class GridItemConditionTracker : public EntityConditionTracker
{

};
class ZombieConditionTracker : public EntityConditionTracker
{
public:
	//char m_pad[706];
};