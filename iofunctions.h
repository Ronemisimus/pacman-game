#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "global.h"

using std::cin;
using std::cout;
using std::endl;


int _kbhit();
void gotoxy( short x, short y ) ;
int _getch();
void setTerminalInputMode(struct termios *saved);
void resetTerminalInputMode(struct termios saved);
void Sleep(long miliSeconds);
