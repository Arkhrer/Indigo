#include <algorithm>
#include <iostream>
#include "RoomThreeFuseBox.h"
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

RoomThreeFuseBox::RoomThreeFuseBox(): State(){
    this->justChanged = false;
    this->states[0] = GameData::stateVariables[21];
    this->states[0] = GameData::stateVariables[24];

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);

    Sprite* img;

    if(!(GameData::stateVariables[21])){
        img = new Sprite(*backgroundGo, "Assets/Images/Room3/FuseBox/1.png");
    }else if(!(GameData::stateVariables[24])){
        img = new Sprite(*backgroundGo, "Assets/Images/Room3/FuseBox/2.png");
    }else{
        img = new Sprite(*backgroundGo, "Assets/Images/Room3/FuseBox/3.png");
    }
    img->SetScaleX(0.75, 0.75);

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

RoomThreeFuseBox::~RoomThreeFuseBox(){

}

void RoomThreeFuseBox::LoadAssets(){

}

void RoomThreeFuseBox::Update(float dt){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(this->states[0] != GameData::stateVariables[21] || this->states[1] != GameData::stateVariables[24]){
        justChanged = true;
        if(this->states[1] == GameData::stateVariables[24]) {
            SpawnFuse();
        }
    }
    this->states[0] = GameData::stateVariables[21];
    this->states[1] = GameData::stateVariables[24];

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

void RoomThreeFuseBox::Render(){

    if(justChanged){
        GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
        Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));

        if(!(GameData::stateVariables[21])){
            backgroundImg->Open("Assets/Images/Room3/FuseBox/1.png");
        }else if(!(GameData::stateVariables[24])){
            backgroundImg->Open("Assets/Images/Room3/FuseBox/2.png");
        }else{
            backgroundImg->Open("Assets/Images/Room3/FuseBox/3.png");
        }

        justChanged = false;
    }

    RenderArray();

    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Render();
    }
}

void RoomThreeFuseBox::Start(){

    if(!(GameData::stateVariables[21])){
        SpawnLid();
    }else if(!(GameData::stateVariables[24])){
        SpawnFuse();
    }

    StartArray();
    if(Inventory::inventory != nullptr){
        Inventory::inventory->openAssociated.Render();
    }
}

void RoomThreeFuseBox::Pause(){

}

void RoomThreeFuseBox::Resume(){

}

void RoomThreeFuseBox::SpawnLid(){
    GameObject* lidInteractionZoneGo = new GameObject();
    InteractionZone* lidInteractionZone = new InteractionZone(*lidInteractionZoneGo, 21);
    lidInteractionZoneGo->AddComponent(dynamic_cast<Component*>(lidInteractionZone));
    Collider* lidInteractionZoneCollider = new Collider(*lidInteractionZoneGo);
    lidInteractionZoneGo->AddComponent(dynamic_cast<Component*>(lidInteractionZoneCollider));
    AddObject(lidInteractionZoneGo);

    lidInteractionZoneGo->box.w = 440;
    lidInteractionZoneGo->box.h = 626;
    lidInteractionZoneGo->box.x = 505 + Camera::pos.x;
    lidInteractionZoneGo->box.y = 87 + Camera::pos.y;
}

void RoomThreeFuseBox::SpawnFuse(){
    GameObject* fuseInteractionZoneGo = new GameObject();
    InteractionZone* fuseInteractionZone = new InteractionZone(*fuseInteractionZoneGo, 42);
    fuseInteractionZoneGo->AddComponent(dynamic_cast<Component*>(fuseInteractionZone));
    Collider* fuseInteractionZoneCollider = new Collider(*fuseInteractionZoneGo);
    fuseInteractionZoneGo->AddComponent(dynamic_cast<Component*>(fuseInteractionZoneCollider));
    AddObject(fuseInteractionZoneGo);

    fuseInteractionZoneGo->box.w = 39;
    fuseInteractionZoneGo->box.h = 104;
    fuseInteractionZoneGo->box.x = 672 + Camera::pos.x;
    fuseInteractionZoneGo->box.y = 234 + Camera::pos.y;
}
