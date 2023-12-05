#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "States/TitleState.h"

int main (int argc, char** argv) {

    srand(time(NULL));

    Game& game = Game::GetInstance();

    game.Push(new TitleState());

    game.Run();

    return 0;
}
