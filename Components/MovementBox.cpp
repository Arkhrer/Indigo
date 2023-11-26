#include "MovementBox.h"
#include "MovementBound.h"
#include "Indigo.h"
#include <iostream>

MovementBox::MovementBox(GameObject& associated, Vec2 scale, Vec2 offset): Collider(associated, scale, offset){

}

MovementBox::~MovementBox(){

}

void MovementBox::Start(){

}

bool MovementBox::Is(std::string type){
    if (type.compare("MovementBox") == 0 || type.compare("Collider") == 0){
        return true;
    }
    else{
        return false;
    }
}

void MovementBox::NotifyCollision(GameObject &other){
    MovementBound* movementBound = (MovementBound*)(other.GetComponent("MovementBound"));
    if(movementBound != nullptr){
        std::cout << "colidindo" << std::endl;

        std::cout << 1;
        Indigo::player->CancelMovement();
    }
}
