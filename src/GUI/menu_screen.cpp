#include "./../headers/menu_screen.hpp"
#include "./../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}
void MenuScreen::LoadContent(void)
{

}

void MenuScreen::Update(void)
{

}

int MenuScreen::Run(sf::RenderWindow &App)
{
    while (1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return 1;

        App.clear(sf::Color(200,10,200, 255));
        App.display();
    }
}