#include <iostream>
#include <thread>
#include "../headers/game.hpp"
#include "../headers/board.hpp"
#include "../headers/ai_algorithm.hpp"
#include "../headers/player.hpp"
#include "../headers/board.hpp"
#include "../headers/human.hpp"
#include "../headers/ai.hpp"
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <string>
#include <vector>

#include <stdio.h>
#include <time.h>

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main(void)
{
	int games = 0;
	std::cout << "Give the amount of games to be simulated" << std::endl;
	std::cin >> games;

	int white_ai = 0;
	std::cout << "Give the ID of AI for white" << std::endl;
	std::cin >> white_ai;

	int black_ai = 0;
	std::cout << "Give the ID of AI for black" << std::endl;
	std::cin >> black_ai;


	//this all shall be moved to another wrapper but for now let them be here for testing purposes
	int turn = 0;
	int status = 2; //this is the normal status
	Game game = Game();
	int whitewins = 0;
	int blackwins = 0;
	int stalemate = 0;
	int draw = 0;
	for(int i = 0;i<games;i++)
	{
		turn = 0;
		game.initialize("Computer", white_ai, "Computer", black_ai);
		while(status == 2)
		{
			status = game.update();
			turn++;
			//std::cout << "It's turn number: " << turn << std::endl;
		}
		if(status == 1)
		{
			if(turn%2)
			{
				whitewins++;
				//whatever needs to be done to restart
			}
			else
			{
				blackwins++;
			}
		}
		if(status == 0)
		{
			stalemate++;
		}
		if(status == -1)
		{
			draw++;
		}
		std::cout << "Whitewins: " << whitewins << std::endl << "Blackwins: " << blackwins << std::endl << "Stalemates: " << stalemate << std::endl << "Draw: " << draw << std::endl << "Turns played: " << turn << std::endl;
    std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
std::cout << std::endl;
		status = 2;
	}

	
}










