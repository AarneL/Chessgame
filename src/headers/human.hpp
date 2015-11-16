#ifndef HUMAN_H
#define HUMAN_H
#include "player.hpp"
#include <iostream>

class Human : public Player
{
public:
	Human(std::string const &n, ColorType c);
	void getMove();
	std::string getType();
private:
};

#endif