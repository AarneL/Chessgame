#include "../headers/menu_screen.hpp"
#include "../headers/base_screen.hpp"
#include <fstream>
#include "../headers/tinyfiledialogs.h"

MenuScreen::MenuScreen(GameScreen* g, sf::RenderWindow &w) : window(w)
{
	gameScreen = g;
}

void MenuScreen::loadContent(void)
{

	// Button positioning variables
	int buttonsFromLeftEdge = (int)(1200 / 1.61); // Golden ratio baby
	int topMargin = 150;
	int buttonDivLength = 200;

	/* All sprites need to be added to "elements" in right order
	 * so that what is drawn "behind" will be added firsts
	 */

	backgroundTexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundTexture);
	elements.push_back(&background);

	newGameButtonTexture.loadFromFile("media/img/new_game_button.png");
	newGameHighlightedButtonTexture.loadFromFile("media/img/new_game_highlighted_button.png");
	newGameButton.setTexture(newGameButtonTexture);
	newGameButton.setPosition(sf::Vector2f(buttonsFromLeftEdge, topMargin));
	elements.push_back(&newGameButton);

	loadGameButtonTexture.loadFromFile("media/img/load_game_button.png");
	loadGameHighlightedButtonTexture.loadFromFile("media/img/load_game_highlighted_button.png");
	loadGameButton.setTexture(loadGameButtonTexture);
	loadGameButton.setPosition(sf::Vector2f(buttonsFromLeftEdge, topMargin+buttonDivLength));
	elements.push_back(&loadGameButton);

	exitButtonTexture.loadFromFile("media/img/exit_button.png");
	exitHighlightedButtonTexture.loadFromFile("media/img/exit_highlighted_button.png");
	exitButton.setTexture(exitButtonTexture);
	exitButton.setPosition(sf::Vector2f(buttonsFromLeftEdge, topMargin+2*buttonDivLength));
	elements.push_back(&exitButton);
}

int MenuScreen::update()
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
				newGameButton.setTexture(newGameHighlightedButtonTexture, false);
				buttonHovered = true;
			}

			else if (loadGameButton.getGlobalBounds().contains(v))
			{
				// Highlight loadGameButton
				loadGameButton.setTexture(loadGameHighlightedButtonTexture, false);
				buttonHovered = true;
			}

			else if (exitButton.getGlobalBounds().contains(v))
			{
				// Highlight exitButton
				exitButton.setTexture(exitHighlightedButtonTexture, false);
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
				return loadGame();
				// Start gameScreen
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


void MenuScreen::draw()
{
	window.clear(sf::Color(250,250,250));
	for (auto element : elements) {
		window.draw(*element);
	}
	window.display();
}

void MenuScreen::clearButtonHighlights()
{
	newGameButton.setTexture(newGameButtonTexture, false);
	loadGameButton.setTexture(loadGameButtonTexture, false);
	exitButton.setTexture(exitButtonTexture, false);
}

int MenuScreen::loadGame()
{
	// This should first open a file dialog where the user can choose file to load

	// Using testfile
	const char* file_loc = tinyfd_openFileDialog("Open load file", "", 0, NULL, "text files", 0);
	if (!file_loc) {
		std::cout << "Error loading file" << std::endl;
		return 0;
	}
	std::ifstream ifs(file_loc, std::ifstream::in);
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
	return 2;
}