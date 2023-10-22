#include "TitleState.h"
#include "../Components/Indigo.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Sprite.h"
#include "../Collider.h"

TitleState::TitleState(): State(){

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/IndigoLabBackground.jpg");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;

    GameObject* indigoGo = new GameObject();
    Indigo* indigo = new Indigo(*indigoGo);
    indigoGo->AddComponent(dynamic_cast<Component*>(indigo));
    AddObject(indigoGo);
    Sprite* indigoSprite = (Sprite*)(indigoGo->GetComponent("Sprite"));
    Collider* indigoCollider = new Collider(*indigoGo, Vec2(0.5, 1.0));
    indigoGo->AddComponent(dynamic_cast<Component*>(indigoCollider));

    indigoSprite->SetScaleX(3.0, 3.0);
    indigoGo->box.x = (480 * 3 - indigoGo->box.w) / 2 - 100;
    indigoGo->box.y = 270 * 3 - indigoGo->box.h - 25;
}

TitleState::~TitleState(){

}

void TitleState::LoadAssets(){

}

void TitleState::Update(float dt){

    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }

    UpdateArray(dt);
}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    StartArray();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
