#include "../headers/new_game_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/base_screen.hpp"
#include "../headers/human.hpp"
#include "../headers/ai.hpp"
#include "../headers/player.hpp"

NewGameScreen::NewGameScreen()
{
}

NewGameScreen::NewGameScreen(GameScreen* g)
{
	gameScreen = g;
}

void NewGameScreen::loadContent(void)
{
	// Player texts
	int topMargin = 100; // Text top margin
	int midMargin = 200; // Text mid margin
	if (!font.loadFromFile("media/img/Calibri.ttf"))
		std::cout << "File not found!" << std::endl;
	whitePlayerText.setFont(font);
	whitePlayerText.setCharacterSize(70);
	whitePlayerText.setStyle(sf::Text::Bold);
	whitePlayerText.setString("White");
	whitePlayerText.setPosition(sf::Vector2f(midMargin, topMargin));

	blackPlayerText.setFont(font);
	blackPlayerText.setCharacterSize(70);
	blackPlayerText.setStyle(sf::Text::Bold);
	blackPlayerText.setString("Black");
	blackPlayerText.setPosition(sf::Vector2f(600 + midMargin, topMargin));

	// Player buttons
	int buttonTopMargin = 300;
	int buttonMidMargin = 100;

	humanButtonTexture.loadFromFile("media/img/humanButton.png");
	humanHighlightedButtonTexture.loadFromFile("media/img/humanHighlightedButton.png");
	humanSelectedButtonTexture.loadFromFile("media/img/humanSelectedButton.png");

	AIButtonTexture.loadFromFile("media/img/computerButton.png");
	AIHighlightedButtonTexture.loadFromFile("media/img/computerHighlightedButton.png");
	AISelectedButtonTexture.loadFromFile("media/img/computerSelectedButton.png");

	whiteHumanButton.setTexture(humanButtonTexture);
	whiteHumanButton.setPosition(sf::Vector2f(buttonMidMargin, buttonTopMargin));
	elements.push_back(&whiteHumanButton);

	blackHumanButton.setTexture(humanButtonTexture);
	blackHumanButton.setPosition(sf::Vector2f(600 + buttonMidMargin, buttonTopMargin));
	elements.push_back(&blackHumanButton);

	whiteAIButton.setTexture(AIButtonTexture);
	whiteAIButton.setPosition(sf::Vector2f(buttonMidMargin + 200, buttonTopMargin));
	elements.push_back(&whiteAIButton);

	blackAIButton.setTexture(AIButtonTexture);
	blackAIButton.setPosition(sf::Vector2f(600 + buttonMidMargin + 200, buttonTopMargin));
	elements.push_back(&blackAIButton);
}

void NewGameScreen::createGame(int players)
{
	if (players == 1) {
		// Name and level should be taken from user input
		std::string name1 = "Pekka";
		ColorType color1 = White;
		Human player1 = Human(name1, color1);
		std::string name2 = "AI";
		ColorType color2 = Black;
		AI player2 = AI(name2, color2, 4);
		std::cout << "created two players:" << std::endl;
		std::cout << player1.getName() << ", " << player1.getColor() << std::endl;
		std::cout << player2.getName() << ", " << player2.getColor() << ", " << player2.getLevel() << std::endl;
	}
	else if (players == 2) {
		// Names should be taken from user input
		std::string name1 = "Pekka";
		ColorType color1 = White;
		Human player1 = Human("Pekka", color1);
		std::string name2 = "Pentti";
		ColorType color2 = Black;
		Human player2 = Human("Pentti", color2);
		std::cout << "created two players:" << std::endl;
		std::cout << player1.getName() << ", " << player1.getColor() << std::endl;
		std::cout << player2.getName() << ", " << player2.getColor() << std::endl;
	}
	// TODO: when players are created, next create the Game with them
	// Game game = Game(player1, player2);
}

int NewGameScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while(window.pollEvent(event)) {
		sf::Vector2f v = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (event.type == sf::Event::MouseMoved)
		{
			bool buttonHovered = false;
			if (whiteHumanButton.getGlobalBounds().contains(v) && whitePlayerSelected != &whiteHumanButton) {
				// Highlight whiteHumanButton
				whiteHumanButton.setTexture(humanHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (blackHumanButton.getGlobalBounds().contains(v) && blackPlayerSelected != &blackHumanButton) {
				// Highlight blackHumanButton
				blackHumanButton.setTexture(humanHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (whiteAIButton.getGlobalBounds().contains(v) && whitePlayerSelected != &whiteAIButton) {
				// Highlight whiteAIButton
				whiteAIButton.setTexture(AIHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (blackAIButton.getGlobalBounds().contains(v) && blackPlayerSelected != &blackAIButton) {
				// Highlight blackAIButton
				blackAIButton.setTexture(AIHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if(!buttonHovered) {
				// If nothing hovered
				clearButtonHighlights();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (whiteHumanButton.getGlobalBounds().contains(v)) {
				// Select whiteHumanButton
				whiteHumanButton.setTexture(humanSelectedButtonTexture, true);
				whitePlayerSelected = &whiteHumanButton;
			} else if (blackHumanButton.getGlobalBounds().contains(v)) {
				// Select blackHumanButton
				blackHumanButton.setTexture(humanSelectedButtonTexture, true);
				blackPlayerSelected = &blackHumanButton;
			} else if (whiteAIButton.getGlobalBounds().contains(v)) {
				// Select whiteAIButton
				whiteAIButton.setTexture(AISelectedButtonTexture, true);
				whitePlayerSelected = &whiteAIButton;
			} else if (blackAIButton.getGlobalBounds().contains(v)) {
				// Select blackAIButton
				blackAIButton.setTexture(AISelectedButtonTexture, true);
				blackPlayerSelected = &blackAIButton;
			}
			return 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return -1;
		}
	}
	return 1;
}

void NewGameScreen::clearButtonHighlights()
{
	if (whitePlayerSelected != &whiteHumanButton)
		whiteHumanButton.setTexture(humanButtonTexture);
	if (blackPlayerSelected != &blackHumanButton)
		blackHumanButton.setTexture(humanButtonTexture);
	if (whitePlayerSelected != &whiteAIButton)
		whiteAIButton.setTexture(AIButtonTexture);
	if (blackPlayerSelected != &blackAIButton)
		blackAIButton.setTexture(AIButtonTexture);
}


void NewGameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0, 0));
	for (auto element : elements) {
		window.draw(*element);
	}
	window.draw(whitePlayerText);
	window.draw(blackPlayerText);
	window.display();
}