#ifndef ROOMTHREESINK_H
#define ROOMTHREESINK_H

#include "../State.h"

class RoomThreeSink: public State{
public:
    RoomThreeSink();
    ~RoomThreeSink();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    bool justChanged;
    bool states[1];

    void SpawnFork();
};

#endif // ROOMTHREESINK_H
