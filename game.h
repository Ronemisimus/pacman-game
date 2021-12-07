
#pragma once

#include "global.h"
#include "ghost.h"
#include "pacman.h"
#include "fruit.h"
#include "collisionFlags.h"


class Game
{
private:
    cell board[boardSize][boardSize];
    ghost enemies[GHOST_NUM];
    int foodLeft;
    pacman player;
    fruit fruit1;
    bool isPaused;
    bool waitForMove; // after strike pause until player moves

   
public:
    Game();
    void initBoard();
    void drawBoard();
    void redrawBoard();
    void updateBoard();
    bool isDone();
    int getFoodLeft();
};