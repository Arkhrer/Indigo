#ifndef ROOMTWOSIDE_H
#define ROOMTWOSIDE_H

#include "../State.h"

class RoomTwoSide: public State{
public:
    RoomTwoSide();
    ~RoomTwoSide();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    bool justChanged;
    bool states[1];

    void SpawnBox();
};

#endif // ROOMTWOSIDE_H
