#include "SecondDialogue.h"
#include "../Sprite.h"
#include "../Camera.h"
#include "../InputManager.h"
#include "PauseMenu.h"
#include "../Game.h"
#include "../Text.h"
#include <iostream>

#define TEXT_COLOR SDL_Color {255, 255, 0, 255}
#define SHADOW_COLOR SDL_Color {0, 0, 0, 255}

SecondDialogue::SecondDialogue(){
    this->currentFile.open("Assets/Dialogues/2/0.txt");
    if(currentFile.is_open()){
        std::getline(this->currentFile, line);
        // std::cout << line << std::endl;
    }
    else{
        exit(61);
    }

    this->currentFrame = 0;
    this->lastFrame = 0;
    this->lineCurrentSize = 0;
    this->showingLine = " ";

    GameObject* backgroundGo = new GameObject();
    AddObject(backgroundGo);
    Sprite* img = new Sprite(*backgroundGo, "Assets/Images/HUD/Dialogue.png");
    backgroundGo->AddComponent(dynamic_cast<Component*>(img));
    img->SetScaleX(3.0, 3.0);
    backgroundGo->box.x = Camera::pos.x;
    backgroundGo->box.y = Camera::pos.y + 50;

    GameObject* indigoBigGo = new GameObject();
    AddObject(indigoBigGo);
    Sprite* indigoBig = new Sprite(*indigoBigGo, "Assets/Images/Indigo/IndigoLarge.png");
    indigoBigGo->AddComponent(dynamic_cast<Component*>(indigoBig));
    indigoBig->SetScaleX(1.8, 1.8);
    indigoBigGo->box.x = Camera::pos.x + 100;
    indigoBigGo->box.y = Camera::pos.y - 49 + 50;

    GameObject* PurpuraBigGo = new GameObject();
    AddObject(PurpuraBigGo);
    Sprite* PurpuraBig = new Sprite(*PurpuraBigGo, "Assets/Images/Purpura/PurpuraLarge.png");
    PurpuraBigGo->AddComponent(dynamic_cast<Component*>(PurpuraBig));
    PurpuraBig->SetScaleX(0.1, 0.1);
    PurpuraBigGo->box.x = Camera::pos.x + 900;
    PurpuraBigGo->box.y = Camera::pos.y + 50 + 2;
    PurpuraBigGo->flip = true;

    GameObject* textGo = new GameObject();
    Text* text = new Text(*textGo, "Assets/font/_decterm.ttf", 28, Text::SOLID, showingLine, TEXT_COLOR);
    textGo->AddComponent(text);
    AddObject(textGo);

    // textGo->box.x = Camera::pos.x;
    // textGo->box.y = Camera::pos.y;

    textGo->box.x = Camera::pos.x + 150;
    textGo->box.y = Camera::pos.y + 450 + 50;

}

SecondDialogue::~SecondDialogue(){
    this->currentFile.close();
}

void SecondDialogue::LoadAssets(){

}

void SecondDialogue::Update(float dt){
    // Camera::Update(dt);

    lastFrame = currentFrame;

    if(showingLine.size() <= line.size()){
        showingLine = showingLine + line[lineCurrentSize];
        ++lineCurrentSize;

        GameObject* textGo = GetObjectContaining("Text").lock().get();
        Text* text = (Text*)(textGo->GetComponent("Text"));
        text->SetText(showingLine);
    }

    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        Game::GetInstance().Push(new PauseMenu());
    }

    if(InputManager::GetInstance().KeyPress(SPACE_BAR) || InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        ++currentFrame;
    }

    if(currentFrame > 12){
        popRequested = true;
    }else{
        if(currentFrame != lastFrame && currentFrame <= 12){
            if(currentFile.is_open()){
                this->currentFile.close();
            }

            std::string directory = "Assets/Dialogues/2/";
            directory.append(std::to_string(currentFrame));
            directory.append(".txt");
            this->currentFile.open(directory);

            if(currentFile.is_open()){
                std::getline(this->currentFile, line);

                GameObject* textGo = GetObjectContaining("Text").lock().get();
                Text* text = (Text*)(textGo->GetComponent("Text"));
                this->showingLine = " ";
                text->SetText(showingLine);
                lineCurrentSize = 0;
            }
            else{
                exit(61);
            }
        }
    }



    UpdateArray(dt);
}

void SecondDialogue::Render(){

    RenderArray();
}

void SecondDialogue::Start(){

    StartArray();
}

void SecondDialogue::Pause(){

}

void SecondDialogue::Resume(){

}
