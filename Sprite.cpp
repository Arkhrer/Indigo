#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated), scale(1.0, 1.0){
    this->frameCount = 1;
    this->frameTime = 1.0;
    currentFrame = 0;
    timeElapsed = 0.0;
    secondsToSelfDestruct = 0.0;
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated), scale(1.0, 1.0), selfDestructCount(){
    texture = nullptr;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    currentFrame = 0;
    timeElapsed = 0.0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    Open(file);
}

Sprite::~Sprite(){

}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);

    // Vec2 oldScale(scale.x, scale.y);

    // SetScaleX(1.0, 1.0);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

    int frameWidth = width / frameCount;
    SetClip(0, 0, frameWidth, height);

    if(scale.x != 0.0){
        associated.box.w = frameWidth * scale.x;
    }
    else{
        associated.box.w = frameWidth;
    }

    if(scale.y != 0.0){
        associated.box.h = height * scale.y;
    }
    else{
        associated.box.h = height;
    }

   // SetScaleX(oldScale.x, oldScale.y);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_Rect dstRect;
    dstRect.x = x - Camera::pos.x;
    dstRect.y = y - Camera::pos.y;
    dstRect.w = clipRect.w * scale.x;
    dstRect.h = clipRect.h * scale.y;
    if(associated.flip){
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_HORIZONTAL);
    }
    else{
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

void Sprite::Render(){
    Render(associated.box.x, associated.box.y);
}

int Sprite::GetWidth(){
    return width * scale.x / frameCount;
}

int Sprite::GetHeight(){
    return height * scale.y;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    else{
        return false;
    }
}

void Sprite::Update(float dt){
    if(secondsToSelfDestruct > 0.0){
        selfDestructCount.Update(dt);

        if(selfDestructCount.Get() >= secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }

    if((timeElapsed+=dt) >= frameTime){
        if(++currentFrame >= frameCount){
            currentFrame = 0;
        }
        timeElapsed-= frameTime;
        clipRect.x = (width / frameCount) * (currentFrame);
    }
}

bool Sprite::Is(std::string type){
    if (type.compare("Sprite") == 0){
        return true;
    }
    else{
        return false;
    }
}


void Sprite::SetScaleX(float scaleX, float scaleY){
    if (scaleX != 0.0){
        associated.box.x += (associated.box.w/2);
        associated.box.w = (width / frameCount) * scaleX;
        scale.x = scaleX;
        associated.box.x -= (associated.box.w/2);
    }

    if (scaleY != 0.0){
        associated.box.y += (associated.box.h/2);
        associated.box.h = height * scaleY;
        scale.y = scaleY;
        associated.box.y -= (associated.box.h/2);
    }
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetFrame(int frame){
    currentFrame = frame % frameCount;
    clipRect.x = (width / frameCount) * (currentFrame);
}

void Sprite::SetFrameCount(int frameCount){
    this->frameCount = frameCount;
    currentFrame = 0;
    associated.box.w = (width / this->frameCount) * scale.x;
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;
}
