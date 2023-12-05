#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Component.h"

class Background: public Component{
public:
    Background(GameObject& associated);
    ~Background();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif // BACKGROUND_H
