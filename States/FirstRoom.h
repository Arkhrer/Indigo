#ifndef FIRSTROOM_H
#define FIRSTROOM_H

#include "../State.h"

class FirstRoom: public State{
public:
    FirstRoom();
    ~FirstRoom();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif // FIRSTROOM_H
