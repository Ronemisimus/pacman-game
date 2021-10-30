
#include "pacman.h"
#include "game.h"
pacman::pacman(): lives(3), initialPos(Position({1,1})), dir(STAY), points(0), prev(Position({-1,-1}))
{
    pos = initialPos;
}

bool pacman::movePacman(cell board[boardSize][boardSize])
{
    Position next;
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
        lives--;
        pos = initialPos;
        dir = STAY;
        board[pos.x][pos.y].data = PACMAN;
        return false;
    }
    else
    {
        pos = next;
        board[pos.x][pos.y].data = PACMAN;
        if(board[pos.x][pos.y].food)
        {
            points++;
            board[pos.x][pos.y].food=false;
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