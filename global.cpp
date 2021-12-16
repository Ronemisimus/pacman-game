#include "global.h"

#ifndef LINUX

void gotoxy(short x, short y)
{
	//moves the cursor to x,y position:
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x, y };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

#endif

void clearScreen()
{
    #ifdef LINUX
        system("clear");
    #else
        system("cls");
    #endif
}

void waitForKeyPress()
{
	#ifdef LINUX
        system("read -N 1");
    #else
        system("pause");
    #endif
}