#include <algorithm>
#include <iostream>
#include "EndingCutscene.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Sprite.h"
#include "../Camera.h"
#include "../Background.h"
#include "PauseMenu.h"
#include "TitleState.h"

EndingCutscene::EndingCutscene(){
    this->currentFrame = 0;
    this->lastFrame = 0;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Cutscenes/2/0.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));
}

EndingCutscene::~EndingCutscene(){

}

void EndingCutscene::LoadAssets(){

}

void EndingCutscene::Update(float dt){
    Camera::Update(dt);

    lastFrame = currentFrame;

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
        ++currentFrame;
    }

    if(currentFrame > 3){
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
    else{
        if(currentFrame != lastFrame){
            std::string directory = "Assets/Images/Cutscenes/2/";
            directory.append(std::to_string(currentFrame));
            directory.append(".png");
            GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
            Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
            backgroundImg->Open(directory);
        }
    }

    UpdateArray(dt);
}

void EndingCutscene::Render(){

    RenderArray();
}

void EndingCutscene::Start(){

    StartArray();
}

void EndingCutscene::Pause(){

}

void EndingCutscene::Resume(){

}
