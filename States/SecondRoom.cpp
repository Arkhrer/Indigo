#include "SecondRoom.h"
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
#include "../Components/SubSceneTrigger.h"
#define SCALE 3.0 * 8/10
#define PI 3.14159265358979323846

SecondRoom::SecondRoom(int x, int y): State(){
    this->initialX = x;
    this->initialY = y;

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
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Room2/Room2Bg.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(0.75, 0.75);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    GameObject* roomTransitionGo = new GameObject();
    roomTransitionGo->box.w = 249;
    roomTransitionGo->box.h = 20;
    roomTransitionGo->box.x = 1044;
    roomTransitionGo->box.y = 634;
    RoomTransition* roomTransition = new RoomTransition(*roomTransitionGo, 4, Vec2(54, 428));
    roomTransitionGo->AddComponent(dynamic_cast<Component*>(roomTransition));
    AddObject(roomTransitionGo);

    GameObject* roomTransition2Go = new GameObject();
    roomTransition2Go->box.w = 20;
    roomTransition2Go->box.h = 300;
    roomTransition2Go->box.x = 150;
    roomTransition2Go->box.y = 630;
    RoomTransition* roomTransition2 = new RoomTransition(*roomTransition2Go, 1, Vec2(864, 417));
    roomTransition2Go->AddComponent(dynamic_cast<Component*>(roomTransition2));
    AddObject(roomTransition2Go);
    roomTransition2Go->angleDeg = 61.0;

    GameObject* subSceneTriggerGo = new GameObject();
    subSceneTriggerGo->box.w = 120;
    subSceneTriggerGo->box.h = 300;
    subSceneTriggerGo->box.x = 1710;
    subSceneTriggerGo->box.y = 320;
    SubSceneTrigger* subSceneTrigger = new SubSceneTrigger(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTrigger));
    Collider* subSceneTriggerCollider = new Collider(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTriggerCollider));
    AddObject(subSceneTriggerGo);
    subSceneTrigger->SetOption(1);
}

SecondRoom::~SecondRoom(){
    Camera::Unfollow();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void SecondRoom::LoadAssets(){

}

void SecondRoom::Update(float dt){
    Camera::Update(dt);

    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

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
        }
    }
}

void SecondRoom::Render(){
    RenderArray();
}

void SecondRoom::Start(){

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

void SecondRoom::Pause(){

}

void SecondRoom::Resume(){

}
