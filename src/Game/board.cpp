#include "./../headers/board.hpp"
#include "./../headers/rules.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "../headers/ai_algorithm.hpp"
#include <string>

Board::Board(void)
{
	//board.reserve(64);
	state = 0x3c; //0011 1100

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
		Board test_board = *this;		
		test_board.movePiece(index, moves[i]); //simulate move
		if(test_board.isCheck(turn)) //see if it leads to check from player on turns point of view
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
			moves = Rules::kingMove(board, index);
			if(state & 0x04)
			{
				moves = join(moves, Rules::leftCastlingMove(board, index));
			}
			if(state & 0x8)
			{				
				moves = join(moves, Rules::rightCastlingMove(board, index));
			}
			break;

		case B_KING:
			moves = Rules::kingMove(board, index);
			if(state & 0x10)
			{
				moves = join(moves, Rules::leftCastlingMove(board, index));
			}
			if(state & 0x20)
			{
				moves = join(moves, Rules::rightCastlingMove(board, index));
			}
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
	//updateState(move.second);
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

void Board::updateState(int index) //index is the destination of last move
{

	//turn lastmove flags off
	state = state & 0x3F; //00111111

	// 0 means it was blacks turn
	int turn = board[index] % 2;
	std::pair<int, int> lastMove;

	lastMove = moveList[moveList.size() -1];

	//Check for promotion
	//White first
	if (board[lastMove.second] == W_PAWN && lastMove.second >= 56 && lastMove.second <= 63)
	{	std::cout << "White pawn promoted" << std::endl;
		board[lastMove.second] = W_QUEEN; } //TODO

	//Then black
	if (board[lastMove.second] == B_PAWN && lastMove.second >= 0 && lastMove.second <= 7)
	{	std::cout << "Black pawn promoted" << std::endl;
		board[lastMove.second] = B_QUEEN; }	//TODO

	//check for el passant
	if(moveList.size() > 4) //this needs to be done so we don't try invalid indexes
	{
		//test for white pawns
		if (board[lastMove.second] == 1 
			&& ((lastMove.second % 2) != (lastMove.first % 2)))
		{
			std::pair<int, int> secondLastMove;
			secondLastMove = moveList[moveList.size() -2];
			if( secondLastMove.second == (lastMove.second - 8) //if we have mowed abowe piece of secondlastmove
				&& (board[secondLastMove.second] == 2)
				&& ((secondLastMove.first) - (secondLastMove.second) == 16))
			{
				state = state | (0x1 << 6);
				board[secondLastMove.second] = 0;
			}

		}

		//test for black pawns
		else if (board[lastMove.second] == 2 
			&& ((lastMove.second % 2) != (lastMove.first % 2)))
		{
			std::pair<int, int> secondLastMove;
			secondLastMove = moveList[moveList.size() -2];
			if( secondLastMove.second == (lastMove.second + 8)
				&& (board[secondLastMove.second] == 1)
				&& ((secondLastMove.second) - (secondLastMove.first) == 16))
			{
				state = state | (0x1 << 7);
				board[secondLastMove.second] = 0;
			}

		}
	}

	//check for castling
	if ((board[lastMove.second] == 11 || board[lastMove.second] == 12)
		&& ((lastMove.second-lastMove.first) == 2 || (lastMove.first - lastMove.second ==2)))
	{
		state = state | 0xC0; //11000000
		if((lastMove.second%8)>4) //castling to right
		{
			board[lastMove.first + 1] = board[lastMove.first + 3]; //move the rook
			board[lastMove.first + 3] = 0;
		}

		else // castling to left
		{
			board[lastMove.first - 1] = board[lastMove.first - 4]; //move the rook
			board[lastMove.first - 4] = 0;
		}
	}





	//castling flags
	if(turn)
	{
		if((state >> 3) & 0x1)//right castling for white
		{
			if((board[4] != 11) || (board[7] != 7))
			{
				state = state & 0xF7; //11110111
			} 
		}
		if((state >> 2) & 0x1)//left castling for white
		{
			if((board[4] != 11) || (board[0] != 7))
			{
				state = state & 0xFB; //11111011
			} 
		}
	}

	else
	{
		if((state >> 5) & 0x1)//right castling for black
		{
			if((board[60] != 12) || (board[63] != 8))
			{
				state = state & 0xDF; //11011111
			} 
		}
		if((state >> 4) & 0x1)//left castling for black
		{
			if((board[60] != 12) || (board[56] != 8))
			{
				state = state & 0xEF; //11101111
			} 
		}
	}

	//checkmate should be checked for the opposite player
	if(turn)
		turn = 0;
	else
		turn = 1;


	int king_location = 0;
	for(int i=0;i<64;i++)
	{
		if(board[i] == (12 - turn))
		{
			king_location = i;
		}
	}

	//see if it's check
	if(isCheck(turn))
	{
		if(isCheckMate(king_location))
		{
			state = state | 0x1;
			//do some stuff to end the game
			return;
		}
	}

	else
	{
		if(isStaleMate(turn))
		{
			state = state | 0x2;
			//do some stuff to end the game
			return;
		}
	}		

	return;
}


bool Board::isCheckMate(int king_location) const
{
	//this algorithm must only be called in case there is check
	std::pair<int, int> pair = AiAlgorithm::algorithm(*this, 1, ((board[king_location]) % 2)==1);
	if(pair.first || pair.second)
		return false;
	return true;
}

int Board::isCheck(int turn) const //0 test if black is checked
{
	std::vector<int> moves;
	int king_location;

	//search the king
	for(int i = 0; i<64;i++)
	{
		if(board[i]== (12-turn))
		{
			king_location = i;
		}
	}

	//check moves for rook
	moves = Rules::rookMove(board, king_location);
	for(auto a:moves)
	{	
		if(board[a] == (7+turn) || board[a] == (9+turn))//check for enemys rook and queen
		{
			return king_location;
		}
	}

	//check moves for bishop and queen

	moves = Rules::bishopMove(board, king_location);
	for(auto a:moves)
	{
		if(board[a] == (5+turn) || board[a] == (9+turn))
		{
			return king_location;
		}
	}

//check moves for knight
	moves = Rules::knightMove(board, king_location);
	for(auto a:moves)
	{
		if(board[a] == (3+turn))
		{
			return king_location;
		}
	}

	//check the pawns
	std::pair<int,int>  nullpair= std::make_pair(0,0); //en passant is not valid
	if(turn) //test if black player is checked
	{
		moves = Rules::whitePawnMoveForwardRight(board, king_location, nullpair);
		moves = join(moves, Rules::whitePawnMoveForwardLeft(board, king_location, nullpair));
		for(auto a:moves)
		{
			if(board[a] == 2)
			{
				return king_location;
			}

		}
	}
	else
	{
		moves = Rules::blackPawnMoveForwardRight(board, king_location, nullpair);
		moves = join(moves, Rules::blackPawnMoveForwardLeft(board, king_location, nullpair));
		for(auto a:moves)
		{
			if(board[a] == 1)
			{
				return king_location;
			}
		}
	}		

	return 0;
}

bool Board::isStaleMate(int turn) const
{
	for(int i = 0;i<64;i++)
	{
		if((board[i] != 0 && (board[i] % 2 == turn) && (possibleMoves(i).size() != 0)))
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