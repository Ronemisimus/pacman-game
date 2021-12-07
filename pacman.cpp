
#include "pacman.h"
#include "game.h"
pacman::pacman(): Creature(CHAR_PACMAN, Position(1,1), Direction::STAY),lives(3), points(0)
{

    pos = initPos;
}


collisionFlags pacman::movePacman(cell board[boardSize][boardSize], int& foodLeft)
{
    collisionFlags cf;
    //this function is in charge of the packman's move
    //calculate the next position:
    Position next = CalculateNext();
    prev = pos;
    board[prev.x][prev.y].data = gameObjectType::EMPTY;
   
    //check for collision:
    cf.setPacmanGhost(board[next.x][next.y].data == gameObjectType::GHOST);
    if(cf.getPacmanGhost())
    {
        return cf;
    }
    else if (board[next.x][next.y].data == gameObjectType::WALL)
    {
        board[prev.x][prev.y].data = gameObjectType::PACMAN;
        SetDir(Direction::STAY);
        next.x = pos.x;
        next.y = pos.y;
        return cf;
    }
    else
    {
       
        cf.setPacmanFruit(board[next.x][next.y].data==gameObjectType::FRUIT);
    
        //move packman:
        pos = next;
        board[pos.x][pos.y].data = gameObjectType::PACMAN;
        //update food:
        if(board[pos.x][pos.y].food)
        { 
            board[pos.x][pos.y].food = false;
            points++;
            foodLeft--;
        }
        return cf;
    }
    
}
void pacman::addFruitPoints(int value)
{
    this->points += value;
}
int pacman::getLives()
{
    return lives;
}

int pacman::getPoints()
{
    return points;
}

void pacman::strike(cell board[boardSize][boardSize])
{
    //this function is in charge of packman losing a life:
    prev = pos;
    pos = initPos;

    board[prev.x][prev.y].data = gameObjectType::EMPTY;
    board[pos.x][pos.y].data = gameObjectType::PACMAN;

    lives--;
    SetDir(Direction::STAY);

}

