#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated): Component(associated){
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file): Sound(associated){
    Open(file);
}

Sound::~Sound(){
    if(chunk != nullptr){
//        Stop();
    }
}

void Sound::Play(int times){
    if(chunk != nullptr){
        channel = Mix_PlayChannel(-1, chunk.get(), times - 1);
    }
}

void Sound::Stop(){
    if(chunk != nullptr){
        if(Mix_Playing(channel) != 0){
            Mix_HaltChannel(channel);
        }
    }
}

void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){
    if (chunk != nullptr){
        return true;
    }
    else{
        return false;
    }
}

void Sound::Update(float dt){

}

void Sound::Render(){

}

bool Sound::Is(std::string type){
    if (type.compare("Sound") == 0){
        return true;
    }
    else{
        return false;
    }
}
