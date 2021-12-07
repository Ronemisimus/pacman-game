#pragma once
#include "game.h"
#include "FileHandler.h"

 FileHandler fh;


enum  MENU {
    START = 1, 
    LOAD = 2,
    PRESENT = 8,
    EXIT = 9 
};

MENU menu();
void present();
void startGame();
