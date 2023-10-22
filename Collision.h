#ifndef COLLISION_H
#define COLLISION_H

#include "Rect.h"

class Collision {
public:
    static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
};

#endif // COLLISION_H
