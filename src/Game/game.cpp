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
		return true;
	}
	return false;
}

