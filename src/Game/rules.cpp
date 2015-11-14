//#include <vector>

#include "../headers/rules.hpp"

namespace Rules
{
	//typedef std::vector<int> ivector;

	/* Here are implementations all the specific rules that might 
	 * prevent moving specific piece to location or to all locations in direction
	 * Some notable information:
	 *    - Every rule gets vector of integers as parameter (board). Each index of vector
	 *    - represents location on map.
	 *
	 *				    + 8		
	 *				     	
	 *           - 1   piece  + 1
	 *				   
	 *				    - 8
	 *    
	 *	  - Target location should be withing boundaries 0 <= target <= 63
	 *
	 *    - If player is moving piece to left, there should be check that it is not on left edge 
	 *      this is easily done: if(currentIndex % 8 = 0) -> its on left edge
	 *
	 *    - If player is moving piece to left, there should be check that it is not on left edge 
	 *      this is easily done: if((index + 1) % 8 = 0) -> its on right edge
	 *
	 *
	 */

	 // ======= Moves for white pieces ======
	//
	std::vector<int> whitePawnMoveForward(const std::vector<int>& board, int index)
	{
		std::vector<int> v; 
		// If there is piece in front of whitepawn it cannot go there or behind it
		if ( board[index + 8] == 0 && (index + 8) <= 63 ) {
			v.push_back(index + 8);
			//2 forward if the +2*8 square is also free and the piece is on the start row
			if ( board[index + 16] == 0 && index >= 8 && index <= 15  )
				v.push_back(index + 16);
		}
		return v;
	}

	//White pawn capture left
	std::vector<int> whitePawnMoveForwardLeft(const std::vector<int>& board, int index, const std::pair<int,int>& lastmove)
	{
		std::vector<int> v;
		int dest = index + 8 - 1;

		//Boundary check
		if ( (dest+1)%8 != 0 ){
			//not empty and contains black piece
			if (board[dest] != 0 && board[dest]%2 == 0)
				v.push_back(dest);
			// en passant //NOTE: this and the normal capture are mutually exclusive so return cannot contain dest twice
			//  1. destination empty 2. to left is black pawn 3. last move was over the destination
			if (board[dest] == 0 && board[index-1] == 2 && lastmove.first == dest+8 && lastmove.second == dest-8 )
				v.push_back(dest);
		}
		return v;
	}

	//White pawn capture right
	std::vector<int> whitePawnMoveForwardRight(const std::vector<int>& board, int index, const std::pair<int,int>& lastmove)
	{
		std::vector<int> v;
		int dest = index + 8 + 1;

		//Don't jump over the boundary
		if ( dest%8 != 0 ){
			//not empty and contains black piece
			if (board[dest] != 0 && board[dest]%2 == 0)
				v.push_back(dest);
			// en passant //NOTE: this and the normal capture are mutually exclusive so return cannot contain dest twice
			//  1. destination empty 2. to right is black pawn 3. last move was over the destination
			if (board[dest] == 0 && board[index+1] == 2 && lastmove.first == dest+8 && lastmove.second == dest-8 )
				v.push_back(dest);
		}
		return v;
	}

	

	// ======= Moves for black pieces ======
	//Black pawn forward
	std::vector<int> blackPawnMoveForward(const std::vector<int>& board, int index)
	{
		std::vector<int> v;

		// If there is piece in front of blackpawn it cannot go there or behind it
		if ( board[index - 8] == 0 && (index + 8) >= 0 ) {
			v.push_back(index - 8);
			//2 forward if the -2*8 square is also free and the piece is on the start row
			if ( board[index - 16] == 0 && index >= 48 && index <= 55 )
				v.push_back(index - 16);
		}
		return v;
	}

	//Black pawn capture left NOTE: absolute left, not relative to black player
	std::vector<int> blackPawnMoveForwardLeft(const std::vector<int>& board, int index, const std::pair<int,int>& lastmove)
	{
		std::vector<int> v;
		int dest = index - 8 - 1;

		//Boundary check
		if ( (dest+1)%8 != 0 ){
			//not empty and contains white piece
			if ( board[dest] != 0 && board[dest]%2 == 1 )
				v.push_back(dest);
			// en passant //NOTE: this and the normal capture are mutually exclusive so return cannot contain dest twice
			//  1. destination empty 2. to left is white pawn 3. last move was over the destination
			if (board[dest] == 0 && board[index-1] == 1 && lastmove.first == dest-8 && lastmove.second == dest+8 )
				v.push_back(dest);
		}
		return v;
	}

	//Black pawn capture right NOTE: absolute right, not relative to black player
	std::vector<int> blackPawnMoveForwardRight(const std::vector<int>& board, int index, const std::pair<int,int>& lastmove)
	{
		std::vector<int> v;
		int dest = index - 8 + 1;

		//Boundary check
		if ( dest%8 != 0 ){
			//not empty and contains white piece
			if ( board[dest] != 0 && board[dest]%2 == 1 )
				v.push_back(dest);
			// en passant //NOTE: this and the normal capture are mutually exclusive so return cannot contain dest twice
			//  1. destination empty 2. to right is white pawn 3. last move was over the destination
			if (board[dest] == 0 && board[index+1] == 1 && lastmove.first == dest-8 && lastmove.second == dest+8 )
				v.push_back(dest);
		}
		return v;
	}


	//Moves for knight
	//Possible moves:
	//+16+1, +16-1, +2+8, +2-8, -16+1, -16-1, -2+8, -2-8
	std::vector<int> knightMove(const std::vector<int>& board, int index) {

		std::vector<int> v;

		//Moves (changes in position) to be tested
		std::vector<int> testvector = {17, 15, 10, -6, -15, -17, 6, -10};	//C++11...

		for (int i : testvector){

			//TODO

		}

		return v;
	}




}