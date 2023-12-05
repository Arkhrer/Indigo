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
#define SCALE 3.0 * 8/10
#define PI 3.14159265358979323846

SecondRoom::SecondRoom(int x, int y): State(){

    //Background initialization

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Room2Bg.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    //Character initialization

    GameObject* indigoGo = new GameObject();
    Indigo* indigo = new Indigo(*indigoGo);
    indigoGo->AddComponent(dynamic_cast<Component*>(indigo));
    AddObject(indigoGo);

    Sprite* indigoSprite = (Sprite*)(indigoGo->GetComponent("Sprite"));
    indigoSprite->SetScaleX(SCALE, SCALE);
    MovementBox* indigoCollider = (MovementBox*)(indigoGo->GetComponent("MovementBox"));
    indigoCollider->SetOffset(Vec2(0.0, (indigoGo->box.h) * (1 - 0.17)  / 2));
    indigoGo->box.x = x;
    indigoGo->box.y = y;

    Camera::Follow(indigoGo);
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
    StartArray();
}

void SecondRoom::Pause(){

}

void SecondRoom::Resume(){

}
