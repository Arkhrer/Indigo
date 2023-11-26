#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define SPACE_BAR           SDLK_SPACE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define W_KEY               SDLK_w
#define S_KEY               SDLK_s
#define A_KEY               SDLK_a
#define D_KEY               SDLK_d
#define I_KEY               SDLK_i

class InputManager{
public:
    static InputManager& GetInstance();
    InputManager();
    ~InputManager();

    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

private:
    bool mouseState[5];
    int mouseUpdate[5];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;
    int updateCounter;

    int mouseX;
    int mouseY;
};

#endif // INPUTMANAGER_H
