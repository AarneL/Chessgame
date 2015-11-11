#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H
#include "../headers/base_screen.hpp"
#include <SFML/Graphics.hpp>

class OptionsScreen : public BaseScreen
{
public:
	OptionsScreen(void);
	virtual void loadContent(void);
	virtual int update(sf::RenderWindow &window, sf::Event & event);
	virtual void draw(sf::RenderWindow &window);
private:
	sf::Texture backButtonTexture;
	sf::Sprite backButton;
};

#endif /* OPTIONS_SCREEN_H */