#pragma once
#include "global.h"
#include "Creature.h"
#include "collisionFlags.h"

class ghost : public Creature
{
public:
    ghost();
    collisionFlags moveGhost(cell board[boardSize][boardSize]);
    void getPossiblePos(cell board[boardSize][boardSize], path Possibilities[4]);
    void strike(cell board[boardSize][boardSize]);
};

