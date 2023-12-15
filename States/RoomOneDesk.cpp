#include <algorithm>
#include <iostream>
#include "RoomOneDesk.h"
#include "../Components/Indigo.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Sprite.h"
#include "../Camera.h"
#include "SecondDialogue.h"
#include "../Components/Item.h"
#include "../Components/MovementBox.h"
#include "../Components/MovementBound.h"
#include "../Collision.h"
#include "../Components/RoomTransition.h"
#include "../Background.h"
#include "../GameData.h"
#include "../Components/BackArrow.h"
#include "PauseMenu.h"
#include "../Components/InteractionZone.h"
#include "../Components/Inventory.h"

#define PI 3.14159265358979323846

RoomOneDesk::RoomOneDesk(): State(){
    this->justChanged = false;

    this->states[0] = GameData::stateVariables[98];
    this->states[1] = GameData::stateVariables[97];
    this->states[2] = GameData::stateVariables[96];

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);

    Sprite* img;

    if(!(GameData::stateVariables[98])){
        img = new Sprite(*backgroundGo, "Assets/Images/Room1/Desk/Desk1.png");
    }
    else{
        if(!(GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
            img = new Sprite(*backgroundGo, "Assets/Images/Room1/Desk/Desk2.png");
        }
        else if((GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
            img = new Sprite(*backgroundGo, "Assets/Images/Room1/Desk/Desk3.png");

        }else if(!(GameData::stateVariables[97]) && (GameData::stateVariables[96])){
            img = new Sprite(*backgroundGo, "Assets/Images/Room1/Desk/Desk4.png");

        }else{
            img = new Sprite(*backgroundGo, "Assets/Images/Room1/Desk/Desk5.png");
        }
    }
    img->SetScaleX(0.75, 0.75);

    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    GameObject* backArrowGo = new GameObject();
    AddObject(backArrowGo);
    BackArrow* backArrow = new BackArrow(*backArrowGo);
    backArrowGo->AddComponent(dynamic_cast<Component*>(backArrow));
    backArrowGo->box.x = 1300;
    backArrowGo->box.y = 670;
    Collider* backArrowCollider = new Collider(*backArrowGo);
    backArrowGo->AddComponent(dynamic_cast<Component*>(backArrowCollider));
}

RoomOneDesk::~RoomOneDesk(){

}

void RoomOneDesk::LoadAssets(){

}

void RoomOneDesk::Update(float dt){
    if(this->states[0] != GameData::stateVariables[98] || this->states[1] != GameData::stateVariables[97] || this->states[2] != GameData::stateVariables[96]){
        justChanged = true;
        if(this->states[0] != GameData::stateVariables[98]){
            SpawnCable();

            SpawnDevice();
        }
    }

    this->states[0] = GameData::stateVariables[98];
    this->states[1] = GameData::stateVariables[97];
    this->states[2] = GameData::stateVariables[96];

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    bool tested[objectArray.size()][objectArray.size()];
    std::fill(*tested, *tested + objectArray.size() * objectArray.size(), false);

    for(int i = objectArray.size() - 1; i >= 0; --i) {
        Collider* collider = (Collider*)(objectArray[i]->GetComponent("Collider"));
        if(collider != nullptr){
            for (int j = objectArray.size() - 1; j >= 0; --j){
                Collider* colliderTarget = (Collider*)(objectArray[j]->GetComponent("Collider"));
                if((colliderTarget != nullptr) && (collider != colliderTarget) && (!tested[j][i])){
                    tested[i][j] = true;
                    tested[j][i] = true;
                    if(Collision::IsColliding(collider->box, colliderTarget->box, objectArray[i]->angleDeg * PI / 180.0, objectArray[j]->angleDeg * PI / 180.0)){
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
            for(int j = Inventory::inventory->items.size() - 1; j >= 0; --j){
                Collider* colliderTarget = (Collider*)(Inventory::inventory->items[j]->GetComponent("Collider"));
                if((colliderTarget != nullptr)){
                    if(Collision::IsColliding(collider->box, colliderTarget->box, objectArray[i]->angleDeg * PI / 180.0, objectArray[j]->angleDeg * PI / 180.0)){
                        objectArray[i]->NotifyCollision(*Inventory::inventory->items[j]);
                        Inventory::inventory->items[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
        }
    }

    UpdateArray(dt);

    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Update(dt);
    }

    for(int i = objectArray.size() - 1; i >= 0; --i) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void RoomOneDesk::Render(){
    if(justChanged){
        GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
        Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
        if(!(GameData::stateVariables[98])){
            backgroundImg->Open("Assets/Images/Room1/Desk/Desk1.png");
        }
        else{
            if(!(GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
                backgroundImg->Open("Assets/Images/Room1/Desk/Desk2.png");
            }
            else if((GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
                backgroundImg->Open("Assets/Images/Room1/Desk/Desk3.png");

            }else if(!(GameData::stateVariables[97]) && (GameData::stateVariables[96])){
                backgroundImg->Open("Assets/Images/Room1/Desk/Desk4.png");

            }else{
                backgroundImg->Open("Assets/Images/Room1/Desk/Desk5.png");
            }
        }
        justChanged = false;
    }

    RenderArray();
    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Render();
    }
}

void RoomOneDesk::Start(){

    if(!(GameData::stateVariables[98])){
        GameObject* drawerInteractionZoneGo = new GameObject();
        InteractionZone* drawerInteractionZone = new InteractionZone(*drawerInteractionZoneGo, 98);
        drawerInteractionZoneGo->AddComponent(dynamic_cast<Component*>(drawerInteractionZone));
        Collider* drawerInteractionZoneCollider = new Collider(*drawerInteractionZoneGo);
        drawerInteractionZoneGo->AddComponent(dynamic_cast<Component*>(drawerInteractionZoneCollider));
        AddObject(drawerInteractionZoneGo);

        drawerInteractionZoneGo->box.w = 340;
        drawerInteractionZoneGo->box.h = 150;
        drawerInteractionZoneGo->box.x = 673;
        drawerInteractionZoneGo->box.y = 675;
    }
    else{
        if(!(GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
            SpawnCable();

            SpawnDevice();
        }
        else if((GameData::stateVariables[97]) && !(GameData::stateVariables[96])){
            SpawnDevice();
        }else if(!(GameData::stateVariables[97]) && (GameData::stateVariables[96])){
            SpawnCable();
        }
    }

    StartArray();
}

void RoomOneDesk::Pause(){

}

void RoomOneDesk::Resume(){

}

void RoomOneDesk::SpawnCable(){
    GameObject* cableInteractionZoneGo = new GameObject();
    InteractionZone* cableInteractionZone = new InteractionZone(*cableInteractionZoneGo, 97);
    cableInteractionZoneGo->AddComponent(dynamic_cast<Component*>(cableInteractionZone));
    Collider* cableInteractionZoneCollider = new Collider(*cableInteractionZoneGo);
    cableInteractionZoneGo->AddComponent(dynamic_cast<Component*>(cableInteractionZoneCollider));
    AddObject(cableInteractionZoneGo);

    cableInteractionZoneGo->box.w = 135;
    cableInteractionZoneGo->box.h = 80;
    cableInteractionZoneGo->box.x = 720;
    cableInteractionZoneGo->box.y = 698;
}

void RoomOneDesk::SpawnDevice(){
    GameObject* deviceInteractionZoneGo = new GameObject();
    InteractionZone* deviceInteractionZone = new InteractionZone(*deviceInteractionZoneGo, 96);
    deviceInteractionZoneGo->AddComponent(dynamic_cast<Component*>(deviceInteractionZone));
    Collider* deviceInteractionZoneCollider = new Collider(*deviceInteractionZoneGo);
    deviceInteractionZoneGo->AddComponent(dynamic_cast<Component*>(deviceInteractionZoneCollider));
    AddObject(deviceInteractionZoneGo);

    deviceInteractionZoneGo->box.w = 125;
    deviceInteractionZoneGo->box.h = 74;
    deviceInteractionZoneGo->box.x = 858;
    deviceInteractionZoneGo->box.y = 707;
}
