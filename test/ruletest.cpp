#include <iostream>

#include "./../src/headers/game.hpp"

bool w_pawntest(void)
{
	//Generate test_game
	Game test_game = Game();

	//Test possible moves for a white pawn that hasn't moved and can't eat
	int index = 14;
	std::vector<int> moves_possible = test_game.possibleMoves(index); 
	std::cout << "Possible moves for white pawn at square " << index << ": ";
	for(auto i:moves_possible)
		std::cout << i << " ";
	std::cout << std::endl;

	//move the pawn one square forward
	test_game.movePiece(14, 22); 

	//Test possible moves for a white pawn that has already moved and can't eat
	index = 22;
	moves_possible = test_game.possibleMoves(index);
	std::cout << "Possible moves for white pawn at square " << index << ": ";
	for(auto i:moves_possible)
		std::cout << i << " ";
	std::cout << std::endl;

	//Test possible moves for a white pawn that hasn't moved and has a piece in front of it

	//Test possible moves for a white pawn that hasn't moved and has a piece two squares in front of it

	//Test possible moves for a white pawn that has moved and has one piece in front of it

	//Test possible moves for a white pawn that can eat to the right

	//Test possible moves for a white pawn that can eat to the left

	//Test en passant to the right

	//Test en passant to the left

}

 bool b_pawntest(void)
{
	//Generate test_game
	Game test_game = Game();

	//Test possible moves for a black pawn that hasn't moved and can't eat
	int index = 49;
	std::vector<int> moves_possible = test_game.possibleMoves(index); 
	std::cout << "Possible moves for black pawn at square " << index << ": ";
	for(auto i:moves_possible)
		std::cout << i << " ";
	std::cout << std::endl;

	//move the pawn one square forward
	test_game.movePiece(49, 41); 

	//Test possible moves for a black pawn that has already moved and can't eat
	index = 41;
	moves_possible = test_game.possibleMoves(index);
	std::cout << "Possible moves for black pawn at square " << index << ": ";
	for(auto i:moves_possible)
		std::cout << i << " ";
	std::cout << std::endl;

	//Test possible moves for a black pawn that hasn't moved and has a piece in front of it

	//Test possible moves for a black pawn that hasn't moved and has a piece two squares in front of it

	//Test possible moves for a black pawn that has moved and has one piece in front of it

	//Test possible moves for a black pawn that can eat to the right

	//Test possible moves for a black pawn that can eat to the left

	//Test en passant to the right

	//Test en passant to the left

}

int main(void)
{
	w_pawntest();
	b_pawntest();
}

