#include "../../headers/player.hpp"
#include "../../headers/ai.hpp"

AI::AI(std::string const &n, ColorType c, int l)
{

	color = c;
	level = l;
	switch (level)
	{
	case 1:
		name = "Wooden box";
		break;
	case 2:
		name = "Sun mutsis";
		break;
	case 3:
		name =	"Granpa";
		break;
	case 4:
		name = "Cleverbot";
		break;
	case 5:
		if (color == ColorType::White) {
			name = "Skynet";
		}
		else {
			name = "Deep thought";
		}
		break;
	default:
		break;
	}
}

int AI::getLevel()
{
	return level;
}

void AI::getMove()
{

}
std::string AI::getType()
{
	return "AI";
}
