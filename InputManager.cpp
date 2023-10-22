#define INCLUDE_SDL
#include "SDL_include.h"
#include "InputManager.h"

InputManager& InputManager::GetInstance(){
    static InputManager inputManager;
    return inputManager;
}

InputManager::InputManager(): mouseState{false, false, false, false, false}, mouseUpdate{0, 0, 0, 0, 0}{
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager(){

}

void InputManager::Update(){
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    ++updateCounter;

    while(SDL_PollEvent(&event)){

        if(event.type == SDL_QUIT){
            quitRequested = true;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if (!(mouseState[event.button.button - 1])){
                mouseUpdate[event.button.button - 1] = updateCounter;
            }

            mouseState[event.button.button - 1] = true;
        }

        if(event.type == SDL_MOUSEBUTTONUP){
            if (mouseState[event.button.button - 1]){
                mouseUpdate[event.button.button - 1] = updateCounter;
            }

            mouseState[event.button.button - 1] = false;
        }

        if(event.type == SDL_KEYDOWN){
            if(!event.key.repeat){
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }

            keyState[event.key.keysym.sym] = true;
        }

        if(event.type == SDL_KEYUP){
            if(!event.key.repeat){
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }

            keyState[event.key.keysym.sym] = false;
        }
    }
}

bool InputManager::KeyPress(int key){
    if(keyState[key] && keyUpdate[key] == updateCounter){
        return true;
    }
    else{
        return false;
    }
}

bool InputManager::KeyRelease(int key){
    if(!(keyState[key]) && keyUpdate[key] == updateCounter){
        return true;
    }
    else{
        return false;
    }
}

bool InputManager::IsKeyDown(int key){
    if(keyState[key]){
        return true;
    }
    else{
        return false;
    }
}

bool InputManager::MousePress(int button){
    if(mouseState[button - 1] && mouseUpdate[button - 1] == updateCounter){
        return true;
    }
    else{
        return false;
    }
}

bool InputManager::MouseRelease(int button){
    if(!(mouseState[button - 1]) && mouseUpdate[button - 1] == updateCounter){
        return true;
    }
    else{
        return false;
    }
}

bool InputManager::IsMouseDown(int button){
    if(mouseState[button - 1]){
        return true;
    }
    else{
        return false;
    }
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}
