
#include "Creature.h"

Creature::Creature(const char drawing, const Position& initPos, const Direction& dir): drawing(drawing), 
			dir(dir), framesSinceMove(0), prev(initPos), initPos(initPos)
{
    
}

Creature::~Creature()
{
    
}

Position Creature::CalculateNext(BoardGame& board) {
    //function to calculate the next move of a creature according to its direction
    Position next(0, 0);
    switch(dir)
    {
    case Direction::RIGHT:
        next.x = (pos.x + 1) %board.getColSize();
        next.y = pos.y;
        break;
    case Direction::LEFT:
        next.x = (pos.x - 1) % board.getColSize();
        if (next.x < 0) next.x = board.getColSize() + next.x;
        next.y = pos.y;
        break;
    case Direction::DOWN:
        next.x = pos.x;
        next.y = (pos.y + 1) % board.getRowSize();
        break;
    case Direction::UP:
        next.x = pos.x;
        next.y = (pos.y - 1) % board.getRowSize();
        if (next.y < 0) next.y = board.getRowSize() + next.y;
        break;
    case Direction::STAY:
        next.x = pos.x;
        next.y = pos.y;
        break;
    default:
        break;
    }
    return next;
}

const Position& Creature::getPos() const
{
    return pos;
}

const Position& Creature::getPrev() const
{
    return prev;
}

void Creature::SetDir(const Direction& dir)
{
    this->dir = dir;
}

void Creature::setFrames(const int framesSinceMove)
{
    this->framesSinceMove = framesSinceMove;
}

int Creature::getFrames() const 
{
    return framesSinceMove;
}

const Direction& Creature::getDir() const
{
    return dir;
}

void Creature::setChar(const char drawing)
{
    this->drawing = drawing;
}

void Creature::chooseRandomDir(BoardGame& board)
{
    //there are 4 possibillities for the ghost's next move: up\down\left\right
    paths possiblities[4] = {};
    //get non blocked cells\direction (not walls\tunnels)
    getPossiblePos(board, possiblities);
    //choose an available direction randomly:
    int choose = rand() % 4;

    bool changed = false;

    for (int i = 0; i < 4; i++)
    {
        if (possiblities[(i + choose) % 4].available)
        {
            SetDir(possiblities[(i + choose) % 4].way);
            changed = true;
        }
    }

    if (!changed)
    {
        SetDir(Direction::STAY);
    }
}

void Creature::getPossiblePos( BoardGame& board, paths possibilities[4])
{
    //this function returns available directions\cells for the ghost to move to from a specific cell
   
    if(board.getCellData(pos.x-1 , pos.y)!= gameObjectType::WALL&& 
        board.getCellData(pos.x - 1, pos.y) != gameObjectType::INVALID)
    {
        possibilities[int(Direction::LEFT)].way = Direction::LEFT;
        possibilities[int(Direction::LEFT)].available = pos.x-1>1;
    }

    if (board.getCellData(pos.x + 1, pos.y) != gameObjectType::WALL &&
        board.getCellData(pos.x + 1, pos.y) != gameObjectType::INVALID)
    {
        possibilities[int(Direction::RIGHT)].way = Direction::RIGHT;
        possibilities[int(Direction::RIGHT)].available = pos.x+1<board.getColSize()-1;
    }
    if (board.getCellData(pos.x , pos.y-1) != gameObjectType::WALL &&
        board.getCellData(pos.x , pos.y-1) != gameObjectType::INVALID)
    {
        possibilities[int(Direction::UP)].way = Direction::UP;
        possibilities[int(Direction::UP)].available = pos.y-1>1;
    }
    if (board.getCellData(pos.x , pos.y+1) != gameObjectType::WALL &&
        board.getCellData(pos.x , pos.y+1) != gameObjectType::INVALID)
    {
        possibilities[int(Direction::DOWN)].way = Direction::DOWN;
        possibilities[int(Direction::DOWN)].available = pos.y+1<board.getRowSize()-1;
    }
}

void Creature::redrawCreature(BoardGame& board)
{
    BoardGame::drawPos(prev.x, prev.y, &board,drawing);
    BoardGame::drawPos(pos.x, pos.y, &board, drawing);

}

void Creature::setInitPos(Position initPos)
{
    this->initPos=initPos;
    this->pos=initPos;
    this->prev=initPos;
}

collisionFlags Creature::moveCreature(BoardGame& board)
{
    //virtual function - implemention in derived classess
    collisionFlags cf;
    return cf;
}

string Creature::addToSave(size_t frames)
{
    return "";
}

char Creature::convertDirToLetter(Direction dir)
{
    switch(dir)
    {
        case(Direction::DOWN):
        return 'D';
        break;
        case(Direction::UP):
        return 'U';
        break;
        case(Direction::STAY):
        return 'S';
        break;
        case(Direction::LEFT):
        return 'L';
        break;
        case(Direction::RIGHT):
        return 'R';
        break;
        default:
        return 0;
        break;    
    }
    
}
