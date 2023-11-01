#include "Indigo.h"
#include "../Sprite.h"
#include "../InputManager.h"

Indigo::Indigo(GameObject& associated): Component(associated), interactingTimer(){
    player = this;
    associated.AddComponent(dynamic_cast<Component*>(new Sprite(associated, "Assets/Images/IndigoStandingSheet.png", 8, 1.5/8.0)));
    lastSpeed = 0;
    interacting = false;

}

Indigo::~Indigo(){
    player = nullptr;
}

void Indigo::Start(){

}

void Indigo::Update(float dt){
    if(interacting == false){

        int directionalSpeed = 250 * dt * (InputManager::GetInstance().IsKeyDown(D_KEY) - InputManager::GetInstance().IsKeyDown(A_KEY));
        associated.box.x += directionalSpeed;
        if(directionalSpeed != 0){
            if(lastSpeed == 0){
                Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
                sprite->SetFrameCount(5);
                sprite->Open("Assets/Images/IndigoRunningSheet.png");
            }

            if(directionalSpeed < 0){
                if(!(associated.flip)){
                    associated.flip = !associated.flip;
                }
            }else if(directionalSpeed > 0){
                if(associated.flip){
                    associated.flip = !associated.flip;
                }
            }
        }
        else{
            if(lastSpeed != 0){
                Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
                sprite->SetFrameCount(8);
                sprite->Open("Assets/Images/IndigoStandingSheet.png");
            }
        }
        lastSpeed = directionalSpeed;

        if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
            Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
            sprite->SetFrameCount(5);
            sprite->Open("Assets/Images/IndigoInteractingSheet.png");
            interacting = true;
            interactingTimer.Restart();
        }
    }
    else{
        interactingTimer.Update(dt);
        if(interactingTimer.Get() >= 5 * (1.5/8.0)){
            interacting = false;
            Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
            sprite->SetFrameCount(8);
            sprite->Open("Assets/Images/IndigoStandingSheet.png");
        }
    }
}

void Indigo::Render(){

}

bool Indigo::Is(std::string type){
    if (type.compare("Indigo") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Indigo::NotifyCollision(GameObject &other){

}
