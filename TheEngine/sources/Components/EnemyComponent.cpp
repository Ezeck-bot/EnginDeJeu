#include "EnemyComponent.h"

EnemyComponent::EnemyComponent()
{
}

EnemyComponent::~EnemyComponent()
{
	m_atlas = nullptr;
	m_animation = nullptr;
}

void EnemyComponent::Start()
{
	m_atlas = m_Entity->GetComponent<AtlasComponent>();

	m_animation = m_Entity->GetComponent<AnimationComponent>();
}

void EnemyComponent::Update(float dt)
{
    if (m_movingLeft == true) {
        m_atlas->SetFrame("gauche");
        m_Entity->SetPositionX(m_Entity->GetX() - 100.0f * dt);

        if (m_Entity->GetX() <= 0.0f) {
            m_movingLeft = false;
        }
    }
    else {
        m_atlas->SetFrame("droite");
        m_Entity->SetPositionX(m_Entity->GetX() + 100.0f * dt);

        if (m_Entity->GetX() >= 100.0f) {
            m_movingLeft = true;
        }
    }
}
