#ifndef GAME_H
#define GAME_H
#include <vector>
#include <map>
#include "./../headers/board.hpp"
#include "./../headers/player.hpp"

class Game
{
public:
	Game(void);

	// If GUI sends index when piece is not active and square contains piece owned by player on turn
	std::vector<int> possibleMoves(int index);

	// 
	void movePiece(int origin, int destination);

	// Returns true if square contains piece owned by player p
	bool containsPlayerPiece(int i, Player& p);

private:
	Player* white;
	Player* black;
	Board board;
	bool pieceActive;
};

#endif /* OPTIONS_SCREEN_H */