#ifndef INDIGO_H
#define INDIGO_H

#include "../Component.h"
#include "../Timer.h"

class Indigo: public Component{
public:
    Indigo(GameObject& associated);
    ~Indigo();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

    void Interact();

    bool IsInteracting();

    void CancelMovement();

    inline static Indigo* player = nullptr;
private:
    Vec2 lastSpeed;
    Vec2 lastPosition;
    bool interacting;
    Timer interactingTimer;
    Vec2* destination;
    bool lastInteracting;
};

#endif // INDIGO_H
