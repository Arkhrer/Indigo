#include "Item.h"
#include "../Sprite.h"
#include "../InputManager.h"
#include "../Game.h"
#include "Inventory.h"
#include "Indigo.h"
#include "../Camera.h"

Item::Item(GameObject &associated, int ID, bool inMap): Component(associated){
    this->ID = ID;
    this->inMap = inMap;
    attached = !inMap;
    std::string directory = "Assets/Images/Items/";
    directory.append(std::to_string(ID));
    directory.append(".png");
    Sprite* itemSprite = new Sprite(associated, directory);
    associated.AddComponent(dynamic_cast<Component*>(itemSprite));
    itemSprite->SetScaleX(2.5,2.5);
}

Item::~Item(){

}

void Item::Start(){

}

void Item::Update(float dt){
    if(!inMap){
        if(attached && InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            attached = false;
        }

        if((!attached) && InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
            attached = true;
        }
    }
    else{
        if(Inventory::inventory != nullptr && InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && associated.box.ContainsPoint(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            if(Indigo::player != nullptr){
                if(!(Indigo::player->IsInteracting())){
                    Inventory::inventory->AddItem(this->ID);
                    Indigo::player->Interact();
                    associated.RequestDelete();
                }
            }
            else{
                Inventory::inventory->AddItem(this->ID);
                Indigo::player->Interact();
                associated.RequestDelete();
            }
        }
    }
}

void Item::Render(){
    if(!attached && !inMap){
        associated.box.x = InputManager::GetInstance().GetMouseX() - associated.box.w / 2 + Camera::pos.x;
        associated.box.y = InputManager::GetInstance().GetMouseY() - associated.box.h / 2 + Camera::pos.y;
    }
}

bool Item::Is(std::string type){
    if (type.compare("Item") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Item::NotifyCollision(GameObject &other){

}

bool Item::Attached(){
    return attached;
}

int Item::GetID(){
    return ID;
}
