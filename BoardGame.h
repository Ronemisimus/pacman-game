#pragma once
#include "global.h"
#include <fstream>
#include <vector>

using std::vector;
using std::ifstream;

class pacman;
class ghost;

class BoardGame
{
	
private:
	cell** board;
	int rowSize;
	int colSize;
	int numOfFood;
	int numOfGhosts;
	Position pacInitPos;
	vector <Position> enemyInitPos;
	Position legend;
public:
	BoardGame(int rowSize, int colSize);
	~BoardGame();
	BoardGame(const BoardGame&) = delete;
	void initBoard(ifstream& file);
	void drawBoard();
	int getFoodLeft();
	int getRowSize();
	int getColSize();
	int getGhostsNum();
	Position getPacInitPos();
	Position* getGhostsInitPos();
	Position getLegendPos();
	bool getIsThereFood(int x,int y);
	void setIsThereFood(int x, int y, bool value);
	void setBoardCellData(int x,int y, gameObjectType data);
	void updatePosition(int x, int y, cell data);
	gameObjectType getCellData(int x,int y);

	static void drawPos(int x, int y, BoardGame* board, char drawing);
	static char getCharFromData(gameObjectType data);

};

