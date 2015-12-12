#include "../headers/menu_screen.hpp"
#include "../headers/base_screen.hpp"
#include "../headers/tinyfiledialogs.h"

MenuScreen::MenuScreen(GameScreen* g, NewGameScreen* n, sf::RenderWindow &w) : window(w)
{
	gameScreen = g;
	newGameScreen = n;
}

void MenuScreen::loadContent(void)
{

	// Button positioning variables
	sf::Vector2u size = window.getSize();
	int width = size.x;
	int buttonsFromLeftEdge = (int)(width / 1.61); // Golden ratio baby
	int topMargin = 150;
	int buttonDivLength = 200;

	/* All sprites need to be added to "elements" in right order
	 * so that what is drawn "behind" will be added firsts
	 */

	backgroundTexture.loadFromFile("media/img/background.png");
	background.setTexture(backgroundTexture);

	continueButton.loadContent("media/img/continue_button.png", "media/img/continue_highlighted_button.png", "", sf::Vector2f(buttonsFromLeftEdge, topMargin-100), false);
	elements.push_back(&continueButton);

	newGameButton.loadContent("media/img/new_game_button.png", "media/img/new_game_highlighted_button.png", "", sf::Vector2f(buttonsFromLeftEdge, topMargin), true);
	elements.push_back(&newGameButton);

	loadGameButton.loadContent("media/img/load_game_button.png", "media/img/load_game_highlighted_button.png", "", sf::Vector2f(buttonsFromLeftEdge, topMargin+buttonDivLength), true);
	elements.push_back(&loadGameButton);

	exitButton.loadContent("media/img/exit_button.png", "media/img/exit_highlighted_button.png", "", sf::Vector2f(buttonsFromLeftEdge, topMargin+2*buttonDivLength), true);
	elements.push_back(&exitButton);

	// Music :D
	backgroundMusicBuffer.loadFromFile("media/sound/chess.wav");
	backgroundMusic.setBuffer(backgroundMusicBuffer);
	backgroundMusic.setVolume(100);
	backgroundMusic.play();
}

int MenuScreen::update()
{
	// Make continue visible and move buttons
	if (continueButton.isVisible() && !isGameActive()) {
		hideContinueButton();
	}
	else if (!continueButton.isVisible() && isGameActive()) {
		showContinueButton();
	}

	sf::Event event;
	while(window.pollEvent(event)) {

		sf::Vector2f v = (sf::Vector2f)(sf::Mouse::getPosition(window));

		// Hovering button highlights the sprite
		if (event.type == sf::Event::MouseMoved)
		{
			if (continueButton.containsMousePos(v) && isGameActive())
			{
				// Highlight newGameButton
				continueButton.setState(Highlighted);
			}

			else if (newGameButton.containsMousePos(v))
			{
				// Highlight newGameButton
				newGameButton.setState(Highlighted);
			}

			else if (loadGameButton.containsMousePos(v))
			{
				// Highlight loadGameButton
				loadGameButton.setState(Highlighted);
			}

			else if (exitButton.containsMousePos(v))
			{
				// Highlight exitButton
				exitButton.setState(Highlighted);
			}

			else {
				// If nothing hovered
				clearButtonHighlights();
			}
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (continueButton.containsMousePos(v) && isGameActive())
			{
				// The there is a game active, continue it
				std::cout << "User pressed continueButton." << std::endl;
				backgroundMusic.stop();
				return 2;
			}

			else if (newGameButton.containsMousePos(v))
			{
				// Start newgamescreen
				std::cout << "User pressed newGameButton." << std::endl;
				backgroundMusic.stop();
				// Initialize the newGameSreen
				newGameScreen->initialize();
				return 1;
			}

			else if (loadGameButton.containsMousePos(v))
			{
				// User pressed loadbutton->Open dialog box
				std::cout << "User pressed loadButton." << std::endl;
				// Start gameScreen
				backgroundMusic.stop();
				return gameScreen->loadGame();
			}

			else if (exitButton.containsMousePos(v))
			{
				// Exit program
				std::cout << "User pressed exitbutton." << std::endl;
				return -1;
			}
		}

		else if (event.type == sf::Event::Closed) {
			window.close();
			return -1;
		}

	}
	// Continue using same screen
	return 0;
}


void MenuScreen::draw()
{
	window.clear(sf::Color(250,250,250));
	window.draw(background);
	for (auto element : elements) {
		element->draw(window);
	}
	window.display();
}

void MenuScreen::clearButtonHighlights()
{
	for (auto element : elements) {
		element->setState(Normal);
	}
}

void MenuScreen::showContinueButton()
{
	continueButton.drawObject = true;
	newGameButton.move(sf::Vector2f(0, 100));
	loadGameButton.move(sf::Vector2f(0, 100));
	exitButton.move(sf::Vector2f(0, 100));
}

void MenuScreen::hideContinueButton()
{
	continueButton.drawObject = false;
	newGameButton.move(sf::Vector2f(0, -100));
	loadGameButton.move(sf::Vector2f(0, -100));
	exitButton.move(sf::Vector2f(0, -100));
}

bool MenuScreen::isGameActive()
{
	return gameScreen->isGameActive();
}
