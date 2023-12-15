#ifndef BACKARROW_H
#define BACKARROW_H

#include "../Component.h"

class BackArrow: public Component{
public:
    BackArrow(GameObject& associated);
    ~BackArrow();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif // BACKARROW_H
