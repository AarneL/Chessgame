#include "./../headers/options_screen.hpp"
#include "./../headers/base_screen.hpp"

OptionsScreen::OptionsScreen(void)
{
}

void OptionsScreen::loadContent(void)
{
	backButtonTexture.loadFromFile("media/img/backbutton.jpg");
	backButton.setTexture(backButtonTexture);
	backButton.setPosition(sf::Vector2f(300, 200));
}

int OptionsScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i v = sf::Mouse::getPosition(window);
			std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

			if (backButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start optionsscreen
				std::cout << "User pressed backbutton." << std::endl;
				return 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
	}
	return 0;
}

void OptionsScreen::draw(sf::RenderWindow &window)
{
	window.draw(backButton);
	window.display();
}