
#include "Engine.h"
#include "../includes/Menu.h"
#include "../includes/Niveau1.h"
#ifdef _WIN32

#ifdef _DEBUG
#include "vld.h"
#endif // DEBUG


#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT) {
#else

int main(int argc, char** argv) {
#endif
	homer::Engine* eng = homer::Engine::Get();

	//passe les paramètres de la fenetres
	eng->Init("Battle City", 800, 600);

	//enregistrer les scenes
	eng->WorlD()->Register("Menu", new Menu());
	eng->WorlD()->Register("Menu", new Niveau1());

	// Charger la scène de départ
	eng->WorlD()->Load("Menu");


	//lance le jeu
	eng->Start();

	delete eng;
	return 0;
}