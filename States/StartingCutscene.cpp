#include <algorithm>
#include <iostream>
#include "StartingCutscene.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Sprite.h"
#include "../Camera.h"
#include "../Background.h"
#include "PauseMenu.h"
#include "FirstRoom.h"
#include "ThirdRoom.h"
#include "EndingCutscene.h"

StartingCutscene::StartingCutscene(){
    this->currentFrame = 0;
    this->lastFrame = 0;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Cutscenes/1/0.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));
}

StartingCutscene::~StartingCutscene(){

}

void StartingCutscene::LoadAssets(){

}

void StartingCutscene::Update(float dt){
    Camera::Update(dt);

    lastFrame = currentFrame;

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
        ++currentFrame;
    }

    if(currentFrame > 4){
        popRequested = true;
        // Game::GetInstance().Push(new FirstRoom(433, 393));
        Game::GetInstance().Push(new ThirdRoom(35, 494));
        // Game::GetInstance().Push(new EndingCutscene());
    }else{
        if(currentFrame != lastFrame && currentFrame <= 4){
            std::string directory = "Assets/Images/Cutscenes/1/";
            directory.append(std::to_string(currentFrame));
            directory.append(".png");
            GameObject* backgroundGo = GetObjectContaining("Background").lock().get();
            Sprite* backgroundImg = (Sprite*)(backgroundGo->GetComponent("Sprite"));
            backgroundImg->Open(directory);
        }
    }

    UpdateArray(dt);
}

void StartingCutscene::Render(){

    RenderArray();
}

void StartingCutscene::Start(){

    StartArray();
}

void StartingCutscene::Pause(){

}

void StartingCutscene::Resume(){

}
