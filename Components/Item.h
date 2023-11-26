#ifndef ITEM_H
#define ITEM_H

#include "../Component.h"

class Item: public Component{
public:
    Item(GameObject& associated, int ID, bool inMap = false);
    ~Item();

    void Start();
    void Update(float dt);
    void Render();

    bool Is(std::string type);
    void NotifyCollision(GameObject &other);

    bool Attached();
    int GetID();
private:
    int ID;
    bool attached;
    bool inMap;
};

#endif // ITEM_H
