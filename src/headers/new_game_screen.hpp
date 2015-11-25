#ifndef NEW_GAME_SCREEN_H
#define NEW_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "base_screen.hpp"
#include "game_screen.hpp"


class NewGameScreen : public BaseScreen
{
public:
	NewGameScreen();

	// New game screen needs to be able to use gameScreens initializer
    NewGameScreen(GameScreen* g);
	void loadContent(void);
	void createGame(int players);
	int update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
private:

	sf::Texture onePlayerButtonTexture;
	sf::Sprite onePlayerButton;
	sf::Texture twoPlayersButtonTexture;
	sf::Sprite twoPlayersButton;

	// Containers for sprite elements so it can be looped
	std::vector<sf::Sprite> elements;

	GameScreen* gameScreen;

	// Player texts
	sf::Font font;
	sf::Text whitePlayerText;
	sf::Text blackPlayerText;

	// Player buttons
	sf::Image humanButton;
	sf::Image humanHighlightedButton;
	sf::Image humanSelectedButton;

	sf::Texture whiteHumanButtonTexture;
	sf::Texture blackHumanButtonTexture;

	sf::Sprite whiteHumanButton;
	sf::Sprite blackHumanButton;
};

#endif
