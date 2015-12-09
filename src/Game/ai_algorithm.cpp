#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
		std::vector<int> v = {0, 0, 0}; // Container for best value and the move to get there
		
		int a = MIN; // Alpha
		int b = MAX; // Beta
		std::srand(std::time(0)); // Use current time as a seed for random

		if (maximizingPlayer) // White players turn
		{

			v[0] = MIN; // Smallest int
			for(int i = 0; i < 64; i++) // Iterate through the board
			{
				if(board.getBoard()[i]%2 == 1) // If piece is white
				{
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j); // Supposing possibleMoves doesn't return origin
						newboard.updateState(j, 1);
						int temp = alphaBeta(newboard, depth-1, a, b, false);
						if(v[0] < temp) // Make sure a proper move is chosen
						{
							v[0] = temp;
							v[1] = i;
							v[2] = j;
						}
						else if(v[0] == temp && (rand()%8 == 1))
						{
								v[0] = temp;
								v[1] = i;
								v[2] = j;
						}
						a = std::max(a, v[0]);
						if (b <= a)
						{
							break; // Cut off bad branch
						}
					}
				}
			}
		}

		else // Black players turn (maximizing == false)
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
						newboard.updateState(j, 1);
						int temp = alphaBeta(newboard, depth-1, a, b, true);
						if(temp < v[0]) // Make sure a proper move is chosen
						{
							v[0] = temp;
							v[1] = i;
							v[2] = j;
						}
						else if(v[0] == temp && (rand()%8 == 1))
						{
								v[0] = temp;
								v[1] = i;
								v[2] = j;
						}
						b = std::min(b,v[0]);
						if(b<=a)
						{
							break; // Cut off bad branch
						}
					}
				}
			}
		}
		return std::make_pair(v[1], v[2]);
	}


	int alphaBeta(Board& board, int depth, int a, int b, bool maximizingPlayer)
	{
		// Check if the algorithm has reached it's depth
		
		if( depth == 0 )
			return evaluate(board);

		// Find all own pieces
		if (maximizingPlayer)//White players turn
		{

			int v = MIN; // Smallest int
			for(int i = 0; i < 64; i++)// Iterate through the board
			{
				if(board.getBoard()[i]%2 == 1)// If piece is white
				{	
					for(auto j:board.possibleMoves(i))
					{
						Board newboard = board;
						newboard.movePiece(i, j);// Supposing possibleMoves doesn't return origin
						newboard.updateState(j, 1);
						v = std::max(v, alphaBeta(newboard, depth-1, a, b, false)); // Call alphabeta for black player
						a = std::max(a, v);
						if (b <= a)
						{
							break; // Cut off
						}
					}
				}
			}
			if(v == MIN) // Has not chosen a move -> possiblemoves must be empty
			{
				if(board.isCheck(maximizingPlayer))
				{
					return (MIN+100-depth);	// If it's check it's also checkmate
				}
				else // Otherwise it must be stalemate
				{
					return 0;
				}
			}
			return v;
		}

		else // Black players turn
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
						newboard.updateState(j, 1);
						v = std::min(v, alphaBeta(newboard, depth-1, a, b, true));
						b = std::min(b,v);
						if(b<=a)
						{
							break; // Cut off
						}
					}
				}
			}
			if(v == MAX) // Has not chosen a move -> possiblemoves must be empty
			{
				if(board.isCheck(maximizingPlayer)) // If it's check it's also checkmate
				{
					return (MAX-100+depth);
				}
				else // Otherwise it must be stalemate
				{
					return 0;
				}
			}
			return v;
		}

	}

	int evaluate(Board& board)
	{
		std::vector<int> b = board.getBoard();
		int value = 0;
		for(int i = 0; i < 64; i++)
		{
			value = value + getValue(b[i], i);
		}

		// Evaluate
		// White pieces are of positive value and black pieces are negative

		// Lets make table for values of pieces
		return value;
	}

	int getValue(int piece, int index)
	{
		switch(piece)
		{
			case W_PAWN:
				return 100 + (((index - 1) / 8) * 10); // Pawns value increases the more it has moved 
				break;

			case B_PAWN:
				return -100 - (((63 - index - 1) / 8) * 10); // Same for black
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
				
			case W_KING:
				return 100000;
				break;

			case B_KING:
				return -100000;
				break;
			
			default:
				return 0;
		}
	}

}
