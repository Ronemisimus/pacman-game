#pragma once
#include "global.h"
#include "iofunctions.h"

struct path
{
    Direction way;
    bool available;
};

class ghost
{
    Position initialPos;
    Direction dir;
    Position prev;
    Position pos;
    int framesSinceMove;
public:
    ghost();
    void moveGhost(cell board[boardSize][boardSize]);
    void setDir(Direction dir);
    Position getPos();
    Position getPrevPos();
    void setFrames(int frames);
    int getFrames();
    void getPossiblePos(cell board[boardSize][boardSize], path Possibilities[4]);
};

