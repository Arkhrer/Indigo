#include "MovementBox.h"
#include "MovementBound.h"
#include "Indigo.h"
#include "RoomTransition.h"
#include <iostream>
#include "../Game.h"
#include "../States/SecondRoom.h"

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
        Indigo::player->CancelMovement();
    }
    RoomTransition* roomTransition = (RoomTransition*)(other.GetComponent("RoomTransition"));
    if(roomTransition != nullptr){
        std::cout << "transição de sala" << std::endl;
        switch(roomTransition->GetTargetRoom()){
        case 0:
            // TITULO
            break;
        case 1:
            // SALA 1
            break;
        case 2:
            // SALA 2
            Game::GetInstance().GetCurrentState().RequestPop();

            Game::GetInstance().Push(new SecondRoom());
            break;
        case 3:
            // SALA 3
            break;
        }
    }
}
