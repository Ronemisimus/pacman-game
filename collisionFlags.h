#pragma once

class collisionFlags
{
	bool PacmanGhost;
	bool PacmanFruit;
	bool FruitGhost;

public:
	collisionFlags(): PacmanGhost(false), PacmanFruit(false), FruitGhost(false){}
	collisionFlags operator+(const collisionFlags& merge)const;
	bool getPacmanGhost() const;
	bool getPacmanFruit() const;
	bool getFruitGhost() const;

	void setPacmanGhost(bool collision);
	void setPacmanFruit(bool collision);
	void setFruitGhost(bool collision);
};