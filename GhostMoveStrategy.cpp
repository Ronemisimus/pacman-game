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
{//move ghost in best level
    Direction res = Direction::STAY;

    /*Position smartNext=ghost.removeFromStartOfSmartList();

    res = getDirFromPos(ghost.getPos(),smartNext);

    return res; */
    ghost.emptyStepsList();
    int** stepsboard = initStepsBoard(ghost, board);
    fillStepsBoard(stepsboard, ghost.getPos());
    fillUnfilledPlaces(stepsboard);
    fillStepsList(ghost, stepsboard);

    Position next = ghost.removeFromStartOfSmartList();

    res = getDirFromPos(ghost.getPos(), next);

    return res;

}

Direction GhostMoveStrategy::goodMove(ghost& ghost, BoardGame& board)
{//move ghost in good level
    //random moves:
    if (ghostMoves >= 0 && ghostMoves < 5)
    {
        if (ghostMoves == 0)
        {//choose random smart moves amount
            ghostMoves = 21 + rand() % 5;
        }
        else
        {
            if (ghostMoves == 5)
            {//move in a random direction for 5 next moves
                ghost.chooseRandomDir(board);
            }
            ghostMoves--;
        }
        //calculate next move
        Position next = ghost.CalculateNext(board);
        int toRemove = ghost.findInList(next);
        
        if (toRemove == -1)
        {//if random move isn't according to the list- add it
            if (next.x != ghost.getPos().x ||
                next.y != ghost.getPos().y)
            {
                ghost.addToStartOfSmartList(ghost.getPos());
            }
        }
        else
        {//prevent loops
            toRemove = ghost.getSmartMovesSize() - toRemove;

            if (ghost.getSmartMovesSize() != 0)
            {
                toRemove++;
            }

            while (toRemove > 0)
            {
                ghost.removeFromStartOfSmartList();
                toRemove--;
            }
        }
        //prevent movement into walls
        if (next.x > 0 && next.x < board.getColSize() &&
            next.y>0 && next.y < board.getRowSize() &&
            board.getCellData(next.x, next.y) != gameObjectType::WALL)
        {
            return ghost.getDir();
        }
        else
        {
            return Direction::STAY;
        }
    }
    //smart moves:
    else
    {
        ghostMoves--;
        return bestMove(ghost, board);
    }
}

Direction GhostMoveStrategy::noviceMove(ghost& ghost, BoardGame& board)
{//move ghost in novice level
    //choose random direction once every 20 moves
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
    //creates a parallel board to count steps:
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
                stepsBoard[i][j]=wallSteps;//blocks walking into walls
                break;
            default:
                stepsBoard[i][j]=-1;//empty reachable cell in the initiallization
                break;
            }
        }
    }

    stepsBoard[ghostPos.x][ghostPos.y] = 0;

    return stepsBoard;

}

void GhostMoveStrategy::fillStepsBoard(int** stepsBoard, Position source)
{
    //fills the parallel board with step count for every location the ghost can reach:
       //step count - the minimal amount of steps the  ghost needs to reach a certain cell
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
{//backtracking from pacman's position to the ghost
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
        if(min==stepsBoard[current.x][current.y])
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


