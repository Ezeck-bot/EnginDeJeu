#include "SDLAudio.h"
#include "SDL_Mixer.h"


void SDLAudio::Init()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void SDLAudio::Shutdown()
{
    Mix_HaltMusic();
    //détruit les audios alloué dans la vram sinon fuite de mémoire
    for (auto& _pair : m_musicCache)
    {
        Mix_FreeMusic(_pair.second);
    }
    m_musicCache.clear();

    //font
    for (auto& _pair : m_soundCache)
    {
        Mix_FreeChunk(_pair.second);
    }
    m_soundCache.clear();

    Mix_CloseAudio();

}

//load
size_t SDLAudio::LoadMusic(const std::string& filename)
{
    const size_t _musicId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map le retourne l'id
    if (m_musicCache.count(_musicId) > 0)
    {
        return _musicId;
    }


    Mix_Music* _music = Mix_LoadMUS(filename.c_str());
    if (_music != NULL)
    {
        m_musicCache[_musicId] = _music;

        return _musicId;
    }

    return static_cast<size_t>(-1);
}

size_t SDLAudio::LoadSound(const std::string& filename)
{
    const size_t _soundId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map 'le retourne l'id
    if (m_soundCache.count(_soundId) > 0 )
    {
        return _soundId;
    }


    Mix_Chunk* _sound = Mix_LoadWAV(filename.c_str());
    if (_sound != NULL)
    {
        m_soundCache[_soundId] = _sound;

        return _soundId;
    }

    return static_cast<size_t>(-1);
}


//music
void SDLAudio::PlayMusic(size_t id)
{
    if (m_musicCache.count(id) == 0) {
        return;
    }

    Mix_PlayMusic(m_musicCache[id], -1);
}

void SDLAudio::PlayMusic(size_t id, int loop)
{

    if (m_musicCache.count(id) == 0) {
        return;
    }

    //-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total
    Mix_PlayMusic(m_musicCache[id], loop);
}


//sfx
void SDLAudio::PlaySFX(size_t id)
{
    if (m_soundCache.count(id) == 0) {
        return;
    }

    //-1 il prend le premier canal libre trouvé
    Mix_PlayChannel(-1, m_soundCache[id], 0);
}

void SDLAudio::PlaySFX(size_t id, int loop)
{
    if (m_soundCache.count(id) == 0) {
        return;
    }

    //-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total
    Mix_PlayChannel(-1, m_soundCache[id], loop);
}

//Buuton
void SDLAudio::PauseMusic()
{
    Mix_PauseMusic();
}

void SDLAudio::StopMusic()
{
    Mix_HaltMusic();
}

void SDLAudio::ResumeMusic()
{
    Mix_ResumeMusic();
}

//Volume
void SDLAudio::SetVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void SDLAudio::SetVolume(size_t soundId, int volume)
{
    if (m_soundCache.count(soundId) == 0) {
        return;
    }

    Mix_VolumeChunk(m_soundCache[soundId], volume);
}
