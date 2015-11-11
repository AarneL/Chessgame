#include "../headers/base_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/menu_screen.hpp"
#include <SFML/Graphics.hpp>



GameScreen::GameScreen(void)
{
}

void GameScreen::loadContent(void)
{

}


int GameScreen::update(sf::RenderWindow &window, sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
	return 2;
}

void GameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 10, 200, 255));
    window.display();
}