#include <fstream>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

#include <iostream>

Game* Game::instance = nullptr;

static void WriteErrorInFile(Game* instance, const char* text, int error_number){
    std::ofstream errorfile("errorlog.txt");
    errorfile << text << std::endl;
    errorfile.close();
    delete instance;
    exit(error_number);
}

Game::Game(std::string title, int width, int height): frameStart(0), dt(0.0), stateStack(){
    if (instance != nullptr){
        exit(1);
    }
    else{
        instance = this;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        WriteErrorInFile(this, SDL_GetError(), 2);
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0){
        WriteErrorInFile(this, SDL_GetError(), 3);
    }

    if (TTF_Init() != 0){
        WriteErrorInFile(this, SDL_GetError(), 99);
    }

    if (Mix_Init(MIX_INIT_OGG) == 0){
        WriteErrorInFile(this, SDL_GetError(), 4);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        WriteErrorInFile(this, SDL_GetError(), 5);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (!window){
        WriteErrorInFile(this, SDL_GetError(), 6);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer){
        WriteErrorInFile(this, SDL_GetError(), 7);
    }

    storedState = nullptr;
}

Game::~Game(){
    if (storedState != nullptr){
        delete storedState;
    }

    while(!(stateStack.empty())){
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game& Game::GetInstance(){
    if (instance == nullptr){
        std::string window_name = "Jonas Soares Rangel - 170146804";
        instance = new Game(window_name, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    return *instance;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetCurrentState(){
    if(!(stateStack.empty())){
        return *(stateStack.top());
    }
    else{
        exit(404);
    }
}

void Game::Push(State *state){
    storedState = state;
}

void Game::Run(){
    if(storedState != nullptr){
        stateStack.emplace(storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }

    while (!(stateStack.empty()) && !(stateStack.top()->QuitRequested())){
        if(stateStack.top()->PopRequested()){
            stateStack.pop();
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();
            if(!(stateStack.empty())){
                stateStack.top()->Resume();
            }
        }

        if(storedState != nullptr){
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        if(!stateStack.empty()){
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    if (storedState != nullptr){
        delete storedState;
    }

    while(!(stateStack.empty())){
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
}

void Game::CalculateDeltaTime(){
    int newFrameStart = SDL_GetTicks();
    dt = ((float)newFrameStart - (float)frameStart) / (1000.0);
    frameStart = newFrameStart;
}

float Game::GetDeltaTime(){
    return dt;
}
