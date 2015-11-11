#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"
// #include "../headers/board.hpp"
#include <SFML/Graphics.hpp>



GameScreen::GameScreen(void)
{
	pieceClicked = NULL;
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

	// Set textures to pieces and push them to whitePieces vector in a right order
	whitePawn1.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn1);
	whitePawn2.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn2);
	whitePawn3.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn3);
	whitePawn4.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn4);
	whitePawn5.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn5);
	whitePawn6.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn6);
	whitePawn7.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn7);
	whitePawn8.setTexture(whitePawnTexture);
	whitePieces.push_back(whitePawn8);

	whiteRook1.setTexture(whiteRookTexture);
	whitePieces.push_back(whiteRook1);
	whiteKnight1.setTexture(whiteKnightTexture);
	whitePieces.push_back(whiteKnight1);
	whiteBishop1.setTexture(whiteBishopTexture);
	whitePieces.push_back(whiteBishop1);
	whiteQueen.setTexture(whiteQueenTexture);
	whitePieces.push_back(whiteQueen);
	whiteKing.setTexture(whiteKingTexture);
	whitePieces.push_back(whiteKing);
	whiteBishop2.setTexture(whiteBishopTexture);
	whitePieces.push_back(whiteBishop2);
	whiteKnight2.setTexture(whiteKnightTexture);
	whitePieces.push_back(whiteKnight2);
	whiteRook2.setTexture(whiteRookTexture);
	whitePieces.push_back(whiteRook2);

	// Same for black pieces
	blackRook1.setTexture(blackRookTexture);
	blackPieces.push_back(blackRook1);
	blackKnight1.setTexture(blackKnightTexture);
	blackPieces.push_back(blackKnight1);
	blackBishop1.setTexture(blackBishopTexture);
	blackPieces.push_back(blackBishop1);
	blackQueen.setTexture(blackQueenTexture);
	blackPieces.push_back(blackQueen);
	blackKing.setTexture(blackKingTexture);
	blackPieces.push_back(blackKing);
	blackBishop2.setTexture(blackBishopTexture);
	blackPieces.push_back(blackBishop2);
	blackKnight2.setTexture(blackKnightTexture);
	blackPieces.push_back(blackKnight2);
	blackRook2.setTexture(blackRookTexture);
	blackPieces.push_back(blackRook2);

	blackPawn1.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn1);
	blackPawn2.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn2);
	blackPawn3.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn3);
	blackPawn4.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn4);
	blackPawn5.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn5);
	blackPawn6.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn6);
	blackPawn7.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn7);
	blackPawn8.setTexture(blackPawnTexture);
	blackPieces.push_back(blackPawn8);

	// Texture for board square
	squareTexture.loadFromFile("media/img/square_white.png");
	// Square colors
	sf::Color color_square_dark(210, 105,30);	//"chocolate"
	sf::Color color_square_light(138,54,15);	//"burntsienna"
	// Square highlight colors
	sf::Color color_highlight_square_dark(0,200,0);
	sf::Color color_highlight_square_light(0,255,255);

	//Create base board
	sf::Sprite square;
	for (int i = 0; i < 64; i++){
		square = sf::Sprite();
		square.setPosition(sf::Vector2f( (i%8)*96, (i/8)*96 ));
		square.setTexture(squareTexture);
		if ( (i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1) )
				square.setColor(color_square_dark);
		else if ( (i%2==0 && (i/8)%2==1) || (i%2==1 && (i/8)%2==0) )
				square.setColor(color_square_light);

		gameBoard.push_back(square);
	}

	// Set initial positions for pieces
	// Using same positions as for squares
	for (int i = 0; i < 16; i++){
		blackPieces[i].setPosition(sf::Vector2f( (i%8)*96, (i/8)*96 ));
	}
	for (int i = 0; i < 16; i++){
		whitePieces[i].setPosition(sf::Vector2f( ((i+48)%8)*96, ((i+48)/8)*96 ));
	}
}

int GameScreen::update(sf::RenderWindow &window, sf::Event & event)
{
	// Square colors
	sf::Color color_square_dark(210, 105,30);	//"chocolate"
	sf::Color color_square_light(138,54,15);	//"burntsienna"
	// Square highlight colors
	sf::Color color_highlight_square_dark(0,200,0);
	sf::Color color_highlight_square_light(0,255,255);

	// Create game board
	// Board board = Board();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return 0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
	else if (event.type == sf::Event::MouseButtonPressed) {
		// Get mouse position
		sf::Vector2i mpos = sf::Mouse::getPosition(window);
		std::cout << "mouse clicked" << std::endl;
		// If white turn
		for (auto i : whitePieces) {
			// Check if current piece is in the mouse position
			if (i.getGlobalBounds().contains((sf::Vector2f)mpos) ) {
				// Check if some piece clicked
				// If no, ask where the piece can move (get indexes for gameBoard)
				// Like std::vector possibleIndexes = board.possibleMoves()
				if (pieceClicked == NULL) {
					std::cout << "piece not clicked" << std::endl;
					// Then highlight these indexes
					// dummy:
					if (gameBoard[35].getColor() == color_square_dark)
						gameBoard[35].setColor(color_highlight_square_dark);
					else if (gameBoard[35].getColor() == color_square_light)
						gameBoard[35].setColor(color_highlight_square_light);
					// Set piece clicked
					pieceClicked = &i;
					return 2;
				}
				else {
					std::cout << "piece clicked" << std::endl;
					// Take away the highlights
					// dummy:
					if (gameBoard[35].getColor() == color_highlight_square_dark)
						gameBoard[35].setColor(color_square_dark);
					else if (gameBoard[35].getColor() == color_highlight_square_light)
						gameBoard[35].setColor(color_square_light);
					// Set piece not clicked
					pieceClicked = NULL;
					return 2;
				}
			}
		}
		for (auto i : gameBoard) {
			// Check if current square is in the mouse position
			if (i.getGlobalBounds().contains((sf::Vector2f)mpos) ) {
				// Check if some piece clicked
				// If yes, check if clicked squre if in the possible indexes
				if (pieceClicked != NULL) {
					std::cout << "piece clicked -> move if possible" << std::endl;
					// Dummy:
					if (gameBoard[35].getGlobalBounds().contains((sf::Vector2f)mpos)) {
						std::cout << "This is the right position" << std::endl;
						auto pos = gameBoard[35].getPosition();
						pieceClicked->move(pos);
					}
					// Take away the higlights
					std::cout << "Take away the higlights" << std::endl;
					if (gameBoard[35].getColor() == color_highlight_square_dark)
						gameBoard[35].setColor(color_square_dark);
					else if (gameBoard[35].getColor() == color_highlight_square_light)
						gameBoard[35].setColor(color_square_light);
					// Set piece clicked
					pieceClicked = NULL;
					return 2;
					// END TURN
				}
				// Else dont do anything
				else {
					std::cout << "Any piece is not clicked yet" << std::endl;
					return 2;
				}
			}
		}
		// TODO: Same if black turn
	}
	return 2;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 10, 200, 255));
	for (auto element : elements) {
		window.draw(element);
	}
	for (std::vector<sf::Sprite>::iterator i=gameBoard.begin(); i!=gameBoard.end(); i++)
		window.draw(*i);
	for (std::vector<sf::Sprite>::iterator i=blackPieces.begin(); i!=blackPieces.end(); i++)
		window.draw(*i);
	for (std::vector<sf::Sprite>::iterator i=whitePieces.begin(); i!=whitePieces.end(); i++)
		window.draw(*i);
    window.display();
}