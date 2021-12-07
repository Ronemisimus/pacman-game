
#include "Creature.h"


Position Creature::CalculateNext() {
    Position next(0, 0);
    switch(dir)
    {
    case Direction::RIGHT:
        next.x = (pos.x + 1) % boardSize;
        next.y = pos.y;
        break;
    case Direction::LEFT:
        next.x = (pos.x - 1) % boardSize;
        if (next.x < 0) next.x = boardSize + next.x;
        next.y = pos.y;
        break;
    case Direction::DOWN:
        next.x = pos.x;
        next.y = (pos.y + 1) % boardSize;
        break;
    case Direction::UP:
        next.x = pos.x;
        next.y = (pos.y - 1) % boardSize;
        if (next.y < 0) next.y = boardSize + next.y;
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
void Creature::chooseRandomDir(cell board[boardSize][boardSize])
{
    //there are 4 possibillities for the ghost's next move: up\down\left\right
    path possiblities[4] = {};
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

void Creature::getPossiblePos(cell board[boardSize][boardSize], path possibilities[4])
{
    //this function returns available directions\cells for the ghost to move to from a specific cell
    if (pos.x - 1 > 0 &&
        board[pos.x - 1][pos.y].data != gameObjectType::WALL)
    {
        possibilities[int(Direction::LEFT)].way = Direction::LEFT;
        possibilities[int(Direction::LEFT)].available = true;
    }
    if (pos.x + 1 < boardSize - 1 &&
        board[pos.x + 1][pos.y].data != gameObjectType::WALL)
    {
        possibilities[int(Direction::RIGHT)].way = Direction::RIGHT;
        possibilities[int(Direction::RIGHT)].available = true;
    }
    if (pos.y - 1 > 0 &&
        board[pos.x][pos.y - 1].data != gameObjectType::WALL)
    {
        possibilities[int(Direction::UP)].way = Direction::UP;
        possibilities[int(Direction::UP)].available = true;
    }
    if (pos.y + 1 < boardSize - 1 &&
        board[pos.x][pos.y + 1].data != gameObjectType::WALL)
    {
        possibilities[int(Direction::DOWN)].way = Direction::DOWN;
        possibilities[int(Direction::DOWN)].available = true;
    }
}

void Creature::drawPos(int x, int y, cell board[boardSize][boardSize], char drawing)
{
    //this function draws the data for a specific board cell
    if (x > 0 && y > 0)
    {
        if (board[x][y].data != gameObjectType::EMPTY)
        {
            gotoxy(3 * (x + 1), y);
            printf("%3c\n", drawing);

        }
        else if (board[x][y].food)
        {
            gotoxy(3 * (x + 1), y);
            printf("%3c\n", CHAR_FOOD);
        }
        else
        {
            gotoxy(3 * (x + 1), y);
            printf("%3c\n", ' ');
        }
    }
}
void Creature::redrawCreature(cell board[boardSize][boardSize])
{
    drawPos(prev.x, prev.y, board,drawing);
    drawPos(pos.x, pos.y, board, drawing);

}

