#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider: public Component{
public:
    Collider(GameObject& associated, Vec2 scale = Vec2(1.0, 1.0), Vec2 offset = Vec2(0.0, 0.0));
    ~Collider();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    Rect box;

private:
    Vec2 scale;
    Vec2 offset;
};

#endif // COLLIDER_H
