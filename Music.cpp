#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Music.h"
#include "Resources.h"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

void Music::Play(int times){
    if (music != nullptr){
        Mix_PlayMusic(music.get(), times);
    }
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
    music = Resources::GetMusic(file);
}

bool Music::IsOpen(){
    if (music != nullptr){
        return true;
    }
    else{
        return false;
    }
}

Music::~Music(){
    Stop(0);
}
