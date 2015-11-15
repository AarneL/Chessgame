#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "./../headers/game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameScreen : public BaseScreen
{
private:
	/* To draw board properly program must have different sprite for each piece
	 *
	 */
	// White pieces
	sf::Texture whitePawnTexture;
	sf::Texture whiteRookTexture;
	sf::Texture whiteBishopTexture;
	sf::Texture whiteKnightTexture;
	sf::Texture whiteQueenTexture;
	sf::Texture whiteKingTexture;

	sf::Sprite whitePawn1;
	sf::Sprite whitePawn2;
	sf::Sprite whitePawn3;
	sf::Sprite whitePawn4;
	sf::Sprite whitePawn5;
	sf::Sprite whitePawn6;
	sf::Sprite whitePawn7;
	sf::Sprite whitePawn8;

	sf::Sprite whiteRook1;
	sf::Sprite whiteRook2;

	sf::Sprite whiteBishop1;
	sf::Sprite whiteBishop2;

	sf::Sprite whiteKnight1;
	sf::Sprite whiteKnight2;

	sf::Sprite whiteQueen;
	sf::Sprite whiteKing;

	// Black pieces
	sf::Texture blackPawnTexture;
	sf::Texture blackRookTexture;
	sf::Texture blackBishopTexture;
	sf::Texture blackKnightTexture;
	sf::Texture blackQueenTexture;
	sf::Texture blackKingTexture;

	sf::Sprite blackPawn1;
	sf::Sprite blackPawn2;
	sf::Sprite blackPawn3;
	sf::Sprite blackPawn4;
	sf::Sprite blackPawn5;
	sf::Sprite blackPawn6;
	sf::Sprite blackPawn7;
	sf::Sprite blackPawn8;

	sf::Sprite blackRook1;
	sf::Sprite blackRook2;

	sf::Sprite blackBishop1;
	sf::Sprite blackBishop2;

	sf::Sprite blackKnight1;
	sf::Sprite blackKnight2;

	sf::Sprite blackQueen;
	sf::Sprite blackKing;

	std::vector<sf::Sprite*> pieces;

	// Game board
	sf::Texture squareTexture;
	std::vector<sf::Sprite> gameBoard;

	// Square colors
	sf::Color color_square_dark;	//"chocolate"
	sf::Color color_square_light;	//"burntsienna"

	// Square highlight colors
	sf::Color color_highlight_square_dark;
	sf::Color color_highlight_square_light;

	std::vector<std::pair<int, int> > moveList;

	sf::SoundBuffer moveSoundBuffer;
	sf::Sound moveSound;

public:
    GameScreen(void);
	void loadContent(void);
	int update(sf::RenderWindow &window, sf::Event & event);
    void draw(sf::RenderWindow &window);
	void highlight(std::vector<int> v);
	void clearHighlights();
	void movePiece(std::pair<int, int> move);

	// Game interface
	Game game;
};

#endif
