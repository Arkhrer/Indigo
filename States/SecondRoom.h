#ifndef SECONDROOM_H
#define SECONDROOM_H

#include "../State.h"

class SecondRoom: public State{
public:
    SecondRoom(int x, int y);
    ~SecondRoom();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    int initialX;
    int initialY;
};

#endif // SECONDROOM_H
