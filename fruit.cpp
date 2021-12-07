#include "fruit.h"

void fruit::chooseBeValue()
{
	value = rand() % 300;
	exists = value>=5&&value<=9;
	if (exists)
	{
		setChar('0'+value);
	}
}
void fruit::chooseInitPos(cell board[boardSize][boardSize])
{
	int x, y;
	x = rand() % (boardSize - 2)+1;
	y = rand() % (boardSize - 2) + 1;
	while(board[x][y].data != gameObjectType::EMPTY)
	{
		x = rand() % (boardSize - 2) + 1;
		y = rand() % (boardSize - 2) + 1;
	}
	board[x][y].data = gameObjectType::FRUIT;
	
	pos.x = x;
	pos.y = y;
}
void fruit::chooseLifeTime()
{
	int fps = 1000 / sleepTime;
	lifeTime = rand() % (fps * 5) + (5*fps);
}
collisionFlags fruit::moveFruit(cell board[boardSize][boardSize])
{
	collisionFlags cf;
	Position tmp;
	tmp=CalculateNext();
	prev = pos;
	pos = tmp;
	board[pos.x][pos.y].data = gameObjectType::FRUIT;
	board[prev.x][prev.y].data = gameObjectType::EMPTY;
		
		cf.setPacmanFruit(board[tmp.x][tmp.y].data == gameObjectType::PACMAN);
		cf.setFruitGhost(board[tmp.x][tmp.y].data == gameObjectType::GHOST);
	
	return cf;
}
bool fruit::getExist() const
{
	return exists;
}
int fruit::getValue()const
{
	return value;
}

void fruit::decreseLifeTime()
{
	this->lifeTime--;
	if (this->lifeTime == 0)
	{
		exists = false;
		toDelete = true;
	}
}

bool fruit::getToDelete() const
{
	return toDelete;
}

void fruit::deleteFromBoard(cell board[boardSize][boardSize]) 
{
	if(board[pos.x][pos.y].data== gameObjectType::FRUIT)
	board[pos.x][pos.y].data = gameObjectType::EMPTY;
	Creature::drawPos(pos.x, pos.y, board, ' ');
	toDelete = false;
}
void fruit:: resetfruit()
{
	toDelete = true;
	exists = false;
}
