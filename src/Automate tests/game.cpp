#include "../headers/ai_algorithm.hpp"
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <string>
#include <vector>

Game::Game(int white_ai, int black_ai)
{
	//there should really be some kind of mapping from ai_id to real ai but for now the id will only be difficulty of the ai in question.
}


int Game::update()
{
	int currTime = (int)clock.getElapsedTime().asSeconds() + timeOffset;
	// Update clockstring
	clockText.setString(std::to_string(currTime / 60) + ":" + std::to_string(currTime % 60));


	if (board.getState() & 0x3) { // Make sure that no moves is asked after checkmate or stalemate
			// Start new thread and calculate time elapsed for algorithm
			aiClock.restart();
			std::pair<int, int> aimove = getAiMove();
	}

	movePiece(temp);
	
	std::cout << "AI(lvl:" << playerOnTurn->getLevel() << ") calculated next turn in " << aiClock.getElapsedTime().asSeconds() << " seconds." << std::endl;
	ai_algorithm_mutex.lock();
	{
		aimove.first = 0;
		aimove.second = 0;
	}
	ai_algorithm_mutex.unlock();

	waitingAiMove = false;
	return changeTurn();

	return 2;
}

