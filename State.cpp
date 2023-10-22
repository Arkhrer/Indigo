#include "State.h"

State::State(): objectArray(){
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State(){
    objectArray.clear();
}

void State::StartArray(){
    for (unsigned int i = 0; i < objectArray.size(); ++i){
        objectArray.at(i)->Start();
    }

    started = true;
}

void State::UpdateArray(float dt){
    for (unsigned int i = 0; i < objectArray.size(); ++i){
        objectArray.at(i)->Update(dt);
    }
}

void State::RenderArray(){
    for (unsigned int i = 0; i < objectArray.size(); ++i){
        objectArray.at(i)->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    auto sharedGo = std::shared_ptr<GameObject>(go);

    objectArray.push_back(sharedGo);

    if (started){
        go->Start();
    }

    std::weak_ptr<GameObject> weakGo = sharedGo;

    return weakGo;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){

    for (unsigned int i = 0; i < objectArray.size(); ++i){
        if (objectArray.at(i).get() == go){
            std::weak_ptr<GameObject> weakGo = objectArray.at(i);
            return weakGo;
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}
