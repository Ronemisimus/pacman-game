
#pragma once

#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "pacman.h"
#include "ghost.h"
#include "GhostMoveStrategy.h"
#include "fruit.h"
#include "collisionFlags.h"

class Game
{
private:
   
    fruit fruit1;
    bool isPaused;
    bool waitForMove; // after strike pause until player moves
    BoardGame* board;
    pacman* player;
	vector <ghost> enemies;
   
public:
    Game(BoardGame* board);
    
    void redrawBoard();
    void updateBoard();
    bool isDone();
    void changeBoard(BoardGame* next);
    void resetStats();
    void calculateSmartMoves();
    
};