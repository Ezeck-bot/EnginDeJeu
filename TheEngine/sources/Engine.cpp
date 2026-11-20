#include <time.h> 
#include "Engine.h"
#include "SDLGfx.h";
#include "SDLInput.h";
#include "SDLAudio.h";
#include "ConsoleLogger.h";
#include "FileLogger.h";
#include "World.h";
#include <Windows.h> // a cause de sleep



bool homer::Engine::Init(const char* title, int w, int h) {
    
#ifdef _DEBUG
    m_logger = new ConsoleLogger();
#else
    m_logger = new FileLogger();
#endif 

    //monde
    m_world = new World();

    m_gfx = new SDLGfx();
    if (!homer::Engine::Get()->gfx()->Init(title, w, h))
    {
        return false;
    }

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

    

    //volume au start
    homer::Engine::Get()->audio()->SetVolume(m_volumeBase);

    //pour affcher un message de début dans la console
    homer::Engine::Get()->logger()->Log("!!!!!!!!!!!!!!!!!!!!!!!!!!!! Bienvenue dans ConsoleLogger !!!!!!!!!!!!!!!!!!!!!!!!!!!!");



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

    homer::Engine::Get()->input()->Update();

    //Controle de la souris
    int _mouseX = 0;
    int _mouseY = 0;
    homer::Engine::Get()->input()->GetMousePosition(&_mouseX, &_mouseY);

    if (homer::Engine::Get()->input()->IsButtonDown(1)) { 
        m_x = _mouseX - 50;
        m_y = _mouseY - 50;
    }

}

void homer::Engine::Update(float dt) {
    //monde
    m_world->Update(dt);
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
    homer::Engine::Get()->gfx()->Clear();

    //monde
    m_world->Draw();

    //present
    homer::Engine::Get()->gfx()->Present();
}

void homer::Engine::Shutdown() {

    delete m_world;
    m_world = NULL;

    homer::Engine::Get()->gfx()->Shutdown();
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
