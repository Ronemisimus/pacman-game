#include "ghost.h"

GhostStrategy ghost::level = GhostStrategy::INVALID;

ghost::ghost(int rowSize, int colSize, Position initPos, pacman& player): Creature(CHAR_ENEMY, initPos, Direction::STAY), player(player)
{
    pos = initPos;
}

ghost::~ghost()
{
    
}

collisionFlags ghost::moveCreature(BoardGame& board)
{
    collisionFlags cf;
    //function that in charge of the ghosts' movement

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
    copyFromInitList();
}

void ghost::addToStartOfSmartList(Position current)
{
    smartMoves.push_front(current);
}

void ghost::addToEndOfSmartList(Position current)
{
    smartMoves.push_back(current);
}

Position ghost::removeFromStartOfSmartList()
{
    Position res = smartMoves.front();
    if(smartMoves.size()>0)
    {
        smartMoves.pop_front();
    }
    return res;
}

Position ghost::removeFromEndOfSmartList()
{
    Position res = smartMoves.back();
    if(smartMoves.size()>0)
    {
        smartMoves.pop_back();
    }
    return res;
}

int ghost::findInList(Position playerPos)
{
    int i=0;
    for(Position& pos:smartMoves)
    {
        if(pos.x==playerPos.x &&
        pos.y==playerPos.y)
        {
            return smartMoves.size()-i; 
        }
        i++;
    }

    return -1;
}

void ghost::copyToInitList()
{
    initSmartMoves.clear();
    initSmartMoves = smartMoves;
}

void ghost::copyFromInitList()
{
    smartMoves.clear();
    smartMoves=initSmartMoves;
}

int ghost::getSmartMovesSize()
{
    return smartMoves.size();
}
