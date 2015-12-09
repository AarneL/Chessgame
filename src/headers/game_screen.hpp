#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <thread>

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
	sf::Texture backgroundTexture;
	sf::Sprite background;
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

	// Pawn promotion
	sf::RectangleShape rectangle;
	Text promotionText;

	std::vector<Square*> promotionSquares;

	ChessPiece whitePromotionQueen;
	ChessPiece whitePromotionRook;
	ChessPiece whitePromotionBishop;
	ChessPiece whitePromotionKnight;

	ChessPiece blackPromotionQueen;
	ChessPiece blackPromotionRook;
	ChessPiece blackPromotionBishop;
	ChessPiece blackPromotionKnight;

	std::vector<ChessPiece*> whitePromotionPieces;
	std::vector<ChessPiece*> blackPromotionPieces;

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

	std::vector<Button*> buttons;

	// Player names
	Text whitePlayerText;
	Text blackPlayerText;
	// InformationBar
	Text infoText;
	std::vector<Text*> texts;
	Text clockText;

	// Clock
	sf::Clock clock;
	sf::Clock aiClock; // To debug ai calculationtimes

	sf::Texture backgroundTexture;
	sf::Sprite background;

public:
    GameScreen(sf::RenderWindow &w);

	// Draw related functions
	void loadContent(void);
	int update();
    void draw();
	void highlight(std::vector<int> v);
	void clearHighlights(std::vector<Square*> v);
	void clearButtonHighlights(std::vector<Button*> v);
	void initialize(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel);
	void tearDown(void);

	// Load game from file
	int loadGame();

	void changeTexture(int index, int newType);

	// Game updating and analysis
	void movePiece(std::pair<int, int> move);
	void changePlayerOnTurn();
	int changeTurn();
	bool containsPlayerPiece(int i, Player* p);
	bool belongsToPlayer(int i, Player* p);
	std::vector<std::pair<int, int> > getMoveList() const;
	void getAiMove();
	void showSaveGameDialog();

	// Pawn promotion
	void changePiece(int index);
	int choosePromotion(int index);
	void drawPromotion();

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

	// End game functions
	int endGame();
	void drawEndGame();
	int endGameOptions();

	Button endGameMainMenuButton;
	Button endGamePlayAgainButton;
	std::vector<Button*> endGameButtons;
	Text endGameText;

	// Utilities
	std::string getMoveStr(std::pair<int, int> m);
	void initPieces();
	void setPieceInitialPositions();
	void playAgainInit();
	void initPlayers(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel);
	bool isGameActive();
	void highlightCheckmate();

	//Threads
	std::thread aithread;
	bool thread_flag;
	bool thread_erased;

};

#endif
