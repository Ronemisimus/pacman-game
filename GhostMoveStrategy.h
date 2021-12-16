#pragma once
#include "global.h"
#include "ghost.h"
#include "BoardGame.h"

class GhostMoveStrategy
{
private:
    
public:
    GhostMoveStrategy() = delete;
    ~GhostMoveStrategy() = delete;

    static int ghostMoves;

    static Direction getNextDir(ghost& ghost, GhostStrategy level, BoardGame& board);
    static Direction bestMove(ghost& ghost, BoardGame& board);
    static Direction goodMove(ghost& ghost, BoardGame& board);
    static Direction noviceMove(ghost& ghost, BoardGame& board);
};
