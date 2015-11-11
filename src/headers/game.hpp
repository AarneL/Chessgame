#ifndef GAME_H
#define GAME_H
#include <vector>
#include <map>
#include "./../headers/board.hpp"

class Game
{
public:
	Game(void);
	std::vector<int> possibleMoves(int index);
	bool movePiece(int origin, int destination);

private:
	Board board;
	std::vector<std::pair<int, int>> moveList; //vector containing old moves
};

#endif /* OPTIONS_SCREEN_H */