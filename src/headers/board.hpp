#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "player.hpp"

enum Piece
	{
		NONE = 0,
		W_PAWN = 1,
		B_PAWN = 2,
		W_KNIGHT = 3,
		B_KNIGHT = 4,
		W_BISHOP = 5,
		B_BISHOP = 6,
		W_ROOK = 7,
		B_ROOK = 8,
		W_QUEEN = 9,
		B_QUEEN = 10,
		W_KING = 11,
		B_KING = 12
	};

class Board
{
public:
	Board();
	std::vector<int> possibleMoves(int index) const;
	std::vector<int> allPossibleMoves(int index) const;
	bool movePiece(int origin, int destination);
	std::vector<int> getBoard() const;
	std::vector<std::pair<int, int> > getMoveList() const;
	void updateState(int);
	bool isCheckMate(int) const; //argument gives turn
	int isCheck(int) const; //returns position of king if it is checked
	bool isStaleMate(int) const; //should end the game
	void saveGame(Player* white, Player* black);
	int getState() const;

private:
	std::vector<int> board; //contains pieces
	std::vector<std::pair<int, int> > moveList; //vector containing old moves
	std::vector<std::vector<int> > boardHistory;
	int state; //0 normal, 1 checkmate, 2 stalemate
};

std::vector<int> join(std::vector<int>, std::vector<int>);

#endif /* OPTIONS_SCREEN_H */