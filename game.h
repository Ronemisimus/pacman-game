
#pragma once

#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "pacman.h"
#include "ghost.h"
#include "fruit.h"
#include "collisionFlags.h"
#include <vector>

using std::vector;
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
    
};