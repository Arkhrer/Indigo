#include "ThirdRoom.h"
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
#include "../Components/Purpura.h"
#include "../Components/SubSceneTrigger.h"
#define SCALE 3.0 * 8/10
#define PI 3.14159265358979323846

ThirdRoom::ThirdRoom(int x, int y): State(){
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
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Room3/Room3Bg.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    GameObject* roomTransitionGo = new GameObject();
    roomTransitionGo->box.w = 115;
    roomTransitionGo->box.h = 20;
    roomTransitionGo->box.x = 30;
    roomTransitionGo->box.y = 742;
    RoomTransition* roomTransition = new RoomTransition(*roomTransitionGo, 4, Vec2(980, 430));
    roomTransitionGo->AddComponent(dynamic_cast<Component*>(roomTransition));
    AddObject(roomTransitionGo);
    roomTransitionGo->angleDeg = -27.0;

    GameObject* subSceneTriggerGo = new GameObject();
    subSceneTriggerGo->box.w = 54;
    subSceneTriggerGo->box.h = 72;
    subSceneTriggerGo->box.x = 1116;
    subSceneTriggerGo->box.y = 429;
    SubSceneTrigger* subSceneTrigger = new SubSceneTrigger(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTrigger));
    Collider* subSceneTriggerCollider = new Collider(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTriggerCollider));
    AddObject(subSceneTriggerGo);
    subSceneTrigger->SetOption(2);

    GameObject* subSceneTrigger2Go = new GameObject();
    subSceneTrigger2Go->box.w = 135;
    subSceneTrigger2Go->box.h = 18;
    subSceneTrigger2Go->box.x = 387;
    subSceneTrigger2Go->box.y = 510;
    SubSceneTrigger* subSceneTrigger2 = new SubSceneTrigger(*subSceneTrigger2Go);
    subSceneTrigger2Go->AddComponent(dynamic_cast<Component*>(subSceneTrigger2));
    Collider* subSceneTrigger2Collider = new Collider(*subSceneTrigger2Go);
    subSceneTrigger2Go->AddComponent(dynamic_cast<Component*>(subSceneTrigger2Collider));
    AddObject(subSceneTrigger2Go);
    subSceneTrigger2->SetOption(3);
}

ThirdRoom::~ThirdRoom(){
    Camera::Unfollow();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void ThirdRoom::LoadAssets(){

}

void ThirdRoom::Update(float dt){
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

void ThirdRoom::Render(){
    RenderArray();
}

void ThirdRoom::Start(){

    //Purpura initialization

    GameObject* purpuraGo = new GameObject();
    Purpura* purpura = new Purpura(*purpuraGo);
    purpuraGo->AddComponent(dynamic_cast<Component*>(purpura));
    AddObject(purpuraGo);
    Sprite* purpuraSprite = (Sprite*)(purpuraGo->GetComponent("Sprite"));
    purpuraSprite->SetScaleX(SCALE, SCALE);

    purpuraGo->box.x = 540;
    purpuraGo->box.y = 500;

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

void ThirdRoom::Pause(){

}

void ThirdRoom::Resume(){

}
