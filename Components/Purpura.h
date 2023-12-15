#ifndef PURPURA_H
#define PURPURA_H

#include "../Component.h"

class Purpura: public Component{
public:
    Purpura(GameObject& associated);
    ~Purpura();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif // PURPURA_H
