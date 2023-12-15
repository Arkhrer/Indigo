#ifndef ROOMTHREEFUSEBOX_H
#define ROOMTHREEFUSEBOX_H

#include "../State.h"

class RoomThreeFuseBox: public State
{
public:
    RoomThreeFuseBox();
    ~RoomThreeFuseBox();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    bool justChanged;
    bool states[2];

    void SpawnLid();
    void SpawnFuse();
};

#endif // ROOMTHREEFUSEBOX_H
