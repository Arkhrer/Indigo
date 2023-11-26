#ifndef MOVEMENTBOUND_H
#define MOVEMENTBOUND_H

#include "../Collider.h"

class MovementBound: public Collider
{
public:
    MovementBound(GameObject& associated, Vec2 scale = Vec2(1.0, 1.0), Vec2 offset = Vec2(0.0, 0.0));
    ~MovementBound();

    void Start();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif // MOVEMENTBOUND_H
