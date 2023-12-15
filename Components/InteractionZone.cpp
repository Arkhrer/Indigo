#include "InteractionZone.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../GameData.h"
#include "Indigo.h"
#include "Inventory.h"
#include "../Camera.h"
#include "../States/EndingCutscene.h"

InteractionZone::InteractionZone(GameObject& associated, int ID): Component(associated){
    this->ID = ID;

}

InteractionZone::~InteractionZone(){

}

void InteractionZone::Start(){

}

void InteractionZone::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            GameData::stateVariables[ID] = true;
            switch(ID){
            case 97:
                Inventory::inventory->AddItem(this->ID);
                associated.RequestDelete();
                break;
            case 31:
                Inventory::inventory->AddItem(this->ID);
                associated.RequestDelete();
                break;
            case 23:
                Inventory::inventory->AddItem(this->ID);
                associated.RequestDelete();
                break;
            case 77:
                Game::GetInstance().GetCurrentState().RequestPop();
                Game::GetInstance().Push(new EndingCutscene());
                break;
            }
        }
    }
}

void InteractionZone::Render(){

}

bool InteractionZone::Is(std::string type){
    if (type.compare("InteractionZone") == 0){
        return true;
    }
    else{
        return false;
    }
}

void InteractionZone::NotifyCollision(GameObject &other){

}

int InteractionZone::GetID(){
    return ID;
}
