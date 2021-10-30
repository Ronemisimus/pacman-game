#pragma once
#include "global.h"

class pacman
{
private:
    int lives;
    Position initialPos;
    Direction dir;
    int points;
    Position prev;
    Position pos;
public:
    pacman();
    bool movePacman(cell board[boardSize][boardSize]);
    void setDir(Direction dir);
    int getLives();
    int getPoints();
    Position getPos();
    Position getPrevPos();
};
