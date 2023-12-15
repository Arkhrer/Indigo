#ifndef THIRDROOM_H
#define THIRDROOM_H

#include "../State.h"

class ThirdRoom: public State
{
public:
    ThirdRoom(int x, int y);
    ~ThirdRoom();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    int initialX;
    int initialY;

    bool lastOpened;
    bool justOpened;

    void SpawnExit();
};

#endif // THIRDROOM_H
