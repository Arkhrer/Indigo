#ifndef STARTINGCUTSCENE_H
#define STARTINGCUTSCENE_H

#include "../State.h"

class StartingCutscene: public State{
public:
    StartingCutscene();
    ~StartingCutscene();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    unsigned int currentFrame;
    unsigned int lastFrame;
};

#endif // STARTINGCUTSCENE_H
