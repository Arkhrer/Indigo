#ifndef ROOMONEDESK_H
#define ROOMONEDESK_H

#include "../State.h"

class RoomOneDesk: public State{
public:
    RoomOneDesk();
    ~RoomOneDesk();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
private:
    bool justChanged;
    bool states[3];

    void SpawnCable();
    void SpawnDevice();
};

#endif // ROOMONEDESK_H
