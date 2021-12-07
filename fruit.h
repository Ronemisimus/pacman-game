#pragma once
#include "global.h"
#include "Creature.h"
#include "collisionFlags.h"

class fruit:public Creature {

	bool exists;
	int value;
	int lifeTime;
	bool toDelete;
public:
	fruit() :Creature('0',Position(-1,-1),Direction::STAY),exists(false), toDelete(false) {}
	void chooseBeValue();
	void chooseInitPos(cell board[boardSize][boardSize]);
	void chooseLifeTime();
	void decreseLifeTime();
	void deleteFromBoard(cell board[boardSize][boardSize]);
	bool getToDelete() const;
	int getValue()const;
	bool getExist() const;
	collisionFlags moveFruit(cell board[boardSize][boardSize]);
	void resetfruit();
	
	

};
