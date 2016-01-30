#include "../headers/game.hpp"
#include "../headers/ai_algorithm.hpp"
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <thread>

Game::Game()
{
	//there should really be some kind of mapping from ai_id to real ai but for now the id will only be difficulty of the ai in question.
	lasteat = 0;
	white = NULL;
	black = NULL;
}


void Game::tearDown(void)
{
	//Create base board starting from down left corner

	if (white != NULL) {
		delete white;
		white = NULL;
	}
	if (black != NULL) {
		delete black;
		black = NULL;
	}


}


void Game::initialize(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel)
{
	tearDown();

	// Game starts with white players turn
	board = Board();
	activeSquare = -1;
	initPlayers(whiteName, whiteLevel, blackName, blackLevel);

	playerOnTurn = white;
	//whitePlayerText.setString("White: " + white->getName());
	//blackPlayerText.setString("Black: " + black->getName());

	// To format info text
	//infoText.setString("Game started!\n" +  playerOnTurn->getName() + "'s turn.");

	timeOffset = 0;
	//clock.restart();
}



int Game::update()
{
	//This is probably graphical stuff and thus commented out
	//int currTime = (int)clock.getElapsedTime().asSeconds() + timeOffset;
	// Update clockstring
	//This is probably graphical stuff and thus commented out
	//clockText.setString(std::to_string(currTime / 60) + ":" + std::to_string(currTime % 60));
	 // Make sure that no moves is asked after checkmate or stalemate
			// Start new thread and calculate time elapsed for algorithm
			//clock.restart();
	std::pair<int, int> aimove = getAiMove();
	movePiece(aimove);
	//std::cout << "AI(lvl:" << playerOnTurn->getLevel() << ") calculated next turn in " << std::endl;



	


	return changeTurn();

}

std::pair<int, int> Game::getAiMove(void)
{

	return AiAlgorithm::algorithm(board, playerOnTurn->getLevel(), (playerOnTurn->getColor() == ColorType::White));


}

int Game::changeTurn()
{
	std::string nameOfOther = playerOnTurn->getName();

	// Change playerOnTurn
	changePlayerOnTurn();

	//Graphical stuff and thus commented out
	// Format infoText
	//infoText.setString(nameOfOther + " moved " + getMoveStr(getMoveList().back()) + "\n" + playerOnTurn->getName() + "'s turn.");

	if(board.getState() & 0x01)
	{
		//infoText.setString("Checkmate by " + nameOfOther + "!");
		//std::cout << "Checkmate" << std::endl;
		//checkmateSound.play()
		//highlightCheckmate();
		// Sleep
		//draw();
		//sf::sleep(sf::seconds(3));
		//endGameText.setString("Game ended!\n" + nameOfOther + " wins!");

		//
		//return endGame(); // End game info box
		return 1;
	}
	else if (board.getState() & 0x02)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		//std::cout << "Stalemate" << std::endl;
		//infoText.setString("Stalemate!");
		//stalemateSound.play()
		//highlightCheckmate();
		// Sleep
		//draw();
		//sf::sleep(sf::seconds(3));
		//endGameText.setString("Game ended to stalemate!\nDraw!");
		//return endGame(); // End game info box
		return 0;
	}
	if(lasteat == 100)
	{
		lasteat = 0;
		return -1;			
	}	
	return 2;
}

void Game::changePlayerOnTurn()
{
	if (playerOnTurn == black) {
		playerOnTurn = white;
	} else {
		playerOnTurn = black;
	}
}

void Game::initPlayers(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel)
{
	// White player type
	if (whiteName == "Computer") {
		white = new AI(whiteName, ColorType::White, whiteLevel);
	}
	else {
		std::cout << "something is wrong, check initPlayers() from Game::" << std::endl;
	}

	// Black player type
	if (blackName == "Computer") {
		black = new AI(blackName, ColorType::Black, blackLevel);
	}
	else {
		std::cout << "something is wrong, check initPlayers() from Game::" << std::endl;
	}
}

void Game::movePiece(std::pair<int,int>& move)
{

	// Move in board
	if(board.getBoard()[move.second] != 0)
		lasteat = 0;
	else
		lasteat++;
	board.movePiece(move.first, move.second);
	int index = board.updateState(move.second, 0); // Returns index if update needed
	if (index != -1) {
		// If stateword 0-63-> means pawn has reached enemy backline. Pawn is promotee
		changePiece(index);
		board.updateState(move.second, 0);
	}

	if((board.getState() >> 6) == 0x01) //01000000 passant made by white
	{

	}

	if((board.getState() >> 6) == 0x02) //10000000 passant made by black
	{

	}

	if((board.getState() >> 6) ==  0x03) //11000000 castling
	{
		if((move.second%8)>4) //castling to right
		{

		}

		else // castling to left
		{

		}
	}
}

void Game::changePiece(int index)
{
	int newPiece = -1;
	if (playerOnTurn == white) {
		newPiece = W_QUEEN;
	} else {
		newPiece = B_QUEEN;
	}
	board.changePiece(index, newPiece);
}

void Game::restartClock()
{
//	clock.restart();
}


