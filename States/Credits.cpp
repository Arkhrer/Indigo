#include "Credits.h"
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


Credits::Credits(): State(){
    this->currentFrame = 0;
    this->lastFrame = 0;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/Black.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

}

Credits::~Credits(){

}

void Credits::LoadAssets(){

}

void Credits::Update(float dt){
    lastFrame = currentFrame;

    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
        ++currentFrame;
    }

    if(currentFrame > 8){
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
        Game::GetInstance().music.Stop();
    }
    else{
        if(currentFrame != lastFrame){
            GameObject* newImageGo = new GameObject;
            std::string directory = "Assets/Images/Credits/";
            directory.append(std::to_string(currentFrame));
            directory.append(".png");
            Sprite* newImage = new Sprite(*newImageGo, directory);
            newImage->SetScaleX(0.15, 0.15);
            newImageGo->AddComponent(dynamic_cast<Component*>(newImage));
            AddObject(newImageGo);
            switch(currentFrame){
            case 1:
                newImageGo->box.x = 0;
                newImageGo->box.y = 100;
                break;
            case 2:
                newImageGo->box.x = 200;
                newImageGo->box.y = 100;
                break;
            case 3:
                newImageGo->box.x = 400;
                newImageGo->box.y = 100;
                break;
            case 4:
                newImageGo->box.x = 600;
                newImageGo->box.y = 100;
                break;
            case 5:
                newImageGo->box.x = 800;
                newImageGo->box.y = 100;
                break;
            case 6:
                newImageGo->box.x = 1000;
                newImageGo->box.y = 100;
                break;
            case 7:
                newImageGo->box.x = 1200;
                newImageGo->box.y = 100;
                break;
            case 8:
                newImageGo->box.x = 600;
                newImageGo->box.y = 400;
                newImage->SetScaleX(0.2, 0.2);
                break;
            }
        }
    }

    UpdateArray(dt);

}

void Credits::Render(){
    RenderArray();
}

void Credits::Start(){

    Game::GetInstance().music.Open("Assets/Musics/CreditsMusic.mp3");
    Game::GetInstance().music.Play();
    StartArray();
}

void Credits::Pause(){

}

void Credits::Resume(){

}
