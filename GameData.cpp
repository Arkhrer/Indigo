#include "GameData.h"

void GameData::Initialize(){
    for(int i = 0; i < 100; ++i){
        stateVariables[i] = false;
    }
}
