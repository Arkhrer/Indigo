#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Component.h"
#include "Timer.h"

class Sprite: public Component{
public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1.0, float secondsToSelfDestruct = 0.0);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    void Render();
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Update(float dt);
    bool Is(std::string type);
    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
private:
    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDestructCount;
    float secondsToSelfDestruct;
};

#endif // SPRITE_H
