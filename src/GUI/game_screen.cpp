#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"
#include "../headers/ai_algorithm.hpp"
#include "../headers/tinyfiledialogs.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>

std::mutex ai_algorithm_mutex;
static volatile std::pair<int, int> aimove = std::make_pair(0, 0);

GameScreen::GameScreen(sf::RenderWindow &w) : window(w)
{
	// Graphical design constants
	BOARD_HORIZONTAL_OFFSET = 50;
	BOARD_VERTICAL_OFFSET = 50;

	thread_flag = false;
	thread_erased = true;
}

void GameScreen::loadContent(void)
{
	initPieces(); // Load piece contents and put piece pointers to pieces vector

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
		}
	}

	// Pawn promotion window
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

	setPieceInitialPositions(); // Put piece sprites to their right initial locations

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
	saveButton.loadContent("media/img/saveGameButton.png", "media/img/saveGameHighlightedButton.png", "", sf::Vector2f(880, 750), true);
	buttons.push_back(&saveButton);
	// MainMenu button
	mainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(1110, 750), true);
	buttons.push_back(&mainMenuButton);

	// Clocktext
	clockText.setColor(sf::Color::Green);
	texts.push_back(&clockText);
	clockText.loadContent("media/img/Calibri.ttf", 60, sf::Vector2f(900, 650), true);

	// Game ending
	endGameMainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(250, 450), true);
	endGamePlayAgainButton.loadContent("media/img/playAgainButton.png", "media/img/playAgainHighlightedButton.png" , "", sf::Vector2f(500, 450), true);
	endGameButtons.push_back(&endGameMainMenuButton);
	endGameButtons.push_back(&endGamePlayAgainButton);
	endGameText.loadContent("media/img/Calibri.ttf", 40, sf::Vector2f(260, 320), true);
	white = NULL;
	black = NULL;

	// Background
	backgroundTexture.loadFromFile("media/img/game_screen_background.jpg");
	background.setTexture(backgroundTexture);
}

int GameScreen::update()
{
	int currTime = (int)clock.getElapsedTime().asSeconds();
	// Update clockstring
	clockText.setString(std::to_string(currTime / 60) + ":" + std::to_string(currTime % 60));

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
	/* Here thread_flag tells if we need a new move. if thread_flag IS active it means <> otherwise <>
	 * thread_erased tells if last thread we launched has finished so even if we need a new move we can't ask for one before that TODO:Why we cant?
	 */
		if (!thread_flag && !(board.getState() & 0x3)) { // Make sure that no moves is asked after checkmate or stalemate
			if(thread_erased) // See if last aithread has finished
			{
				// Start new thread and calculate time elapsed for algorithm
				aiClock.restart();
				aithread = std::thread(&GameScreen::getAiMove, this); // The actual calculation starts here
				thread_flag = true;
			}
		}

		sf::Event event;

		while (window.pollEvent(event)) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				thread_flag = false; // If user goes to mainmenu while calculating -> abandon calculation
				aithread.detach();
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
			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (saveButton.containsMousePos(mousePos))
				{
					showSaveGameDialog();
				}
				else if (mainMenuButton.containsMousePos(mousePos)) {
					if(!thread_erased)
					{
						if(thread_flag == true)
						{
							thread_flag = false; // If user goes to mainmenu while calculating -> abandon calculation
							aithread.detach();
						}
					}
					return 0;
				}
			}
		}
		if(aimove.first != aimove.second && thread_flag == true) // Means that getaimove thread is ALMOST ready
		{
			// TODO: Comment this block
			aithread.join();
			std::pair<int, int> test;
			ai_algorithm_mutex.lock();
			{
				test.first = aimove.first;
				test.second = aimove.second;
			}
			ai_algorithm_mutex.unlock();

			movePiece(test);
			std::cout << "AI(lvl:" << playerOnTurn->getLevel() << ") calculated next turn in " << aiClock.getElapsedTime().asSeconds() << " seconds." << std::endl;
			ai_algorithm_mutex.lock();
			{
				aimove.first = 0;
				aimove.second = 0;
			}
			ai_algorithm_mutex.unlock();
			std::cout << playerOnTurn->getName() << " made move. (Level: " << playerOnTurn->getLevel() << ")" << std::endl;
			thread_flag = false;
			return changeTurn();
		}
	}
	return 2;
}

void GameScreen::draw()
{
	window.clear();
	window.draw(background);
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
	tearDown();

	thread_flag = false;

	// Game starts with white players turn
	board = Board();
	activeSquare = -1;
	initPlayers(whiteName, whiteLevel, blackName, blackLevel);

	playerOnTurn = white;
	whitePlayerText.setString("White: " + white->getName());
	blackPlayerText.setString("Black: " + black->getName());

	// To format info text
	infoText.setString("Game started!\n" +  playerOnTurn->getName() + "'s turn.");
	clock.restart();
}

void GameScreen::tearDown(void)
{
	//Create base board starting from down left corner
	if (white != NULL) {
		delete white;
		white = NULL;
	}
	if (black != NULL) {
		delete black;
		black = NULL;
	}
	pieces.clear();
	initPieces();
	setPieceInitialPositions();
	clearHighlights(gameBoard);
}

int GameScreen::loadGame()
{
	// Open file dialog
	const char* file_loc = tinyfd_openFileDialog("Open load file", "", 0, NULL, "text files", 0);
	if (!file_loc) {
		std::cout << "Error loading file" << std::endl;
		return 0;
	}
	std::ifstream ifs(file_loc, std::ifstream::in);
	if (!ifs) {
		std::cout << "File not found" << std::endl;
	}

	// Collect information about players
	std::string white;
	std::getline(ifs, white);
	std::string black;
	std::getline(ifs, black);

	std::string whiteName = white.substr(0, white.find('-'));
	std::string blackName = black.substr(0, black.find('-'));
	int whiteLevel = atoi((white.substr(white.find('-')+1)).c_str());
	int blackLevel = atoi((black.substr(black.find('-')+1)).c_str());

	std::cout << whiteName << std::endl;
	std::cout << blackName << std::endl;

	// Initialize the game screen with the players from file
	initialize(whiteName, whiteLevel, blackName, blackLevel);

	for (std::string line; std::getline(ifs, line); ) {
		if (line == "BOARD") {
			break;
		}
		int origin = atoi((line.substr(0, line.find('-'))).c_str());
		int destination = atoi((line.substr(line.find('-')+1)).c_str());
		std::cout << "move: " << origin << "->" << destination << std::endl;
		// Move in board
		board.movePiece(origin, destination);
		std::cout << "piece moved in board" << std::endl;
		// Move in GUI
		pieces[destination] = pieces[origin];
		pieces[origin] = NULL;
		pieces[destination]->setPosition(gameBoard[destination]->getPosition());
		std::cout << "piece moved in GUI" << std::endl;
		// Change turn
		changePlayerOnTurn();
	}

	int piece;
	for (int i = 0; i < 64; i++) {
		ifs >> piece;
		std::cout << "piece is " << piece << std::endl;
		if (pieces[i] != NULL) {
			std::cout << "pieces[i]->getType is " << pieces[i]->getType() << std::endl;
			if (pieces[i]->getType() != piece) {
				changeTexture(i, piece);
				board.changePiece(i, piece);
			}
		}
	}

	std::string state;
	ifs >> state;
	unsigned char* stateChar = (unsigned char*)state.c_str();
	std::cout << "State: " << stateChar << std::endl;
	board.setState(*stateChar);

	// Format infoText
	std::string s;
	s = "Game continues!\n";
	s += playerOnTurn->getName() + "'s turn.";
	infoText.setString(s);
	s.clear();

	ifs.close();
	return 2;
}

void GameScreen::changeTexture(int index, int newType)
{
	std::cout << "came to change texture" << std::endl;
	if (newType == W_QUEEN) {
		pieces[index]->changeTexture(whiteQueen.getTexture());
	} else if (newType == W_ROOK) {
		pieces[index]->changeTexture(whiteRook1.getTexture());
	} else if (newType == W_KNIGHT) {
		pieces[index]->changeTexture(whiteKnight1.getTexture());
	} else if (newType == W_BISHOP) {
		pieces[index]->changeTexture(whiteBishop1.getTexture());
	} else if (newType == B_QUEEN) {
		pieces[index]->changeTexture(blackQueen.getTexture());
	} else if (newType == B_ROOK) {
		pieces[index]->changeTexture(blackRook1.getTexture());
	} else if (newType == B_KNIGHT) {
		pieces[index]->changeTexture(blackKnight1.getTexture());
	} else if (newType == B_BISHOP) {
		pieces[index]->changeTexture(blackBishop1.getTexture());
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
		board.updateState(move.second, 0);
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

void GameScreen::changePlayerOnTurn()
{
	if (playerOnTurn == black) {
		playerOnTurn = white;
	} else {
		playerOnTurn = black;
	}
	std::cout << "Turn changed" << std::endl;
}

int GameScreen::changeTurn()
{
	std::string nameOfOther = playerOnTurn->getName();

	// Change playerOnTurn
	changePlayerOnTurn();

	// Format infoText
	infoText.setString(nameOfOther + " moved " + getMoveStr(getMoveList().back()) + "\n" + playerOnTurn->getName() + "'s turn.");

	moveSound.play(); // SWWIP
	if(board.getState() & 0x01)
	{
		infoText.setString("Checkmate by " + nameOfOther + "!");
		//checkmateSound.play()
		highlightCheckmate();
		// Sleep
		draw();
		sf::sleep(sf::seconds(3));
		endGameText.setString("Game ended!\n" + nameOfOther + " wins!");
		return endGame(); // End game info box
	}
	else if (board.getState() & 0x02)
	{
		// TODO: Needs to print some box that announces winner and when ok pressed goes to main menu
		std::cout << "Stalemate" << std::endl;
		infoText.setString("Stalemate!");
		//stalemateSound.play()
		highlightCheckmate();
		// Sleep
		draw();
		sf::sleep(sf::seconds(3));
		endGameText.setString("Game ended to stalemate!\nDraw!");
		return endGame(); // End game info box
	}
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

void GameScreen::getAiMove(void)
{
	thread_erased = false;
	std::pair<int, int> test2 = AiAlgorithm::algorithm(board, playerOnTurn->getLevel(), (playerOnTurn->getColor() == ColorType::White));
	// will fail because the thread will be stopped when the first is written
	ai_algorithm_mutex.lock();
	{
		aimove.first = test2.first;
		aimove.second = test2.second;
	}
	ai_algorithm_mutex.unlock();

	std::cout << "getAiMove ended" << std::endl;
	thread_erased = true;
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
	window.clear();
	window.draw(background);
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
				return 0;
			}
			else if (endGamePlayAgainButton.containsMousePos(mousePos)) {
				playAgainInit();
				return 2;
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

void GameScreen::initPieces()
{
	// Set textures to pieces and push them to pieces vector in a right order
	whiteRook1.loadContent("media/img/rook_white.png", W_ROOK);
	whiteKnight1.loadContent("media/img/knight_white.png", W_KNIGHT);
	whiteBishop1.loadContent("media/img/bishop_white.png", W_BISHOP);
	whiteQueen.loadContent("media/img/queen_white.png", W_QUEEN);
	whiteKing.loadContent("media/img/king_white.png", W_KING);
	whiteBishop2.loadContent("media/img/bishop_white.png", W_BISHOP);
	whiteKnight2.loadContent("media/img/knight_white.png", W_KNIGHT);
	whiteRook2.loadContent("media/img/rook_white.png", W_ROOK);
	whitePawn1.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn2.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn3.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn4.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn5.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn6.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn7.loadContent("media/img/pawn_white.png", W_PAWN);
	whitePawn8.loadContent("media/img/pawn_white.png", W_PAWN);

	blackPawn1.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn2.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn3.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn4.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn5.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn6.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn7.loadContent("media/img/pawn_black.png", B_PAWN);
	blackPawn8.loadContent("media/img/pawn_black.png", B_PAWN);
	blackRook1.loadContent("media/img/rook_black.png", B_ROOK);
	blackKnight1.loadContent("media/img/knight_black.png", B_KNIGHT);
	blackBishop1.loadContent("media/img/bishop_black.png", B_BISHOP);
	blackQueen.loadContent("media/img/queen_black.png", B_QUEEN);
	blackKing.loadContent("media/img/king_black.png", B_KING);
	blackBishop2.loadContent("media/img/bishop_black.png", B_BISHOP);
	blackKnight2.loadContent("media/img/knight_black.png", B_KNIGHT);
	blackRook2.loadContent("media/img/rook_black.png", B_ROOK);

	// Promotion pieces
	whitePromotionQueen.loadContent("media/img/queen_white.png", W_QUEEN);
	whitePromotionRook.loadContent("media/img/rook_white.png", W_ROOK);
	whitePromotionBishop.loadContent("media/img/bishop_white.png", W_BISHOP);
	whitePromotionKnight.loadContent("media/img/knight_white.png", W_KNIGHT);
	blackPromotionQueen.loadContent("media/img/queen_black.png", B_QUEEN);
	blackPromotionRook.loadContent("media/img/rook_black.png", B_ROOK);
	blackPromotionBishop.loadContent("media/img/bishop_black.png", B_BISHOP);
	blackPromotionKnight.loadContent("media/img/knight_black.png", B_KNIGHT);

	// This method initialises pieces vector with right starting positions
	pieces.push_back(&whiteRook1);
	pieces.push_back(&whiteKnight1);
	pieces.push_back(&whiteBishop1);
	pieces.push_back(&whiteQueen);
	pieces.push_back(&whiteKing);
	pieces.push_back(&whiteBishop2);
	pieces.push_back(&whiteKnight2);
	pieces.push_back(&whiteRook2);
	pieces.push_back(&whitePawn1);
	pieces.push_back(&whitePawn2);
	pieces.push_back(&whitePawn3);
	pieces.push_back(&whitePawn4);
	pieces.push_back(&whitePawn5);
	pieces.push_back(&whitePawn6);
	pieces.push_back(&whitePawn7);
	pieces.push_back(&whitePawn8);

	// To keep the pieces list as long as gameboard squares, add null sprites
	// to the indexes where we have no pieces
	for (int i = 0; i < 32; i++) {
		pieces.push_back(NULL);
	}

	pieces.push_back(&blackPawn1);
	pieces.push_back(&blackPawn2);
	pieces.push_back(&blackPawn3);
	pieces.push_back(&blackPawn4);
	pieces.push_back(&blackPawn5);
	pieces.push_back(&blackPawn6);
	pieces.push_back(&blackPawn7);
	pieces.push_back(&blackPawn8);

	pieces.push_back(&blackRook1);
	pieces.push_back(&blackKnight1);
	pieces.push_back(&blackBishop1);
	pieces.push_back(&blackQueen);
	pieces.push_back(&blackKing);
	pieces.push_back(&blackBishop2);
	pieces.push_back(&blackKnight2);
	pieces.push_back(&blackRook2);

	whitePromotionPieces.push_back(&whitePromotionQueen);
	whitePromotionPieces.push_back(&whitePromotionRook);
	whitePromotionPieces.push_back(&whitePromotionBishop);
	whitePromotionPieces.push_back(&whitePromotionKnight);
	blackPromotionPieces.push_back(&blackPromotionQueen);
	blackPromotionPieces.push_back(&blackPromotionRook);
	blackPromotionPieces.push_back(&blackPromotionBishop);
	blackPromotionPieces.push_back(&blackPromotionKnight);
}

void GameScreen::setPieceInitialPositions()
{
	for (int i = 0; i < 64; i++) {
		if (pieces[i] != NULL) {
			pieces[i]->setPosition(gameBoard[i]->getPosition());
		}
	}

	whitePromotionQueen.setPosition(promotionSquares[0]->getPosition());
	whitePromotionRook.setPosition(promotionSquares[1]->getPosition());
	whitePromotionBishop.setPosition(promotionSquares[2]->getPosition());
	whitePromotionKnight.setPosition(promotionSquares[3]->getPosition());

	blackPromotionQueen.setPosition(promotionSquares[0]->getPosition());
	blackPromotionRook.setPosition(promotionSquares[1]->getPosition());
	blackPromotionBishop.setPosition(promotionSquares[2]->getPosition());
	blackPromotionKnight.setPosition(promotionSquares[3]->getPosition());
}

void GameScreen::playAgainInit()
{
	std::string whiteName = (white->getType() == "AI") ? "Computer" : white->getName();
	std::string blackName = (black->getType() == "AI") ? "Computer" : black->getName();

	initialize(whiteName, white->getLevel(), blackName, black->getLevel());
}

void GameScreen::initPlayers(std::string whiteName, int whiteLevel, std::string blackName, int blackLevel)
{
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
}

bool GameScreen::isGameActive()
{
	if (white != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void GameScreen::highlightCheckmate()
{
	clearHighlights(gameBoard);
	// Highlights the position of lost king
	if (playerOnTurn->getColor() == ColorType::White) {
		for (int i = 0; i < 64; i++)
		{
			if (board.getBoard()[i] == Piece::W_KING) {
				gameBoard[i]->setState(Highlighted);
			}
		}
	} else {
		for (int i = 0; i < 64; i++)
		{
			if (board.getBoard()[i] == Piece::B_KING) {
				gameBoard[i]->setState(Highlighted);
			}
		}
	}
}

void GameScreen::showSaveGameDialog() {
	// This should show file dialog for saving file
	// Save the game
	const char* savePath = tinyfd_saveFileDialog("Save game", "", 0, NULL, "text files");
	board.saveGame(white, black, savePath);
}
