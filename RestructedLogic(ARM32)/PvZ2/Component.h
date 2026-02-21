#pragma once
#include "../PvZ2/GameObject.h"

class ComponentBase : public GameObject
{
public:
    Sexy::SexyString m_name;
    int m_state;
    Sexy::RtWeakPtr<Sexy::RtObject> m_owner;
    char pad[8];
};

class ComponentRunnerBase : public ComponentBase {};

class ComponentRunner : public ComponentRunnerBase
{
public:
    std::vector<Sexy::RtWeakPtr<Sexy::RtObject>> m_components;
};