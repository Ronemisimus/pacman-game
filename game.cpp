#include "game.h"

Game::Game(): enemies() ,foodLeft(0), player(pacman()), isPaused(false), waitForMove(true)
{
    // this function initiallizes the board to empty
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j].data = gameObjectType::EMPTY;
            board[i][j].food = false;
        }
        
    }
    
}

void Game::initBoard()
{
    //set the level board:
    //set the walls:
    for(int i=0;i<boardSize;i++)
    {
        board[0][i].data = gameObjectType::WALL;
        board[i][0].data = gameObjectType::WALL;
        board[i][boardSize-1].data = gameObjectType::WALL;
        board[boardSize-1][i].data = gameObjectType::WALL;
    }
    //set tunnels:
    board[5][0].data = gameObjectType::EMPTY;
    board[0][15].data = gameObjectType::EMPTY;
    board[5][boardSize-1].data = gameObjectType::EMPTY;
    board[boardSize-1][15].data = gameObjectType::EMPTY;

    board[12][0].data = gameObjectType::EMPTY;
    //set packman's starting position:
    Position pac = player.getPos();
    board[pac.x][pac.y].data = gameObjectType::PACMAN;
    //place food in empty places:
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if(board[i][j].data == gameObjectType::EMPTY &&
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
    //this function draws the whole board at the beginning of the game
   
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            switch (board[i][j].data)
            {
            case gameObjectType::WALL:
                gotoxy(3 * (i + 1), j);
                printf("%3c\n", CHAR_WALL);

                    break;
            case gameObjectType::GHOST:
                Creature::drawPos(i,j,board,CHAR_ENEMY);
                break;
            case gameObjectType::PACMAN:
                Creature::drawPos(i,j,board,CHAR_PACMAN);
                break;
            case gameObjectType::EMPTY:
                if (board[i][j].food)
                {
                    gotoxy(3 * (i + 1), j);
                    printf("%3c\n", CHAR_FOOD);
                }
                else
                {
                    gotoxy(3 * (i + 1), j);
                    printf("%3c\n", ' ');
                }
            default:
                break;

            }
           
        }
        
    }
    //draw life and points status:
    gotoxy(0,boardSize+3);
    cout << "Lives: " << player.getLives() << '\n';
    cout << "Points: " << player.getPoints() << endl;
    
}


bool Game::isDone()
{
    return player.getLives()==0 || foodLeft==0;
}

Direction getNewDir()
{
    //function to check\get new user input for direction
    if( _kbhit())
    {
        char key = _getch();
        

        switch (key)
        {
        case RIGHT_KEY_op1:
        case RIGHT_KEY_op2:
            return Direction::RIGHT;
            break;
        case LEFT_KEY_op1:
        case LEFT_KEY_op2:
            return Direction::LEFT;
            break;
        case UP_KEY_op1:
        case UP_KEY_op2:
            return Direction::UP;
            break;
        case DOWN_KEY_op1:
        case DOWN_KEY_op2:
            return Direction::DOWN;
            break;
        case STAY_KEY_op1:
        case STAY_KEY_op2:
            return Direction::STAY;
            break;
        case ESC_KEY:
            return Direction::PAUSE;
            break;
        default:
            return Direction::NOCHANGE;
            break;
        }
    }
    else
    {
        return Direction::NOCHANGE;
    }
}

void Game::updateBoard()
{
    //this function updates the board for every frame
    // update only if not paused
    if(!waitForMove && !isPaused)
    {
        
        // advance a clock for every character in the game
        player.setFrames(player.getFrames()+1);
        for (auto& enemy : enemies)
        {
            enemy.setFrames(enemy.getFrames() + 1);
        }
        
        collisionFlags cf;
        if (fruit1.getExist())
        {
            fruit1.setFrames(fruit1.getFrames() + 1);
            if (fruit1.getFrames() == FRUIT_SPEED)
            {
                fruit1.chooseRandomDir(board);
                if (!cf.getPacmanGhost() && !cf.getPacmanFruit() && !cf.getFruitGhost())
                    cf = cf + fruit1.moveFruit(board);
                fruit1.setFrames(0);

            }

            fruit1.decreseLifeTime();

        }
        else
        {
            fruit1.chooseBeValue();
            if (fruit1.getExist())
            {
                fruit1.chooseInitPos(board);
                fruit1.chooseLifeTime();
                fruit1.SetDir(Direction::STAY);
                fruit1.setFrames(0);
            }
        }
        // if the clock is reached we update the character
        if(player.getFrames()==PACMAN_SPEED)
        {
            // move pacman and check for lives lost
            cf = player.movePacman(board, foodLeft);
            //reset clock
            player.setFrames(0);
        }
        for (auto& enemy : enemies)
        {
            // move ghost if clock is reached
            if (enemy.getFrames() == GHOST_SPEED)
            {
                if (!cf.getPacmanGhost())
                    // move ghost and check for lives lost by pacman
                    cf = cf + enemy.moveGhost(board);
                   
                //reset clock
                enemy.setFrames(0);
            }
        }
      /*  if (fruit.getExist())
        {
            fruit.setFrames(fruit.getFrames() + 1);
            if (fruit.getFrames() == FRUIT_SPEED)
            {
                fruit.chooseRandomDir(board);
                if(!cf.getPacmanGhost()&&!cf.getPacmanFruit()&&!cf.getFruitGhost())
                    cf=cf+fruit.moveFruit(board);
                fruit.setFrames(0);

            }

            fruit.decreseLifeTime();

        }
        else
        {
            fruit.chooseBeValue();
            if (fruit.getExist())
            {
                fruit.chooseInitPos(board);
                fruit.chooseLifeTime();
                fruit.SetDir(Direction::STAY);
                fruit.setFrames(0);
            }
        }*/
        // if a life was lost reset the board
        if(cf.getPacmanGhost())
        {
            redrawBoard();
            player.strike(board);
            for (auto& enemy : enemies)
            {
                enemy.strike(board);
            }
            // set pause until input is received
            waitForMove = true;
            fruit1.resetfruit();
            
        }
        else if (cf.getPacmanFruit())
        {
            player.addFruitPoints(fruit1.getValue());
            fruit1.resetfruit();
        }
        else if(cf.getFruitGhost())
        {
            fruit1.resetfruit();
        }
    }
//get new direction from user's input
    Direction dir = getNewDir();
    if(!waitForMove && dir == Direction::PAUSE)
    {
        //change pause mode
        isPaused = !isPaused;
        //message about pausing the game:
        if (isPaused)
        {
            gotoxy(boardSize / 2, boardSize);
            cout << "Game is paused. Click esc to continue!" << '\n';
        }
        else
        {
            gotoxy(boardSize / 2, boardSize);
            cout << "                                         " << '\n';
        }
        
    }

    if(dir!= Direction::NOCHANGE && dir!= Direction::PAUSE)
    {
        // if the game isn't paused but waits input then continue
        waitForMove = false;
        player.SetDir(dir);
    }

    
}

void Game::redrawBoard()
{
    //this function redraws the updated board for every frame
    if (fruit1.getExist())
    {
        fruit1.redrawCreature(board);
    }
    if (fruit1.getToDelete())
    {
        fruit1.deleteFromBoard(board);
    }
    player.redrawCreature(board);

    for (auto& enemy : enemies)
    {
       enemy.redrawCreature(board);
    }
   
    //update points\lives count:
    gotoxy(0, boardSize + 3);
    cout << "Lives: " << player.getLives() << '\n';
    cout << "Points: " << player.getPoints() << endl;

}

int Game::getFoodLeft()
{
    return foodLeft;
}