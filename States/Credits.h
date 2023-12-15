#ifndef CREDITS_H
#define CREDITS_H

#include "../State.h"

class Credits: public State
{
public:
    Credits();
    ~Credits();

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

#endif // CREDITS_H
