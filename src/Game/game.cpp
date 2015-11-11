#include "./../headers/game.hpp"
#include "./../headers/board.hpp"
#include <vector>

Game::Game(void)
{
	board = Board();
}

std::vector<int> Game::possibleMoves(int index)
{
	return board.possibleMoves(index);
}

bool Game::movePiece(int origin, int destination)
{
	if(board.movePiece(origin, destination))
	{
		std::pair <int, int> move;
		move.first = origin;
		move.second = destination;
		moveList.push_back(move);
		return true;
	}
	return false;
}

