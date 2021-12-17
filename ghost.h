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
    list<Position> smartMoves;
    list<Position> initSmartMoves;
public:
    static GhostStrategy level;

    ghost(int rowSize,int colSize, Position initPos, pacman& player);
    collisionFlags moveGhost(BoardGame& board);
    void strike(BoardGame& board);
    pacman& getTarget() const;
    void addToStartOfSmartList(Position current);
    void addToEndOfSmartList(Position current);
    Position removeFromStartOfSmartList();
    Position removeFromEndOfSmartList();
    int findInList(Position playerPos);
    void copyToInitList();
    void copyFromInitList();
};
