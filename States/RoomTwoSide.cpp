#include <algorithm>
#include <iostream>
#include "RoomTwoSide.h"
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

RoomTwoSide::RoomTwoSide(): State(){
    this->justChanged = false;

    this->states[0] = GameData::stateVariables[31];

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);

    Sprite* img;

    if(!(GameData::stateVariables[31])){
        img = new Sprite(*backgroundGo, "Assets/Images/Room2/Side/Side1.png");
    }
    else{
        img = new Sprite(*backgroundGo, "Assets/Images/Room2/Side/Side2.png");
    }
    img->SetScaleX(3.0, 3.0);

    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    backgroundGo->box.x = 0 + Camera::pos.x;
    backgroundGo->box.y = 0 + Camera::pos.y;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    GameObject* backArrowGo = new GameObject();
    AddObject(backArrowGo);
    BackArrow* backArrow = new BackArrow(*backArrowGo);
    backArrowGo->AddComponent(dynamic_cast<Component*>(backArrow));
    backArrowGo->box.x = 1300 + Camera::pos.x;
    backArrowGo->box.y = 670 + Camera::pos.y;
    Collider* backArrowCollider = new Collider(*backArrowGo);
    backArrowGo->AddComponent(dynamic_cast<Component*>(backArrowCollider));
}

RoomTwoSide::~RoomTwoSide(){

}

void RoomTwoSide::LoadAssets(){

}

void RoomTwoSide::Update(float dt){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(this->states[0] != GameData::stateVariables[31]){
        justChanged = true;
    }
    this->states[0] = GameData::stateVariables[31];

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

void RoomTwoSide::Render(){

    if(justChanged){
        GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
        Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
        if(!(GameData::stateVariables[31])){
            backgroundImg->Open("Assets/Images/Room2/Side/Side1.png");
        }else{
            backgroundImg->Open("Assets/Images/Room2/Side/Side2.png");
        }

        justChanged = false;
    }
    RenderArray();
    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Render();
    }
}

void RoomTwoSide::Start(){

    if(!(GameData::stateVariables[31])){
        SpawnBox();
    }

    StartArray();
    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Render();
    }
}

void RoomTwoSide::Pause(){

}

void RoomTwoSide::Resume(){

}


void RoomTwoSide::SpawnBox(){
    GameObject* boxInteractionZoneGo = new GameObject();
    InteractionZone* boxInteractionZone = new InteractionZone(*boxInteractionZoneGo, 31);
    boxInteractionZoneGo->AddComponent(dynamic_cast<Component*>(boxInteractionZone));
    Collider* boxInteractionZoneCollider = new Collider(*boxInteractionZoneGo);
    boxInteractionZoneGo->AddComponent(dynamic_cast<Component*>(boxInteractionZoneCollider));
    AddObject(boxInteractionZoneGo);

    boxInteractionZoneGo->box.w = 168;
    boxInteractionZoneGo->box.h = 123;
    boxInteractionZoneGo->box.x = 636 + Camera::pos.x;
    boxInteractionZoneGo->box.y = 284 + Camera::pos.y;
}
