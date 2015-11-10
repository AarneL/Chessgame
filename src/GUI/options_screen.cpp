#include "./../headers/options_screen.hpp"
#include "./../headers/base_screen.hpp"

OptionsScreen::OptionsScreen(void)
{
}

void OptionsScreen::LoadContent(void)
{
	backbuttontexture.loadFromFile("media/img/backbutton.jpg");
	backbutton.setTexture(backbuttontexture);
	backbutton.setPosition(sf::Vector2f(300, 200));
}

void OptionsScreen::Update(void)
{

}

int OptionsScreen::Run(sf::RenderWindow &App)
{
	sf::Event event;
	while (App.pollEvent(event)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i v = sf::Mouse::getPosition(App);
			std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

			if (backbutton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start optionsscreen
				std::cout << "User pressed backbutton." << std::endl;
				return 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
	}

	App.draw(backbutton);
	App.display();
	return 0;
}