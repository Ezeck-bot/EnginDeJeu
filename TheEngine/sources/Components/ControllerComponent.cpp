#include "ControllerComponent.h"
#include <BulletComponent.h>

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
    homer::Entity* fire = homer::Engine::Get()->world()->Find("Bullet");

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_A)) {

        m_Entity->SetPositionX(m_Entity->GetX() - 100.0f * dt);
        m_atlas->SetFrame("gauche");

        //position du player
        m_dirX = -1.0f; m_dirY = 0.0f;

        //orientation image balle
        fire->GetComponent<AtlasComponent>()->SetFrame("gauche");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_W)) {

        m_Entity->SetPositionY(m_Entity->GetY() - 100.0f * dt);
        m_atlas->SetFrame("haut");

        //position du player
        m_dirX = 0.0f; m_dirY = -1.0f;

        //orientation image balle
        fire->GetComponent<AtlasComponent>()->SetFrame("haut");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_S)) {

        m_Entity->SetPositionY(m_Entity->GetY() + 100.0f * dt);
        m_atlas->SetFrame("bas");

        //position du player
        m_dirX = 0.0f; m_dirY = 1.0f;

        //orientation image balle
        fire->GetComponent<AtlasComponent>()->SetFrame("bas");

    } else if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_D)) {

        m_Entity->SetPositionX(m_Entity->GetX() + 100.0f * dt);
        m_atlas->SetFrame("droite");

        //position du player
        m_dirX = 1.0f; m_dirY = 0.0f;

        //orientation image balle
        fire->GetComponent<AtlasComponent>()->SetFrame("droite");
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_E))
    {
        //m_animation->Stop();

        if (fire != nullptr)
        {
            

            fire->SetPositionX(m_Entity->GetX()+12);
            fire->SetPositionY(m_Entity->GetY()+12); //+12 pour centrer
            fire->GetComponent<BulletComponent>()->Fire(m_dirX, m_dirY);
            fire->SetActive(true);
        }
    }
}
