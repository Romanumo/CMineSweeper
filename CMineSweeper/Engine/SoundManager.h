#pragma once
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <unordered_map>

class SoundManager {
public:
    static SoundManager& GetInstance() {
        static SoundManager instance;
        return instance;
    }

    static void OpenAudio()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
        }
    }

    bool LoadMusic(const std::string& name, const std::string& path) 
    {
        auto music = Mix_LoadMUS(path.c_str());
        if (!music) return false;
        musicTracks[name] = music;
        return true;
    }

    bool LoadSFX(const std::string& name, const std::string& path) 
    {
        auto sound = Mix_LoadWAV(path.c_str());
        if (!sound) return false;
        soundEffects[name] = sound;
        return true;
    }

    void PlayMusic(const std::string& name, int loops = -1) 
    {
        if (currentMusic) Mix_HaltMusic();
        currentMusic = musicTracks[name];
        if (currentMusic) Mix_PlayMusic(currentMusic, loops);
    }

    void PlaySFX(const std::string& name) 
    {
        Mix_PlayChannel(-1, soundEffects[name], 0);
    }

    void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }
    void SetSFXVolume(int volume) { Mix_Volume(-1, volume); }

    ~SoundManager() {
        for (auto& [_, music] : musicTracks) Mix_FreeMusic(music);
        for (auto& [_, sfx] : soundEffects) Mix_FreeChunk(sfx);
        Mix_CloseAudio();
    }

private:
    SoundManager() { Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); }
    std::unordered_map<std::string, Mix_Music*> musicTracks;
    std::unordered_map<std::string, Mix_Chunk*> soundEffects;
    Mix_Music* currentMusic = nullptr;
};
