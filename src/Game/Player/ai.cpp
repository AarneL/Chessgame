#include "../../headers/player.hpp"
#include "../../headers/ai.hpp"

AI::AI(std::string const &n, ColorType c, int l)
{
	name = n;
	color = c;
	level = l;
}

int AI::getLevel()
{
	return level;
}

void AI::getMove()
{

}