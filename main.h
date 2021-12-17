#pragma once
#include "game.h"
#include "ghost.h"
#include "global.h"
#include "FileHandler.h"
#include <iostream>

FileHandler fh;

using std::cin;
using std::cout;
using std::endl;

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

