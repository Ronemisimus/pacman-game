#pragma once

class collisionFlags
{//class to signal coliision between different creatures
	bool PacmanGhost;
	bool PacmanFruit;
	bool FruitGhost;
	bool moved;// if creature moved as in dir or did something else

public:
	collisionFlags(): PacmanGhost(false), PacmanFruit(false), FruitGhost(false){}
	collisionFlags operator+(const collisionFlags& merge)const;
	bool getPacmanGhost() const;
	bool getPacmanFruit() const;
	bool getFruitGhost() const;
	bool getMoved() const;

	void setPacmanGhost(bool collision);
	void setPacmanFruit(bool collision);
	void setFruitGhost(bool collision);
	void setMoved(bool moved);
};