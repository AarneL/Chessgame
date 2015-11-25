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
	void clearButtonHighlights();
    void draw(sf::RenderWindow &window);

private:
	// Containers for sprite elements so it can be looped
	std::vector<sf::Sprite*> elements;

	GameScreen* gameScreen;

	// Player texts
	sf::Font font;
	sf::Text whitePlayerText;
	sf::Text blackPlayerText;

	// Player buttons
	sf::Texture humanButtonTexture;
	sf::Texture humanHighlightedButtonTexture;
	sf::Texture humanSelectedButtonTexture;

	sf::Texture AIButtonTexture;
	sf::Texture AIHighlightedButtonTexture;
	sf::Texture AISelectedButtonTexture;

	sf::Sprite whiteHumanButton;
	sf::Sprite blackHumanButton;

	sf::Sprite whiteAIButton;
	sf::Sprite blackAIButton;

	sf::Sprite* whitePlayerSelected;
	sf::Sprite* blackPlayerSelected;
};

#endif
