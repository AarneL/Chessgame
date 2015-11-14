#ifndef GAME_H
#define GAME_H
#include <vector>
#include <map>
#include "./../headers/board.hpp"
#include "./../headers/player.hpp"

class Game
{
public:
	Game();

	// If GUI sends index when piece is not active and square contains piece owned by player on turn
	std::vector<int> possibleMoves(int index);

	// 
	void movePiece(int origin, int destination);

	// Returns true if square contains piece owned by player p
	bool containsPlayerPiece(int i, Player* p);

	// Returns true if given board value belongs to player (enum)
	bool belongsToPlayer(int i, Player* p);

private:
	Player* white;
	Player* black;
	Board board;
	Player* playerOnTurn;
	bool pieceActive;
};

#endif /* OPTIONS_SCREEN_H */