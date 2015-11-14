#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include <map>
#include <vector>


namespace Rules {


	std::vector<int> whitePawnMoveForward(const std::vector<int>&, int);
	std::vector<int> whitePawnMoveForwardLeft(const std::vector<int>&, int, const std::pair<int,int>&);
	std::vector<int> whitePawnMoveForwardRight(const std::vector<int>&, int, const std::pair<int,int>&);


	std::vector<int> blackPawnMoveForward(const std::vector<int>&, int);
	std::vector<int> blackPawnMoveForwardLeft(const std::vector<int>&, int, const std::pair<int,int>&);
	std::vector<int> blackPawnMoveForwardRight(const std::vector<int>&, int, const std::pair<int,int>&);

	std::vector<int> whiteKnightMove(const std::vector<int>&, int);


	//Utilities
	bool checkBoundaries(int, int);
}


#endif