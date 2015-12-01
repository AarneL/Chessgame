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
	// Set textures to pieces and push them to pieces vector in a right order
	whiteRook1.loadContent("media/img/rook_white.png");
	pieces.push_back(&whiteRook1);
	whiteKnight1.loadContent("media/img/knight_white.png");
	pieces.push_back(&whiteKnight1);
	whiteBishop1.loadContent("media/img/bishop_white.png");
	pieces.push_back(&whiteBishop1);
	whiteQueen.loadContent("media/img/queen_white.png");
	pieces.push_back(&whiteQueen);
	whiteKing.loadContent("media/img/king_white.png");
	pieces.push_back(&whiteKing);
	whiteBishop2.loadContent("media/img/bishop_white.png");
	pieces.push_back(&whiteBishop2);
	whiteKnight2.loadContent("media/img/knight_white.png");
	pieces.push_back(&whiteKnight2);
	whiteRook2.loadContent("media/img/rook_white.png");
	pieces.push_back(&whiteRook2);

	whitePawn1.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn1);
	whitePawn2.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn2);
	whitePawn3.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn3);
	whitePawn4.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn4);
	whitePawn5.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn5);
	whitePawn6.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn6);
	whitePawn7.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn7);
	whitePawn8.loadContent("media/img/pawn_white.png");
	pieces.push_back(&whitePawn8);

	// To keep the pieces list as long as gameboard squares, add null sprites
	// to the indexes where we have no pieces
	for (int i = 0; i < 32; i++) {
		pieces.push_back(NULL);
	}

	blackPawn1.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn1);
	blackPawn2.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn2);
	blackPawn3.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn3);
	blackPawn4.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn4);
	blackPawn5.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn5);
	blackPawn6.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn6);
	blackPawn7.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn7);
	blackPawn8.loadContent("media/img/pawn_black.png");
	pieces.push_back(&blackPawn8);

	blackRook1.loadContent("media/img/rook_black.png");
	pieces.push_back(&blackRook1);
	blackKnight1.loadContent("media/img/knight_black.png");
	pieces.push_back(&blackKnight1);
	blackBishop1.loadContent("media/img/bishop_black.png");
	pieces.push_back(&blackBishop1);
	blackQueen.loadContent("media/img/queen_black.png");
	pieces.push_back(&blackQueen);
	blackKing.loadContent("media/img/king_black.png");
	pieces.push_back(&blackKing);
	blackBishop2.loadContent("media/img/bishop_black.png");
	pieces.push_back(&blackBishop2);
	blackKnight2.loadContent("media/img/knight_black.png");
	pieces.push_back(&blackKnight2);
	blackRook2.loadContent("media/img/rook_black.png");
	pieces.push_back(&blackRook2);

	//Create base board starting from down left corner
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			Square* square = new Square();
			if ( (i+j)%2 == 0 ) {
				square->loadContent("media/img/square_light.png", "media/img/square_light_highlighted.png", sf::Vector2f((j*96 + BOARD_VERTICAL_OFFSET), (i*96 + BOARD_HORIZONTAL_OFFSET)));
			}
			else if ( (i+j)%2 == 1 ) {
				square->loadContent("media/img/square_dark.png", "media/img/square_dark_highlighted.png", sf::Vector2f((j*96 + BOARD_VERTICAL_OFFSET), (i*96 + BOARD_HORIZONTAL_OFFSET)));
			}
			gameBoard.push_back(square);
			int index = gameBoard.size() - 1;
			if (pieces[index] != NULL) {
				pieces[index]->setPosition(gameBoard[index]->getPosition());
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
	whitePlayerText.loadContent("media/img/Calibri.ttf", 30, sf::Vector2f(900, 10), true);
	elements.push_back(&whitePlayerText);
	blackPlayerText.loadContent("media/img/Calibri.ttf", 30, sf::Vector2f(900, 50), true);
	elements.push_back(&blackPlayerText);

	// Save button
	saveButton.loadContent("media/img/saveGameButton.png", "media/img/saveGameHighlightedButton.png", "", sf::Vector2f(900, 200), true);
	elements.push_back(&saveButton);
	// MainMenu button
	mainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(900, 400), true);
	elements.push_back(&mainMenuButton);
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
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
			if (event.type == sf::Event::MouseMoved) {
				if (saveButton.containsMousePos(mousePos)) {
					saveButton.setState(Highlighted);
				}
				else if (mainMenuButton.containsMousePos(mousePos)) {
					mainMenuButton.setState(Highlighted);
				}
				else
					clearButtonHighlights();
			}
			if (event.type == sf::Event::MouseButtonPressed) {

				if (saveButton.containsMousePos(mousePos)) {
					showSaveGameDialog();
				}
				else if (mainMenuButton.containsMousePos(mousePos)) {
					return 0;
				}
				else {
					for (int i = 0; i < 64; i++) {
						if (gameBoard[i]->containsMousePos(mousePos)) {
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
								activeSquare = -1;
								possibleMoves.clear();
								clearHighlights();
								return changeTurn();
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
		return changeTurn();
	}
	return 2;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear();
	for (auto square : gameBoard) {
		square->draw(window);
	}
	for (auto piece : pieces) {
		if (piece != NULL) {
			piece->draw(window);
		}
	}
	for (auto element : elements) {
		element->draw(window);
	}
	window.display();
}

void GameScreen::highlight(std::vector<int> v)
{
	for (auto i : v) {
		gameBoard[i]->setState(Highlighted);
	}
}

void GameScreen::clearHighlights()
{
	for (auto i : gameBoard) {
		i->setState(Normal);
	}
}

void GameScreen::clearButtonHighlights()
{
	saveButton.setState(Normal);
	mainMenuButton.setState(Normal);

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

void GameScreen::tearDown(void)
{
	free(white);
	free(black);
	board = Board();
	pieces.clear();
	gameBoard.clear();
	//Create base board starting from down left corner
	Square square;
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			square = Square();
			if ((i + j) % 2 == 0) {
				square.loadContent("media/img/square_light.png", "media/img/square_light_highlighted.png", sf::Vector2f((j*96 + BOARD_VERTICAL_OFFSET), (i*96 + BOARD_HORIZONTAL_OFFSET)));
			}
			else if ((i + j) % 2 == 1) {
				square.loadContent("media/img/square_dark.png", "media/img/square_dark_highlighted.png", sf::Vector2f((j*96 + BOARD_VERTICAL_OFFSET), (i*96 + BOARD_HORIZONTAL_OFFSET)));
			}
			gameBoard.push_back(&square);
			int index = gameBoard.size() - 1;
			if (pieces[index] != NULL) {
				pieces[index]->setPosition(gameBoard[index]->getPosition());
			}
		}
	}

}

void GameScreen::movePiece(std::pair<int,int> move)
{
	// Move in GUI
	pieces[move.second] = pieces[move.first];
	pieces[move.first] = NULL;
	pieces[move.second]->setPosition(gameBoard[move.second]->getPosition());

	// Move in board
	board.movePiece(move.first, move.second);
	int index = board.updateState(move.second, 0); // Returns index if update needed
	if (index != -1) {
		// If stateword 0-63-> means pawn has reached enemy backline. Pawn is promotee
		changePiece(index);
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
			pieces[move.first + 1]->setPosition(gameBoard[move.first + 1]->getPosition());
		}

		else // castling to left
		{
			pieces[move.first - 1] = pieces[move.first - 4]; //move the rook
			pieces[move.first - 4] = NULL;
			pieces[move.first - 1]->setPosition(gameBoard[move.first - 1]->getPosition());
		}
	}
}

int GameScreen::changeTurn()
{
	//test if it's checkmate
	if(board.getState() & 0x01)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		std::cout << "Checkmate by " << playerOnTurn->getName() << std::endl;
		tearDown();
		return 0;
	}
	else if (board.getState() & 0x02)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		std::cout << "Stalemate" << std::endl;
		tearDown();
		return 0;
	}

	// If its black turn
	if (playerOnTurn == black) {
		playerOnTurn = white;
	}
	else if(playerOnTurn == white){
		playerOnTurn = black;
	}
	moveSound.play();
	return 2;
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
		board.changePiece(index, B_QUEEN);
	}
	else
	{
		board.changePiece(index, W_QUEEN);
	}
}

void GameScreen::showSaveGameDialog() {
	// This should show file dialog for saving file
	// Save the game
	const char* savePath = tinyfd_saveFileDialog("Save game", "", 0, NULL, "text files");
	board.saveGame(white, black, savePath);
}
