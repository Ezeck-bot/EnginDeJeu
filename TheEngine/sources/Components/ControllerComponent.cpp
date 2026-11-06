#include "ControllerComponent.h"

ControllerComponent::ControllerComponent()
{
}

ControllerComponent::~ControllerComponent()
{
    m_atlas = nullptr;
    m_animation = nullptr;
}

void ControllerComponent::Start()
{
    m_atlas = m_Entity->GetComponent<AtlasComponent>();

    m_animation = m_Entity->GetComponent<AnimationComponent>();
}

void ControllerComponent::Update(float dt)
{
    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_A)) {

        m_Entity->SetPositionX(m_Entity->GetX() - 100.0f * dt);
        m_atlas->SetFrame("gauche");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_W)) {

        m_Entity->SetPositionY(m_Entity->GetY() - 100.0f * dt);
        m_atlas->SetFrame("haut");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_S)) {

        m_Entity->SetPositionY(m_Entity->GetY() + 100.0f * dt);
        m_atlas->SetFrame("bas");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_D)) {

        m_Entity->SetPositionX(m_Entity->GetX() + 100.0f * dt);
        m_atlas->SetFrame("droite");

    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_E))
    {
        //m_animation->Stop();

        //------PROJECTILE
        homer::Entity* bullet = homer::Engine::Get()->world()->Create("Bullet_1");

        bullet->SetPositionX(m_Entity->GetX());
        bullet->SetPositionY(m_Entity->GetY());

        bullet->AddComponent<SpriteComponent>("Assets/Images/Bullet.png");
    }
}
