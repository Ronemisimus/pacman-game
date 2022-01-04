#pragma once
#include "global.h"
#include "BoardGame.h"
#include "collisionFlags.h"

using std::string;

class Creature 
{//handle basic functionallities for all the creatures in the game
private:
    char drawing;
	Direction dir;
	int framesSinceMove;
	vector<Direction>* loadedMoves;
	size_t loadedMovesIndex;
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
	Direction getNextLoadedDir();

	void setChar(const char drawing);
	void SetDir(const Direction& dir);
	void setFrames(const int framesSinceMove);

	Position CalculateNext(BoardGame& board);
	void collision();
	void chooseRandomDir(BoardGame& board);
	void getPossiblePos(BoardGame& board, paths possibilities[4]);
	void redrawCreature(BoardGame& board);
	void setInitPos(Position initPos);
	void setLoadedMoves(vector<Direction>* moves);
	void undoMove();
	
	static void drawPos(int x, int y, BoardGame* board, char drawing);
	static char convertDirToLetter(Direction dir);
	
	virtual string addToSave(size_t frames);
	virtual collisionFlags moveCreature(BoardGame& board);


};
