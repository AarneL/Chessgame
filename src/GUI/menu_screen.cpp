#include "./../headers/menu_screen.hpp"
#include "./../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}

void MenuScreen::loadContent(void)
{
	/* All sprites need to be added to "elements" in right order 
	 * so that what is drawn "behind" will be added first
	 */
	backgroundTexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundTexture);
	elements.push_back(background);

	newGameButtonTexture.loadFromFile("media/img/new_game_button.png");
	newGameButton.setTexture(newGameButtonTexture);
	newGameButton.setPosition(sf::Vector2f(300, 100));
	elements.push_back(newGameButton);

	loadGameButtonTexture.loadFromFile("media/img/load_game_button.png");
	loadGameButton.setTexture(loadGameButtonTexture);
	loadGameButton.setPosition(sf::Vector2f(300, 300));
	elements.push_back(loadGameButton);

	optionsButtonTexture.loadFromFile("media/img/options_button.png");
	optionsButton.setTexture(optionsButtonTexture);
	optionsButton.setPosition(sf::Vector2f(300, 500));
	elements.push_back(optionsButton);

	exitButtonTexture.loadFromFile("media/img/exit_button.png");
	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(sf::Vector2f(300, 700));
	elements.push_back(exitButton);

	// Set positions
	
}

int MenuScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i v = sf::Mouse::getPosition(window);
			std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

			if (newGameButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start gamescreen
				std::cout << "User pressed playButton." << std::endl;
				return 1;
			}

			if (loadGameButton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Exit program
				std::cout << "User pressed loadButton." << std::endl;
				return -1;
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
	for (auto element : elements) {
		window.draw(element);
	}
	window.display();
}