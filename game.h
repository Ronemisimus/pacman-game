
#pragma once
#include "iofunctions.h"
#include "global.h"
#include "ghost.h"
#include "pacman.h"

class Game
{
private:
    cell board[boardSize][boardSize];
    ghost enemy;
    int foodLeft;
    pacman player;

    void drawPos(int x, int y);
public:
    Game();
    void initBoard();
    void drawBoard();
    void redrawBoard();
    void updateBoard();
    bool isDone();
    int getFoodLeft();
};