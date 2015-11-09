#include "./../headers/menu_screen.hpp"
#include "./../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}

void MenuScreen::LoadContent(void)
{
	backgroundtexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundtexture);
}

void MenuScreen::Update(void)
{

}

int MenuScreen::Run(sf::RenderWindow &App)
{
	sf::Event event;
    while (App.pollEvent(event)) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
			
    }

    App.clear(sf::Color(200,10,200, 255));
	App.draw(background);
	App.display();
	return 0;
}