#include "./../headers/game.hpp"
#include "./../headers/board.hpp"
#include <vector>

Game::Game(void)
{
	board = Board();
	pieceActive = false;
}

std::vector<int> Game::possibleMoves(int index)
{
	std::vector<int> v;
	if (pieceActive) {
		// If piece is active check if index is on possibleMovesList

		// If not, clear pieceActive and clear highlights (return empty list)

	}

	else if (containsPlayerPiece(index, PLAYER_ON_TURN)) {
		pieceActive = true;
		return board.possibleMoves(index);
	}
	return v;
}

bool Game::movePiece(int origin, int destination)
{
	if(board.movePiece(origin, destination))
	{
		return true;
	}
	return false;
}

bool Game::containsPlayerPiece(int, int)
{

}