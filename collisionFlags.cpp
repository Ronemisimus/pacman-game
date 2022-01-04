#include "collisionFlags.h"

bool collisionFlags::getPacmanGhost() const
{
	return PacmanGhost;
}
bool collisionFlags::getPacmanFruit() const
{
	return PacmanFruit;
}
bool collisionFlags::getFruitGhost() const
{
	return FruitGhost;
}

void collisionFlags::setPacmanGhost(bool collision)
{
	this->PacmanGhost = collision;
}
void collisionFlags::setPacmanFruit(bool collision)
{
	this->PacmanFruit = collision;
}
void collisionFlags::setFruitGhost(bool collision)
{
	this->FruitGhost = collision;
}
collisionFlags collisionFlags::operator+(const collisionFlags& merge)const
{
	collisionFlags res;
	res.setFruitGhost(getFruitGhost()||merge.FruitGhost);
	res.setPacmanFruit(getPacmanFruit() || merge.PacmanFruit);

	res.setPacmanGhost(getPacmanGhost() || merge.PacmanGhost);
	res.setMoved(merge.getMoved());
	return res;
}

void collisionFlags::setMoved(bool moved)
{
	this->moved=moved;
}

bool collisionFlags::getMoved() const
{
	return moved;
}
