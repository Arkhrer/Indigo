#ifndef ROOMTRANSITION_H
#define ROOMTRANSITION_H

#include "../Collider.h"

class RoomTransition: public Collider
{
public:
    RoomTransition(GameObject& associated, int targetRoom, Vec2 targetIndigoPosition = Vec2(0.0, 0.0), Vec2 scale = Vec2(1.0, 1.0), Vec2 offset = Vec2(0.0, 0.0));
    ~RoomTransition();

    void Start();

    bool Is(std::string type);
    void NotifyCollision(GameObject& other);

    int GetTargetRoom();
    Vec2 GetTargetIndigoPosition();
private:
    int targetRoom;
    Vec2 targetIndigoPosition;
};

#endif // ROOMTRANSITION_H
