#include <algorithm>
#include <iostream>
#include "FirstRoom.h"
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
#include "../Components/SubSceneTrigger.h"

#define SCALE 3.0
#define PI 3.14159265358979323846

FirstRoom::FirstRoom(int x, int y): State(){
    this->initialX = x;
    this->initialY = y;

    GameObject* preBackgroundGo = new GameObject();
    AddObject(preBackgroundGo);
    Sprite* preBackground = new Sprite(*preBackgroundGo, "Assets/Images/Black.png");
    preBackgroundGo->AddComponent(dynamic_cast<Component*>(preBackground));
    preBackground->SetScaleX(2.0, 2.0);
    preBackgroundGo->box.x = 0;
    preBackgroundGo->box.y = 0;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Room1/Room1Bg.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(0.75, 0.75);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    // if(!(GameData::stateVariables[1])){
    //     GameObject* itemTesteGo = new GameObject();
    //     Item* itemTeste = new Item(*itemTesteGo, 1, true);
    //     itemTesteGo->AddComponent(dynamic_cast<Component*>(itemTeste));
    //     AddObject(itemTesteGo);
    //     itemTesteGo->box.x = 400 * SCALE;
    //     itemTesteGo->box.y = 200 * SCALE;
    // }

    //Setting movement bounds

    GameObject* testBoundGo0 = new GameObject();
    testBoundGo0->box.w = 1;
    testBoundGo0->box.h = 350;
    testBoundGo0->box.x = 1150;
    testBoundGo0->angleDeg = -45.0;
    testBoundGo0->box.y = SCREEN_HEIGHT - testBoundGo0->box.h + 40;
    MovementBound* testBound0 = new MovementBound(*testBoundGo0);
    testBoundGo0->AddComponent(dynamic_cast<Component*>(testBound0));
    AddObject(testBoundGo0);

    GameObject* testBoundGo1 = new GameObject();
    testBoundGo1->box.w = 550;
    testBoundGo1->box.h = 1;
    testBoundGo1->box.x = 550;
    testBoundGo1->box.y = 550;
    MovementBound* testBound1 = new MovementBound(*testBoundGo1);
    testBoundGo1->AddComponent(dynamic_cast<Component*>(testBound1));
    AddObject(testBoundGo1);

    GameObject* testBoundGo2 = new GameObject();
    testBoundGo2->box.w = 500;
    testBoundGo2->box.h = 1;
    testBoundGo2->box.x = 125;
    testBoundGo2->box.y = 650;
    testBoundGo2->angleDeg = -27.0;
    MovementBound* testBound2 = new MovementBound(*testBoundGo2);
    testBoundGo2->AddComponent(dynamic_cast<Component*>(testBound2));
    AddObject(testBoundGo2);

    GameObject* roomTransitionGo = new GameObject();
    roomTransitionGo->box.w = 1000;
    roomTransitionGo->box.h = 20;
    roomTransitionGo->box.x = 200;
    roomTransitionGo->box.y = 800;
    RoomTransition* roomTransition = new RoomTransition(*roomTransitionGo, 2, Vec2(136, 506));
    roomTransitionGo->AddComponent(dynamic_cast<Component*>(roomTransition));
    AddObject(roomTransitionGo);

    GameObject* subSceneTriggerGo = new GameObject();
    subSceneTriggerGo->box.w = 350;
    subSceneTriggerGo->box.h = 200;
    subSceneTriggerGo->box.x = 0;
    subSceneTriggerGo->box.y = 340;
    SubSceneTrigger* subSceneTrigger = new SubSceneTrigger(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTrigger));
    Collider* subSceneTriggerCollider = new Collider(*subSceneTriggerGo);
    subSceneTriggerGo->AddComponent(dynamic_cast<Component*>(subSceneTriggerCollider));
    AddObject(subSceneTriggerGo);
}

FirstRoom::~FirstRoom(){
    Camera::Unfollow();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void FirstRoom::LoadAssets(){

}

void FirstRoom::Update(float dt){


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

void FirstRoom::Render(){
    RenderArray();
}

void FirstRoom::Start(){

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

void FirstRoom::Pause(){

}

void FirstRoom::Resume(){

}
