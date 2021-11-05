
#include "pacman.h"
#include "game.h"
pacman::pacman(): lives(300), initialPos(1,1), dir(STAY), points(0), prev(-1,-1), framesSinceMove(0)
{
    pos = initialPos;
}

bool pacman::movePacman(cell board[boardSize][boardSize], int& foodLeft)
{
    Position next(0,0);
    switch (dir)
    {
    case RIGHT:
        next.x = (pos.x + 1)%boardSize;
        next.y = pos.y;
        break;
    case LEFT:
        next.x = (pos.x - 1)%boardSize;
        if(next.x<0) next.x = boardSize + next.x;
        next.y = pos.y;
        break;
    case DOWN:
        next.x = pos.x;
         next.y = (pos.y+1)%boardSize;
       break;
    case UP:
        next.x = pos.x ;
        next.y = (pos.y-1)%boardSize;
        if(next.y<0) next.y = boardSize + next.y;
        break;
    case STAY:
        next.x=pos.x;
        next.y=pos.y;
        break;    
    default:
        break;
    }

    prev = pos;
    board[prev.x][prev.y].data = EMPTY;
    if(board[next.x][next.y].data==WALL ||
        board[next.x][next.y].data==GHOST)
    {
        return false;
    }
    else
    {
        pos = next;
        board[pos.x][pos.y].data = PACMAN;
        if(board[pos.x][pos.y].food)
        { 
            board[pos.x][pos.y].food = false;
            points++;
            foodLeft--;
        }
        return true;
    }
    
}

int pacman::getLives()
{
    return lives;
}

int pacman::getPoints()
{
    return points;
}

Position pacman::getPos()
{
    return pos;
}

Position pacman::getPrevPos()
{
    return prev;
}

void pacman::setDir(Direction dir)
{
    this->dir = dir;
}

void pacman::setFrames(int framesSinceMove)
{
    this->framesSinceMove = framesSinceMove;
}

int pacman::getFrames()
{
    return framesSinceMove;
}

void pacman::strike(cell board[boardSize][boardSize])
{
    prev = pos;
    pos = initialPos;

    board[prev.x][prev.y].data = EMPTY;
    board[pos.x][pos.y].data = PACMAN;

    lives--;
    dir = STAY;

}

