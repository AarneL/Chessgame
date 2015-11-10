#include "./../headers/menu_screen.hpp"
#include "./../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}

void MenuScreen::loadContent(void)
{
	backgroundTexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundTexture);
	playButtonTexture.loadFromFile("media/img/playbutton.png");
	playButton.setTexture(playButtonTexture);
	playButton.setPosition(sf::Vector2f(300, 200));
	optionsButtonTexture.loadFromFile("media/img/optionsbutton.png");
	optionsButton.setTexture(optionsButtonTexture);
	optionsButton.setPosition(sf::Vector2f(300, 400));
	exitButtonTexture.loadFromFile("media/img/exitbutton.png");
	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(sf::Vector2f(300, 600));
}

int MenuScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i v = sf::Mouse::getPosition(window);
			std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

			if (playButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start gamescreen
				std::cout << "User pressed playbutton." << std::endl;
				return 1;
			}

			if (optionsButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start optionsscreen
				std::cout << "User pressed optionsbutton." << std::endl;
				return 2;
			}

			if (exitButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Exit program
				std::cout << "User pressed exitbutton." << std::endl;
				return -1;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;
	}
	return 0;
}

void MenuScreen::draw(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(playButton);
	window.draw(optionsButton);
	window.draw(exitButton);
	window.display();
}