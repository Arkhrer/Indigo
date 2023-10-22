#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <memory>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music{
public:
    Music();
    Music(std::string);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string);
    bool IsOpen();
private:
    std::shared_ptr<Mix_Music> music;
};

#endif // MUSIC_H
