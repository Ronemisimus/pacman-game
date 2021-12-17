#include "GhostMoveStrategy.h"

int GhostMoveStrategy::ghostMoves=0;
int GhostMoveStrategy::colSize=0;
int GhostMoveStrategy::rowSize=0;

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

int** GhostMoveStrategy::initStepsBoard(ghost& ghost, BoardGame& board){
    int ** stepsBoard = new int*[colSize];

    int wallSteps = colSize*rowSize+1; // not possible to move that much

    Position ghostPos= ghost.getPos();

    for(int i=0;i<colSize;i++)
    {
        stepsBoard[i] = new int[rowSize];

        for(int j=0;j<rowSize;j++)
        {
            switch (board.getCellData(i, j))
            {
            case gameObjectType::WALL:
                stepsBoard[i][j]=wallSteps;
                break;
            default:
                stepsBoard[i][j]=-1;
                break;
            }
        }
    }

    stepsBoard[ghostPos.x][ghostPos.y] = 0;

    return stepsBoard;

}

void GhostMoveStrategy::fillStepsBoard(int** stepsBoard, Position source)
{
    list<Position> toFillAround;

    toFillAround.push_front(source);

    Position current;

    while(toFillAround.size()>0)
    {
        current = toFillAround.back();
        toFillAround.pop_back();
        if(current.x-1>=0 && stepsBoard[current.x-1][current.y]==-1)
        {
            stepsBoard[current.x-1][current.y] = stepsBoard[current.x][current.y] +1;
            toFillAround.push_front(Position(current.x-1, current.y));
        }
        if(current.x+1<colSize && stepsBoard[current.x+1][current.y]==-1)
        {
            stepsBoard[current.x+1][current.y] = stepsBoard[current.x][current.y] +1;
            toFillAround.push_front(Position(current.x+1, current.y));
        }
        if(current.y-1>=0 && stepsBoard[current.x][current.y-1]==-1)
        {
            stepsBoard[current.x][current.y-1] = stepsBoard[current.x][current.y] +1;
            toFillAround.push_front(Position(current.x, current.y-1));
        }
        if(current.y+1<rowSize && stepsBoard[current.x][current.y+1]==-1)
        {
            stepsBoard[current.x][current.y+1] = stepsBoard[current.x][current.y] +1;
            toFillAround.push_front(Position(current.x, current.y+1));
        }
    }
}

void GhostMoveStrategy::fillStepsList(ghost& ghost, int** stepsBoard)
{
    Position current = ghost.getTarget().getPos();
    while(stepsBoard[current.x][current.y]!=0)
    {
        ghost.addToStartOfSmartList(current);

        int min = stepsBoard[current.x][current.y];
        Position minPos = current;
        if(current.x-1>=0 && stepsBoard[current.x-1][current.y]<min)
        {
            min = stepsBoard[current.x-1][current.y];
            minPos = Position(current.x-1, current.y);
        }
        if(current.x+1<colSize && stepsBoard[current.x+1][current.y]<min)
        {
            min = stepsBoard[current.x+1][current.y];
            minPos = Position(current.x+1, current.y);
        }
        if(current.y-1>=0 && stepsBoard[current.x][current.y-1]<min)
        {
            min = stepsBoard[current.x][current.y-1];
            minPos = Position(current.x, current.y-1);
        }
        if(current.y+1<rowSize && stepsBoard[current.x][current.y+1]<min)
        {
            min = stepsBoard[current.x][current.y+1];
            minPos = Position(current.x, current.y+1);
        }
        current = minPos;
    }
}

void GhostMoveStrategy::freeStepsBoard(int** stepsBoard)
{
    for(int i=0;i<colSize;i++)
    {
        delete [] stepsBoard[i];
    }
    delete [] stepsBoard;
}


