#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../State.h"
#include "../Sprite.h"

class PauseMenu: public State{
public:
    PauseMenu();
    ~PauseMenu();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    int option;
    int lastFrameOption;
    Sprite* backgroundImage;
};

#endif // PAUSEMENU_H
