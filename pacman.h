#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"

class pacman : public Creature
{
private:
    int lives;
    int points;
public:
    pacman(Position initPos);
    virtual ~pacman();
    virtual collisionFlags moveCreature(BoardGame& board);
    int getLives();
    int getPoints();
    void strike(BoardGame& board);
    void addFruitPoints(int value);
    
    void resetLives();
    void resetPoints();
};
