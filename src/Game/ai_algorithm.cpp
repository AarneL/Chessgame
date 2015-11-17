#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "./../headers/ai_algorithm.hpp"
#include "./../headers/board.hpp"

#define MAX 1000000
#define MIN -1000000
//black pieces have negative value so black player is always minimizing
//needs to use board merhods


namespace AiAlgorithm
{

	std::pair<int, int> algorithm(const Board& board, int depth, bool maximizingPlayer)
	{
		std::vector<int> v = {0, 0, 0}; //container for best value and the move to get there
		
		int a = MIN; //alpha
		int b = MAX; //beta

		if (maximizingPlayer)//White players turn
		{

			v[0] = MIN; //smallest int
			for(int i = 0; i < 64; i++)//iterate through the board
			{
				if(board.getBoard()[i]%2 == 1)//if piece is white
				{
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j);//supposing possibleMoves doesn't return origin
						int temp = alphaBeta(newboard, depth-1, a, b, false);
						if(v[0] < temp)
						{
							v[0] = temp;
							v[1] = i;
							v[2] = j;
						}
						a = std::max(a, v[0]);
						if (b <= a)
						{
							break; //cut off
						}
					}
				}
			}
		}

		else //Black players turn
		{
			v[0] = MAX;
			for(int i = 0; i < 64; i++)
			{
				if(board.getBoard()[i]%2 == 0 && board.getBoard()[i] != 0)
				{
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j);
						int temp = alphaBeta(newboard, depth-1, a, b, true);
						if(temp < v[0])
						{
							v[0] = temp;
							v[1] = i;
							v[2] = j;
						}
						b = std::min(b,v[0]);
						if(b<=a)
						{
							break; //cut off
						}
					}
				}
			}
		}
		return std::make_pair(v[1], v[2]);
	}


	int alphaBeta(Board& board, int depth, int a, int b, bool maximizingPlayer)
	{
		//check if the algorithm has reached it's depth
		
		if( depth == 0 )
			return evaluate(board);

		//staleMate

		//check if the board is in chessmate
		if( board.isCheckMate())
		{
			if(maximizingPlayer)
			{
				return MIN;	//if it's white players turn the result is good for black player
			}
			else
			{
				return MAX;
			}

		}

		//find all own pieces
		if (maximizingPlayer)//White players turn
		{

			int v = MIN; //smallest int
			for(int i = 0; i < 64; i++)//iterate through the board
			{
				if(board.getBoard()[i]%2 == 1)//if piece is white
				{	
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j);//supposing possibleMoves doesn't return origin
						v = std::max(v, alphaBeta(newboard, depth-1, a, b, false)); //call alphabeta for black player
						a = std::max(a, v);
						if (b <= a)
						{
							break; //cut off
						}
					}
				}
			}
			return v;
		}

		else //Black players turn
		{
			int v = MAX;
			for(int i = 0; i < 64; i++)
			{
				if(board.getBoard()[i]%2 == 0 && board.getBoard()[i] != 0)
				{
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j);
						v = std::min(v, alphaBeta(newboard, depth-1, a, b, true));
						b = std::min(b,v);
						if(b<=a)
						{
							break; //cut off
						}
					}
				}
			}
			return v;
		}

	}

	int evaluate(Board& board)
	{
		int value = 0;
		for(int i = 0; i < 64; i++)
		{
			value = value + getValue(board.getBoard()[i]);
		}

		//evaluate
		//white pieces are of positive value and black pieces are negative

		//lets make table for values of pieces
		return value;
	}

	int getValue(int piece)
	{
		switch(piece)
		{
			case W_PAWN:
				return 100;
				break;

			case B_PAWN:
				return -100;
				break;

			case W_KNIGHT:
				return  300;
				break;

			case B_KNIGHT:
				return -300;
				break;

			case W_BISHOP:
				return 300;
				break;

			case B_BISHOP:
				return -300;
				break;

			case W_ROOK:
				return 450;
				break;

			case B_ROOK:
				return -450;
				break;

			case W_QUEEN:
				return 850;
				break;

			case B_QUEEN:
				return -850;
				break;
		}
	return 0;
	}

}