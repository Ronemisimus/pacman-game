#pragma once
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "collisionFlags.h"
#include "fruitLife.h"

class fruit:public Creature {
//class to handle the fruit's life cycle 
	bool exists;
	int value;
	int lifeTime;
	bool toDelete;
	vector<fruitLife> lives;
	size_t indexLife;
public:
	fruit();
	virtual ~fruit();
	void chooseBeValue();
	void setExist(bool exist);
	void setValue(int value);
	void chooseInitPos(BoardGame &board);
	void chooseLifeTime();
	void decreseLifeTime();
	void deleteFromBoard(BoardGame& board);
	bool getToDelete() const;
	int getValue()const;
	bool getExist() const;
	void resetfruit();
	void addToLives(fruitLife fl);
	void clearLives();
	void setLifeTime(int lifeTime);
	fruitLife* getNextLife();

	virtual collisionFlags moveCreature(BoardGame& board);
	virtual string addToSave(size_t frames);
	

};
