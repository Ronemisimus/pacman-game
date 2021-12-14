//in this program, we play the pacman game
//Ronen Margolin ID: 318999349, Ronit Libenson ID: 313133035
#include "main.h"


int main()
{
    srand((unsigned int)time(NULL));

    BoardGame* board = fh.loadScreen();

    bool win = false;

    //present the main menu
    MENU option;
    do{
        option = menu();
        switch (option)
        {
        case START:
            while(board)
            {
                win = startGame(board);
                if(win){
                    board = fh.loadScreen();
                }
                else
                {
                    //delete board;
                    board = nullptr;
                    fh.resetScreensLoaded();
                }
            }
            fh.resetScreensLoaded();
            break;
        case LOAD:
            //
            break;
        case PRESENT:
            present();
            break;
        
        case EXIT:
            cout << "\nbye!!!!!\n\n";
            break;
        default:
            cout << "no such option, try again! :)\n";
            break;
        }
    }while(option != EXIT);

}

MENU menu()
{
    //this function presents the main menu and gets the user's input
    int input;
    MENU option;
    cout << "Pacman:\n" <<
        "1 - start a new game\n" <<
        "2 - load a specific board file\n" <<
        "8 - present Instructions and keys\n" <<
        "9 - exit" << endl;
    cin >> input;
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


bool startGame(BoardGame *board)
{
    //this function is in charge of the main game loop
#ifdef LINUX
    system("clear");
#else
    system("cls");
#endif

#ifdef LINUX
    termios saved;
    setTerminalInputMode(&saved);
#endif

   

    Game game(board);
   
    board->drawBoard();
  
    while(!game.isDone())
    {
        game.updateBoard();
        game.redrawBoard();
        Sleep(sleepTime);
    }

    #ifdef LINUX
    system("clear");
#else
    system("cls");
#endif

    if(board->getFoodLeft()==0)
    {
        cout << "victory!!\n";   
    }
    else
    {
        cout << "Game Over!!!!\n";
    }

#ifdef LINUX
    system("");
#else
    system("pause");
#endif

#ifdef LINUX
    system("clear");
#else
    system("cls");
#endif

#ifdef LINUX
    resetTerminalInputMode(saved);
#endif

    return board->getFoodLeft()==0;
}