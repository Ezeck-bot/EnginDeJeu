
#include "Engine.h"
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
	eng->Init("Battle City", 800, 600);
	eng->Start();

	return 0;
}