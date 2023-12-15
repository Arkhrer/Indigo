#include "Inventory.h"
#include "../Sprite.h"
#include "../Camera.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../GameData.h"
#include "Item.h"


Inventory::Inventory(GameObject &associated): Component(associated), openAssociated(associated){
    inventory = this;
    visible = false;
    Sprite* inventoryHUD = new Sprite(associated, "Assets/Images/HUD/InventoryHUD.png");
    associated.AddComponent(dynamic_cast<Component*>(inventoryHUD));
    inventoryHUD->SetScaleX(3.0, 3.0);

    associated.box.x = Camera::pos.x + (SCREEN_WIDTH - associated.box.w) / 2;
    associated.box.y = Camera::pos.y - associated.box.h;

    for(int i = 0; i < GameData::posessedItems.size(); ++i){

        GameObject* itemTesteGo = new GameObject();
        Item* itemTeste = new Item(*itemTesteGo, GameData::posessedItems.at(i));
        items.push_back(std::shared_ptr<GameObject>(itemTesteGo));
        itemTesteGo->AddComponent(dynamic_cast<Component*>(itemTeste));
    }

    // associated.box.x = (SCREEN_WIDTH - associated.box.w) / 2;
    // associated.box.y = (SCREEN_HEIGHT - associated.box.h) * 99 / 100;
}

Inventory::~Inventory(){
    inventory = nullptr;
}

void Inventory::Start(){
    for(unsigned int i = 0; i < items.size(); ++i){
        items.at(i)->Start();
    }
}

void Inventory::Update(float dt){
    inventory = this;

    if(InputManager::GetInstance().KeyPress(I_KEY)){
        if (visible){
            visible = false;
            // associated.box.y = Camera::pos.y - associated.box.h;
        }
        else{
            visible = true;
        }
    }

    float animSpeed = 1000.0 * dt;

    if (visible){
        if(associated.box.y < Camera::pos.y){
            if((Camera::pos.y - associated.box.y) < animSpeed){
                associated.box.y = Camera::pos.y;
            }
            else{
                associated.box.y += animSpeed;
            }
        }
    }
    else{
        if(associated.box.y > Camera::pos.y - associated.box.h){
            if((associated.box.y - (Camera::pos.y - associated.box.h)) < animSpeed){
                associated.box.y = Camera::pos.y - associated.box.h;
            }
            else{
                associated.box.y -= animSpeed;
            }
        }
    }

    for(unsigned int i = 0; i < items.size(); ++i){
        if(((Item*)(items.at(i)->GetComponent("Item")))->Attached()){
            items.at(i)->box.x = associated.box.x + (i * 47 + 2) * 3.0 + 5;
            items.at(i)->box.y = associated.box.y + 10;
        }
        items.at(i)->Update(dt);
    }
}

void Inventory::Render(){
    associated.box.x = Camera::pos.x + (SCREEN_WIDTH - associated.box.w) / 2;

    for(unsigned int i = 0; i < items.size(); ++i){
        items.at(i)->Render();
    }
}

bool Inventory::Is(std::string type){
    if (type.compare("Inventory") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Inventory::NotifyCollision(GameObject &other){
}

void Inventory::AddItem(int ID){
    GameData::posessedItems.emplace_back(ID);
    GameObject* itemTesteGo = new GameObject();
    Item* itemTeste = new Item(*itemTesteGo, ID);
    items.push_back(std::shared_ptr<GameObject>(itemTesteGo));
    itemTesteGo->AddComponent(dynamic_cast<Component*>(itemTeste));
}

void Inventory::RemoveItem(int ID){
    for(int i = 0; i < GameData::posessedItems.size(); ++i){
        if (ID == GameData::posessedItems.at(i)){
            GameData::posessedItems.erase(GameData::posessedItems.begin() + i);
            break;
        }
    }


    for(int i = 0; i < items.size(); ++i){
        if (ID == ((Item*)(items.at(i)->GetComponent("Item")))->GetID()){
            items.erase(items.begin() + i);
            break;
        }
    }
}
