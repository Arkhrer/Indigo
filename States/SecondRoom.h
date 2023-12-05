#ifndef SECONDROOM_H
#define SECONDROOM_H

#include "../State.h"

class SecondRoom: public State{
public:
    SecondRoom();
    ~SecondRoom();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif // SECONDROOM_H
