#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

enum ColorType
{
    White,
    Black
};

class Player
{
public:
	Player() {};
	~Player() {};
	std::string getName() const;
	ColorType getColor() const;
	virtual void getMove() = 0;
	virtual std::string getType() = 0;
	virtual int getLevel() = 0;

protected:
	std::string name;
	ColorType color;
};

#endif