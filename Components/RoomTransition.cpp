#include "RoomTransition.h"

RoomTransition::RoomTransition(GameObject& associated, int targetRoom, Vec2 scale, Vec2 offset): Collider(associated, scale, offset){
    this->targetRoom = targetRoom;
}

RoomTransition::~RoomTransition(){

}

void RoomTransition::Start(){

}

bool RoomTransition::Is(std::string type){
    if (type.compare("RoomTransition") == 0 || type.compare("Collider") == 0){
        return true;
    }
    else{
        return false;
    }
}

void RoomTransition::NotifyCollision(GameObject &other){

}

int RoomTransition::GetTargetRoom(){
    return targetRoom;
}
