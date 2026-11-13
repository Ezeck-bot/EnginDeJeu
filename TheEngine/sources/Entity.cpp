#include "Entity.h"
#include "Component.h"

namespace homer {

    Entity::Entity(const std::string& name) : m_Name(name)
    {
    }

    Entity::~Entity()
    {
	    Destroy();
    }

    void Entity::Start() {
        for (auto c : m_components) {
            c->Start();
        }
    }

    void Entity::Draw() {

        if (!m_active) return;

        for (IDrawable* d : m_drawables) {
            d->Draw();
        }
    }

    void Entity::Update(float dt) {

        if (!m_active) return;

        for (IUpdatable* u : m_updatables) {
            u->Update(dt);
        }
    }

    void Entity::Destroy() {

        m_updatables.clear();
        m_drawables.clear();

        for (auto c : m_components) {
            c->Destroy();
            delete c;
        }
        m_components.clear();
    }
}
