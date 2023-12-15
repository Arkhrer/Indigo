#include "SubSceneTrigger.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../Sprite.h"
#include "../States/RoomOneDesk.h"
#include "../States/RoomTwoSide.h"
#include "../States/RoomThreeFuseBox.h"
#include "../States/RoomThreeSink.h"
#include "../Camera.h"

SubSceneTrigger::SubSceneTrigger(GameObject& associated): Component(associated){
    this->option = 0;
}

SubSceneTrigger::~SubSceneTrigger(){

}

void SubSceneTrigger::Start(){

}

void SubSceneTrigger::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            switch(option){
            case 0:
                Game::GetInstance().Push(new RoomOneDesk());
                break;
            case 1:
                Game::GetInstance().Push(new RoomTwoSide());
                break;
            case 2:
                Game::GetInstance().Push(new RoomThreeFuseBox());
                break;
            case 3:
                Game::GetInstance().Push(new RoomThreeSink());
                break;
            }

        }
    }
}

void SubSceneTrigger::Render(){

}

bool SubSceneTrigger::Is(std::string type){
    if (type.compare("SubSceneTrigger") == 0){
        return true;
    }
    else{
        return false;
    }
}

void SubSceneTrigger::NotifyCollision(GameObject &other){

}

void SubSceneTrigger::SetOption(int newOption){
    this->option = newOption;
}
