#include "ghost.h"

ghost::ghost(int rowSize, int colSize, Position initPos): Creature(CHAR_ENEMY, initPos, Direction::STAY)
{
    pos = initPos;
}


collisionFlags ghost::moveGhost(BoardGame& board)
{
    collisionFlags cf;
    //function that in charge of the ghosts' movement

    chooseRandomDir(board);
    
    //move the ghost accordingly:
    prev = pos;
    pos = CalculateNext(board);
    board.setBoardCellData(prev.x,prev.y,gameObjectType::EMPTY);
   
    //check if the ghost ate packman:
 
    cf.setPacmanGhost(board.getCellData(pos.x, pos.y) == gameObjectType::PACMAN);
    cf.setFruitGhost(board.getCellData(pos.x, pos.y) == gameObjectType::FRUIT);
    board.setBoardCellData(pos.x, pos.y, gameObjectType::GHOST);
    
    return cf;
}

void ghost::strike(BoardGame& board)
{
    //this function handles the case of packman losing a life
    prev = pos;
    pos = initPos;
    board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
    board.setBoardCellData(pos.x, pos.y, gameObjectType::GHOST);
  
}

