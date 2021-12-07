#pragma once
#include "global.h"
#include "Creature.h"
#include "collisionFlags.h"
class pacman : public Creature
{
private:
    int lives;
    int points;
public:
    pacman();
    collisionFlags movePacman(cell board[boardSize][boardSize], int& foodLeft);
    int getLives();
    int getPoints();
    void strike(cell board[boardSize][boardSize]);
    void addFruitPoints(int value);
};
