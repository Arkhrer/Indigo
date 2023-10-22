#define INCLUDE_SDL
#include "SDL_include.h"
#include "Camera.h"
#include "InputManager.h"

void Camera::Follow(GameObject *newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if (focus != nullptr){
        pos.x = focus->box.Center().x - 1024/2;
        pos.y = focus->box.Center().y - 600/2;
    }
    else{
        float linearSpeed = 500.0;

//        speed.x = (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) - InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY));
//        speed.y = (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) - InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY));
//        Vec2 normalizedSpeed = speed.Normalized();

//        pos.x += normalizedSpeed.x * dt * linearSpeed;
//        pos.y += normalizedSpeed.y * dt * linearSpeed;
    }
}
