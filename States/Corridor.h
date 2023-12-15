#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "../State.h"
#include "../Timer.h"

class Corridor: public State{
public:
    Corridor(int x, int y);
    ~Corridor();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    int initialX;
    int initialY;
    int currentFrame;
    int lastFrame;
    Timer timer;
    bool activated;
    bool reversed;
    bool lastBoxed;
    bool justOpened;

    void SpawnBoxZone();
};

#endif // CORRIDOR_H
