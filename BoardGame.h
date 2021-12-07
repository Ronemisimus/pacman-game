#pragma once
#include "global.h"
class GameBoard
{
	cell** board;
	int width, hight;
	Position legend;
	int numOfFood;
	int numOfGhosts;
};