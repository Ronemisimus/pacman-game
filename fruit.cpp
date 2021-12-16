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

void fruit::chooseInitPos(BoardGame& board)
{
	int x, y;
	x = rand() % (board.getColSize() - 2)+1;
	y = rand() % (board.getRowSize() - 2) + 1;
	
	while(board.getCellData(x, y) != gameObjectType::EMPTY)
	{
		x = rand() % (board.getColSize() - 2) + 1;
		y = rand() % (board.getRowSize() - 2) + 1;
	}
	
	board.setBoardCellData(x,y, gameObjectType::FRUIT);
	pos.x = x;
	pos.y = y;
}

void fruit::chooseLifeTime()
{
	int fps = 1000 / sleepTime;
	lifeTime = rand() % (fps * 5) + (5*fps);
}

collisionFlags fruit::moveFruit(BoardGame& board)
{
	collisionFlags cf;
	Position tmp;
	tmp=CalculateNext(board);
	prev = pos;
	pos = tmp;
	board.setBoardCellData(pos.x,pos.y, gameObjectType::FRUIT);
	board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
	
	
		cf.setPacmanFruit(board.getCellData(tmp.x, tmp.y) == gameObjectType::PACMAN);
		cf.setFruitGhost(board.getCellData(tmp.x, tmp.y) == gameObjectType::GHOST);
	
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

void fruit::deleteFromBoard(BoardGame &board) 
{
	
	if (board.getCellData(pos.x, pos.y) == gameObjectType::FRUIT)
		board.setBoardCellData(pos.x,pos.y, gameObjectType::EMPTY);
	
	BoardGame::drawPos(pos.x, pos.y, &board, ' ');
	toDelete = false;
}

void fruit:: resetfruit()
{
	toDelete = true;
	exists = false;
}
