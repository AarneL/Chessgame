#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"


// #include "../headers/board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <typeinfo>
#include <chrono>
#include <thread>


GameScreen::GameScreen(void)
{
	// Game starts with white players turn
	board = Board();
	activeSquare = -1;
	white = new Human("White player", ColorType::White);
	// black = new Human("Black player", ColorType::Black);
	black = new AI("Black player", ColorType::Black, 1);
	playerOnTurn = white;
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
			square.setPosition(j*96, i*96);
			square.setTexture(squareTexture);
			if ( (i+j)%2 == 0 ) {
				square.setColor(color_square_dark);
			}
			else if ( (i+j)%2 == 1 ) {
				square.setColor(color_square_light);
			}
			gameBoard.push_back(square);
		}
	}

	// Load game sounds
	if (!moveSoundBuffer.loadFromFile("media/sound/movePiece.wav")) {
		std::cout << "Could not load sound file." << std::endl;
	}
	else {
		moveSound.setBuffer(moveSoundBuffer);
	}
}

int GameScreen::update(sf::RenderWindow &window, sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return 0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		free(white);
		free(black);
		return -1;
	}

	// Human turn
	if (playerOnTurn->getType() == std::string("Human")) {
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
			for (int i = 0; i < 64; i++) {
				if (gameBoard[i].getGlobalBounds().contains(mousePos)) {
					// If no piece active yet
					if (activeSquare == -1)
					{
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
					break;
				}
			}
		}
	}

	// AI Turn
	else {
		movePiece(getAiMove());
		changeTurn();
	}
	return 1;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear();
	for (int i = 0; i < 64; i++) {
		window.draw(gameBoard[i]);
		if (!(pieces[i] == NULL)) {
			pieces[i]->setPosition(gameBoard[i].getPosition());
			window.draw(*pieces[i]);
		}
	}
    window.display();
}

void GameScreen::highlight(std::vector<int> v)
{
	sf::Color color_highlight_square_dark(0, 200, 0);
	sf::Color color_highlight_square_light(0, 255, 255);
	for (auto i : v) {
		if (i % 2 == 0){
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

void GameScreen::movePiece(std::pair<int,int> move)
{
	// Move in GUI
	pieces[move.second] = pieces[move.first];
	pieces[move.first] = NULL;

	// Move in board
	board.movePiece(move.first, move.second);
}

void GameScreen::changeTurn()
{
	// If its black turn
	if (playerOnTurn == black) {
		playerOnTurn = white;
	}
	else {
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
	// A little delay before AI move
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	// This dummy version gets random move from AI's all possible moves
	std::vector<std::pair<int, int>> allPossibleMoves;
	for (int i = 0; i < 64; i++) {
		if (containsPlayerPiece(i, playerOnTurn)) {
			possibleMoves = board.possibleMoves(i);
			for (auto j : possibleMoves) {
				if (i != j) {
					std::pair<int, int> move;
					move.first = i;
					move.second = j;
					allPossibleMoves.push_back(move);
				}
			}
		}
	}
	std::srand(std::time(0));
	auto randMove = std::rand() % allPossibleMoves.size();

	return allPossibleMoves[randMove];
}




