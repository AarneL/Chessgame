#include "./../headers/game.hpp"
#include "./../headers/board.hpp"
#include "./../headers/human.hpp"
#include "./../headers/player.hpp"
#include <vector>
#include <string>

Game::Game()
{
	std::string name1 = "White player";
	std::string name2 = "Black player";
	white = new Human(name1, ColorType::White);
	black = new Human(name2, ColorType::Black);
	board = Board();
	pieceActive = false;
	playerOnTurn = white;
}

std::vector<int> Game::possibleMoves(int index)
{
	std::vector<int> v;
	if (pieceActive) {
		// If piece is active check if index is on possibleMovesList
		// If not, clear pieceActive and clear highlights (return empty list)

	}

	else if (containsPlayerPiece(index, playerOnTurn)) {
		pieceActive = true;
		return board.possibleMoves(index);
	}
	return v;
}

void Game::movePiece(int origin, int destination)
{
	std::cout << "Moving piece" << std::endl;

	//TODO: This should maybe return boolean to check if successfull?
	if (!board.movePiece(origin, destination))
		std::cout << "Moving piece failed!" << std::endl;
	else {
		std::cout << "Piece moved" << std::endl;
		// Change turn
		if (playerOnTurn == white)
			playerOnTurn = black;
		else if (playerOnTurn == black)
			playerOnTurn = white;
	}
}

bool Game::containsPlayerPiece(int i, Player* p)
{
	if (belongsToPlayer(board.getBoard()[i], p))
		return true;
	return false;
}

bool Game::belongsToPlayer(int i, Player* p)
{
	if ((p->getColor() == ColorType::White) && (i % 2 == 0) && (i != 0))
		return true;
	else if ((p->getColor() == ColorType::Black) && (i % 2 == 1) && (i != 0))
		return true;
	return false;
}
