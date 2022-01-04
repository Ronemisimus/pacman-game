#include "game.h"

Game::Game(BoardGame * board):  isPaused(false), waitForMove(true), board(board),player(nullptr), saveFile(nullptr)
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
{//when loading a new screen
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

void Game::updateBoard(size_t frames)
{
    //this function updates the board for every frame
    // update only if not paused
    collisionFlags cf;
    Direction pacmanPrev=Direction::NOCHANGE;
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

        //handles fruit logic
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
            pacmanPrev = player->getDir();
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
            //redraw positions that the pause message deletes
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

    if(saveFile && ((!waitForMove && !isPaused) || cf.getPacmanGhost()))
    {
        for(size_t i=0;i<creatures.size();i++)
        {
            if(typeid(*creatures[i]) == typeid(pacman))
            {
                if(cf.getPacmanGhost())
                {
                    creatureSave[i]+=player->addToSave(frames, pacmanPrev);
                }
                else
                {
                    creatureSave[i]+=creatures[i]->addToSave(frames);
                }
            }
            else
            {
                creatureSave[i]+=creatures[i]->addToSave(frames);
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
{//creates a vector of all creatures to allow mutual actions for everyone
    creatures.clear();
    creatures.push_back(player);
    creatureSave.push_back("");
    creatures.push_back(&fruit1);
    creatureSave.push_back("");
    for(auto& ghost:enemies)
    {
        creatures.push_back(&ghost);
        creatureSave.push_back("");
    }
}

void Game::resetStats()
{
    player->resetLives();
    player->resetPoints();
}

void Game::calculateSmartMoves()
{//at the initiallization of each board, we calculate and save the best path fromm each ghost to pacman
    GhostMoveStrategy::colSize = board->getColSize();
    GhostMoveStrategy::rowSize = board->getRowSize();

    for(auto& ghost:enemies)
    {
        //creates a parallel board to count steps:
        int** stepsBoard = GhostMoveStrategy::initStepsBoard(ghost, *board);
        //fills the parallel board with step count for every location the ghost can reach:
        //step count - the minimal amount of steps the  ghost needs to reach a certain cell
        GhostMoveStrategy::fillStepsBoard(stepsBoard, ghost.getPos());
        //fills places with other indexex that the ghost cannot reach(shouldn't be possible)
        GhostMoveStrategy::fillUnfilledPlaces(stepsBoard);
        //backtracking from pacman's position to the ghost
        GhostMoveStrategy::fillStepsList(ghost, stepsBoard);

        GhostMoveStrategy::freeStepsBoard(stepsBoard);
        ghost.copyToInitList();//save a copy of the calculated paths
    }
}

void Game::updateGhostsSmatMoveList(Position playerPos)
{//keep the smartMoves list connected between pacman and (each) ghost
    for(auto& ghost:enemies)
    {
        Position lastSmartMove = ghost.removeFromEndOfSmartList();
        int stepsCanceled = ghost.findInList(playerPos);
        //prevents ghosts to move in loops
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

void Game::setSaveFile(ofstream* saveFile)
{
    this->saveFile=saveFile;
}

void Game::save()
{
    compressStrings();
    ofstream& f = *saveFile;
    int ghost_num=1;
    for(size_t index=0;index<creatures.size();index++)
    {
        auto& creature = *(creatures[index]);
        if(typeid(creature)==typeid(pacman))
        {
            f << CHAR_PACMAN << '\n';
        }
        else if(typeid(creature)==typeid(fruit))
        {
            f << '\n' << 'f';
            
        }
        else
        {
            f << '\n' << CHAR_ENEMY << '\n';
            ghost_num++;
        }
        f << creatureSave[index];
        f << '\n';
    }

    f.close();
}

void Game::resetCreatureSave()
{
    creatureSave.clear();
}


string Game::compress(string dirsOnly)
{
    string res="";
    int duplicates=0;
    char prev=' ';
    for(auto& current:dirsOnly)
    {
        if(prev==current)
        {
            duplicates++;
        }
        else
        {
            if(prev!=' ')
            {
                res+=prev;
                res+=std::to_string(duplicates);
            }
            duplicates=1;
        }
        prev = current;
    }
    if(duplicates!=0)
    {
        res+=prev;
        res+=std::to_string(duplicates);
    }

    return res;
}

string Game::compressFruit(string moves)
{
    string res = "";
    string dirs="";
    string check = "UDSLR";
    for(char& current:moves)
    {
        if(check.find(current)!=std::string::npos)
        {
            dirs+=current;
        }
        else
        {
            dirs=compress(dirs);
            res+=dirs;
            res+=current;
            dirs="";
        }
    }
    if(dirs.size()!=0)
    {
        dirs=compress(dirs);
        res+=dirs;
    }
    return res;
}

void Game::compressStrings()
{
    for(size_t index=0;index<creatures.size();index++)
    {
        string finalResult = "";
        auto& creature = *(creatures[index]);
        if(typeid(creature)==typeid(fruit))
        {
            finalResult = compressFruit(creatureSave[index]);
        }
        else
        {
            finalResult = compress(creatureSave[index]);
        }
        creatureSave[index] = finalResult; 
    }
}

vector<Direction>* Game::uncompress(ifstream& stepsFile)
{
    vector<Direction>* res = new vector<Direction>();

    Direction dir;
    size_t amount;
    char curr=0;
    bool endOfSteps = false;
    while (!endOfSteps && stepsFile.good())
    {                                       
        curr = stepsFile.get();
        switch (curr)
        {
        case 'S':
            dir = Direction::STAY;
            break;
        case 'L':
            dir = Direction::LEFT;
            break;
        case 'R':
            dir = Direction::RIGHT;
            break;
        case 'D':
            dir = Direction::DOWN;
            break;
        case 'U':
            dir = Direction::UP;
            break;
        default:
            endOfSteps=true;
            break;
        }
        if(!endOfSteps)
        {
            stepsFile >> amount;

            for (size_t i = 0; i < amount; i++)
            {
                res->push_back(dir);
            }
            if(amount<=0)
            {
                endOfSteps=true;
            }
        }
    }

    if(curr=='\r')
    {
        stepsFile.get();
    }
    
    return res;
}

bool Game::loadStepsFile(ifstream& stepsFile)
{
    bool good=true;
    char curr;
    
    fruit1.clearLives();

    stepsFile >> curr;
    if(curr==CHAR_PACMAN)
    {
        curr=stepsFile.get();
        if(curr=='\r')
        {
            curr=stepsFile.get();
        }
        vector<Direction>* res = uncompress(stepsFile);
        player->setLoadedMoves(res);
        stepsFile>>curr;
        if(curr!='f')
        {
            good =false;
        }
    }
    else
    {
        good=false;
    }

    

    if(good)
    {
        
        while(good && curr!=CHAR_ENEMY)
        {
            size_t temp;
            int temp2;
            fruitLife fl;
            if(!(stepsFile >> temp))
            {
                curr=CHAR_ENEMY;
                stepsFile.clear();
            }
            if(curr!=CHAR_ENEMY)
            {
                if(temp>0)
                {
                    fl.setFrames(temp);
                }
                else
                {
                    good=false;
                }
                if(good)
                {
                    stepsFile >> temp2;
                    if(temp2>=5 && temp2<=9)
                    {
                        fl.setValue(temp2);
                    }
                    else
                    {
                        good=false;
                    }
                }
                Position p;
                if(good)
                {
                    stepsFile >> temp2;
                    if(temp2>=0 && temp2<=board->getColSize())
                    {
                        p.x = temp2;
                    }
                    else
                    {
                        good=false;
                    }
                }
                if(good)
                {
                    stepsFile >> temp2;
                    if(temp2>=0 && temp2<=board->getRowSize())
                    {
                        p.y = temp2;
                    }
                    else
                    {
                        good=false;
                    }
                }

                if(good)
                {
                    fl.setPos(p);
                    curr=stepsFile.get();
                    if(curr=='\r')
                    {
                        curr=stepsFile.get();
                    }
                    vector<Direction>* lst = uncompress(stepsFile);
                    fl.setSteps(lst);
                    fruit1.addToLives(fl);
                }
            }
        }
    }

    if(good)
    {
        int ghost_count=0;
        while (stepsFile.good() && good)
        {
            stepsFile >> curr;
            if(curr==CHAR_ENEMY && stepsFile.good())
            {   

                curr=stepsFile.get();
                if(curr=='\r')
                {
                    curr=stepsFile.get();
                }
                vector<Direction>* steps = uncompress(stepsFile);
                
                enemies[ghost_count].setLoadedMoves(steps);

                ghost_count++;
            }
            else if(curr!=CHAR_ENEMY && !(stepsFile.eof()))
            {
                good=false;
            }
        }
        
    }

    return good;
}

bool Game::checkSpeed(Creature& c)
{
    if(typeid(c)==typeid(pacman))
    {
        return c.getFrames()==PACMAN_SPEED;
    }
    if(typeid(c)==typeid(fruit))
    {
        return c.getFrames()==FRUIT_SPEED;
    }
    if(typeid(c)==typeid(ghost))
    {
        return c.getFrames()==GHOST_SPEED;
    }

    return false;
}


void Game::updateGameFromLoad(size_t frames, bool silent)
{
    static fruitLife* current = nullptr;

    for(auto& creature: creatures)
    {
        bool advance = true;
        if(typeid(*creature)==typeid(fruit))
        {
            advance = ((fruit*)creature)->getExist();
        }
        if(advance)
        {
            creature->setFrames(creature->getFrames() + 1);
        }
    }

    collisionFlags cf;

    for(auto& creature: creatures)
    {
        bool shouldMove = checkSpeed(*creature);

        if(typeid(*creature) == typeid(fruit))
        {
            if(fruit1.getExist())
            {
                if(shouldMove)
                {
                    
                    fruit1.decreseLifeTime();
                    if(!fruit1.getExist())
                    {
                        current=nullptr;
                    }
                    else
                    {
                        fruit1.SetDir(current->getNextDir());
                        if (!cf.getPacmanGhost() && !cf.getPacmanFruit() && !cf.getFruitGhost())
                            cf = cf + fruit1.moveCreature(*board);
                        fruit1.setFrames(0);
                    }
                }   
            }
            else
            {
                if(!current)
                {
                    current = fruit1.getNextLife();
                }
                if(current)
                {
                    if(frames == current->getFrames())
                    {
                        fruit1.setExist(true);
                        fruit1.setInitPos(current->getPos());
                        fruit1.setChar('0'+current->getValue());
                        fruit1.setValue(current->getValue());
                        fruit1.SetDir(Direction::STAY);
                        fruit1.setFrames(0);
                        fruit1.setLifeTime(current->getStepsLen()+1);
                        board->setBoardCellData(fruit1.getPos().x, fruit1.getPos().y, gameObjectType::FRUIT);
                    }
                } 
            }
        }
        else
        {
            if(shouldMove)
            {
                creature->SetDir(creature->getNextLoadedDir());
                if (!cf.getPacmanGhost())
                {
                    cf = cf + creature->moveCreature(*board);
                }
                creature->setFrames(0);
            }
        }
    }

    if(cf.getPacmanGhost())
    {
        if(!silent)
            redrawBoard();
        player->strike(*board);
        
        for (int i = 0; i < board->getGhostsNum(); i++)
        {
            
            auto& enemy = enemies[i];
            enemy.strike(*board);
        }
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

