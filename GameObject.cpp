#include "GameObject.h"
#include "Component.h"
#include "Camera.h"

GameObject::GameObject(): box(){
    started = false;
    isDead = false;
    angleDeg = 0.0;
    flip = false;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Start(){
    for(unsigned int i = 0; i < components.size(); ++i){
        components.at(i)->Start();
    }
}


void GameObject::Update(float dt){
    for(unsigned int i = 0; i < components.size(); ++i){
        components.at(i)->Update(dt);
    }
}


void GameObject::Render(){
    for(unsigned int i = 0; i < components.size(); ++i){
        components.at(i)->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);

    if (started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt){
    for(int i = components.size() - 1; i >= 0; --i) {
        if (components.at(i).get() == cpt){
            components.erase(components.begin() + i);
            break;
        }
    }
}

Component* GameObject::GetComponent(std::string type){
    for(int i = components.size() - 1; i >= 0; --i) {
        if (components.at(i)->Is(type))
            return components.at(i).get();
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject& other){
    for(unsigned int i = 0; i < components.size(); ++i){
        components.at(i)->NotifyCollision(other);
    }
}
