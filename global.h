#pragma once

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


#define CHAR_WALL '#'
#define CHAR_ENEMY '$'
#define CHAR_PACMAN '@'
#define CHAR_FOOD '*'

const int boardSize = 20;
const int sleepTime = 100;

struct Position
{
    int x;
    int y;
};

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    STAY,
    NOCHANGE
};

enum gameObjectType {
    WALL,
    GHOST,
    PACMAN, 
    EMPTY
};

struct cell{
    bool food;
    gameObjectType data;
};