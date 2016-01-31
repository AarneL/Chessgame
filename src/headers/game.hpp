#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include "../headers/player.hpp"
#include "../headers/board.hpp"
#include "../headers/human.hpp"
#include "../headers/ai.hpp"


class Game
{
private:
	// Clock
	//sf::Clock clock;
	// For saving the current time when saving or going to
	// main menu that is added to clock's elapsed time
	// when restarting the clock
	int timeOffset;

	
	//sf::Clock w_aiClock; // To record white ai calculation times
	//sf::Clock b_aiClock; // To record black ai calculation times

public:
	Game(void);
	int update(); //return values, 2=normal, 1=checmate by black, 0=checkmate by white, -1=stalemate
	void movePiece(std::pair<int, int>& move);
	void changePlayerOnTurn();
	int changeTurn();
	bool containsPlayerPiece(int i, Player* p);
	bool belongsToPlayer(int i, Player* p);
	std::vector<std::pair<int, int>> getMovelist() const;
	std::pair<int,int> getAiMove();
	void initialize(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel);
	void tearDown(void);
	int lasteat; // calculates moves form last move when piece was eaten

	// Pawn promotion
	void changePiece(int index);

	// Game interface
	Board board;
	int activeSquare;

	void initPlayers(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel);

	Player *white;
	Player *black;
	Player *playerOnTurn;
	std::vector<int> possibleMoves;

	void restartClock(); // Other screens can also restart the clock

};
#endif


