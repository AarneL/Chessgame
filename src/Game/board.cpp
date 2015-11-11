#include "./../headers/board.hpp"
#include "./../headers/game.hpp"
#include <vector>

Board::Board(void)
{
	//initialize the board
}

std::vector<int> Board::possibleMoves(int index)
{
	std::vector<int> moves;
	return moves; //return indexes to be highlighted
}

bool Board::movePiece(int origin, int destination)
{
	return true; //move piece and update board accordingly
}
