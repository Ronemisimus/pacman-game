#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"


class fruit:public Creature {

	bool exists;
	int value;
	int lifeTime;
	bool toDelete;
public:
	fruit();
	virtual ~fruit();
	void chooseBeValue();
	void chooseInitPos(BoardGame &board);
	void chooseLifeTime();
	void decreseLifeTime();
	void deleteFromBoard(BoardGame& board);
	bool getToDelete() const;
	int getValue()const;
	bool getExist() const;
	virtual collisionFlags moveCreature(BoardGame& board);
	void resetfruit();
	
	

};
