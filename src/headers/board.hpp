#ifndef BOARD_H
#define BOARD_H
#include <vector>

enum Piece {NONE, 
	W_PAWN, B_PAWN, 
	W_KNIGHT, B_KNIGHT, 
	W_BISHOP, B_BISHOP, 
	W_ROOK, B_ROOK, 
	W_QUEEN, B_QUEEN, 
	W_KING, B_KING};

class Board
{
public:
	Board(void);
	std::vector<int> possibleMoves(int index);
	bool movePiece(int origin, int destination);

private:
	std::vector<int> board; //contains pieces
	std::vector<std::pair<int, int>> moveList; //vector containing old moves
	std::vector<std::vector<int>> boardHistory;
};

#endif /* OPTIONS_SCREEN_H */