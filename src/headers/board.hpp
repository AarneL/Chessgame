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
	int updateState(int, int);	//Return the index that should be manipulated after update (needed for pawn promotion)
	bool isCheckMate(int) const; //argument gives turn
	int isCheck(int) const; //returns position of king if it is checked
	bool isStaleMate(int) const; //should end the game
	void saveGame(Player* white, Player* black, const char* savePath);
	int getState() const;
	void changePiece(int, int);

private:
	std::vector<int> board; //contains pieces
	std::vector<std::pair<int, int> > moveList; //vector containing old moves
	std::vector<std::vector<int> > boardHistory;
	unsigned char state;
 /* Description of state:
  *
  * first two bits describe the last move
  * 01 = el passant made by white, 10 = el passant made by black, 11 = castling
  * rest of the bits are flags
  * (state >> 5) & 0x1 = right castling allowed for black
  * (state >> 4) & 0x1 = left castling allowed for black
  * (state >> 3) & 0x1 = right castling allowed for white
  * (state >> 2) & 0x1 = left castling allowed for white
  * (state >> 1) & 0x1 = stalemate
  * (state >> 0) & 0x1 = checkmate
  */

};

std::vector<int> join(std::vector<int>, std::vector<int>);

#endif /* OPTIONS_SCREEN_H */
