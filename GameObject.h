#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "Rect.h"

class Component;

class GameObject{
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
    void NotifyCollision(GameObject& other);

    Rect box;
    bool started;
    double angleDeg;
    bool flip;
private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
};

#endif // GAMEOBJECT_H
