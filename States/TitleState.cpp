#include "TitleState.h"
#include "../Text.h"
#include "../Game.h"
#include "../Sprite.h"
#include "../InputManager.h"
#include "FirstRoom.h"
#include "SecondRoom.h"
#include "ThirdRoom.h"
#include "Corridor.h"
#include "../Background.h"
#include "../GameData.h"
#include "StartingCutscene.h"

#include <cstdlib>

#define ACTIVE_COLOR SDL_Color {255, 255, 0, 255}
#define INACTIVE_COLOR SDL_Color {255, 255, 255, 255}
#define SHADOW_COLOR SDL_Color {0, 0, 0, 255}

TitleState::TitleState(){

    //Background initialization

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/MainMenu/MenuBg.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = 0;
    backgroundGo->box.y = 0;
    Background* background = new Background(*backgroundGo);
    backgroundGo->AddComponent(dynamic_cast<Component*>(background));

    //Text initialization

    option = 0;

    GameObject* startGo = new GameObject();
    Sprite* startButton = new Sprite(*startGo, "Assets/Images/HUD/Button.png");
    startGo->AddComponent(dynamic_cast<Component*>(startButton));
    startButton->SetScaleX(3.0, 3.0);
    Text* startShadowText = new Text(*startGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Novo jogo", SHADOW_COLOR);
    Text* startText = new Text(*startGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Novo jogo", INACTIVE_COLOR);
    startButton->Open("Assets/Images/HUD/Button.png");
    startGo->AddComponent(startShadowText);
    startGo->AddComponent(startText);
    AddObject(startGo);
    startGo->box.x = SCREEN_WIDTH * 1/2 - startGo->box.w / 2;
    startGo->box.y = SCREEN_HEIGHT * 7/10 - startGo->box.y / 2;

    Vec2 startTextSize = startText->GetSize();
    startText->SetOffset((startGo->box.w - startTextSize.x) / 2, (startGo->box.h - startTextSize.y) / 2);
    startShadowText->SetOffset((startGo->box.w - startTextSize.x) / 2 + 1, (startGo->box.h - startTextSize.y) / 2 + 1);

    GameObject* exitGo = new GameObject();
    Sprite* exitButton = new Sprite(*exitGo, "Assets/Images/HUD/Button.png");
    exitGo->AddComponent(dynamic_cast<Component*>(exitButton));
    exitButton->SetScaleX(3.0, 3.0);
    Text* exitShadowText = new Text(*exitGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Sair", SHADOW_COLOR);
    Text* exitText = new Text(*exitGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Sair", INACTIVE_COLOR);
    exitButton->Open("Assets/Images/HUD/Button.png");
    exitGo->AddComponent(exitShadowText);
    exitGo->AddComponent(exitText);
    AddObject(exitGo);
    exitGo->box.x = SCREEN_WIDTH * 1/2 - exitGo->box.w / 2;
    exitGo->box.y = SCREEN_HEIGHT * 8/10 - exitGo->box.y / 2;

    Vec2 exitTextSize = exitText->GetSize();
    exitText->SetOffset((exitGo->box.w - exitTextSize.x) / 2, (exitGo->box.h - exitTextSize.y) / 2);
    exitShadowText->SetOffset((exitGo->box.w - exitTextSize.x) / 2 + 1, (exitGo->box.h - exitTextSize.y) / 2 + 1);
}

TitleState::~TitleState(){

}

void TitleState::LoadAssets(){

}

void TitleState::Update(float dt){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
        option = option - 1;
        if (option == -1){
            option = 1;
        }
    }

    if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
        option = (option + 1) % 2;
    }

    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
        switch(option){
        case 0:
            GameData::Initialize();
            popRequested = true;
            // Game::GetInstance().Push(new FirstRoom(350, 500));
            // Game::GetInstance().Push(new SecondRoom(350, 500));
            // Game::GetInstance().Push(new Corridor(350, 500));
            // Game::GetInstance().Push(new ThirdRoom(350, 500));
            Game::GetInstance().Push(new StartingCutscene());
            break;
        case 1:
            quitRequested = true;
            break;
        }
    }

    UpdateArray(dt);
}

void TitleState::Render(){
    Text* text = nullptr;
    for(int i = 0; i < objectArray.size(); ++i){
        text = (Text*)(objectArray[i]->GetComponent("Text"));
        if(text != nullptr){
            if(text->GetText() == "Novo jogo"){
                if (option == 0){
                    text->SetColor(ACTIVE_COLOR);
                }
                else{
                    text->SetColor(INACTIVE_COLOR);
                }
            }
            if(text->GetText() == "Sair"){
                if (option == 1){
                    text->SetColor(ACTIVE_COLOR);
                }
                else{
                    text->SetColor(INACTIVE_COLOR);
                }
            }
        }
    }
    RenderArray();
}

void TitleState::Start(){
    StartArray();
}

void TitleState::Pause(){

}

void TitleState::Resume(){

}
