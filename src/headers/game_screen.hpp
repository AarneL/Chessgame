#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "board.hpp"
#include "human.hpp"
#include "ai.hpp"
#include "text.hpp"
#include "button.hpp"
#include "object.hpp"
#include "square.hpp"
#include "chess_piece.hpp"


class GameScreen : public BaseScreen
{
private:
	/* To draw board properly program must have different sprite for each piece
	 *
	*/
	sf::RenderWindow &window;
	// Container for all elements to draw
	std::vector<Object*> elements;
	// White pieces
	ChessPiece whitePawn1;
	ChessPiece whitePawn2;
	ChessPiece whitePawn3;
	ChessPiece whitePawn4;
	ChessPiece whitePawn5;
	ChessPiece whitePawn6;
	ChessPiece whitePawn7;
	ChessPiece whitePawn8;

	ChessPiece whiteRook1;
	ChessPiece whiteRook2;

	ChessPiece whiteBishop1;
	ChessPiece whiteBishop2;

	ChessPiece whiteKnight1;
	ChessPiece whiteKnight2;

	ChessPiece whiteQueen;
	ChessPiece whiteKing;

	// Black pieces
	ChessPiece blackPawn1;
	ChessPiece blackPawn2;
	ChessPiece blackPawn3;
	ChessPiece blackPawn4;
	ChessPiece blackPawn5;
	ChessPiece blackPawn6;
	ChessPiece blackPawn7;
	ChessPiece blackPawn8;

	ChessPiece blackRook1;
	ChessPiece blackRook2;

	ChessPiece blackBishop1;
	ChessPiece blackBishop2;

	ChessPiece blackKnight1;
	ChessPiece blackKnight2;

	ChessPiece blackQueen;
	ChessPiece blackKing;

	std::vector<ChessPiece*> pieces;

	// Game board
	std::vector<Square*> gameBoard;

	std::vector<std::pair<int, int> > moveList;

	sf::SoundBuffer moveSoundBuffer;
	sf::Sound moveSound;

	//sf::SoundBuffer gameWinSoundBuffer;
	//sf::SoundBuffer gameLoseSoundBuffer;

	// Buttons
	Button saveButton;
	Button mainMenuButton;

	// Player names
	Text whitePlayerText;
	Text blackPlayerText;

public:
    GameScreen(sf::RenderWindow &w);

	// Draw related functions
	void loadContent(void);
	int update();
    void draw();
	void highlight(std::vector<int> v);
	void clearHighlights();
	void clearButtonHighlights();
	void initialize(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel);
	void tearDown(void);

	// Game updating and analysis
	void movePiece(std::pair<int, int> move);
	int changeTurn();
	bool containsPlayerPiece(int i, Player* p);
	bool belongsToPlayer(int i, Player* p);
	std::vector<std::pair<int, int> > getMoveList() const;
	std::pair<int, int> getAiMove();
	void changePiece(int index);
	void showSaveGameDialog();

	// Game interface
	Board board;
	int activeSquare;

	// Game functionality to gamescreen
	Player *white;
	Player *black;
	Player *playerOnTurn;
	std::vector<int> possibleMoves;

	// Parameters for graphical design
	int BOARD_HORIZONTAL_OFFSET;
	int BOARD_VERTICAL_OFFSET;

};

#endif
