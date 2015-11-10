#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H
#include "./../headers/base_screen.hpp"
#include <SFML/Graphics.hpp>

class OptionsScreen : public BaseScreen
{
public:
	OptionsScreen(void);
	virtual void LoadContent(void);
	virtual void Update(void);
	virtual int Run(sf::RenderWindow &App);
private:
	sf::Texture backbuttontexture;
	sf::Sprite backbutton;
};

#endif /* OPTIONS_SCREEN_H */