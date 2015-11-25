#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "../headers/base_screen.hpp"
#include "game_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
public:
    MenuScreen(void);
    // Menu screen needs to be able to use gameScreens initializer
    MenuScreen(GameScreen* g);
    void loadGame();
	virtual void loadContent(void);
	virtual int update(sf::RenderWindow &window);
    virtual void draw(sf::RenderWindow &window);

private:
	// Temporary containers for elements
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture newGameButtonTexture;
	sf::Texture newGameHighlightedButtonTexture;
	sf::Sprite newGameButton;

	sf::Texture loadGameButtonTexture;
	sf::Texture loadGameHighlightedButtonTexture;
	sf::Sprite loadGameButton;

	sf::Texture optionsButtonTexture;
	sf::Texture optionsHighlightedButtonTexture;
	sf::Sprite optionsButton;

	sf::Texture exitButtonTexture;
	sf::Texture exitHighlightedButtonTexture;
	sf::Sprite exitButton;

	// Containers for sprite elements so it can be looped
	std::vector<sf::Sprite*> elements;

	void clearButtonHighlights();

	GameScreen* gameScreen;
};

#endif /* MENU_SCREEN_H */