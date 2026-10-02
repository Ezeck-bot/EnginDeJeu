#pragma once
#include <time.h>
#include "IGfx.h"
#include "IInput.h"
#include "ILogger.h"
#include "IAudio.h"

struct SDL_Window;
struct SDL_Renderer;
class SDLInput;
class SDLIGfx;
class ConsoleLogger;
class FileLogger;
class SDLAudio;

namespace homer {
	//empecher que la classe engin soit herite avec le mot cle final
	class Engine final {
	
	public:
		//le rendre singleton
		static Engine* Get() {
			static Engine* eng = nullptr;
			if (eng == nullptr)
			{
				eng = new Engine();
			}
			return eng;
		}

		//en c++ l avantage est que on peut donner acces a diffrentes fonction
		
		bool Init(const char* title, int w, int h);

		//la fonction de la fonction start est commencer la boucle de jeu
		void Start();

		//mes servives de ma facade Engine
		IGfx* Gfx() { return m_gfx; };
		IInput* Input() { return m_input; };
		ILogger* LoggerF() { return m_logger; };
		IAudio* Audio() { return m_audio; };
	private:
		//ici on gere la gestion de la detection des message

		void ProcessInput();
		void Update(float dt);

		//je l'utilise pour gérer facilement mes fps. Une autre personne devra mettre juste le nombre de fps il voudra.
		//j'ai ajouter start ici pour que le temps qui est initialiser dans engine.cpp soit le même partout
		void SetTargetFPS(int fps, clock_t start);
		void Render();
		void Shutdown();
		void Exit();

	private:
		IGfx* m_gfx;
		IInput* m_input;
		ILogger* m_logger;
		IAudio* m_audio;
		bool m_IsRunning = false;
		bool m_IsInit = false;

		//sauvegarde état
		size_t m_textureId = 0;
		size_t m_musicId = 0;
		size_t m_soundId = 0;

		//pour connaître l'orientation du player
		Flip m_flip{ false, false };
		size_t m_fontId = 0;
		

		int m_volumeBase = 100;
		int m_currentVolume;

	protected:
		friend class SDLInput;

	};
}