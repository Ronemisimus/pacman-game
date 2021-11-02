#include "game.h"

Game::Game(): enemy(ghost()) ,foodLeft(0), player(pacman())
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j].data = EMPTY;
            board[i][j].food = false;
        }
        
    }
    
}

void Game::initBoard()
{
    for(int i=0;i<boardSize;i++)
    {
        board[0][i].data = WALL;
        board[i][0].data = WALL;
        board[i][boardSize-1].data = WALL;
        board[boardSize-1][i].data = WALL;
    }

    board[5][0].data = EMPTY;
    board[0][15].data = EMPTY;
    board[5][boardSize-1].data = EMPTY;
    board[boardSize-1][15].data = EMPTY;

    board[12][0].data = EMPTY;

    Position pac = player.getPos();
    board[pac.x][pac.y].data = PACMAN;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if(board[i][j].data == EMPTY &&
            i!=0 && j!=0 && i!=boardSize-1 && j!=boardSize-1)
            {
                board[i][j].food = true;
                foodLeft++;
            }
        }
        
    }
    
}

void Game::drawBoard()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            drawPos(i,j);
        }
        
    }

    gotoxy(0,22);
    
}

void Game::drawPos(int x, int y)
{
    if(board[x][y].data!=EMPTY)
    {
        switch (board[x][y].data)
        {
        case WALL:
            gotoxy(3*(x+1),y);
            printf("%3c\n", CHAR_WALL);
            break;
        
        case GHOST:
            gotoxy(3*(x+1),y);
            printf("%3c\n", CHAR_ENEMY);
            break;
        
        case PACMAN:
            gotoxy(3*(x+1),y);
            printf("%3c\n", CHAR_PACMAN);
            break;
        
        default:
            break;
        }
    }   
    else if(board[x][y].food)
    {
        gotoxy(3*(x+1),y);
        printf("%3c\n", CHAR_FOOD);
    }
    else
    {
        gotoxy(3*(x+1),y);
        printf("%3c\n", ' ');
    }
}

bool Game::isDone()
{
    return player.getLives()==0 || foodLeft==0;
}

Direction getNewDir()
{
    if( _kbhit())
    {
        char key = _getch();
        gotoxy(0, boardSize + 2);
        cout << "key pressed: " << key << '\n';

        switch (key)
        {
        case RIGHT_KEY_op1:
        case RIGHT_KEY_op2:
            return RIGHT;
            break;
        case LEFT_KEY_op1:
        case LEFT_KEY_op2:
            return LEFT;
            break;
        case UP_KEY_op1:
        case UP_KEY_op2:
            return UP;
            break;
        case DOWN_KEY_op1:
        case DOWN_KEY_op2:
            return DOWN;
            break;
        case STAY_KEY_op1:
        case STAY_KEY_op2:
            return STAY;
            break;
        case ESC_KEY:
        default:
            return NOCHANGE;
            break;
        }
    }
    else
    {
        return NOCHANGE;
    }
}

void Game::updateBoard()
{
    player.setFrames(player.getFrames()+1);
    enemy.setFrames(enemy.getFrames()+1);
    bool moved = true;
    if(player.getFrames()==PACMAN_SPEED)
    {
        moved = player.movePacman(board, foodLeft);
        player.setFrames(0);
    }
    if(enemy.getFrames()==GHOST_SPEED)
    {
        enemy.moveGhost(board);
        enemy.setFrames(0);
    }

    Direction dir = getNewDir();

    if(dir!=NOCHANGE)
    {
        player.setDir(dir);
    }

    
}

void Game::redrawBoard()
{
    Position prev = player.getPrevPos();
    Position next = player.getPos();

    Position enemyPrev = enemy.getPrevPos();
    Position enemyNext = enemy.getPos();
    
    drawPos(prev.x,prev.y);
    drawPos(next.x,next.y);
    drawPos(enemyPrev.x, enemyPrev.y);
    drawPos(enemyNext.x, enemyNext.y);

}

int Game::getFoodLeft()
{
    return foodLeft;
}