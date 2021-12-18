#include "BoardGame.h"

BoardGame::BoardGame(int rowSize,int colSize)
{
    int  col;
    board = new cell*[colSize];
    for (col = 0; col < colSize; col++)
    {
        board[col] = new cell[rowSize];
    }
    for(int i=0;i<colSize;i++)
    {
        for(int j=0; j<rowSize;j++)
        {
            board[i][j] = {false, gameObjectType::EMPTY};
        }
    }
    this->rowSize = rowSize;
    this->colSize = colSize;
    this->numOfGhosts = 0;
    this->numOfFood = 0;
    this->legend = Position(-1,-1);
    this->pacInitPos = Position(-1,-1);
}

BoardGame::~BoardGame()
{
    for(int i=0;i<colSize;i++)
    {
        delete [] board[i];
    }
    delete [] board;
}


void BoardGame::initBoard(ifstream& file)
{
    int row, col;
    bool lineEnded = false;
    char data;
    for (row = 0; row < rowSize; row++)
    {
        lineEnded = false;
        for (col = 0; col < colSize; col++)
        {
            if(!lineEnded)
            {
                data=file.get();
            }
            if(data=='\r')
            {
                data=file.get();
            }
            if(data=='\n')
            {
                lineEnded=true;
                data = CHAR_EMPTY;
            }
            if(!lineEnded && !file.good())
            {
                data=CHAR_EMPTY;
                lineEnded=true;
            }
            switch (data) {
            case CHAR_WALL:
                board[col][row].data = gameObjectType::WALL;
                board[col][row].food = false;
                break;
            case CHAR_ENEMY:
                board[col][row].data = gameObjectType::GHOST;
                board[col][row].food = false;
                numOfGhosts++;
                enemyInitPos.push_back(Position(col,row));
                break;
            case CHAR_PACMAN:
                board[col][row].data = gameObjectType::PACMAN;
                board[col][row].food = false;
                pacInitPos = Position(col,row);
                break;
            case ' ':
                board[col][row].data = gameObjectType::EMPTY;
                board[col][row].food = true;
                numOfFood++;
                break;
            case CHAR_LEGEND:
                legend = Position(col, row);
                break;
            //empty space without food and \n:
            default:
                board[col][row].data = gameObjectType::EMPTY;
                board[col][row].food = false;
                break;
            }
          
        }
        if(!lineEnded)
        {
            while(data!='\n' && file.good())
            {
                data = file.get();
            }
        }
    }
    
    /* while (file.good())
    {
        char data = file.get();
        col++;
        if (data == '\r') {
            data = file.get();
        }
        if (data == '\n')
        {
            row++;
            col = 0;
            data = file.get();
        }

        if (data == CHAR_LEGEND)
        {
            legend = Position(col, row);
        }

    } */

}

Position BoardGame::getPacInitPos()
{
    return this->pacInitPos;
}

Position* BoardGame::getGhostsInitPos()
{
    return this->enemyInitPos.data();
}

int BoardGame::getGhostsNum()
{
    return numOfGhosts;
}

int BoardGame::getFoodLeft()
{
    return numOfFood;
}

void BoardGame::setBoardCellData(int x, int y, gameObjectType data)
{
    board[x][y].data = data;
}

char BoardGame::getCharFromData(gameObjectType data)
{
    switch (data)
    {
    case gameObjectType::WALL:
        return CHAR_WALL;
        break;
    case gameObjectType::GHOST:
        return CHAR_ENEMY;
        break;
    case gameObjectType::PACMAN:
        return CHAR_PACMAN;
        break;
    case gameObjectType::EMPTY:
        return ' ';
    default:
        return 0;
        break;

    }
}

void BoardGame::drawBoard()
{
    //this function draws the whole board at the beginning of the game

    for (int i = 0; i < colSize; i++)
    {
        for (int j = 0; j < rowSize; j++)
        {
            char drawing = getCharFromData(getCellData(i,j));
            drawPos(i,j,this,drawing);
        }

    }
}

int BoardGame::getRowSize()
{
    return this->rowSize;
}

int BoardGame::getColSize()
{
    return this->colSize;
}

void BoardGame::updatePosition(int x, int y, cell data)
{
    board[x][y] = data;
}

gameObjectType BoardGame::getCellData(int x, int y)
{
    if (x<0 || x>colSize-1 || y > rowSize-1 || y < 0)
        return gameObjectType::INVALID;
    else
    return board[x][y].data;
}

bool BoardGame::getIsThereFood(int x, int y)
{
    return board[x][y].food;
}

void BoardGame::setIsThereFood(int x, int y, bool value)
{
    if (board[x][y].food != value)
    {
        if (value == false)
            numOfFood--;
        else
            numOfFood++;
    }
    board[x][y].food = value;

}

void BoardGame::drawPos(int x, int y, BoardGame* board, char drawing)
{
    //this function draws the data for a specific board cell
    if (board->getCellData(x,y)!=gameObjectType::INVALID)
    {
        
        if (board->getCellData(x, y) != gameObjectType::EMPTY)
        {
            gotoxy(3 * (x + 1), y);
            printf("%3c\n", drawing);

        }
       
        else if (board->getIsThereFood(x, y))
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

Position BoardGame::getLegendPos()
{
    return legend;
}
