#include "./../headers/base_screen.hpp"
#include "./../headers/game_screen.hpp"
#include "./../headers/menu_screen.hpp"
#include <SFML/Graphics.hpp>



GameScreen::GameScreen(void)
{
}

void GameScreen::LoadContent(void)
{

}


void GameScreen::Update(void)
{

}

int GameScreen::Run(sf::RenderWindow &App)
{
    while (1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return 0;
        App.clear(sf::Color(0,10,200, 255));
        App.display();
    }
}