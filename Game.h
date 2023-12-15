#ifndef GAME_H
#define GAME_H

#include <stack>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "Music.h"

#define SCREEN_WIDTH   480 * 3
#define SCREEN_HEIGHT  270 * 3

class Game{
    public:
        ~Game();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();

        void Push(State* state);

        void Run();

        float GetDeltaTime();

        Music music;
    private:
        Game(std::string title, int width, int height);

        void CalculateDeltaTime();
        int frameStart;
        float dt;

        static Game* instance;

        SDL_Window* window;
        SDL_Renderer* renderer;
        State* storedState;
        std::stack<std::unique_ptr<State>> stateStack;
};

#endif // GAME_H
