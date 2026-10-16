#pragma once
#include <Entity.h>

class Component
{
public:
    virtual ~Component() = default;
    Component();
    Component(Entity* parent);

    virtual void Start() {}
    virtual void Destroy() {}

protected:
    Entity* m_Entity = nullptr;
};