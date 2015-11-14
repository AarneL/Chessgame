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

	std::vector<int> knightMove(const std::vector<int>&, int);

	std::vector<int> rookMove(const std::vector<int>&, int);

	std::vector<int> bishopMove(const std::vector<int>&, int);

	std::vector<int> queenMove(const std::vector<int>&, int);

	//NOTE the 3rd argument to prevent infinite recursions (when false)
	std::vector<int> kingMove(const std::vector<int>& board, int index, bool recurse=true);



	bool isThreatenedAfter(const std::vector<int>&, int, int);


}


#endif