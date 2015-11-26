#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"
#include "../headers/ai_algorithm.hpp"
#include "../headers/tinyfiledialogs.h"


// #include "../headers/board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <thread>


GameScreen::GameScreen(void)
{

	// Graphical design constants
	BOARD_HORIZONTAL_OFFSET = 0;
	BOARD_VERTICAL_OFFSET = 100;

}

void GameScreen::loadContent(void)
{
	// Load textures
	whitePawnTexture.loadFromFile("media/img/pawn_white.png");
	whiteRookTexture.loadFromFile("media/img/rook_white.png");
	whiteBishopTexture.loadFromFile("media/img/bishop_white.png");
	whiteKnightTexture.loadFromFile("media/img/knight_white.png");
	whiteQueenTexture.loadFromFile("media/img/queen_white.png");
	whiteKingTexture.loadFromFile("media/img/king_white.png");

	blackPawnTexture.loadFromFile("media/img/pawn_black.png");
	blackRookTexture.loadFromFile("media/img/rook_black.png");
	blackBishopTexture.loadFromFile("media/img/bishop_black.png");
	blackKnightTexture.loadFromFile("media/img/knight_black.png");
	blackQueenTexture.loadFromFile("media/img/queen_black.png");
	blackKingTexture.loadFromFile("media/img/king_black.png");

	// Set textures to pieces and push them to pieces vector in a right order
	whiteRook1.setTexture(whiteRookTexture);
	pieces.push_back(&whiteRook1);
	whiteKnight1.setTexture(whiteKnightTexture);
	pieces.push_back(&whiteKnight1);
	whiteBishop1.setTexture(whiteBishopTexture);
	pieces.push_back(&whiteBishop1);
	whiteQueen.setTexture(whiteQueenTexture);
	pieces.push_back(&whiteQueen);
	whiteKing.setTexture(whiteKingTexture);
	pieces.push_back(&whiteKing);
	whiteBishop2.setTexture(whiteBishopTexture);
	pieces.push_back(&whiteBishop2);
	whiteKnight2.setTexture(whiteKnightTexture);
	pieces.push_back(&whiteKnight2);
	whiteRook2.setTexture(whiteRookTexture);
	pieces.push_back(&whiteRook2);

	whitePawn1.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn1);
	whitePawn2.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn2);
	whitePawn3.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn3);
	whitePawn4.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn4);
	whitePawn5.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn5);
	whitePawn6.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn6);
	whitePawn7.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn7);
	whitePawn8.setTexture(whitePawnTexture);
	pieces.push_back(&whitePawn8);

	// To keep the pieces list as long as gameboard squares, add null sprites
	// to the indexes where we have no pieces
	for (int i = 0; i < 32; i++) {
		pieces.push_back(NULL);
	}

	blackPawn1.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn1);
	blackPawn2.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn2);
	blackPawn3.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn3);
	blackPawn4.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn4);
	blackPawn5.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn5);
	blackPawn6.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn6);
	blackPawn7.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn7);
	blackPawn8.setTexture(blackPawnTexture);
	pieces.push_back(&blackPawn8);

	blackRook1.setTexture(blackRookTexture);
	pieces.push_back(&blackRook1);
	blackKnight1.setTexture(blackKnightTexture);
	pieces.push_back(&blackKnight1);
	blackBishop1.setTexture(blackBishopTexture);
	pieces.push_back(&blackBishop1);
	blackQueen.setTexture(blackQueenTexture);
	pieces.push_back(&blackQueen);
	blackKing.setTexture(blackKingTexture);
	pieces.push_back(&blackKing);
	blackBishop2.setTexture(blackBishopTexture);
	pieces.push_back(&blackBishop2);
	blackKnight2.setTexture(blackKnightTexture);
	pieces.push_back(&blackKnight2);
	blackRook2.setTexture(blackRookTexture);
	pieces.push_back(&blackRook2);


	// Texture for board square
	squareTexture.loadFromFile("media/img/square_white.png");
	// Square colors
	color_square_dark = sf::Color(210, 105,30);	//"chocolate"
	color_square_light = sf::Color(138,54,15);	//"burntsienna"
	// Square highlight colors
	color_highlight_square_dark = sf::Color(0,200,0);
	color_highlight_square_light = sf::Color(0,255,255);

	//Create base board starting from down left corner
	sf::Sprite square;
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			square = sf::Sprite();
			square.setPosition((j*96 + BOARD_VERTICAL_OFFSET), (i*96 + BOARD_HORIZONTAL_OFFSET));
			square.setTexture(squareTexture);
			if ( (i+j)%2 == 0 ) {
				square.setColor(color_square_dark);
			}
			else if ( (i+j)%2 == 1 ) {
				square.setColor(color_square_light);
			}
			gameBoard.push_back(square);
			int index = gameBoard.size() - 1;
			if (pieces[index] != NULL) {
				pieces[index]->setPosition(gameBoard[index].getPosition());
			}
		}
	}

	// Load game sounds
	if (!moveSoundBuffer.loadFromFile("media/sound/movePiece.wav")) {
		std::cout << "Could not load sound file." << std::endl;
	}
	else {
		moveSound.setBuffer(moveSoundBuffer);
	}

	// Player names
	if (!font.loadFromFile("media/img/Calibri.ttf"))
		std::cout << "File not found!" << std::endl;

	whitePlayerText.setFont(font);
	whitePlayerText.setCharacterSize(30);
	whitePlayerText.setStyle(sf::Text::Bold);
	whitePlayerText.setPosition(sf::Vector2f(900, 10));

	blackPlayerText.setFont(font);
	blackPlayerText.setCharacterSize(30);
	blackPlayerText.setStyle(sf::Text::Bold);
	blackPlayerText.setPosition(sf::Vector2f(900, 50));

	// Save button and file dialog
	saveGameButtonTexture.loadFromFile("media/img/saveGameButton.png");
	saveGameHighlightedButtonTexture.loadFromFile("media/img/saveGameHighlightedButton.png");
	saveButton.setTexture(saveGameButtonTexture);
	saveButton.setPosition(sf::Vector2f(900, 200));
}

int GameScreen::update(sf::RenderWindow &window)
{
	if (playerOnTurn->getType() == std::string("Human")) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				return 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				free(white);
				free(black);
				return -1;
			}

			// Human turn
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
				if (saveButton.getGlobalBounds().contains(mousePos)) {
					std::cout << "save clicked" << std::endl;
					showSaveGameDialog();
				} else {
					for (int i = 0; i < 64; i++) {
						if (gameBoard[i].getGlobalBounds().contains(mousePos)) {
							// If no piece active yet
							if (activeSquare == -1) {
								if (containsPlayerPiece(i, playerOnTurn))
								{
									possibleMoves = board.possibleMoves(i);
									highlight(possibleMoves);
									activeSquare = i;
								}
							}
							// If possible moves already found
							else if (activeSquare != -1 && (std::find(possibleMoves.begin(), possibleMoves.end(), i) != possibleMoves.end()) && i != activeSquare) {
								movePiece(std::make_pair(activeSquare, i));

								std::cout << playerOnTurn->getName() << " made move." << std::endl;
								changeTurn();
								activeSquare = -1;
								possibleMoves.clear();
								clearHighlights();
							}

							else {
								activeSquare = -1;
								possibleMoves.clear();
								clearHighlights();
							}
						}
					}
				}
			}
		}
	}
	// AI Turn
	else if (playerOnTurn->getType() == std::string("AI")) {

		std::pair<int, int> aimove = getAiMove();
		if(aimove.first==aimove.second) {
			std::cout << "AI made illegal move!" << std::endl;
		}
		movePiece(aimove);
		std::cout << playerOnTurn->getName() << " made move. (Level: " << playerOnTurn->getLevel() << ")" << std::endl;
		changeTurn();
	}
	return 2;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear();
	for (int i = 0; i < 64; i++) {
		window.draw(gameBoard[i]);
		if (!(pieces[i] == NULL)) {
			window.draw(*pieces[i]);
		}
	}
	window.draw(whitePlayerText);
	window.draw(blackPlayerText);
	window.draw(saveButton);
	window.display();
}

void GameScreen::highlight(std::vector<int> v)
{
	sf::Color color_highlight_square_dark(0, 200, 0);
	sf::Color color_highlight_square_light(0, 255, 255);
	for (auto i : v) {
		if (((i % 8)+(i / 8)) % 2 == 0) {
			gameBoard[i].setColor(color_highlight_square_dark);
		}
		else {
			gameBoard[i].setColor(color_highlight_square_light);
		}
	}
}

void GameScreen::clearHighlights()
{
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if ( (i+j)%2 == 0 ) {
				gameBoard[i*8+j].setColor(color_square_light);
			}
			else if ( (i+j)%2 == 1 ) {
				gameBoard[i*8+j].setColor(color_square_dark);
			}
		}
	}
}

void GameScreen::initialize(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel)
{
	// Game starts with white players turn
	board = Board();
	activeSquare = -1;

	// White player type
	if (whiteName == "Computer") {
		white = new AI(whiteName, ColorType::White, whiteLevel);
	}
	else {
		white = new Human(whiteName, ColorType::White);
	}

	// Black player type
	if (blackName == "Computer") {
		black = new AI(blackName, ColorType::Black, blackLevel);
	}
	else {
		black = new Human(blackName, ColorType::Black);
	}
	playerOnTurn = white;
	whitePlayerText.setString("White: " + white->getName());
	blackPlayerText.setString("Black: " + black->getName());
}

void GameScreen::movePiece(std::pair<int,int> move)
{
	// Move in GUI
	pieces[move.second] = pieces[move.first];
	pieces[move.first] = NULL;
	pieces[move.second]->setPosition(gameBoard[move.second].getPosition());

	// Move in board
	board.movePiece(move.first, move.second);
	int index = board.updateState(move.second); // Returns index if update needed
	if (index != -1) {
		board.changePiece(index);
	}
	if((board.getState() >> 6) == 0x01) //01000000 passant made by white
	{
		pieces[move.second - 8] = NULL;
	}

	if((board.getState() >> 6) == 0x02) //10000000 passant made by black
	{
		pieces[move.second + 8] = NULL;
	}

	if((board.getState() >> 6) ==  0x03) //11000000 castling
	{
		if((move.second%8)>4) //castling to right
		{
			pieces[move.first + 1] = pieces[move.first + 3]; //move the rook
			pieces[move.first + 3] = NULL;
			pieces[move.first + 1]->setPosition(gameBoard[move.first + 1].getPosition());
		}

		else // castling to left
		{
			pieces[move.first - 1] = pieces[move.first - 4]; //move the rook
			pieces[move.first - 4] = NULL;
			pieces[move.first - 1]->setPosition(gameBoard[move.first - 1].getPosition());
		}
	}
}

void GameScreen::changeTurn()
{
	//test if it's checkmate
	if(board.getState() & 0x01)
	{
		std::cout << "Checkmate by " << playerOnTurn->getName() << std::endl;
	}
	else if (board.getState() & 0x02)
	{
		std::cout << "Stalemate" << std::endl;
	}

	// If its black turn
	if (playerOnTurn == black) {
		playerOnTurn = white;
	}
	else if(playerOnTurn == white){
		playerOnTurn = black;
	}
	moveSound.play();
}

bool GameScreen::containsPlayerPiece(int i, Player* p)
{
	if (belongsToPlayer(board.getBoard()[i], p))
		return true;
	return false;
}

bool GameScreen::belongsToPlayer(int i, Player* p)
{
	if ((p->getColor() == ColorType::White) && (i % 2 == 1) && (i != 0))
		return true;
	else if ((p->getColor() == ColorType::Black) && (i % 2 == 0) && (i != 0))
		return true;
	return false;
}

std::vector<std::pair<int, int> > GameScreen::getMoveList() const
{
	return board.getMoveList();
}

std::pair<int,int> GameScreen::getAiMove(void)
{
	return AiAlgorithm::algorithm(board, playerOnTurn->getLevel(), (playerOnTurn->getColor() == ColorType::White));
}

void GameScreen::changePiece(int index)
{
	if (board.getBoard()[index] % 2 == 0)
	{
		board.changePiece(index, W_QUEEN);
	}
	else
	{
		board.changePiece(index, B_QUEEN);
	}
}

void GameScreen::showSaveGameDialog() {
	// This should show file dialog for saving file
	// Save the game
	tinyfd_saveFileDialog("Save game", "", 0, NULL, "text files");
	board.saveGame(white, black);
}
