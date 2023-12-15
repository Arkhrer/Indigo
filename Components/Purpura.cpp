#include "Purpura.h"
#include "../Sprite.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../States/SecondDialogue.h"
#include "../GameData.h"
#include "../Camera.h"

Purpura::Purpura(GameObject& associated): Component(associated){
    associated.AddComponent(dynamic_cast<Component*>(new Sprite(associated, "Assets/Images/Purpura/PurpuraStandingSheet.png", 5, 1.5/8.0)));
}

Purpura::~Purpura(){

}

void Purpura::Start(){

}

void Purpura::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && !(GameData::stateVariables[99])){
        if(associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            GameData::stateVariables[99] = true;
            Game::GetInstance().Push(new SecondDialogue());
        }
    }
}

void Purpura::Render(){

}

bool Purpura::Is(std::string type){
    if (type.compare("Purpura") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Purpura::NotifyCollision(GameObject &other){

}
