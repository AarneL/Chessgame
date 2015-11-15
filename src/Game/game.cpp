#include "./../headers/game.hpp"
#include "./../headers/board.hpp"
#include "./../headers/human.hpp"
#include "./../headers/player.hpp"
#include <vector>
#include <string>
#include <algorithm>

Game::Game()
{
	std::string name1 = "White player";
	std::string name2 = "Black player";
	white = new Human(name1, ColorType::White);
	black = new Human(name2, ColorType::Black);
	board = Board();
	activeSquare = -1;
	playerOnTurn = white;
}

std::vector<int> Game::getPossibleMoves(int index)
{
	std::vector<int> v;
	if (activeSquare != -1) {
		// If piece is active check if index is on possibleMovesList
		// If not, clear pieceActive and clear highlights(done in GUI) (return empty list)
		if (std::find(possibleMoves.begin(), possibleMoves.end(), index) != possibleMoves.end())
		{
			board.movePiece(activeSquare, index);
			changeTurn();
		}
		activeSquare = -1;
	}

	else if (containsPlayerPiece(index, playerOnTurn)) {
		activeSquare = index;
		possibleMoves = board.possibleMoves(index);
		return possibleMoves;
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

void Game::changeTurn()
{
	if (playerOnTurn == black) {
		playerOnTurn = white;
	}
	else {
		playerOnTurn = black;
	}
}
