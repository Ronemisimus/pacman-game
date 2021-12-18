#pragma once
#include "global.h"
#include "BoardGame.h"
#include "collisionFlags.h"

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
	Creature(const char drawing, const Position& initPos, const Direction& dir);
	virtual ~Creature();
	void drawCreature(cell** board);
	const Position& getPrev() const;
	const Position& getPos() const;
	const Direction& getDir() const;
	int getFrames() const;
	
	void setChar(const char drawing);
	void SetDir(const Direction& dir);
	void setFrames(const int framesSinceMove);

	Position CalculateNext(BoardGame& board);
	void collision();
	void chooseRandomDir(BoardGame& board);
	void getPossiblePos(BoardGame& board, paths possibilities[4]);
	static void drawPos(int x, int y, BoardGame* board, char drawing);
	void redrawCreature(BoardGame& board);
	void setInitPos(Position initPos);

	virtual collisionFlags moveCreature(BoardGame& board);

};
