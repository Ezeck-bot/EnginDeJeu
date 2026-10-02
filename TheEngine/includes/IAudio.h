#pragma once
#include <string>

class IAudio {
public:
	virtual ~IAudio() = default;

	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	//charger la music à jouer dans dans un cache
	virtual size_t LoadMusic(const std::string& filename) = 0;

	//charger le sfx à jouer dans dans un cache
	virtual size_t LoadSound(const std::string& filename) = 0;

	//se charge de jouer la music en arrière plan ajouter dans le cache
	virtual void PlayMusic(size_t id) = 0;

	//joue la misuque mais avec une option de loop (-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total)
	virtual void PlayMusic(size_t id, int loop) = 0;

	//se charge de jouer un SFX, un son en dehors de la musique ajouter dans le cache
	virtual void PlaySFX(size_t id) = 0;

	//se charge de jouer le SFX mais avec une loop (-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total)
	virtual void PlaySFX(size_t id, int loop) = 0;

	//Mettre pause à la musique
	virtual void PauseMusic() = 0;

	//Arrêter la musique tout court
	virtual void StopMusic() = 0;

	//Reprendre une musique si elle est en pause
	virtual void ResumeMusic() = 0;

	//pour ajuster le volume
	virtual void SetVolume(int volume) = 0;

	//modifie le volume d'une musique precise
	virtual void SetVolume(size_t soundId, int volume) = 0;
};