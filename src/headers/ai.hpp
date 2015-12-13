#ifndef AI_H
#define AI_H
#include "player.hpp"
#include <iostream>

class AI : public Player
{
public:
	AI(std::string const &n, ColorType c, int l);
	int getLevel();
	std::string getType();

private:
	int level;
};

#endif