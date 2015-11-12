#include "./../headers/board.hpp"
#include "./../headers/game.hpp"
#include <vector>

Board::Board(void)
{
	// Set initial positions for pieces
	for (int i = 0; i < 64; i++){
		if(i == 0 || i == 7)
		{
			board[i] = 
		}
	}
	//initialize the board
}

std::vector<int> Board::possibleMoves(int index)
{
	std::vector<int> moves;
	return moves; //return indexes to be highlighted
}

bool Board::movePiece(int origin, int destination)
{
	//making the move
	board[destination] = board[origin];	

	//saving move to movelist
	std::pair <int, int> move;
	move.first = origin;
	move.second = destination;
	moveList.push_back(move);

	//saving the new state of board into boardhistory
	boardHistory.push_back(board);

	return true;
}
