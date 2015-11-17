#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <map>
#include <vector>
#include "./board.hpp"


namespace AiAlgorithm {


	std::pair<int, int> algorithm(Board, int, bool);

	int alphabeta(Board, int, int, int, bool);

	int evaluate(Board&);

	int getValue(int);

}



#endif
