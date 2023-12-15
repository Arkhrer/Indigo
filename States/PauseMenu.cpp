#include "PauseMenu.h"
#include "../Camera.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../Text.h"

#define ACTIVE_COLOR SDL_Color {255, 255, 0, 255}
#define INACTIVE_COLOR SDL_Color {255, 255, 255, 255}
#define SHADOW_COLOR SDL_Color {0, 0, 0, 255}

PauseMenu::PauseMenu(){
    option = 0;
    map = false;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/HUD/PauseMenu/Menu1.png");
    this->backgroundImage = img;
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(0.5, 0.5);
    backgroundGo->box.x = (SCREEN_WIDTH - backgroundGo->box.w) / 2 + Camera::pos.x;
    backgroundGo->box.y = (SCREEN_HEIGHT - backgroundGo->box.h) / 2 + Camera::pos.y;

    GameObject* textGo = new GameObject();
    Text* text3 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Sair", INACTIVE_COLOR);
    text3->SetOffset(645.0, 481.0);
    Text* text1 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Resumir", INACTIVE_COLOR);
    text1->SetOffset(645.0, 275.0);
    Text* text2 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Registros", INACTIVE_COLOR);
    text2->SetOffset(645.0, 378.0);
    textGo->AddComponent(dynamic_cast<Component*>(text3));
    textGo->AddComponent(dynamic_cast<Component*>(text1));
    textGo->AddComponent(dynamic_cast<Component*>(text2));

    AddObject(textGo);

}

PauseMenu::~PauseMenu(){

}

void PauseMenu::LoadAssets(){

}

void PauseMenu::Update(float dt){
    lastFrameOption = option;
    lastFrameMap = map;

    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) || InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
        map = !map;
    }

    if(!map){
        if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
            option = (option - 1) % 3;
            if(option == -1){
                option = 2;
            }
        }

        if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
            option = (option + 1) % 3;
        }

        if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
            switch(option){
            case 0:
                popRequested = true;
                break;
            case 1:
                break;
            case 2:
                quitRequested = true;
                break;
            }
        }
    }


    if(map){
        if(lastFrameMap != map){
            Text* text = nullptr;
            for(int i = 0; i < objectArray.size(); ++i){
                text = (Text*)(objectArray[i]->GetComponent("Text"));
                if(text != nullptr){
                    objectArray[i]->RequestDelete();
                }
            }
        }
    }
    else{
        if(lastFrameMap != map){
            GameObject* textGo = new GameObject();
            Text* text3 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Sair", INACTIVE_COLOR);
            text3->SetOffset(645.0, 481.0);
            Text* text1 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Resumir", INACTIVE_COLOR);
            text1->SetOffset(645.0, 275.0);
            Text* text2 = new Text(*textGo, "Assets/font/pixela-extreme.ttf", 28, Text::SOLID, "Registros", INACTIVE_COLOR);
            text2->SetOffset(645.0, 378.0);
            textGo->AddComponent(dynamic_cast<Component*>(text3));
            textGo->AddComponent(dynamic_cast<Component*>(text1));
            textGo->AddComponent(dynamic_cast<Component*>(text2));

            AddObject(textGo);
        }
    }

    UpdateArray(dt);

    for(int i = objectArray.size() - 1; i >= 0; --i) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void PauseMenu::Render(){
    if(map){
        if(lastFrameMap != map){
            backgroundImage->Open("Assets/Images/HUD/PauseMenu/Map.png");
        }
    }
    else{
        if(lastFrameOption != option || lastFrameMap != map){
            switch(option){
            case 0:
                backgroundImage->Open("Assets/Images/HUD/PauseMenu/Menu1.png");
                break;
            case 1:
                backgroundImage->Open("Assets/Images/HUD/PauseMenu/Menu2.png");
                break;
            case 2:
                backgroundImage->Open("Assets/Images/HUD/PauseMenu/Menu3.png");
                break;
            }
        }
    }
    RenderArray();
}

void PauseMenu::Start(){
    StartArray();
}

void PauseMenu::Pause(){

}

void PauseMenu::Resume(){

}
