#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#define LINUX

#ifndef LINUX
#include <conio.h>
#include <Windows.h> 

#else
#include "iofunctions.h"
#endif

#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;
// controls
#define RIGHT_KEY_op1 100
#define RIGHT_KEY_op2 68
#define LEFT_KEY_op1 97
#define LEFT_KEY_op2 65
#define UP_KEY_op1 119
#define UP_KEY_op2 87
#define DOWN_KEY_op1 120
#define DOWN_KEY_op2 88
#define STAY_KEY_op1 115
#define STAY_KEY_op2 83
#define ESC_KEY 27

#define PACMAN_SPEED 2 // represents frames between moves - lower is faster
#define GHOST_SPEED PACMAN_SPEED*2
#define FRUIT_SPEED GHOST_SPEED*2
#define GHOST_NUM 2

#define CHAR_WALL '#'
#define CHAR_ENEMY '$'
#define CHAR_PACMAN '@'
#define CHAR_FOOD '*'
#define CHAR_EMPTY '%'

#define CHAR_LEGEND '&'

const int sleepTime = 50;

struct Position
{
    int x;
    int y;
    Position(int _x, int _y): x(_x), y(_y){}
    Position(): x(0), y(0){}
};
enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    STAY,
    NOCHANGE,
    PAUSE
};
struct paths
{
    Direction way;
    bool available;
};



enum class gameObjectType {
    WALL,
    GHOST,
    PACMAN, 
    EMPTY,
    FRUIT,
    INVALID
};

struct cell{
    bool food;
    gameObjectType data;
};

void gotoxy(short x, short y);