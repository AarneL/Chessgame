#include "../headers/menu_screen.hpp"
#include "../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}

void MenuScreen::loadContent(void)
{
	/* All sprites need to be added to "elements" in right order
	 * so that what is drawn "behind" will be added first
	 */
	//backgroundTexture.loadFromFile("media/img/background.jpg");
	//background.setTexture(backgroundTexture);
	//elements.push_back(background);

	newGameButtonTexture.loadFromFile("media/img/new_game_button.png");
	newGameButton.setTexture(newGameButtonTexture);
	newGameButton.setPosition(sf::Vector2f(300, 100));
	elements.push_back(newGameButton);

	loadGameButtonTexture.loadFromFile("media/img/load_game_button.png");
	loadGameButton.setTexture(loadGameButtonTexture);
	loadGameButton.setPosition(sf::Vector2f(300, 250));
	elements.push_back(loadGameButton);

	optionsButtonTexture.loadFromFile("media/img/options_button.png");
	optionsButton.setTexture(optionsButtonTexture);
	optionsButton.setPosition(sf::Vector2f(300, 400));
	elements.push_back(optionsButton);

	exitButtonTexture.loadFromFile("media/img/exit_button.png");
	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(sf::Vector2f(300, 550));
	elements.push_back(exitButton);

}

int MenuScreen::update(sf::RenderWindow &window, sf::Event & event)
{
	sf::Vector2f v = (sf::Vector2f)(sf::Mouse::getPosition(window));

	// Hovering button highlights the sprite
	if (event.type == sf::Event::MouseMoved)
	{
		std::cout << "Mouse moved" << std::endl;
		if (newGameButton.getGlobalBounds().contains(v))
		{
			std::cout << "Mouse hovering newgamebutton" << std::endl;
		}
		if (loadGameButton.getGlobalBounds().contains(v))
		{
			std::cout << "Mouse hovering loadgamebutton" << std::endl;
		}
		if (optionsButton.getGlobalBounds().contains(v))
		{
			std::cout << "Mouse hovering optionsbutton" << std::endl;
		}
		if (exitButton.getGlobalBounds().contains(v))
		{
			std::cout << "Mouse hovering exitbutton" << std::endl;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

		if (newGameButton.getGlobalBounds().contains(v))
		{
			// Start newgamescreen
			std::cout << "User pressed newGameButton." << std::endl;
			return 1;
		}

		if (loadGameButton.getGlobalBounds().contains(v))
		{
			// User pressed loadbutton->Open dialog box
			std::cout << "User pressed loadButton." << std::endl;

		}

		if (optionsButton.getGlobalBounds().contains(v))
		{
			// Start optionsscreen
			std::cout << "User pressed optionsbutton." << std::endl;
			return 3;
		}

		if (exitButton.getGlobalBounds().contains(v))
		{
			// Exit program
			std::cout << "User pressed exitbutton." << std::endl;
			return -1;
		}
	}

	// Close whole program
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return -1;

	// Continue using same screen
	return 0;
}


void MenuScreen::draw(sf::RenderWindow &window)
{
	window.clear();
	for (auto element : elements) {
		window.draw(element);
	}
	window.display();
}