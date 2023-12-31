#ifndef INVENTORY_H
#define INVENTORY_H

#include "../Component.h"
class Inventory: public Component{
public:
    Inventory(GameObject& associated);
    ~Inventory();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

    void AddItem(int ID);
    void RemoveItem(int ID);

    inline static Inventory* inventory = nullptr;

    GameObject& openAssociated;
    std::vector<std::shared_ptr<GameObject>> items;
private:
    bool visible;

};

#endif // INVENTORY_H
