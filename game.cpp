#include "game.h"

Game::Game(BoardGame * board):  isPaused(false), waitForMove(true), board(board)
{
    if(board)
    {
        player = new pacman(board->getPacInitPos());
        changeBoard(board);
    }
}

void Game::changeBoard(BoardGame* next)
{
    isPaused = false;
    waitForMove = true;
    board= next;
    player->setInitPos(next->getPacInitPos());
    Position* ghostPos = board->getGhostsInitPos();
    enemies.clear();
    for (int i = 0; i < board->getGhostsNum(); i++)
    {
        enemies.push_back(ghost(board->getRowSize(), board->getColSize(), ghostPos[i], *player));
    }
}

bool Game::isDone()
{
    return player->getLives()==0 || board->getFoodLeft() ==0;
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
        player->setFrames(player->getFrames() + 1);
      
        for (int i = 0; i < board->getGhostsNum(); i++)
        {
            auto& enemy = enemies[i];
            enemy.setFrames(enemy.getFrames() + 1);
        }
     
        
        collisionFlags cf;
        if (fruit1.getExist())
        {
            fruit1.setFrames(fruit1.getFrames() + 1);
            if (fruit1.getFrames() == FRUIT_SPEED)
            {
                fruit1.chooseRandomDir(*board);
                if (!cf.getPacmanGhost() && !cf.getPacmanFruit() && !cf.getFruitGhost())
                    cf = cf + fruit1.moveFruit(*board);
                fruit1.setFrames(0);

            }

            fruit1.decreseLifeTime();

        }
        else
        {
            fruit1.chooseBeValue();
            if (fruit1.getExist())
            {
                fruit1.chooseInitPos(*board);
                fruit1.chooseLifeTime();
                fruit1.SetDir(Direction::STAY);
                fruit1.setFrames(0);
            }
        }
        // if the clock is reached we update the character
        if(player->getFrames()==PACMAN_SPEED)
        {
            // move pacman and check for lives lost
            cf = player->movePacman(*board);

            if(ghost::level != GhostStrategy::NOVICE)
            {
                updateGhostsSmatMoveList(player->getPos());       
            }

            //reset clock
            player->setFrames(0);
        }
        for (int i = 0; i < board->getGhostsNum(); i++)
        {
            // move ghost if clock is reached
            auto& enemy = enemies[i];
            if (enemy.getFrames() == GHOST_SPEED)
            {
                if (!cf.getPacmanGhost())
                    // move ghost and check for lives lost by pacman
                    cf = cf + enemy.moveGhost(*board);
                   
                //reset clock
                enemy.setFrames(0);
            }
        }
        // if a life was lost reset the board
        if(cf.getPacmanGhost())
        {
            redrawBoard();
            player->strike(*board);
          
            for (int i = 0; i < board->getGhostsNum(); i++)
            {
               
                auto& enemy = enemies[i];
                enemy.strike(*board);
            }
            // set pause until input is received
            waitForMove = true;
            fruit1.resetfruit();
            
        }
        else if (cf.getPacmanFruit())
        {
            player->addFruitPoints(fruit1.getValue());
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
            gotoxy(board->getColSize() / 2, board->getRowSize());
            cout << "Game is paused. Click esc to continue!" << '\n';
        }
        else
        {
            gotoxy(board->getColSize() / 2, board->getRowSize());
            cout << "                                         " << '\n';
        }
        
    }

    if(dir!= Direction::NOCHANGE && dir!= Direction::PAUSE)
    {
        // if the game isn't paused but waits input then continue
        waitForMove = false;
        player->SetDir(dir);
    }

    
}

void Game::redrawBoard()
{
    //this function redraws the updated board for every frame
    if (fruit1.getExist())
    {
        fruit1.redrawCreature(*board);
    }
    if (fruit1.getToDelete())
    {
        fruit1.deleteFromBoard(*board);
    }
   player->redrawCreature(*board);

   for (int i = 0; i < board->getGhostsNum(); i++)
   {

       auto& enemy = enemies[i];
       enemy.redrawCreature(*board);
    }
   
    //update points\lives count:
    gotoxy(board->getLegendPos().x, board->getLegendPos().y);
    cout << "Lives: " << player->getLives() << '|';
   
    cout << "Points: " << player->getPoints() << endl;

}

void Game::resetStats()
{
    player->resetLives();
    player->resetPoints();
}

void Game::calculateSmartMoves()
{
    GhostMoveStrategy::colSize = board->getColSize();
    GhostMoveStrategy::rowSize = board->getRowSize();

    for(auto& ghost:enemies)
    {
        int** stepsBoard = GhostMoveStrategy::initStepsBoard(ghost, *board);
        GhostMoveStrategy::fillStepsBoard(stepsBoard, ghost.getPos());
        GhostMoveStrategy::fillStepsList(ghost, stepsBoard);
        GhostMoveStrategy::freeStepsBoard(stepsBoard);
        ghost.copyToInitList();
    }
}

void Game::updateGhostsSmatMoveList(Position playerPos)
{
    for(auto& ghost:enemies)
    {
        Position lastSmartMove = ghost.removeFromEndOfSmartList();
        int stepsCanceled = ghost.findInList(playerPos);

        if(stepsCanceled!=-1)
        {
            if(stepsCanceled>1)
            {
                stepsCanceled--;
                while (stepsCanceled>0)
                {
                    ghost.removeFromEndOfSmartList();
                    stepsCanceled--;
                }
                
            }
        }
        else
        {
            ghost.addToEndOfSmartList(lastSmartMove);
            if(playerPos.x!=lastSmartMove.x ||
                playerPos.y!=lastSmartMove.y)
            {
                ghost.addToEndOfSmartList(playerPos);
            }
        }
    }
}

