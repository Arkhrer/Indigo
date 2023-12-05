#include "PauseMenu.h"
#include "../Camera.h"
#include "../Game.h"
#include "../InputManager.h"

PauseMenu::PauseMenu(){
    option = 0;

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/PauseMenu/Option1.png");
    this->backgroundImage = img;
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(0.5, 0.5);
    backgroundGo->box.x = (SCREEN_WIDTH - backgroundGo->box.w) / 2 + Camera::pos.x;
    backgroundGo->box.y = (SCREEN_HEIGHT - backgroundGo->box.h) / 2 + Camera::pos.y;


}

PauseMenu::~PauseMenu(){

}

void PauseMenu::LoadAssets(){

}

void PauseMenu::Update(float dt){
    lastFrameOption = option;

    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }

    if(option < 4){
        if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
            option = (option - 1) % 3;
            if(option == -1){
                option = 2;
            }
        }

        if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
            option = (option + 1) % 3;
        }
    }

    if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
        if(option < 3){
            option = 4;
        }
        else{
            --option;
            if(option == 2){
                option = 0;
            }
        }
    }

    if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
        if(option < 3){
            option = 3;
        }
        else{
            ++option;
            if(option == 5){
                option = 0;
            }
        }
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

    UpdateArray(dt);
}

void PauseMenu::Render(){
    if(lastFrameOption != option){
        switch(option){
        case 0:
            backgroundImage->Open("Assets/Images/PauseMenu/Option1.png");
            break;
        case 1:
            backgroundImage->Open("Assets/Images/PauseMenu/Option2.png");
            break;
        case 2:
            backgroundImage->Open("Assets/Images/PauseMenu/Option3.png");
            break;
        case 3:
            backgroundImage->Open("Assets/Images/PauseMenu/Option4.png");
            break;
        case 4:
            backgroundImage->Open("Assets/Images/PauseMenu/Option5.png");
            break;
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
