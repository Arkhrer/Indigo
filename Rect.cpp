#include "Rect.h"

Rect::Rect(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Rect::AddVector(Vec2 v){
    x = x + v.x;
    y = y + v.y;
}

Vec2 Rect::Center(){
    return Vec2((x + (x + w))/2, (y + (y + h))/2);
}

float Rect::CenterDistance(Rect r){
    return Center().Distance(r.Center());
}

bool Rect::ContainsPoint(float x, float y){
    if (x >= this->x && x <= (this->x + w) && y >= this->y && y <= (this->y + h)){
        return true;
    }else{
        return false;
    }
}
