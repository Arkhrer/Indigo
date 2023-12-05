#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "States/FirstRoom.h"

int main (int argc, char** argv) {

    srand(time(NULL));

    Game& game = Game::GetInstance();

    game.Push(new FirstRoom());

    game.Run();

    return 0;
}
