#include "BackArrow.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../Sprite.h"
#include <iostream>
#include "../Camera.h"

BackArrow::BackArrow(GameObject& associated): Component(associated){
    Sprite* arrowSprite = new Sprite(associated, "Assets/Images/HUD/Arrow.png");
    // arrowSprite->SetScaleX(1/100, 1/100);
    associated.AddComponent(dynamic_cast<Component*>(arrowSprite));

}

BackArrow::~BackArrow(){

}

void BackArrow::Start(){

}

void BackArrow::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            std::cout << "ok" << std::endl;
            Game::GetInstance().GetCurrentState().RequestPop();
        }
    }
}

void BackArrow::Render(){

}

bool BackArrow::Is(std::string type){
    if (type.compare("BackArrow") == 0){
        return true;
    }
    else{
        return false;
    }
}

void BackArrow::NotifyCollision(GameObject &other){

}
