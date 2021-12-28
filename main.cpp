//in this program, we play the pacman game
//Ronen Margolin ID: 318999349, Ronit Libenson ID: 313133035
#include "main.h"

int main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));

    if(argc==1)
    {
        run(false);
    }
    else
    {
        bool goodParameters = true;
        if(strcmp(argv[1],"-save")==0)
        {
            run(true);
        }
        else if(strcmp(argv[1],"-load")==0)
        { 
            bool silent=false;
            if(argc==3)
            {
                if(strcmp(argv[2],"-silent")==0)
                {
                    silent=true;
                }
                else
                {
                    goodParameters = false;
                }
            }
            else if(argc==2)
            {
                silent=false;
            }
            else
            {
                goodParameters=false;
            }
            if(goodParameters)
            {
                try
                {
                    load(silent);
                }
                catch(const std::exception& e)
                {
                    goodParameters=false;
                }
                
            }
        }
        else
        {
            goodParameters=false;
        }

        if(!goodParameters)
        {
            cout << "invalid parameters or missing/incomplete files.\n" << 
            "Usage: pacman.exe -save|-load [-silent]\n";
        }
    }
}

void load(bool silent)
{
    FileHandler& fh = *FileHandler::getInstance();

    BoardGame* board = fh.loadNextScreen();

    

}

void run(bool save)
{
    FileHandler& fh = *FileHandler::getInstance();


    BoardGame* board = fh.loadNextScreen();

    Game game(board);

    bool win = false;
    size_t file_num;

    //present the main menu
    MENU option= MENU::INVALID;
    do{
        option = menu();
        switch (option)
        {
        case MENU::START:
            if(!board)
            {
                cout << "there are no files in the directory.\n" <<
                "please add them and restart the program\n" <<
                "the files should end with .screen\n";
                waitForKeyPress();
            }
            else
            {
                getDifficultyLevel();
                while(board)
                {
                    if(save)
                    {
                        ofstream* saveFile = fh.getSaveFile(fh.getScreensLoaded()-1);
                        game.setSaveFile(saveFile);
                    }
                    win = startGame(board, game);
                    if(win){
                        delete board;
                        board = fh.loadNextScreen();
                        if(board)
                        {
                            game.changeBoard(board);
                        }
                        else
                        {
                            endGameMessage(win);
                        } 
                    }
                    else
                    {
                        delete board;
                        board = nullptr;
                        endGameMessage(win);
                    }
                }
                fh.resetScreensLoaded();
                board = fh.loadNextScreen();
               
                    game.changeBoard(board);
               
                game.resetStats();
            }
            break;
        case MENU::LOAD:
            if(board)
            {
                delete board;
            }
            file_num=0;
            board = fh.chooseScreen(file_num);
            if(board)
            {
                if(save)
                {
                    ofstream* saveFile = fh.getSaveFile(file_num);
                    game.setSaveFile(saveFile);
                }
                getDifficultyLevel();
                game.changeBoard(board);
                endGameMessage(startGame(board,game));
            }
            fh.resetScreensLoaded();
            if(board)
            {
                delete board;
            }
            board = fh.loadNextScreen();
            game.changeBoard(board);
            game.resetStats();
            break;
        case MENU::PRESENT:
            present();
            break;
        
        case MENU::EXIT:
            cout << "\nbye!!!!!\n\n";
            break;
        default:
            cout << "no such option, try again! :)\n";
            break;
        }
    }while(option != MENU::EXIT);
}

void endGameMessage(bool victory)
{
    if(victory)
    {
        cout << "victory!!\n";   
    }
    else
    {
        cout << "Game Over!!!!\n";
    }

    cout << "press any key to continue to the menu" << '\n';

    waitForKeyPress();
    clearScreen();
}

MENU menu()
{
    clearScreen();
    //this function presents the main menu and gets the user's input
    int input;
    MENU option;
    cout << "Pacman:\n" <<
        "1 - start a new game\n" <<
        "2 - load a specific board file\n" <<
        "8 - present Instructions and keys\n" <<
        "9 - exit" << endl;
    cin >> input;
    cin.ignore();
    option = (MENU) input;
    return  option;
}

void present()
{
    //this function presents the game rules
    cout << "\nYour goal is to eat all the breadcrumbs , without touching the walls or being eaten by the ghosts.\n" <<
        "You got 3 lives.\n" << 
        "Press: a\\A to move left,\n" << 
        "d\\D to move right,\n" << 
        "w\\W to move up,\n" <<
        "x\\X to move down,\n" << 
        "s\\S to stay,\n" << 
        "ESC to pause\\continue.\n" <<
        "Good luck!\n\n"; 
}

void getDifficultyLevel()
{
    int level=0;

    clearScreen();

    while(level<1 || level>3)
    {
        cout << "choose the difficulty level: (enter a number from the list)\n" <<
            "1. Best\n" <<
            "2. Good\n" <<
            "3. Novice\n";

        if(!(cin >> level) || level<1 || level>3)
        {
            cout << "invalid choice\n";
            if(!cin.good())
            {
                cin.clear();
                cin.ignore(10000,'\n');
            }
        }
    }

    clearScreen();

    ghost::level = GhostStrategy(level);
}

bool startGame(BoardGame *board, Game& game)
{
    //this function is in charge of the main game loop
    clearScreen();

#ifdef LINUX
    termios saved;
    setTerminalInputMode(&saved);
#endif

    if(ghost::level!=GhostStrategy::NOVICE)
    {
        game.calculateSmartMoves();
    }

    game.fillCreatureVector();
   
    board->drawBoard();
  
    size_t frame = 0;

    while(!game.isDone())
    {
        game.updateBoard(frame);
        game.redrawBoard();
        frame++;
        Sleep(sleepTime);
    }

    game.save();
    game.resetCreatureSave();

    clearScreen();

#ifdef LINUX
    resetTerminalInputMode(saved);
#endif

    return board->getFoodLeft()==0;
}

