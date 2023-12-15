#ifndef INTERACTIONZONE_H
#define INTERACTIONZONE_H

#include "../Component.h"

class InteractionZone: public Component
{
public:
    InteractionZone(GameObject& associated, int ID);
    ~InteractionZone();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

    int GetID();
private:
    int ID;
};

#endif // INTERACTIONZONE_H
