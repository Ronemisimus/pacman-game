#pragma once
#include "global.h"
class fruitLife
{
private:
    int frames;
    int value;
    Position initPos;
    vector<Direction> steps;
    
public:
    int getFrames();
    void setFrames(int frames);
    int getValue();
    void setValue(int val);
    Position getPos();
    void setPos(Position pos);
};