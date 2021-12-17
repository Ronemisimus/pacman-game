#include "ghost.h"

GhostStrategy ghost::level = GhostStrategy::INVALID;

ghost::ghost(int rowSize, int colSize, Position initPos, pacman& player): Creature(CHAR_ENEMY, initPos, Direction::STAY), player(player)
{
    pos = initPos;
}


collisionFlags ghost::moveGhost(BoardGame& board)
{
    collisionFlags cf;
    //function that in charge of the ghosts' movement

    //chooseRandomDir(board);

    SetDir(GhostMoveStrategy::getNextDir(*this, ghost::level, board));
    
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

pacman& ghost::getTarget() const
{
    return player; 
}

void ghost::strike(BoardGame& board)
{
    //this function handles the case of packman losing a life
    prev = pos;
    pos = initPos;
    board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
    board.setBoardCellData(pos.x, pos.y, gameObjectType::GHOST);
  
}

void ghost::addToStartOfSmartList(Position current)
{
    smartMoves.push_front(current);
}

void ghost::addToEndOfSmartList(Position current)
{
    smartMoves.push_back(current);
}
