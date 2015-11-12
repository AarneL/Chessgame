#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"
// #include "../headers/board.hpp"
#include <SFML/Graphics.hpp>



GameScreen::GameScreen(void)
{
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
	sf::Color color_square_dark(210, 105,30);	//"chocolate"
	sf::Color color_square_light(138,54,15);	//"burntsienna"
	// Square highlight colors
	sf::Color color_highlight_square_dark(0,200,0);
	sf::Color color_highlight_square_light(0,255,255);

	//Create base board starting from down left corner
	sf::Sprite square;
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			std::cout << i << std::endl;
			square = sf::Sprite();
			square.setPosition(j*96, i*96);
			square.setTexture(squareTexture);
			if ( (i+j)%2 == 0 ) {
				square.setColor(color_square_dark);
			}
			else if ( (i+j)%2 == 1 ) {
				square.setColor(color_square_light);
			}
			gameBoard.push_back(&square);
		}
	}
	// Set positions to pieces

}

int GameScreen::update(sf::RenderWindow &window, sf::Event & event)
{
	// Square colors
	sf::Color color_square_dark(210, 105,30);	//"chocolate"
	sf::Color color_square_light(138,54,15);	//"burntsienna"
	// Square highlight colors
	sf::Color color_highlight_square_dark(0,200,0);
	sf::Color color_highlight_square_light(0,255,255);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return 0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return -1;
	else if (event.type == sf::Event::MouseButtonPressed) {
		// Get mouse position
		sf::Vector2i mpos = sf::Mouse::getPosition(window);
		for (auto i : gameBoard) {
			// Check if current square is in the mouse position
			if (i->getGlobalBounds().contains((sf::Vector2f)mpos) ) {
				// std::vector<int> possibleIndexes = game.possibleMoves(i) (actually this shloud be inxed of i)
				// if (possibleIndexes.size() > 0) {
					// Then highlight these indexes
					// dummy:
					// 	if (gameBoard[35].getColor() == color_square_dark)
					// 		gameBoard[35].setColor(color_highlight_square_dark);
					// 	else if (gameBoard[35].getColor() == color_square_light)
					// 		gameBoard[35].setColor(color_highlight_square_light);
					// 	return 2;
				// }
				// else {
				// 	// Take away the possible highlights
				// 	// dummy:
				// 	if (gameBoard[35].getColor() == color_highlight_square_dark)
				// 		gameBoard[35].setColor(color_square_dark);
				// 	else if (gameBoard[35].getColor() == color_highlight_square_light)
				// 		gameBoard[35].setColor(color_square_light);
				// 	return 2;
				// }
				return 2;
			}
		}
	}
	return 2;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 10, 200, 255));
	for (auto i : gameBoard) {
		window.draw(*i);
	}
	for (auto i : pieces) {
		if (i != NULL) {
			window.draw(*i);
		}
	}
    window.display();
}