#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>


#include "./../headers/ai_algorithm.hpp"
#include "./../headers/board.hpp"

#define MAX 1000000
#define MIN -1000000
//black pieces have negative value so black player is always minimizing
//needs to use board merhods


namespace AiAlgorithm
{


	std::pair<int, int> algorithm(const Board& board, int depth, bool whiteOnTurn)
	{
		Move currentBestMove = {0, 0, 0}; // Container for best value and the move to get there
		
		int a = MIN; // Alpha
		int b = MAX; // Beta

		// 1. Get number of threads that system can manage
		unsigned int num_of_threads = std::thread::hardware_concurrency();
		std::srand((int)std::time(0));
		// 2. Get all possible moves and divide them as tasks to threads
		std::vector<std::vector<Move>> taskVectors;
		taskVectors = divideForThreads(getAllPossibleMoves(board, whiteOnTurn), (int)num_of_threads);

		// 3. Create threadpool and run tasks with threads
		std::vector<std::thread> threads;

		// Lambda
		auto lambda = [taskVectors, board, depth, whiteOnTurn](int i, int a, int b)
		{
			int thread_b = b;
			std::srand((int)std::time(0)); // Use current time as a seed for random

										   // This is what the thread does to its tasks 
										   // This also works as 1st level of algorithm (because of alphaBeta structure)
			for (auto move : taskVectors[i]) {
				Board new_board = board;
				new_board.movePiece(move.origin, move.destination);
				int temp = alphaBeta(new_board, depth - 1, a, b, whiteOnTurn);

				if ((temp < move.value) && whiteOnTurn) // Make sure a proper move is chosen
				{
					move.value = temp;
				}
				else if (temp > move.value && !whiteOnTurn)
				{
					move.value = temp;
				}

				else if (move.value == temp && (rand() % 8 == 1))
				{
					move.value = temp;
				}
				thread_b = std::min(b, move.value);
				if (b <= a)
				{
					break; // Cut off bad branch
				}
			}
		};

		// Create threads and push them in vector
		for (unsigned int i = 0; i < taskVectors.size(); i++) {
			// Some magic with lambda functions
			threads.push_back(std::thread(lambda, i, a, b));
		}

		// 4. Wait threads to finish
		for (auto thread = threads.begin(); thread != threads.end(); thread++)
		{
			thread->join();
		}

		// 5. Choose best value
		for (auto list : taskVectors) {
			for (auto move : list) {
				if (move.value > currentBestMove.value) {
					currentBestMove = move; // Replace with better one
				}
				// To have some random factor if same values
				else if (move.value == currentBestMove.value && (rand() % 8 == 1)) {
					currentBestMove = move;
				}
			}
		}
		return std::make_pair(currentBestMove.destination,currentBestMove.destination);
	}


	int alphaBeta(const Board& board, int depth, int a, int b, bool maximizingPlayer)
	{
		if( depth == 0 )  // Check if the algorithm has reached it's depth
		{
			if(board.isStaleMate(maximizingPlayer))  //before evaluation see if it's stalemate or checkmate
			{
				// Do some stuff to end the game
				if(board.isCheck(maximizingPlayer))
				{
					if(maximizingPlayer)
						return MIN + 100;
					else
						return MAX - 100;
				}
				else
				{
					return 0;
				}
			}
			return evaluate(board);
		}
		// Find all own pieces
		if (maximizingPlayer) // White players turn
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

	int evaluate(const Board& board)
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

	// Divides all possible moves for given thread amount
	std::vector<std::vector<Move>> divideForThreads(std::vector<Move> allPossibleMoves, int threads)
	{
		// This divides possiblemoves to n vectors (number of usable cores)
		int size = allPossibleMoves.size();
		std::vector<std::vector<Move>> returnVector;

		int move = 0;
		for (int core = 1; core <= threads; core++) {
			std::vector<Move> temp;
			while (move < ((size - 1)/ threads)*core) {
				temp.push_back(allPossibleMoves[move++]);
			}
			returnVector.push_back(temp);
		}

		return returnVector;
	}

	// Gets all possible moves of player (to be used by threads
	std::vector<Move> getAllPossibleMoves(const Board& board, bool whiteTurn)
	{
		std::vector<Move> ret;
		if (whiteTurn) {
			for (int i = 0; i < 64; i++) // Iterate through the board
			{
				if (board.getBoard()[i] % 2 == 1) // If piece is white
				{
					for (auto dest : board.possibleMoves(i)) {
						Move temp = { 0, i, dest }; // 0 is initial value of move
						ret.push_back(temp);
					}
				}
			}
		}
		else {
			for (int i = 0; i < 64; i++) // Iterate through the board
			{
				if (board.getBoard()[i] % 2 == 0 && board.getBoard()[i] != 0) // If piece is black (0 is empty)
				{
					for (auto dest : board.possibleMoves(i)) {
						Move temp = { 0, i, dest }; // 0 is initial value of move
						ret.push_back(temp);
					}
				}
			}
		}
		return ret;
	}
}
