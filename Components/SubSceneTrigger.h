#ifndef SUBSCENETRIGGER_H
#define SUBSCENETRIGGER_H

#include "../Component.h"

class SubSceneTrigger: public Component{
public:
    SubSceneTrigger(GameObject& associated);
    ~SubSceneTrigger();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
    void SetOption(int newOption);
private:
    int option;
};

#endif // SUBSCENETRIGGER_H
