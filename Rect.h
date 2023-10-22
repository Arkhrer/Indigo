#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
    Rect(float x = 0, float y = 0, float w = 0, float h = 0);

    void AddVector(Vec2 v);
    Vec2 Center();
    float CenterDistance(Rect r);
    bool ContainsPoint(float, float);

    float x;
    float y;
    float w;
    float h;
};

#endif // RECT_H
