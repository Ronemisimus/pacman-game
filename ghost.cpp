#include "ghost.h"

ghost::ghost(): initialPos(boardSize-2,boardSize-2), dir(STAY), prev(-1,-1), framesSinceMove(0)
{
    pos = initialPos;
}

Position ghost::getPos()
{
    return pos;
}

Position ghost::getPrevPos()
{
    return prev;
}

void ghost::setDir(Direction dir)
{
    this->dir = dir;
}

void ghost::setFrames(int framesSinceMove)
{
    this->framesSinceMove = framesSinceMove;
}

int ghost::getFrames()
{
    return framesSinceMove;
}

bool ghost::moveGhost(cell board[boardSize][boardSize])
{
    path possiblities[4] = {}; 
    getPossiblePos(board, possiblities);

    int choose = rand() % 4;

    bool changed = false;

    for(int i=0;i<4;i++)
    {
        if(possiblities[(i+choose)%4].available)
        {
            setDir(possiblities[(i+choose)%4].way);
            changed = true;
        }
    }

    if(!changed)
    {
        setDir(STAY);
    }

    if(dir!=STAY)
    {
        prev = pos;
        switch (dir)
        {
        case LEFT:
            pos.x--;
            break;
        case RIGHT:
            pos.x++;
            break;
        case UP:
            pos.y--;
            break;
        case DOWN:
            pos.y++;
            break;
        default:
            break;
        }

        board[prev.x][prev.y].data = EMPTY;
        bool notHit = board[pos.x][pos.y].data != PACMAN;
        board[pos.x][pos.y].data = GHOST;
        
        return notHit;
    }

    return true;
}

void ghost::getPossiblePos(cell board[boardSize][boardSize], path possibilities[4])
{
    if(pos.x-1>0 && 
        board[pos.x-1][pos.y].data!=WALL)
    {
        possibilities[LEFT].way =LEFT;
        possibilities[LEFT].available=true;
    }
    if(pos.x+1<boardSize-1 &&
        board[pos.x+1][pos.y].data!=WALL)
    {
        possibilities[RIGHT].way =RIGHT;
        possibilities[RIGHT].available=true;
    }
    if(pos.y-1>0 &&
        board[pos.x][pos.y-1].data!=WALL)
    {
        possibilities[UP].way =UP;
        possibilities[UP].available=true;
    }
    if(pos.y+1<boardSize-1 &&
        board[pos.x][pos.y+1].data!=WALL)
    {
        possibilities[DOWN].way =DOWN;
        possibilities[DOWN].available=true;
    }
}

void ghost::strike(cell board[boardSize][boardSize])
{
    prev = pos;
    pos = initialPos;

    board[prev.x][prev.y].data = EMPTY;
    board[pos.x][pos.y].data = GHOST;
}

