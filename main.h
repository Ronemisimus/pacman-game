#pragma once
#include "game.h"
#include "ghost.h"
#include "global.h"
#include "FileHandler.h"
#include "GameResult.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

enum class MENU {
    START = 1, 
    LOAD = 2,
    PRESENT = 8,
    EXIT = 9 ,
    INVALID
};

MENU menu();
void present();
bool startGame(BoardGame* board, Game& game);
void endGameMessage(bool victory, bool silent);
void getDifficultyLevel();
void run(bool save);
bool load(bool silent);
bool startLoadGame(BoardGame *board, Game& game, bool silent, GameResult& res);
