
#include "pacman.h"
#include "game.h"
pacman::pacman(Position initPos): Creature(CHAR_PACMAN, initPos, Direction::STAY),lives(3), points(0)
{
    pos = initPos;
}

pacman::~pacman()
{
    
}

collisionFlags pacman::moveCreature(BoardGame& board)
{
    collisionFlags cf;
    //this function is in charge of the packman's move
    //calculate the next position:
    Position next = CalculateNext(board);
    prev = pos;
   
    board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
   

    //check for collision:
    
    cf.setPacmanGhost(board.getCellData(next.x,next.y)== gameObjectType::GHOST);
   
    if(cf.getPacmanGhost())
    {
        return cf;
    }
    else if (board.getCellData(next.x, next.y) == gameObjectType::WALL)
    {
        board.setBoardCellData(prev.x, prev.y, gameObjectType::PACMAN);
      
        SetDir(Direction::STAY);
        next.x = pos.x;
        next.y = pos.y;
        return cf;
    }
    else
    {
       
        cf.setPacmanFruit(board.getCellData(next.x, next.y) ==gameObjectType::FRUIT);
    
        //move packman:
        pos = next;

        board.setBoardCellData(pos.x, pos.y, gameObjectType::PACMAN);
       
        //update food:
        if(board.getIsThereFood(pos.x,pos.y))
        { 
            board.setIsThereFood(pos.x, pos.y, false);
            
            points++;
           
        }
        return cf;
    }
    
}

string pacman::addToSave(size_t frames)
{
    string res = "";

    if(getFrames()==0)
    {
        res += convertDirToLetter(getDir());
    }
    return res;

}

void pacman::addFruitPoints(size_t value)
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

void pacman::strike(BoardGame& board)
{
    //this function is in charge of packman losing a life:
    prev = pos;
    pos = initPos;
    board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
    board.setBoardCellData(pos.x, pos.y, gameObjectType::PACMAN);
   

    lives--;
    SetDir(Direction::STAY);

}

void pacman::resetLives()
{
    lives=3;
}

void pacman::resetPoints()
{
    points=0;
}
