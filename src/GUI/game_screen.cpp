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
#include <string>
#include <vector>


GameScreen::GameScreen(sf::RenderWindow &w) : window(w)
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
	texts.push_back(&whitePlayerText);
	blackPlayerText.loadContent("media/img/Calibri.ttf", 30, sf::Vector2f(900, 50), true);
	texts.push_back(&blackPlayerText);
	// Information text
	infoText.loadContent("media/img/Calibri.ttf", 30, sf::Vector2f(900, 100), true);
	infoText.setColor(sf::Color::Yellow);
	texts.push_back(&infoText);

	// Buttons
	// Save button
	saveButton.loadContent("media/img/saveGameButton.png", "media/img/saveGameHighlightedButton.png", "", sf::Vector2f(900, 400), true);
	buttons.push_back(&saveButton);
	// MainMenu button
	mainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(900, 600), true);
	buttons.push_back(&mainMenuButton);

	// Pawn promotion
	rectangle.setSize(sf::Vector2f(530, 250));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(230, 300);

	promotionText.loadContent("media/img/Calibri.ttf", 40, sf::Vector2f(260, 320), true);
	promotionText.setString("Choose a piece:");

	for (int i = 0; i < 4; i++) {
		Square* square = new Square();
		square->loadContent("media/img/square_light.png", "media/img/square_light_highlighted.png", sf::Vector2f((260 + i*96 + i*25), 420));
		promotionSquares.push_back(square);
	}

	whitePromotionQueen.loadContent("media/img/queen_white.png");
	whitePromotionQueen.setPosition(promotionSquares[0]->getPosition());
	whitePromotionPieces.push_back(&whitePromotionQueen);
	whitePromotionRook.loadContent("media/img/rook_white.png");
	whitePromotionRook.setPosition(promotionSquares[1]->getPosition());
	whitePromotionPieces.push_back(&whitePromotionRook);
	whitePromotionBishop.loadContent("media/img/bishop_white.png");
	whitePromotionBishop.setPosition(promotionSquares[2]->getPosition());
	whitePromotionPieces.push_back(&whitePromotionBishop);
	whitePromotionKnight.loadContent("media/img/knight_white.png");
	whitePromotionKnight.setPosition(promotionSquares[3]->getPosition());
	whitePromotionPieces.push_back(&whitePromotionKnight);

	blackPromotionQueen.loadContent("media/img/queen_black.png");
	blackPromotionQueen.setPosition(promotionSquares[0]->getPosition());
	blackPromotionPieces.push_back(&blackPromotionQueen);
	blackPromotionRook.loadContent("media/img/rook_black.png");
	blackPromotionRook.setPosition(promotionSquares[1]->getPosition());
	blackPromotionPieces.push_back(&blackPromotionRook);
	blackPromotionBishop.loadContent("media/img/bishop_black.png");
	blackPromotionBishop.setPosition(promotionSquares[2]->getPosition());
	blackPromotionPieces.push_back(&blackPromotionBishop);
	blackPromotionKnight.loadContent("media/img/knight_black.png");
	blackPromotionKnight.setPosition(promotionSquares[3]->getPosition());
	blackPromotionPieces.push_back(&blackPromotionKnight);

	// Game ending
	endGameMainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(250, 450), true);
	endGamePlayAgainButton.loadContent("media/img/playAgainButton.png", "media/img/playAgainHighlightedButton.png" , "", sf::Vector2f(500, 450), true);
	endGameButtons.push_back(&endGameMainMenuButton);
	endGameButtons.push_back(&endGamePlayAgainButton);
	endGameText.loadContent("media/img/Calibri.ttf", 40, sf::Vector2f(260, 320), true);
}

int GameScreen::update()
{
	// Human turn
	if (playerOnTurn->getType() == std::string("Human")) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				return 0;
			}
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
			if (event.type == sf::Event::MouseMoved) {
				if (saveButton.containsMousePos(mousePos)) {
					saveButton.setState(Highlighted);
				}
				else if (mainMenuButton.containsMousePos(mousePos)) {
					mainMenuButton.setState(Highlighted);
				}
				else
					clearButtonHighlights(buttons);
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
								clearHighlights(gameBoard);
								return changeTurn();
							}
							else {
								activeSquare = -1;
								possibleMoves.clear();
								clearHighlights(gameBoard);
							}
						}
					}
				}
			}
			else if (event.type == sf::Event::Closed) {
			   window.close();
			   return -1;
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

void GameScreen::draw()
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
	for (auto text : texts) {
		text->draw(window);
	}
	for (auto button : buttons) {
		button->draw(window);
	}
	window.display();
}

void GameScreen::highlight(std::vector<int> v)
{
	for (auto i : v) {
		gameBoard[i]->setState(Highlighted);
	}
}

void GameScreen::clearHighlights(std::vector<Square*> v)
{
	for (auto i : v) {
		i->setState(Normal);
	}
}

void GameScreen::clearButtonHighlights(std::vector<Button*> v)
{
	for (auto i : v) {
		i->setState(Normal);
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

	// To format info text
	infoText.setString("Game started!\n" +  playerOnTurn->getName() + "'s turn.");
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
	std::string s;
	//test if it's checkmate
	if(board.getState() & 0x01)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		infoText.setString("Checkmate by " + playerOnTurn->getName() + "!");
		endGameText.setString("Game ended!\n" + playerOnTurn->getName() + " wins!");
		return endGame();
	}
	else if (board.getState() & 0x02)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		std::cout << "Stalemate" << std::endl;
		endGameText.setString("Game ended!");
		return endGame();
	}

	// If its black turn
	if (playerOnTurn == black) {
		// Format infoText
		s = playerOnTurn->getName() + " moved " + getMoveStr(getMoveList().back()) + "\n";
		playerOnTurn = white;
		s += playerOnTurn->getName() + "'s turn.";
		infoText.setString(s);
		s.clear();
	}
	else if(playerOnTurn == white){
		s = playerOnTurn->getName() + " moved " + getMoveStr(getMoveList().back()) + "\n";
		playerOnTurn = black;
		s += playerOnTurn->getName() + "'s turn.";
		infoText.setString(s);
		s.clear();
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
	std::cout << "changePiece" << std::endl;
	int newPiece = -1;
	if (playerOnTurn->getType() == std::string("Human")) {
		while (newPiece == -1) {
			newPiece = choosePromotion(index);
			if (newPiece == -1) {
				drawPromotion();
			}
		}
	}
	else {
		if (playerOnTurn == white) {
			pieces[index]->changeTexture(whitePromotionQueen.getTexture());
			newPiece = W_QUEEN;
		} else {
			pieces[index]->changeTexture(blackPromotionQueen.getTexture());
			newPiece = B_QUEEN;
		}
	}
	board.changePiece(index, newPiece);
}

int GameScreen::choosePromotion(int index)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (event.type == sf::Event::MouseMoved) {
			for (auto square : promotionSquares) {
				if (square->containsMousePos(mousePos)) {
					square->setState(Highlighted);
					break;
				} else {
					clearHighlights(promotionSquares);
				}
			}
		} else if (event.type == sf::Event::MouseButtonPressed) {
			if (playerOnTurn == white) {
				if (whitePromotionQueen.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(whitePromotionQueen.getTexture());
					return W_QUEEN;
				} else if (whitePromotionKnight.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(whitePromotionKnight.getTexture());
					return W_KNIGHT;
				} else if (whitePromotionBishop.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(whitePromotionBishop.getTexture());
					return W_BISHOP;
				} else if (whitePromotionRook.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(whitePromotionRook.getTexture());
					return W_ROOK;
				}
			} else {
				if (blackPromotionQueen.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(blackPromotionQueen.getTexture());
					return B_QUEEN;
				} else if (blackPromotionKnight.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(blackPromotionKnight.getTexture());
					return B_KNIGHT;
				} else if (blackPromotionBishop.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(blackPromotionBishop.getTexture());
					return B_BISHOP;
				} else if (blackPromotionRook.containsMousePos(mousePos)) {
					pieces[index]->changeTexture(blackPromotionRook.getTexture());
					return B_ROOK;
				}
			}
		} else if (event.type == sf::Event::Closed) {
			window.close();
			return -1;
		}
	}
	return -1;
}

void GameScreen::drawPromotion()
{
	window.draw(rectangle);
	promotionText.draw(window);
	for (auto square : promotionSquares) {
		square->draw(window);
	}
	if (playerOnTurn == white) {
		for (auto piece : whitePromotionPieces) {
			piece->draw(window);
		}
	} else {
		for (auto piece : blackPromotionPieces) {
			piece->draw(window);
		}
	}
	window.display();
}

int GameScreen::endGame()
{
	// This is called always when game ends
	int status = -1;
	while (status == -1) {
		status = endGameOptions();
		drawEndGame();
	}
	// This needs to empty the game and if necessary start new game

	return status;
}

void GameScreen::drawEndGame()
{
	window.draw(rectangle);
	for (auto button : endGameButtons) {
		button->draw(window);
	}
	endGameText.draw(window);
	window.display();
}

int GameScreen::endGameOptions()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (event.type == sf::Event::MouseMoved) {
			bool highlight = false;
			for (auto button : endGameButtons) {
				if (button->containsMousePos(mousePos)) {
					button->setState(Highlighted);
					highlight = true;
				}
			}
			if (!highlight) {
				clearButtonHighlights(endGameButtons);
			}

		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (endGameMainMenuButton.containsMousePos(mousePos)) {
				tearDown();
				return 0;
			}
			else if (endGamePlayAgainButton.containsMousePos(mousePos)) {
				tearDown();
				return 0;
			}
		}
		else if (event.type == sf::Event::Closed) {
			window.close();
			return -1;
		}
	}
	return -1;
}

std::string GameScreen::getMoveStr(std::pair<int,int> m)
{
	std::vector<std::string> letters;
	letters.push_back("a");
	letters.push_back("b");
	letters.push_back("c");
	letters.push_back("d");
	letters.push_back("e");
	letters.push_back("f");
	letters.push_back("g");
	letters.push_back("h");

	std::string ret = letters[m.first % 8] + std::to_string((m.first / 8) + 1) + "->" + letters[m.second % 8] + std::to_string((m.second / 8) + 1);
	return ret;
}

void GameScreen::showSaveGameDialog() {
	// This should show file dialog for saving file
	// Save the game
	const char* savePath = tinyfd_saveFileDialog("Save game", "", 0, NULL, "text files");
	board.saveGame(white, black, savePath);
}