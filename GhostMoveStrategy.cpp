#include "GhostMoveStrategy.h"

int GhostMoveStrategy::ghostMoves=0;

Direction GhostMoveStrategy::getNextDir(ghost& ghost, GhostStrategy level, BoardGame& board)
{
    switch (level)
    {
    case GhostStrategy::BEST:
        return bestMove(ghost, board);
        break;
    case GhostStrategy::GOOD:
        return goodMove(ghost,board);
        break;
    case GhostStrategy::NOVICE:
        return noviceMove(ghost,board);
        break;
    default:
        return Direction::STAY;
        break;
    }
}

Direction GhostMoveStrategy::bestMove(ghost& ghost, BoardGame& board)
{
    return Direction::STAY;
}

Direction GhostMoveStrategy::goodMove(ghost& ghost, BoardGame& board)
{
    return Direction::STAY;
}

Direction GhostMoveStrategy::noviceMove(ghost& ghost, BoardGame& board)
{
    if(GhostMoveStrategy::ghostMoves==0)
    {
        ghost.chooseRandomDir(board);
    }
    GhostMoveStrategy::ghostMoves = (GhostMoveStrategy::ghostMoves +1) % 20;
    Position next = ghost.CalculateNext(board);
    if(next.x>0 && next.x<board.getColSize() && 
        next.y>0 && next.y<board.getRowSize() && 
        board.getCellData(next.x, next.y)!=gameObjectType::WALL)
    {
        return ghost.getDir();
    }
    else
    {
        return Direction::STAY;
    }
}

