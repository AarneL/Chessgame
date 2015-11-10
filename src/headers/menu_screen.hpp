#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "./../headers/base_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
public:
    MenuScreen(void);
	virtual void LoadContent(void);
	virtual void Update(void);
    virtual int Run(sf::RenderWindow &App);
private:
	sf::Texture backgroundtexture;
	sf::Sprite background;
	sf::Texture playbuttontexture;
	sf::Sprite playbutton;
	sf::Texture optionsbuttontexture;
	sf::Sprite optionsbutton;
	sf::Texture exitbuttontexture;
	sf::Sprite exitbutton;
};

#endif /* MENU_SCREEN_H */