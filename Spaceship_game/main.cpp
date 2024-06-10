#include "Game.h"

#include <iostream>

int main()
{
    Game game;

    //starting screen
    while (!game.gameStarted() && game.isRunning()) {
        game.startScreen();
    }

    //game loop
    while (game.isRunning()) {

        game.update();

        game.render();

    }

    //ending screen
    while (!game.exit()) {

        game.endScreen();
    }

    return 0;
}