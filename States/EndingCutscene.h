#ifndef ENDINGCUTSCENE_H
#define ENDINGCUTSCENE_H

#include "../State.h"

class EndingCutscene: public State
{
public:
    EndingCutscene();
    ~EndingCutscene();

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

#endif // ENDINGCUTSCENE_H
