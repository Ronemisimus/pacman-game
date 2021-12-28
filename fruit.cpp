#include "fruit.h"

fruit::fruit(): Creature('0',Position(-1,-1),Direction::STAY),exists(false), value(0), lifeTime(0), toDelete(false), lives(vector<fruitLife>())
{

}

fruit::~fruit()
{
    
}

void fruit::chooseBeValue()
{//the fruit chooses its value
	//if as premitted (5-9), then it will eventually appear on the screen
	value = rand() % 300;
	exists = value>=5&&value<=9;
	if (exists)
	{
		setChar('0'+value);
	}
}

void fruit::chooseInitPos(BoardGame& board)
{//choose an available position to place the fruit 
	int x, y;
	x = rand() % (board.getColSize() - 2)+1;
	y = rand() % (board.getRowSize() - 2) + 1;
	
	while(board.getCellData(x, y) != gameObjectType::EMPTY)
	{
		x = rand() % (board.getColSize() - 2) + 1;
		y = rand() % (board.getRowSize() - 2) + 1;
	}
	
	board.setBoardCellData(x,y, gameObjectType::FRUIT);
	initPos = Position(x,y);
	pos.x = x;
	pos.y = y;
}

void fruit::chooseLifeTime()
{//choose random lifetime for the fruit to exist
	int fps = 1000 / sleepTime;
	lifeTime = rand() % (fps * 5) + (5*fps);
}

collisionFlags fruit::moveCreature(BoardGame& board)
{//function to handle the fruit's movement
	collisionFlags cf;
	Position tmp;
	//update next position:
	tmp=CalculateNext(board);
	prev = pos;
	pos = tmp;
	board.setBoardCellData(pos.x,pos.y, gameObjectType::FRUIT);
	board.setBoardCellData(prev.x, prev.y, gameObjectType::EMPTY);
	
	//handle collision with other creatures:
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
{//we have chosen a lifetime for the fruit previously
	//decrease it every frame
	//the fruit vanishes when lifetime reaches 0
	this->lifeTime--;
	if (this->lifeTime == 0)
	{
		exists = false;
		toDelete = true;//flag to delete the fruit later
		initPos = Position(-1,-1);
	}
}

bool fruit::getToDelete() const
{
	return toDelete;
}

void fruit::deleteFromBoard(BoardGame &board) 
{//function to delete the fruit at the end of its lifespan
	//activated if toDelete flag is true
	
	if (board.getCellData(pos.x, pos.y) == gameObjectType::FRUIT)
		board.setBoardCellData(pos.x,pos.y, gameObjectType::EMPTY);
	
	BoardGame::drawPos(pos.x, pos.y, &board, ' ');
	toDelete = false;
}

void fruit:: resetfruit()
{
	toDelete = true;
	exists = false;
	initPos = Position(-1,-1);
}

string fruit::addToSave(size_t frames)
{
	static bool saveTime=true;
	string res = "";
	if(getExist())
	{
		if(pos.x==initPos.x&&
		pos.y==initPos.y && saveTime)
		{
			res += "\n";
			res += std::to_string(frames);
			res += "\n";
			res += std::to_string(value);
			res += "\n";
			res += std::to_string(initPos.x);
			res += " ";
			res += std::to_string(initPos.y);
			res += "\n";
			saveTime=false;
		}

		if(getFrames()==0)
		{
			res += convertDirToLetter(getDir());
		}
	}
	if(getToDelete())
	{
		saveTime=true;
	}
	return res;
}

void fruit::addToLives(fruitLife fl)
{
	lives.push_back(fl);
}

void fruit::clearLives()
{
	lives.clear();
}
