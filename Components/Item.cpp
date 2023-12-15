#include "Item.h"
#include "../Sprite.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../GameData.h"
#include "Inventory.h"
#include "Indigo.h"
#include "../Camera.h"
#include "../Collider.h"
#include "InteractionZone.h"
#include <iostream>

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
    Collider* itemCollider = new Collider(associated);
    associated.AddComponent(dynamic_cast<Component*>(itemCollider));
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
                    GameData::stateVariables[ID] = true;
                    Inventory::inventory->AddItem(this->ID);
                    Indigo::player->Interact();
                    associated.RequestDelete();
                }
            }
            else{
                GameData::stateVariables[ID] = true;
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
    InteractionZone* interactionZone = (InteractionZone*)(other.GetComponent("InteractionZone"));
    if(interactionZone != nullptr){
        if(ID == 97){
            if(interactionZone->GetID() == 95){

                if((!inMap) && (!attached) && InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
                    GameData::stateVariables[10] = true;
                    Inventory::inventory->RemoveItem(ID);
                    associated.RequestDelete();
                }
            }
        }
        if(ID == 31){
            if(interactionZone->GetID() == 40){
                if((!inMap) && InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
                    GameData::stateVariables[11] = true;
                    Inventory::inventory->RemoveItem(ID);
                }
            }
        }
        if(ID == 23){
            if(interactionZone->GetID() == 42){
                if((!inMap) && InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
                    GameData::stateVariables[24] = true;
                    Inventory::inventory->RemoveItem(ID);
                }
            }
        }
    }

}

bool Item::Attached(){
    return attached;
}

int Item::GetID(){
    return ID;
}
