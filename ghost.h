#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"


class ghost : public Creature
{
public:
    ghost(int rowSize,int colSize, Position initPos);
    collisionFlags moveGhost(BoardGame& board);
    
    void strike(BoardGame& board);
};

