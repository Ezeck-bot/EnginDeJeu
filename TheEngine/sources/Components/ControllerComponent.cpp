#include "ControllerComponent.h"
#include <BulletComponent.h>

ControllerComponent::ControllerComponent()
{
    m_currentVolume = m_volumeBase;
}

ControllerComponent::~ControllerComponent()
{
    m_atlas = nullptr;
    m_animation = nullptr;
}

void ControllerComponent::Start()
{
    //musique du jeu
    m_musicId = homer::Engine::Get()->audio()->LoadMusic("Assets/Audio/SoundTrack2.wav");
    homer::Engine::Get()->audio()->PlayMusic(m_musicId, -1);

    //effet sonore (sfx)
    m_soundId = homer::Engine::Get()->audio()->LoadSound("Assets/Audio/faaah.mp3");

    m_atlas = m_Entity->GetComponent<AtlasComponent>();

    m_animation = m_Entity->GetComponent<AnimationComponent>();

    //audio
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

    //animation
    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_E))
    {
        m_animation->Stop();
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_F))
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

    //pour changer de scene
    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::SPACE))
    {
        homer::Engine::Get()->world()->Load("Niveau1");
    }

    //audio
    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_K)) {

        homer::Engine::Get()->audio()->PlayMusic(m_musicId);
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_I)) {

        homer::Engine::Get()->audio()->PlaySFX(m_soundId, 0);
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_P)) {

        homer::Engine::Get()->audio()->PauseMusic();
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_R)) {

        homer::Engine::Get()->audio()->ResumeMusic();
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_H)) {

        homer::Engine::Get()->audio()->StopMusic();
    }

    ////volume
    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_J) && m_currentVolume > 0) {

        m_currentVolume--;
        homer::Engine::Get()->audio()->SetVolume(m_currentVolume);
    }

    if (homer::Engine::Get()->input()->IsKeyDown((int)Keys::Key_L) && m_currentVolume < 100) {

        m_currentVolume++;
        homer::Engine::Get()->audio()->SetVolume(m_currentVolume);
    }
}
