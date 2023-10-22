#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "GameObject.h"

class Component{
public:
    Component(GameObject& asssociated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void NotifyCollision(GameObject& other);
protected:
    GameObject& associated;
};

#endif // COMPONENT_H
