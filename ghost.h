#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"
#include "GhostMoveStrategy.h"


class ghost : public Creature
{
private:
    pacman& player;
public:
    static GhostStrategy level;

    ghost(int rowSize,int colSize, Position initPos, pacman& player);
    collisionFlags moveGhost(BoardGame& board);
    void strike(BoardGame& board);
    pacman& getTarget() const;
};
