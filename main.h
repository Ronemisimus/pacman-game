#pragma once
#include "game.h"
#include "ghost.h"
#include "FileHandler.h"
#include <iostream>

using std::cout;
using std::cin;

FileHandler fh;


enum  MENU {
    START = 1, 
    LOAD = 2,
    PRESENT = 8,
    EXIT = 9 
};

MENU menu();
void present();
bool startGame(BoardGame* board, Game& game);
void endGameMessage(bool victory);
void getDifficultyLevel();

