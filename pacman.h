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
    int framesSinceMove;
public:
    pacman();
    bool movePacman(cell board[boardSize][boardSize], int& foodLeft);
    void setDir(Direction dir);
    int getLives();
    int getPoints();
    Position getPos();
    Position getPrevPos();
    void setFrames(int frames);
    int getFrames();
    void strike(cell board[boardSize][boardSize]);
};
