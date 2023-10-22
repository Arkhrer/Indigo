#ifndef INDIGO_H
#define INDIGO_H

#include "../Component.h"

class Indigo: public Component{
public:
    Indigo(GameObject& associated);
    ~Indigo();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

    inline static Indigo* player = nullptr;
};

#endif // INDIGO_H
