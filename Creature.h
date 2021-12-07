#pragma once
#include "global.h"

class Creature 
{
private:
    char drawing;
	Direction dir;
	int framesSinceMove;
protected:
	Position prev;
	Position pos;
	Position initPos;
public:
	Creature(const char drawing, const Position& initPos, const Direction& dir): drawing(drawing), dir(dir), framesSinceMove(0), prev(initPos), initPos(initPos){}
	void drawCreature(cell board[boardSize][boardSize]);
	const Position& getPrev() const;
	const Position& getPos() const;
	const Direction& getDir() const;
	int getFrames() const;
	
	void setChar(const char drawing);
	void SetDir(const Direction& dir);
	void setFrames(const int framesSinceMove);

	Position CalculateNext();
	void collision();
	void chooseRandomDir(cell board[boardSize][boardSize]);
	void getPossiblePos(cell board[boardSize][boardSize], path possibilities[4]);
	static void drawPos(int x, int y, cell board[boardSize][boardSize], char drawing);
	void redrawCreature(cell board[boardSize][boardSize]);


};
