#include "SDLAudio.h"
#include "SDL_Mixer.h"


void SDLAudio::Init()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void SDLAudio::Shutdown()
{

    //détruit les texture alloué dans la vram sinon fuite de mémoire
    for (auto& _pair : m_musicMap)
    {
        Mix_FreeMusic(_pair.second);
    }
    m_musicMap.clear();

    //font
    for (auto& _pair : m_soundMap)
    {
        Mix_FreeChunk(_pair.second);
    }
    m_soundMap.clear();

    Mix_CloseAudio();

}

//load
size_t SDLAudio::LoadMusic(const std::string& filename)
{
    const size_t _musicId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map le retourne l'id
    if (m_musicMap.find(_musicId) != m_musicMap.end())
    {
        return _musicId;
    }


    Mix_Music* _music = Mix_LoadMUS(filename.c_str());
    if (_music != NULL)
    {
        m_musicMap[_musicId] = _music;

        return _musicId;
    }

    return static_cast<size_t>(-1);
}

size_t SDLAudio::LoadSound(const std::string& filename)
{
    const size_t _soundId = std::hash<std::string>()(filename);

    //si l'id est déjà dans ma map le retourne l'id
    if (m_soundMap.find(_soundId) != m_soundMap.end())
    {
        return _soundId;
    }


    Mix_Chunk* _sound = Mix_LoadWAV(filename.c_str());
    if (_sound != NULL)
    {
        m_soundMap[_soundId] = _sound;

        return _soundId;
    }

    return static_cast<size_t>(-1);
}


//music
void SDLAudio::PlayMusic(size_t id)
{
    if (m_musicMap.find(id) == m_musicMap.end()) {
        return;
    }

    Mix_PlayMusic(m_musicMap.find(id)->second, -1);
}

void SDLAudio::PlayMusic(size_t id, int loop)
{

    if (m_musicMap.find(id) == m_musicMap.end()) {
        return;
    }

    //-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total
    Mix_PlayMusic(m_musicMap.find(id)->second, loop);
}


//sfx
void SDLAudio::PlaySFX(size_t id)
{
    if (m_soundMap.find(id) == m_soundMap.end()) {
        return;
    }

    //-1 il prend le premier canal libre trouvé
    Mix_PlayChannel(-1, m_soundMap.find(id)->second, 0);
}

void SDLAudio::PlaySFX(size_t id, int loop)
{
    if (m_soundMap.find(id) == m_soundMap.end()) {
        return;
    }

    //-1 fait une loop, 0 joue que une fois, 1 joue deux fois au total
    Mix_PlayChannel(-1, m_soundMap.find(id)->second, loop);
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
}
