#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "../headers/base_screen.hpp"
#include "game_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
public:
    // Menu screen needs to be able to use gameScreens initializer
    MenuScreen(GameScreen* g, sf::RenderWindow &w);
    int loadGame();
	virtual void loadContent(void);
	virtual int update();
    virtual void draw();

private:
	sf::RenderWindow &window;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Button newGameButton;
	Button loadGameButton;
	Button optionsButton;
	Button exitButton;

	// Containers for Button elements so it can be looped
	std::vector<Button*> elements;

	void clearButtonHighlights();

	GameScreen* gameScreen;
};

#endif /* MENU_SCREEN_H */