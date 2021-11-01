#include "main.h"

int main()
{

    MENU option;
    do{
        option = menu();
        switch (option)
        {
        case START:
            startGame();
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
    int input;
    MENU option;
    cout << "Pacman:\n" <<
        "1 - start a new game\n" <<
        "8 - present Instructions and keys\n" <<
        "9 - exit" << endl;
    cin >> input;
    option = (MENU) input;
    return  option;
}

void present()
{
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

void startGame()
{

#ifdef LINUX
    system("clear");
#else
    system("cls");
#endif

#ifdef LINUX
    termios saved;
    setTerminalInputMode(&saved);
#endif

    Game game;
    game.initBoard();
    game.drawBoard();
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

    if(game.getFoodLeft()==0)
    {
        cout << "victory!!\n";   
    }
    else
    {
        cout << "loser!!!!1\n";
    }

#ifdef LINUX
    resetTerminalInputMode(saved);
#endif

}