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

Direction getDirFromPos(Position ghost, Position next)
{
    int x = next.x-ghost.x;
    int y = next.y-ghost.y;

    if(x==1)
    {
        return Direction::RIGHT;
    }
    if(x==-1)
    {
        return Direction::LEFT;
    }
    if(y==-1)
    {
        return Direction::UP;
    }
    if(y==1)
    {
        return Direction::DOWN;
    }

    return Direction::STAY;
}

Direction GhostMoveStrategy::bestMove(ghost& ghost, BoardGame& board)
{
    Direction res = Direction::STAY;

    Position smartNext=ghost.removeFromStartOfSmartList();

    res = getDirFromPos(ghost.getPos(),smartNext);

    return res;

}

Direction GhostMoveStrategy::goodMove(ghost& ghost, BoardGame& board)
{
    if(ghostMoves>=0 && ghostMoves<5)
    {
        if(ghostMoves==0)
        {
            ghostMoves = 21+rand()%5;
            ghost.chooseRandomDir(board);
        }
        else
        {
            ghostMoves--;
        }
        Position next = ghost.CalculateNext(board);
        int toRemove = ghost.findInList(next);

        if(toRemove==-1)
        {
            if(next.x!=ghost.getPos().x ||
                next.y!=ghost.getPos().y)
            {
                ghost.addToStartOfSmartList(ghost.getPos());
            }
        }
        else
        {
            toRemove = ghost.getSmartMovesSize() - toRemove;

            if(ghost.getSmartMovesSize()!=0)
            {
                toRemove++;
            }

            while (toRemove>0)
            {
                ghost.removeFromStartOfSmartList();
                toRemove--;
            }
        }

        return ghost.getDir();
    }
    else 
    {
        ghostMoves--;
        return bestMove(ghost, board);
    }

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
    bool hasMove=true;
    Position current = ghost.getTarget().getPos();
    while(hasMove && stepsBoard[current.x][current.y]!=0)
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
        if(min==stepsBoard[current.x-1][current.y])
        {
            hasMove=false;
        }
        current = minPos;
    }

    if(current.x!=ghost.getPos().x ||
        current.y!=ghost.getPos().y)
    {
        while(ghost.getSmartMovesSize()>0)
        {
            ghost.removeFromStartOfSmartList();
        }
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

void GhostMoveStrategy::fillUnfilledPlaces(int** stepsBoard)
{
    int max = rowSize*colSize+1;
    for(int i=0;i<colSize;i++)
    {
        for(int j=0;j<rowSize;j++)
        {
            if(stepsBoard[i][j]==-1)
            {
                stepsBoard[i][j]=max;
            }
        }
    }
}


