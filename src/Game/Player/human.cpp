#include "../../headers/player.hpp"
#include "../../headers/human.hpp"

Human::Human(std::string const &n, ColorType c)
{
	name = n;
	color = c;
}

void Human::getMove()
{

}

std::string Human::getType()
{
	return "Human";
}

int Human::getLevel()
{
	return 1;
}
