#include "./../headers/board.hpp"
#include "./../headers/rules.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "../headers/ai_algorithm.hpp"

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

void Board::updateState(int index)
{
	int turn = board[index] % 2;
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
			state = 1;
			//do some stuff to end the game
			if(turn)
			{
				std::cout << "Checkmate by black player" << std::endl; 
			}
			else
			{
				std::cout << "Checkmate by white player" << std::endl;
			}
			return;
		}
	}
	else
	{
		if(isStaleMate(turn))
		{
			state = 2;
			std::cout << "Stalemate" << std::endl;
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