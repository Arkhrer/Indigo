#include "Indigo.h"
#include "../Sprite.h"
#include "../InputManager.h"
#include "../Game.h"
// #include "../Collider.h"
#include "Inventory.h"
#include "MovementBox.h"
#include "../Camera.h"
#include "../States/PauseMenu.h"

Indigo::Indigo(GameObject& associated): Component(associated), interactingTimer(), lastSpeed(0.0,0.0), lastPosition(0.0, 0.0){
    player = this;
    associated.AddComponent(dynamic_cast<Component*>(new Sprite(associated, "Assets/Images/IndigoStandingSheet.png", 8, 1.5/8.0)));
    MovementBox* indigoCollider = new MovementBox(associated, Vec2(0.25, 0.17), Vec2(0.0, (associated.box.h) * (1 - 0.17)  / 2));
    associated.AddComponent(dynamic_cast<Component*>(indigoCollider));
    interacting = false;
    destination = nullptr;

}

Indigo::~Indigo(){
    player = nullptr;
}

void Indigo::Start(){
    GameObject* InventoryGo = new GameObject();
    Inventory* inventory = new Inventory(*InventoryGo);
    InventoryGo->AddComponent(dynamic_cast<Component*>(inventory));
    Game::GetInstance().GetCurrentState().AddObject(InventoryGo);
}

void Indigo::Update(float dt){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(interacting == false){
        if(InputManager::GetInstance().IsMouseDown(RIGHT_MOUSE_BUTTON)){
            if(destination != nullptr){
                delete destination;
            }
            destination = new Vec2(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        }

        Vec2 speed(0.0, 0.0);
        lastPosition.x = associated.box.x;
        lastPosition.y = associated.box.y;

        if (destination != nullptr){
            Vec2 movingPoint(associated.box.Center().x, associated.box.Center().y + ((associated.box.h) * (1 - 0.1) / 2));
            float angle = movingPoint.LineInclination(*destination);
            speed.x = 250.0 * dt;
            speed.SelfRotate(angle);

            if ((movingPoint - (*destination)).Magnitude() < speed.Magnitude()){
                associated.box.x = destination->x - (associated.box.w / 2);
                associated.box.y = destination->y - (associated.box.h) * (1 - 0.1/2);
                delete destination;
                destination = nullptr;
                speed.x = 0;
                speed.y = 0;
            }
            else{
                associated.box.AddVector(speed);
            }
        }

        if(speed.Magnitude() != 0){
            if(lastSpeed.Magnitude() == 0){
                Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
                sprite->SetFrameCount(5);
                sprite->Open("Assets/Images/IndigoRunningSheet.png");
            }

            if(speed.x < 0){
                if(!(associated.flip)){
                    associated.flip = !associated.flip;
                }
            }else if(speed.x > 0){
                if(associated.flip){
                    associated.flip = !associated.flip;
                }
            }
        }
        else{
            if(lastSpeed.Magnitude() != 0){
                Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
                sprite->SetFrameCount(8);
                sprite->Open("Assets/Images/IndigoStandingSheet.png");
            }
        }
        lastSpeed.x = speed.x;
        lastSpeed.y = speed.y;
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

void Indigo::Interact(){
    Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
    sprite->SetFrameCount(5);
    sprite->Open("Assets/Images/IndigoInteractingSheet.png");
    interacting = true;
    interactingTimer.Restart();
}

bool Indigo::IsInteracting(){
    return interacting;
}

void Indigo::CancelMovement(){
    // associated.box.x -= 2* lastSpeed.x;
    // associated.box.y -= 2* lastSpeed.y;
    associated.box.x -=  2 * (associated.box.x - lastPosition.x);
    associated.box.y -=  2 * (associated.box.y - lastPosition.y);
    // associated.box.y = lastPosition.y;
    delete destination;
    destination = nullptr;
}
