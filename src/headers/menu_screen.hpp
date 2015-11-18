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

	sf::Image newGameButtonImg;
	sf::Image newGameHighlightedButtonImg;
	sf::Texture newGameButtonTexture;
	sf::Sprite newGameButton;

	sf::Image loadGameButtonImg;
	sf::Image loadGameHighlightedButtonImg;
	sf::Texture loadGameButtonTexture;
	sf::Sprite loadGameButton;

	sf::Image optionsButtonImg;
	sf::Image optionsHighlightedButtonImg;
	sf::Texture optionsButtonTexture;
	sf::Sprite optionsButton;

	sf::Image exitButtonImg;
	sf::Image exitHighlightedButtonImg;
	sf::Texture exitButtonTexture;
	sf::Sprite exitButton;

	// Containers for sprite elements so it can be looped
	std::vector<sf::Sprite> elements;

	void clearButtonHighlights();

	GameScreen* gameScreen;
};

#endif /* MENU_SCREEN_H */