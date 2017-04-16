#include "Music.hpp"

Music::Music(std::string filePath)
{
    _music = Mix_LoadMUS(filePath.c_str());
    _sound = Mix_LoadWAV(filePath.c_str());
}

Music::~Music()
{
    Mix_FreeMusic(_music);
    _music = NULL;
    Mix_FreeChunk(_sound);
    _sound = NULL;
}

void Music::playMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(_music, -1);
    }
}

void Music::pauseMusic()
{
    if (Mix_PlayingMusic() == 1)
    {
        Mix_PauseMusic();
    }
}

void Music::endMusic()
{
    if (Mix_PlayingMusic() == 1)
    {
        Mix_HaltMusic();
    }
}

void Music::playSound()
{
    Mix_PlayChannel(-1, _sound, 0);
}

