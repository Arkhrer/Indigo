#include "Corridor.h"
#include <algorithm>
#include <iostream>
#include "../Components/Indigo.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Sprite.h"
#include "../Components/Inventory.h"
#include "../Components/Item.h"
#include "../Components/MovementBox.h"
#include "../Components/MovementBound.h"
#include "../Collision.h"
#include "../Components/RoomTransition.h"
#include "../CameraFollower.h"
#include "../Camera.h"
#include "../Background.h"
#include "../GameData.h"
#include "../Components/InteractionZone.h"
#define SCALE 3.0
#define PI 3.14159265358979323846

Corridor::Corridor(int x, int y): State() {
    this->initialX = x;
    this->initialY = y;
    this->lastFrame = 0;
    this->currentFrame = 0;
    this->timer.Restart();
    this->reversed = false;
    this->activated = true;
    this->lastBoxed = GameData::stateVariables[11];
    this->justOpened = false;

    GameObject* preBackgroundGo = new GameObject();
    AddObject(preBackgroundGo);
    Sprite* preBackground = new Sprite(*preBackgroundGo, "Assets/Images/Black.png");
    preBackgroundGo->AddComponent(dynamic_cast<Component*>(preBackground));
    preBackground->SetScaleX(2.0, 2.0);
    preBackgroundGo->box.x = 0;
    preBackgroundGo->box.y = 0;

    //Background initialization

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img;
    if(GameData::stateVariables[11]){
        img = new Sprite(*backgroundGo, "Assets/Images/Corridor/Box.png");
    }
    else{
        img = new Sprite(*backgroundGo, "Assets/Images/Corridor/0.png");
    }
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(0.75, 0.75);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    if(GameData::stateVariables[11]){
        GameObject* roomTransitionGo = new GameObject();
        roomTransitionGo->box.w = 145;
        roomTransitionGo->box.h = 20;
        roomTransitionGo->box.x = 1248;
        roomTransitionGo->box.y = 735;
        RoomTransition* roomTransition = new RoomTransition(*roomTransitionGo, 3, Vec2(35, 494));
        roomTransitionGo->AddComponent(dynamic_cast<Component*>(roomTransition));
        AddObject(roomTransitionGo);
        roomTransitionGo->angleDeg = 17.0;
    }

    GameObject* roomTransition2Go = new GameObject();
    roomTransition2Go->box.w = 115;
    roomTransition2Go->box.h = 20;
    roomTransition2Go->box.x = 68;
    roomTransition2Go->box.y = 738;
    RoomTransition* roomTransition2 = new RoomTransition(*roomTransition2Go, 2, Vec2(1003, 425));
    roomTransition2Go->AddComponent(dynamic_cast<Component*>(roomTransition2));
    AddObject(roomTransition2Go);
    roomTransition2Go->angleDeg = -17.0;

    SpawnBoxZone();
}

Corridor::~Corridor(){
    Camera::Unfollow();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void Corridor::LoadAssets(){

}

void Corridor::Update(float dt){
    Camera::Update(dt);

    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    lastFrame=currentFrame;

    UpdateArray(dt);

    for(int i = objectArray.size() - 1; i >= 0; --i) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
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
            if(currentFrame == 7 && !(GameData::stateVariables[11])){
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
    }

    if(!(GameData::stateVariables[11])){
        if(activated){
            timer.Update(dt);
            if(timer.Get() >= 1.5){
                if(!reversed){
                    ++currentFrame;
                    if(currentFrame == 7){
                        reversed = true;
                    }
                    timer.Restart();
                }
                else{
                    --currentFrame;
                    if(currentFrame == 0){
                        reversed = false;
                        // activated = false;
                    }
                    timer.Restart();
                }
            }
        }
    }else{
        if(lastBoxed != GameData::stateVariables[11]){
            GameObject* roomTransitionGo = new GameObject();
            roomTransitionGo->box.w = 145;
            roomTransitionGo->box.h = 20;
            roomTransitionGo->box.x = 1248;
            roomTransitionGo->box.y = 735;
            RoomTransition* roomTransition = new RoomTransition(*roomTransitionGo, 3, Vec2(35, 494));
            roomTransitionGo->AddComponent(dynamic_cast<Component*>(roomTransition));
            AddObject(roomTransitionGo);
            roomTransitionGo->angleDeg = 17.0;

            justOpened = true;
        }
    }
    lastBoxed = GameData::stateVariables[11];
}

void Corridor::Render(){
    if(justOpened){
        GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
        Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
        std::string directory = "Assets/Images/Corridor/Box.png";

        backgroundImg->Open(directory);
        justOpened = false;
    }else{
        if(currentFrame != lastFrame){
            GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
            Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
            std::string directory = "Assets/Images/Corridor/";
            directory.append(std::to_string(currentFrame));
            directory.append(".png");

            backgroundImg->Open(directory);
        }
    }

    RenderArray();
}

void Corridor::Start(){

    //Character initialization

    GameObject* indigoGo = new GameObject();
    Indigo* indigo = new Indigo(*indigoGo);
    indigoGo->AddComponent(dynamic_cast<Component*>(indigo));
    AddObject(indigoGo);

    Sprite* indigoSprite = (Sprite*)(indigoGo->GetComponent("Sprite"));
    indigoSprite->SetScaleX(SCALE, SCALE);
    MovementBox* indigoCollider = (MovementBox*)(indigoGo->GetComponent("MovementBox"));
    indigoCollider->SetOffset(Vec2(0.0, (indigoGo->box.h) * (1 - 0.17)  / 2));
    indigoGo->box.x = initialX;
    indigoGo->box.y = initialY;

    Camera::Follow(indigoGo);

    StartArray();
}

void Corridor::Pause(){

}

void Corridor::Resume(){

}


void Corridor::SpawnBoxZone(){
    GameObject* BoxInteractionZoneGo = new GameObject();
    InteractionZone* BoxInteractionZone = new InteractionZone(*BoxInteractionZoneGo, 40);
    BoxInteractionZoneGo->AddComponent(dynamic_cast<Component*>(BoxInteractionZone));
    Collider* BoxInteractionZoneCollider = new Collider(*BoxInteractionZoneGo);
    BoxInteractionZoneGo->AddComponent(dynamic_cast<Component*>(BoxInteractionZoneCollider));
    AddObject(BoxInteractionZoneGo);

    BoxInteractionZoneGo->box.w = 84;
    BoxInteractionZoneGo->box.h = 574;
    BoxInteractionZoneGo->box.x = 1297;
    BoxInteractionZoneGo->box.y = 162;
}
