#pragma once
#include "global.h"
class fruitLife
{
private:
    size_t frames;
    int value;
    Position initPos;
    vector<Direction>* steps;
    int currentDir=0;

public:
    size_t getFrames();
    void setFrames(size_t frames);
    int getValue();
    void setValue(int val);
    Position getPos();
    void setPos(Position pos);
    void setSteps(vector<Direction>* steps);
    Direction getNextDir();
    int getStepsLen();
};