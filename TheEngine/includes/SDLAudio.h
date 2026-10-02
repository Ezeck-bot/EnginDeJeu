#pragma once
#include "IAudio.h"
#include <map>

struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

class SDLAudio final : public IAudio {
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	virtual size_t LoadMusic(const std::string& filename) override;
	virtual size_t LoadSound(const std::string& filename) override;
	virtual void PlayMusic(size_t id) override;
	virtual void PlayMusic(size_t id, int loop) override;
	virtual void PlaySFX(size_t id) override;
	virtual void PlaySFX(size_t id, int loop) override;
	virtual void PauseMusic() override;
	virtual void StopMusic() override;
	virtual void ResumeMusic() override;
	virtual void SetVolume(int volume) override;
	virtual void SetVolume(size_t soundId, int volume) override;

	//destructeur
	virtual ~SDLAudio() = default;
private:
	std::map<size_t, Mix_Music*> m_musicCache;
	std::map<size_t, Mix_Chunk*> m_soundCache;
};