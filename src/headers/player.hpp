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
	std::string getName();
	ColorType getColor();
	virtual void getMove() = 0;
	virtual std::string getType() = 0;
protected:
	std::string name;
	ColorType color;
};

#endif