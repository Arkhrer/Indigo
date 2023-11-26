#include "MovementBound.h"

MovementBound::MovementBound(GameObject& associated, Vec2 scale, Vec2 offset): Collider(associated, scale, offset){

}

MovementBound::~MovementBound(){

}

void MovementBound::Start(){

}

bool MovementBound::Is(std::string type){
    if (type.compare("MovementBound") == 0 || type.compare("Collider") == 0){
        return true;
    }
    else{
        return false;
    }
}

void MovementBound::NotifyCollision(GameObject &other){

}
