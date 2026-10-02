#include <time.h> 
#include "Engine.h"
#include "SDLGfx.h";
#include "SDLInput.h";
#include "SDLAudio.h";
#include "ConsoleLogger.h";
#include "FileLogger.h";
#include <Windows.h> // a cause de sleep



bool homer::Engine::Init(const char* title, int w, int h) {
    
#ifdef _DEBUG
    m_logger = new ConsoleLogger();
#else
    m_logger = new FileLogger();
#endif 

    m_gfx = new SDLGfx();
    if (!homer::Engine::Get()->Gfx()->Init(title, w, h))
    {
        return false;
    }

    //image
    m_textureId = homer::Engine::Get()->Gfx()->LoadTexture("Assets/Images/test.png");

    //font
    m_fontId = homer::Engine::Get()->Gfx()->LoadFont("Assets/Fonts/Inter-VariableFont.ttf", 50);

    //audio
    m_audio = new SDLAudio();
    m_audio->Init();


    //input
    m_input = new SDLInput();

    
    m_IsInit = true;
    return m_IsInit;
}

void homer::Engine::Start() {
    // si la personne a appeler start sans appeler init on veut supporter cette situation
    if (!m_IsInit) {
        if (!Init("Unknow title", 800, 600)) {
            return;
        }
    
    }

    

    //music de fond
    m_musicId = homer::Engine::Get()->Audio()->LoadMusic("Assets/Audio/SoundTrack2.wav");
    homer::Engine::Get()->Audio()->PlayMusic(m_musicId, -1);
    homer::Engine::Get()->Audio()->SetVolume(m_volumeBase);
    m_currentVolume = m_volumeBase;

    //effet sonore (sfx)
    m_soundId = homer::Engine::Get()->Audio()->LoadSound("Assets/Audio/098_Unpause_04.wav");

    //pour affcher un message de début dans la console
    homer::Engine::Get()->LoggerF()->Log("!!!!!!!!!!!!!!!!!!!!!!!!!!!! Bienvenue dans ConsoleLogger !!!!!!!!!!!!!!!!!!!!!!!!!!!!");



    //creer notre boucle de jeu
    m_IsRunning = true;
    clock_t _end = clock();


    while (m_IsRunning) {

        clock_t _start = clock();
        float dt = (_start - _end) * 0.001f;
        ProcessInput();
        Update(dt);
        Render();

        //saisir le target fps de notre jeu
        SetTargetFPS(60, _start);
        
        _end = _start;
    }

    //on ferme tous
    Shutdown();
}


float m_x, m_y;
void homer::Engine::ProcessInput() {

    homer::Engine::Get()->Input()->Update();

    //Controle de la souris
    int _mouseX = 0;
    int _mouseY = 0;
    homer::Engine::Get()->Input()->GetMousePosition(&_mouseX, &_mouseY);

    if (homer::Engine::Get()->Input()->IsButtonDown(1)) { 
        m_x = _mouseX - 50;
        m_y = _mouseY - 50;
    }

}

void homer::Engine::Update(float dt) {

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_A)) {
        m_x -= 100 * dt;

        //je modifie ma variable flip pour que je puisse la psser adns la fonction
        m_flip.h = true;
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_D)) {
        m_x += 100 * dt;
        m_flip.h = false;
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_W)) {
        m_y -= 100 * dt;
        m_flip.v = false;
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_S)) {
        m_y += 100 * dt;
        m_flip.v = true;
    }


    //audio
    //K pour Play la music
    //I pour jouer un sfx
    //P pour mettre pause à la musique
    //R pour continuer la music
    //H pour stop la music
    //J Pour diminuer le volume
    //L pour augmenter le volume
    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_K)) {

        homer::Engine::Get()->Audio()->PlayMusic(m_musicId);
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_I)) {
       
        homer::Engine::Get()->Audio()->PlaySFX(m_soundId, 0);
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_P)) {

        homer::Engine::Get()->Audio()->PauseMusic();
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_R)) {

        homer::Engine::Get()->Audio()->ResumeMusic();
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_H)) {

        homer::Engine::Get()->Audio()->StopMusic();
    }

    //volume
    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_J) && m_currentVolume > 0) {

        m_currentVolume--;
        m_audio->SetVolume(m_currentVolume);
    }

    if (homer::Engine::Get()->Input()->IsKeyDown((int)Keys::Key_L) && m_currentVolume < m_volumeBase) {

        m_currentVolume++;
        m_audio->SetVolume(m_currentVolume);
    }
}


//FPS
void homer::Engine::SetTargetFPS(int fps, clock_t start)
{
    //faire une conversion du fps en float pour que la divison soit exact
    double MS_PER_FRAME = (1 / float(fps)) * 1000;

    double s = start + MS_PER_FRAME - clock();

    
     if (s >= 0) Sleep(s);
}


//Render
void homer::Engine::Render() {
    //clear
    homer::Engine::Get()->Gfx()->Clear();

    homer::Engine::Get()->Gfx()->DrawRect(m_x, m_y, 100, 100, {0, 255, 0, 0});
    homer::Engine::Get()->Gfx()->Fillrect(m_x, m_y, 100, 100, {0, 0, 255, 0});
    homer::Engine::Get()->Gfx()->DrawLine(2.0, 2.0, 100.0, 100.0, { 0, 255, 255, 0 });
    
    //homer::Engine::Get()->Gfx()->DrawTexture(m_textureId, { m_x, m_y, 150, 150}, {255, 255, 255, 255});

    int w = 0, h = 0;
    homer::Engine::Get()->Gfx()->GetTextureSize(m_textureId, &w, &h); // taille réelle de la texture

    RectI src{ 0, 0, w, h};
    RectF dst{ (float)m_x, (float)m_y, 150, 150 };
    homer::Engine::Get()->Gfx()->DrawTexture(m_textureId, src, dst, 0.0, Flip{ m_flip.h, m_flip.v }, Color{ 255, 255, 255, 255 });

    
    homer::Engine::Get()->Gfx()->DrawString(
        "Battle City \n wasd pour bouger le player \n K pour Play la music \n I pour jouer un sfx \n P pour mettre pause a la musique \n R pour continuer la music \n H pour stop la music \n J Pour diminuer le volume \n L pour augmenter le volume",
        m_fontId, 
        0, 
        0, 
        { 0, 0, 255, 255 }
    );

    //prenst
    homer::Engine::Get()->Gfx()->Present();
}

void homer::Engine::Shutdown() {

    homer::Engine::Get()->Gfx()->Shutdown();
    m_audio->Shutdown();

    //delete
    delete m_audio;
    m_audio = NULL;
    delete m_input;
    m_input = NULL;
    delete m_logger;
    m_logger = NULL;
    delete m_gfx;
    m_gfx = NULL;
}

void homer::Engine::Exit() {
    m_IsRunning = false;
}
