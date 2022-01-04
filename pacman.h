#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"

class pacman : public Creature
{//handles the pacman's data
private:
    int lives;
    int points;
public:
    pacman(Position initPos);
    virtual ~pacman();
    virtual collisionFlags moveCreature(BoardGame& board);
    virtual string addToSave(size_t frames);
    int getLives();
    int getPoints();
    void strike(BoardGame& board);
    void addFruitPoints(size_t value);
    string addToSave(size_t frames, Direction dir);

    
    void resetLives();
    void resetPoints();
};
