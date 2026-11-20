
#include "Engine.h"
#include "Menu.h"
#include "Niveau1.h"
#ifdef _WIN32

#ifdef _DEBUG
#include "vld.h"
#endif // DEBUG


#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>


static void InitGame()
{
	homer::Engine* eng = homer::Engine::Get();

	//passe les paramètres de la fenetres
	eng->Init("Battle City", 610, 600);

	//enregistrer les scenes
	eng->world()->Register("Menu", new Menu());
	eng->world()->Register("Niveau1", new Niveau1());

	// Charger la scène de départ
	eng->world()->Load("Menu");
}


INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT) {
#else

int main(int argc, char** argv) {
#endif

	InitGame();

	homer::Engine* eng = homer::Engine::Get();
	//lance le jeu
	eng->Start();

	delete eng;
	return 0;
}