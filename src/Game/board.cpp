#include "./../headers/board.hpp"
#include "./../headers/rules.hpp"
#include <vector>
#include <iostream>
#include <fstream>

Board::Board(void)
{
	//board.reserve(64);
	state = 0;

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

std::vector<int> Board::possibleMoves(int index) const
{
	//check for possible moves from which the check hasn't been removed
	std::vector<int> moves = allPossibleMoves(index);

	//remove moves that would lead to Check
	int turn = board[index] % 2;

	for(int i = 0 ; i < (int) moves.size() ; i++)
	{
		Board test_board = *this;		//does this make a copy or does it mess up the actual board?
		test_board.movePiece(index, moves[i]); //do move
		if(test_board.isCheck(turn)) //se if it leads to check from play on turns point of view
		{
			moves.erase(moves.begin()+i);
			i--;
		}
	}

	return moves;
}

//possibleMoves without testing for check
std::vector<int> Board::allPossibleMoves(int index) const
{
	std::vector<int> moves;
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
			break;

		case B_PAWN:
			moves = join(moves, Rules::blackPawnMoveForward(board, index));
			moves = join(moves, Rules::blackPawnMoveForwardLeft(board, index, lastMove));
			moves = join(moves, Rules::blackPawnMoveForwardRight(board, index, lastMove));
			break;

		case W_ROOK:
		case B_ROOK:
			moves = Rules::rookMove(board, index);
			break;

		case W_KNIGHT:
		case B_KNIGHT:
			moves = Rules::knightMove(board, index);
			break;

		case W_BISHOP:
		case B_BISHOP:
			moves = Rules::bishopMove(board, index);
			break;

		case W_QUEEN:
		case B_QUEEN:
			moves = Rules::queenMove(board, index);
			break;

		case W_KING:
		case B_KING:
			moves = Rules::kingMove(board, index);
			break;
	}
	return moves;
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

	//update board state
	//updateState(); do not do this here because methods inside updatestate() use movepiece

	return true;
}

std::vector<int> Board::getBoard() const
{
	return board;
}

std::vector<std::pair<int, int> > Board::getMoveList() const
{
	return moveList;
}


/* instead of using different functions for checking for chess, chessmate and stalemate it is
 * more efficient to check for them all in a single loop through the pieces */

void Board::updateState()
{
	int king_location = isCheck(0);
	if(!king_location)
	{
		king_location = isCheck(1);
	}
	if(king_location) //if it is check test for checkmate
	{
		if(isCheckMate(king_location))
		{
			state = 1;
		//do some stuff to stop the game			
		}
	}
	if(isStaleMate(king_location%2))
	{
		state = 2;
		//do some stuff to stop the game
	}
}


bool Board::isCheckMate(int king_location) const
{
	//this algorithm must only be called in case there is check

	//phase a: see if moving the king will help
	for(auto a:allPossibleMoves(king_location))
	{
		Board test_board = *this;  //is this a good idea
		test_board.movePiece(king_location, a);
		if(!test_board.isCheck(board[king_location]%2)) //for the player whos king is threatened in the first place
		{
			return false;
		}

	}

	//phase b: if that didn't help see if moving other pieces of same color help
	for(int i = 0; i < 64; i++)
	{
		if((board[king_location] % 2) == (board[i] % 2))
		{
			for(auto a:allPossibleMoves(i))
			{
				Board test_board = *this; //good idea?????
				test_board.movePiece(i, a);
				if(test_board.isCheck(a%2)) //see if the board is at check for the same player
				{
					return false;
				}
			}
		}
	}
	//no can do it's checkmate
	return true;
}

int Board::isCheck(int turn) const
{
	//loop through all squares and call for possible moves and see if the location of king is included
	//No need to check whos turn it is  because the king can't be threatened two turns in a row
	for(int i = 0;i<64;i++)
	{
		if(board[i] != 0 && board[i]%2 != turn)	//test for piece other than the one in turn
		{
			for(auto a:allPossibleMoves(i))
			{
				if(board[a] == W_KING || board[a] == B_KING)
				{
					return a;
				}
			}
		}
	}
	return 0;
}

bool Board::isStaleMate(int turn) const
{
	for(int i = 0;i<64;i++)
	{
		if(board[i] != 0 && (board[i] % 2 == turn) && (possibleMoves(i).size() != 0))
		{
			return false;
		}
	}
	return true;
}

int Board::getState() const
{
	return state;
}

void Board::saveGame(Player* white, Player* black)
{
	std::ofstream ofs ("test.txt", std::ofstream::out);
	ofs << white->getName() << "-" << white->getLevel() << std::endl;
	ofs << black->getName() << "-" << black->getLevel() << std::endl;
	for (auto move : moveList) {
		ofs << move.first << '-' << move.second << std::endl;
	}
	ofs.close();
}

std::vector<int> join(std::vector<int> a, std::vector<int> b)
{
	std::vector<int> result;
	result.reserve( a.size() + b.size() );
	result.insert( result.end(), a.begin(), a.end() );
	result.insert( result.end(), b.begin(), b.end() );
	return result;
}