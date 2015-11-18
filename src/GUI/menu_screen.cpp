#include "../headers/menu_screen.hpp"
#include "../headers/base_screen.hpp"
#include <fstream>

MenuScreen::MenuScreen(void)
{
}

MenuScreen::MenuScreen(GameScreen* g)
{
	gameScreen = g;
}

void MenuScreen::loadContent(void)
{
	/* All sprites need to be added to "elements" in right order
	 * so that what is drawn "behind" will be added first
	 */
	backgroundTexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundTexture);
	elements.push_back(background);

	newGameButtonImg.loadFromFile("media/img/new_game_button.png");
	newGameHighlightedButtonImg.loadFromFile("media/img/new_game_highlighted_button.png");
	newGameButtonTexture.loadFromFile("media/img/new_game_button.png");
	newGameButton.setTexture(newGameButtonTexture);
	newGameButton.setPosition(sf::Vector2f(400, 100));
	elements.push_back(newGameButton);

	loadGameButtonImg.loadFromFile("media/img/load_game_button.png");
	loadGameHighlightedButtonImg.loadFromFile("media/img/load_game_highlighted_button.png");
	loadGameButtonTexture.loadFromFile("media/img/load_game_button.png");
	loadGameButton.setTexture(loadGameButtonTexture);
	loadGameButton.setPosition(sf::Vector2f(400, 250));
	elements.push_back(loadGameButton);

	optionsButtonImg.loadFromFile("media/img/options_button.png");
	optionsHighlightedButtonImg.loadFromFile("media/img/options_highlighted_button.png");
	optionsButtonTexture.loadFromFile("media/img/options_button.png");
	optionsButton.setTexture(optionsButtonTexture);
	optionsButton.setPosition(sf::Vector2f(400, 400));
	elements.push_back(optionsButton);

	exitButtonImg.loadFromFile("media/img/exit_button.png");
	exitHighlightedButtonImg.loadFromFile("media/img/exit_highlighted_button.png");
	exitButtonTexture.loadFromFile("media/img/exit_button.png");
	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(sf::Vector2f(400, 550));
	elements.push_back(exitButton);
}

int MenuScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while(window.pollEvent(event)) {

		sf::Vector2f v = (sf::Vector2f)(sf::Mouse::getPosition(window));

		// Hovering button highlights the sprite
		if (event.type == sf::Event::MouseMoved)
		{
			bool buttonHovered = false;
			if (newGameButton.getGlobalBounds().contains(v))
			{
				// Highlight newGameButton
				newGameButtonTexture.update(newGameHighlightedButtonImg);
				buttonHovered = true;
			}

			else if (loadGameButton.getGlobalBounds().contains(v))
			{
				// Highlight loadGameButton
				loadGameButtonTexture.update(loadGameHighlightedButtonImg);
				buttonHovered = true;
			}
			else if (optionsButton.getGlobalBounds().contains(v))
			{
				// Highlight loadGameButton
				optionsButtonTexture.update(optionsHighlightedButtonImg);
				buttonHovered = true;
			}


			else if (exitButton.getGlobalBounds().contains(v))
			{
				// Highlight exitButton
				exitButtonTexture.update(exitHighlightedButtonImg);
				buttonHovered = true;
			}

			else if(!buttonHovered) {
				// If nothing hovered
				clearButtonHighlights();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (newGameButton.getGlobalBounds().contains(v))
			{
				// Start newgamescreen
				std::cout << "User pressed newGameButton." << std::endl;
				return 1; // NOTE: For now new game will start game immeaditely
			}

			if (loadGameButton.getGlobalBounds().contains(v))
			{
				// User pressed loadbutton->Open dialog box
				std::cout << "User pressed loadButton." << std::endl;
				loadGame();
				// Start gameScreen
				return 2;
			}

			if (optionsButton.getGlobalBounds().contains(v))
			{
				// Start optionsscreen
				std::cout << "User pressed optionsbutton." << std::endl;
				return 2;
			}

			if (exitButton.getGlobalBounds().contains(v))
			{
				// Exit program
				std::cout << "User pressed exitbutton." << std::endl;
				return -1;
			}
		}

	}
	// Continue using same screen
	return 0;
}


void MenuScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(250,250,250));
	for (auto element : elements) {
		window.draw(element);
	}
	window.display();
}

void MenuScreen::clearButtonHighlights()
{
	newGameButtonTexture.update(newGameButtonImg);
	loadGameButtonTexture.update(loadGameButtonImg);
	optionsButtonTexture.update(optionsButtonImg);
	exitButtonTexture.update(exitButtonImg);
}

void MenuScreen::loadGame()
{
	// This should first open a file dialog where the user can choose file to load

	// Using testfile
	std::ifstream ifs("test.txt", std::ifstream::in);
	if (!ifs) {
		std::cout << "File not found" << std::endl;
	}

	// Collect information about players
	std::string white;
	std::getline(ifs, white);
	std::string black;
	std::getline(ifs, black);

	std::string whiteName = white.substr(0, white.find('-'));
	std::string blackName = black.substr(0, black.find('-'));
	int whiteLevel = atoi((white.substr(white.find('-')+1)).c_str());
	int blackLevel = atoi((black.substr(black.find('-')+1)).c_str());

	// Initialize the game screen with the players from file
	gameScreen->initialize(whiteName, whiteLevel, blackName, blackLevel);

	for (std::string line; std::getline(ifs, line); )
	{
		std::cout << line << std::endl;
		std::pair<int, int> move;
		move.first = atoi((line.substr(0, line.find('-'))).c_str());
		move.second = atoi((line.substr(line.find('-')+1)).c_str());
		gameScreen->movePiece(move);
	}

	ifs.close();
}
