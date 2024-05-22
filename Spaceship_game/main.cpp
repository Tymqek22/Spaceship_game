#include "Game.h"

#include <iostream>

extern int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT = 800;

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

    std::cout << "Hello World!\n";
}