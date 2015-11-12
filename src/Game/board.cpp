#include "./../headers/board.hpp"
#include "./../headers/game.hpp"
#include <vector>

Board::Board(void)
{
	// Set initial positions for pieces
	for (int i = 0; i < 64; i++){
		if(i == 0 || i == 7)
		{
			board[i] = W_ROOK;
		}

		else if(i == 1 || i == 6)
		{
			board[i] = W_KNIGHT;
		}

		else if(i==2 || i == 5)
		{
			board[i] = W_BISHOP;
		}

		else if(i == 3)
		{
			board[i] = W_QUEEN;
		}

		else if(i == 4)
		{
			board[i] = W_KING;
		}

		else if(i < 15 && i > 7)
		{
			board[i] = B_PAWN;
		}

		else if(i == 63 || i==55)
		{
			board[i] = B_ROOK;
		}

		else if(i == 62 || i == 56)
		{
			board[i] = B_KNIGHT;
		}

		else if(i == 61 || i == 57)
		{
			board[i] = B_BISHOP;
		}

		else if(i == 60)
		{
			board[i] = B_QUEEN;
		}

		else if(i == 59)
		{
			board[i] = B_KING;
		}

		else if(i < 55 && i > 47)
		{
			board[i] = B_PAWN;
		}

		else
		{
			board[i] = NONE;
		}
	}
	//initialize the board
}

std::vector<int> Board::possibleMoves(int index)
{
	std::vector<int> moves;
	moves[0] = index;
	switch (board[index])
	{
		case W_PAWN:
			return moves;
			break;

		case B_PAWN:
			return moves;
			break;

		case W_ROOK:
			return moves;
			break;

		case B_ROOK:
			return moves;
			break;

		case W_KNIGHT:
			return moves;
			break;
			
		case B_KNIGHT:
			return moves;
			break;

		case W_BISHOP:
			return moves;
			break;
			
		case B_BISHOP:
			return moves;
			break;

		case W_QUEEN:
			return moves;
			break;

		case B_QUEEN:
			return moves;
			break;	

		case W_KING:
			return moves;
			break;

		case B_KING:
			return moves;
			break;			
	}
	return moves; // in case of NONE
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

std::vector<int> Board::getBoard()
{
	return board;
}