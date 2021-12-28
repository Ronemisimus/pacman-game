#pragma once
#include "global.h"
#include "ghost.h"
#include "pacman.h"
#include "BoardGame.h"

class GhostMoveStrategy
{//this class handles the ghost's difficulty levels
private:
    
public:
    GhostMoveStrategy() = delete;
    ~GhostMoveStrategy() = delete;

    static int ghostMoves;
    static int colSize, rowSize; //size of the board

    static Direction getNextDir(ghost& ghost, GhostStrategy level, BoardGame& board);
    static Direction bestMove(ghost& ghost, BoardGame& board);
    static Direction goodMove(ghost& ghost, BoardGame& board);
    static Direction noviceMove(ghost& ghost, BoardGame& board);
    static int** initStepsBoard(ghost& ghost, BoardGame& board);
    static void fillStepsBoard(int** stepsBoard, Position source);
    static void fillStepsList(ghost& ghost, int** stepsBoard);
    static void freeStepsBoard(int** stepsBoard);
    static void fillUnfilledPlaces(int** stepsBoard);

};
