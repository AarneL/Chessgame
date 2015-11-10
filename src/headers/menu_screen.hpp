#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "./../headers/base_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
public:
    MenuScreen(void);
	virtual void loadContent(void);
	virtual int update(sf::RenderWindow &window);
    virtual void draw(sf::RenderWindow &window);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture playButtonTexture;
	sf::Sprite playButton;
	sf::Texture optionsButtonTexture;
	sf::Sprite optionsButton;
	sf::Texture exitButtonTexture;
	sf::Sprite exitButton;
};

#endif /* MENU_SCREEN_H */