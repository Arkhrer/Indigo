#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera{
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    static inline Vec2 pos;
    static inline Vec2 speed;

private:
    static inline GameObject* focus = nullptr;
};

#endif // CAMERA_H
