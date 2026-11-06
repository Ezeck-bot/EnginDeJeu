#pragma once
#include <Entity.h>

namespace homer {
    class Component
    {
    public:
        virtual ~Component() = default;
        Component() = default;
        Component(homer::Entity* parent);

        virtual void Start() {}
        /*virtual void Update(float dt) {}
        virtual void Draw() {}*/
        virtual void Destroy() {}

    protected:
        homer::Entity* m_Entity = nullptr;
        friend class Entity;
    };
}