#define INCLUDE_SDL
#include "SDL_include.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

void Camera::Follow(GameObject *newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if (focus != nullptr){
        GameObject* backgroundGo = Game::GetInstance().GetCurrentState().GetObjectContaining("Background").lock().get();
        if(backgroundGo != nullptr){
            if(focus->box.Center().x > SCREEN_WIDTH / 2 && focus->box.Center().x < backgroundGo->box.w - SCREEN_WIDTH / 2){
                pos.x = focus->box.Center().x - SCREEN_WIDTH/2;
            }

            if(focus->box.Center().y > SCREEN_HEIGHT / 2 && focus->box.Center().y < backgroundGo->box.h - SCREEN_HEIGHT / 2){
                pos.y = focus->box.Center().y - SCREEN_HEIGHT/2;
            }
        }
        else{
            pos.x = focus->box.Center().x - SCREEN_WIDTH/2;
            pos.y = focus->box.Center().y - SCREEN_HEIGHT/2;
        }


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
