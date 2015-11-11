#include <vector>

namespace Rules
{
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
	std::vector<int> whitePawnMoveForward(std::vector<int> board, int index)
	{
		std::vector<int> v; 
		// If there is piece in front of whitepawn it cannot go there or behind it
		if (!(board[index + 8] != 0) && ((index + 8) <= 63)) {
			v.push_back(index + 8);
			if (!(board[index + 16] != 0) && ((index + 16) <= 63)) // 2-forward
				v.push_back(index + 16);
		}
		return v;
	}

	int whitePawnMoveForwardLeft()
	{
		return 0;
	}

	int whitePawnMoveForwardRight()
	{
		return 0;
	}

	// ======= Moves for black pieces ======
	std::vector<int> blackPawnMoveForward(std::vector<int> board, int index)
	{
		std::vector<int> v;

		// If there is piece in front of blackpawn it cannot go there or behind it
		if (!(board[index - 8] != 0) && ((index + 8) >= 0)) {
			v.push_back(index - 8);
			if (!(board[index - 16] != 0) && ((index - 16) <= 63)) // 2-forward
				v.push_back(index - 16);
		}
		return v;
	}

	void blackPawnMoveForwardLeft()
	{

	}

	void blackPawnMoveForwardRight()
	{

	}


}