#include "Background.h"

Background::Background(GameObject& associated):Component(associated){

}

Background::~Background(){

}

void Background::Start(){

}

void Background::Update(float dt){

}

void Background::Render(){

}

bool Background::Is(std::string type){
    if (type.compare("Background") == 0){
        return true;
    }
    else{
        return false;
    }
}

void Background::NotifyCollision(GameObject &other){

}
