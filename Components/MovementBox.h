#ifndef MOVEMENTBOX_H
#define MOVEMENTBOX_H

#include "../Collider.h"

class MovementBox: public Collider
{
public:
    MovementBox(GameObject& associated, Vec2 scale = Vec2(1.0, 1.0), Vec2 offset = Vec2(0.0, 0.0));
    ~MovementBox();

    void Start();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif // MOVEMENTBOX_H
