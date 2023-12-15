#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <memory>
#include <vector>

class GameData{
public:
    static void Initialize();
    inline static bool playerVictory = false;
    inline static std::vector<int> posessedItems;
    inline static bool stateVariables[100];
};

#endif // GAMEDATA_H
