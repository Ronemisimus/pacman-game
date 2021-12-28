#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"

class fruit:public Creature {
//class to handle the fruit's life cycle 
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
	void resetfruit();
	
	virtual collisionFlags moveCreature(BoardGame& board);
	virtual string addToSave(size_t frames);
	

};
