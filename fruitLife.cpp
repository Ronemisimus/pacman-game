#include "fruitLife.h"
size_t fruitLife::getFrames()
{
    return this->frames;

}
void fruitLife::setFrames(size_t frames)
{
    this->frames=frames;

}
int fruitLife::getValue()
{
 return this->value;
}
void fruitLife::setValue(int val)
{
    value=val;

}
Position fruitLife::getPos()
{
 return this->initPos;
}
void fruitLife::setPos(Position pos)
{
    initPos=pos;

}

void fruitLife::setSteps(vector<Direction>* steps)
{
    this->steps=steps;
}

Direction fruitLife::getNextDir()
{
    if(steps && currentDir<(int)steps->size())
    {
        return (*steps)[currentDir++];
    }
    else
    {
        return Direction::NOCHANGE;
    }
}

int fruitLife::getStepsLen()
{
    if(steps)
    {
        return steps->size();
    }
    else
    {
        return 0;
    }
}
