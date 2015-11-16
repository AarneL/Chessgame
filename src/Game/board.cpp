#include "./../headers/board.hpp"
#include "./../headers/game.hpp"
#include "./../headers/rules.hpp"
#include <vector>
#include <iostream>

Board::Board(void)
{
	//board.reserve(64);
	for (int s = 0; s < 64;  s++) {
		board.push_back(0);
	}
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

		else if(i < 16 && i > 7)
		{
			board[i] = W_PAWN;
		}

		else if(i == 63 || i==56)
		{
			board[i] = B_ROOK;
		}

		else if(i == 62 || i == 57)
		{
			board[i] = B_KNIGHT;
		}

		else if(i == 61 || i == 58)
		{
			board[i] = B_BISHOP;
		}

		else if(i == 59)
		{
			board[i] = B_QUEEN;
		}

		else if(i == 60)
		{
			board[i] = B_KING;
		}

		else if(i < 56 && i > 47)
		{
			board[i] = B_PAWN;
		}

		else
		{
			board[i] = NONE;
		}
	}
}

std::vector<int> Board::possibleMoves(int index)
{
	std::vector<int> moves;
	moves.push_back(index);
	std::pair<int, int> lastMove;

	if(moveList.size() == 0)
	{
		lastMove = std::make_pair(0, 0);
	}
	else
		lastMove = moveList[moveList.size() -1];
	switch (board[index])
	{
		case W_PAWN:
			moves = join(moves, Rules::whitePawnMoveForward(board, index));
			moves = join(moves, Rules::whitePawnMoveForwardLeft(board, index, lastMove));
			moves = join(moves, Rules::whitePawnMoveForwardRight(board, index, lastMove));
			return moves;
			break;

		case B_PAWN:
			moves = join(moves, Rules::blackPawnMoveForward(board, index));
			moves = join(moves, Rules::blackPawnMoveForwardLeft(board, index, lastMove));
			moves = join(moves, Rules::blackPawnMoveForwardRight(board, index, lastMove));
			return moves;
			break;

		case W_ROOK:
		case B_ROOK:
			moves = Rules::rookMove(board, index);
			return moves;
			break;

		case W_KNIGHT:
		case B_KNIGHT:
			moves = Rules::knightMove(board, index);
			return moves;
			break;

		case W_BISHOP:
		case B_BISHOP:
			moves = Rules::bishopMove(board, index);
			return moves;
			break;

		case W_QUEEN:
		case B_QUEEN:
			moves = Rules::queenMove(board, index);
			return moves;
			break;

		case W_KING:
		case B_KING:
			moves = Rules::kingMove(board, index);
			return moves;
			break;
	}
	return moves; // in case of NONE
}

bool Board::movePiece(int origin, int destination)
{
	//making the move
	board[destination] = board[origin];
	board[origin] = NONE;

	//saving move to movelist
	std::pair <int, int> move;
	move.first = origin;
	move.second = destination;
	moveList.push_back(move);

	//saving the new state of board into boardhistory
	boardHistory.push_back(board);

	return true;
}

std::vector<int>& Board::getBoard()
{
	return board;
}

std::vector<std::pair<int, int> > Board::getMoveList() const
{
	return moveList;
}

std::vector<int> join(std::vector<int> a, std::vector<int> b)
{
	std::vector<int> result;
	result.reserve( a.size() + b.size() );
	result.insert( result.end(), a.begin(), a.end() );
	result.insert( result.end(), b.begin(), b.end() );
	return result;
}