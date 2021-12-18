#include "game.h"

Game::Game(BoardGame * board):  isPaused(false), waitForMove(true), board(board)
{
    if(board)
    {
        player = new pacman(board->getPacInitPos());
        changeBoard(board);
    }
}

Game::~Game()
{
    if(player)
    {
        delete player;
    }
    if(board)
    {
        delete board;
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
        for(auto& creature: creatures)
        {
            bool advance = true;
            if(typeid(creature)==typeid(fruit))
            {
                advance = ((fruit*)creature)->getExist();
            }
            if(advance)
            {
                creature->setFrames(creature->getFrames() + 1);
            }
        }
     
        
        collisionFlags cf;

        if (fruit1.getExist())
        {
            if (fruit1.getFrames() == FRUIT_SPEED)
            {
                fruit1.chooseRandomDir(*board);
                if (!cf.getPacmanGhost() && !cf.getPacmanFruit() && !cf.getFruitGhost())
                    cf = cf + fruit1.moveCreature(*board);
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
            cf = player->moveCreature(*board);

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
                    cf = cf + enemy.moveCreature(*board);
                   
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
        int messageX = board->getColSize() / 2;
        int messageY = board->getRowSize() / 2; 
        //change pause mode
        isPaused = !isPaused;
        //message about pausing the game:
        if (isPaused)
        {
            gotoxy(3*(messageX+1), messageY);
            cout << "Game is paused. Click esc to continue!" << '\n';
        }
        else
        {
            gotoxy(3*(messageX+1), messageY);
            cout << "                                         " << '\n';
            
            int col = messageX;
            for(int i=0;col+i<board->getColSize()&&i<41;i++)
            {
                BoardGame::drawPos(col+i, messageY, board, 
                                    BoardGame::getCharFromData(
                                        board->getCellData(col+i, messageY)
                                        )
                                    );
            }

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
    if (!isPaused)
    {
        for(auto& creature: creatures)
        {
            if(typeid(*creature)==typeid(fruit))
            {
                if (fruit1.getExist())
                {
                    fruit1.redrawCreature(*board);
                }
                if (fruit1.getToDelete())
                {
                    fruit1.deleteFromBoard(*board);
                }
            }
            else
            {
                creature->redrawCreature(*board);
            }
        }
    
        //update points\lives count:
        gotoxy(3*(board->getLegendPos().x+1), board->getLegendPos().y);
        cout << "Lives: " << player->getLives() << '|';
    
        cout << "Points: " << player->getPoints() << endl;
    }
}

void Game::fillCreatureVector()
{
    creatures.push_back(player);
    creatures.push_back(&fruit1);
    for(auto& ghost:enemies)
    {
        creatures.push_back(&ghost);
    }
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
        GhostMoveStrategy::fillUnfilledPlaces(stepsBoard);
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
