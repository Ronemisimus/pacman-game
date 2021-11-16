
#pragma once
#include "global.h"
#ifdef LINUX
#include "iofunctions.h"
#else
#include <conio.h>
#include <Windows.h>
#endif
#include "ghost.h"
#include "pacman.h"

class Game
{
private:
    cell board[boardSize][boardSize];
    ghost enemy;
    int foodLeft;
    pacman player;
    bool isPaused;
    bool waitForMove; // after strike pause until player moves

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