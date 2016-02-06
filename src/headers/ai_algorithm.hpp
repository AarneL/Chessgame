#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <map>
#include <vector>
#include "../headers/board.hpp"


namespace AiAlgorithm {
	
	struct Move {
		int value;
		int origin;
		int destination;
	};

	std::pair<int, int> algorithm(const Board&, int, bool);

	int alphaBeta(const Board&, int, int, int, bool);

	int evaluate(const Board&);

	int getValue(int,int);

	std::vector<std::vector<Move>> divideForThreads(std::vector<Move> allPossibleMoves, int threads);

	std::vector<Move> getAllPossibleMoves(const Board& board, bool whiteTurn);
}



#endif
