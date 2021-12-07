#include "ghost.h"

ghost::ghost(): Creature(CHAR_ENEMY, Position(boardSize - 2, boardSize - 2), Direction::STAY)
{
    pos = initPos;
}


collisionFlags ghost::moveGhost(cell board[boardSize][boardSize])
{
    collisionFlags cf;
    //function that in charge of the ghosts' movement

    chooseRandomDir(board);
    
    //move the ghost accordingly:
    prev = pos;
    pos = CalculateNext();
        
    board[prev.x][prev.y].data = gameObjectType::EMPTY;
    //check if the ghost ate packman:
    cf.setPacmanGhost(board[pos.x][pos.y].data == gameObjectType::PACMAN);
    cf.setFruitGhost(board[pos.x][pos.y].data == gameObjectType::FRUIT);
    board[pos.x][pos.y].data = gameObjectType::GHOST;
    return cf;
}

void ghost::strike(cell board[boardSize][boardSize])
{
    //this function handles the case of packman losing a life
    prev = pos;
    pos = initPos;

    board[prev.x][prev.y].data = gameObjectType::EMPTY;
    board[pos.x][pos.y].data = gameObjectType::GHOST;

}

