#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"
#include "GhostMoveStrategy.h"


class ghost : public Creature
{//class to handle the ghost's data
private:
    pacman& player;
    list<Position> smartMoves;
    list<Position> initSmartMoves;
public:
    static GhostStrategy level;

    ghost(int rowSize,int colSize, Position initPos, pacman& player);
    virtual ~ghost();
    void strike(BoardGame& board);
    pacman& getTarget() const;
    void addToStartOfSmartList(Position current);
    void addToEndOfSmartList(Position current);
    Position removeFromStartOfSmartList();
    Position removeFromEndOfSmartList();
    void emptyStepsList();
    int findInList(Position playerPos);
    void copyToInitList();
    void copyFromInitList();
    int getSmartMovesSize();
    
    virtual collisionFlags moveCreature(BoardGame& board);
    virtual string addToSave(size_t frames);

};
