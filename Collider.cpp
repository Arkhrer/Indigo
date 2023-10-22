#include "Collider.h"

#ifdef QT_QML_DEBUG
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Camera.h"
#include "Game.h"
#define PI 3.14159265358979323846
#endif // QT_QML_DEBUG

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset): Component(associated), scale(scale), offset(offset){

}

Collider::~Collider(){

}

void Collider::Update(float dt){
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;

    Vec2 rotatedOffset(offset.Rotate(associated.angleDeg));
    box.x = associated.box.x + (associated.box.w - box.w) / 2 + rotatedOffset.x;
    box.y = associated.box.y + (associated.box.h - box.h) / 2 + rotatedOffset.y;
}

void Collider::Render(){
#ifdef QT_QML_DEBUG
    Vec2 center( box.Center() );
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated.angleDeg/(180/PI) )
                 + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180/PI) )
            + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180/PI) )
            + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180/PI) )
            + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // QT_QML_DEBUG
}

bool Collider::Is(std::string type){
    if (type.compare("Collider") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Collider::SetScale(Vec2 scale){
    this->scale.x = scale.x;
    this->scale.y = scale.y;
}

void Collider::SetOffset(Vec2 offset){
    this->offset.x = offset.x;
    this->offset.y = offset.y;
}
