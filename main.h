#pragma once
#include "game.h"


enum MENU {
    START = 1, 
    PRESENT = 8,
    EXIT = 9 
};

MENU menu();
void present();
void startGame();