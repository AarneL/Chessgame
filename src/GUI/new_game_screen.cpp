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
	whiteNameClicked = false;
	blackNameClicked = false;
	// Default types
	whitePlayerSelected = Human;
	blackPlayerSelected = AI;
	// Default names
	whiteNameString = "Player1";
	blackNameString = "Player2";
	// Default levels
	whiteLevel = 1;
	blackLevel = 1;
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
	elements.push_back(&whitePlayerText);

	blackPlayerText.setFont(font);
	blackPlayerText.setCharacterSize(70);
	blackPlayerText.setStyle(sf::Text::Bold);
	blackPlayerText.setString("Black");
	blackPlayerText.setPosition(sf::Vector2f(600 + midMargin, topMargin));
	elements.push_back(&blackPlayerText);

	// Player name texts
	int nameTopMargin = 500;
	int nameMidMargin = 100;

	whiteNameText.setFont(font);
	whiteNameText.setCharacterSize(40);
	whiteNameText.setStyle(sf::Text::Bold);
	whiteNameText.setString("Name:");
	whiteNameText.setPosition(sf::Vector2f(nameMidMargin, nameTopMargin));
	whiteInformationElements.push_back(&whiteNameText);

	whitePlayerName.setFont(font);
	whitePlayerName.setCharacterSize(38);
	whitePlayerName.setString(whiteNameString);
	whitePlayerName.setPosition(sf::Vector2f(nameMidMargin + 150, nameTopMargin));
	whiteInformationElements.push_back(&whitePlayerName);

	blackNameText.setFont(font);
	blackNameText.setCharacterSize(40);
	blackNameText.setStyle(sf::Text::Bold);
	blackNameText.setString("Name:");
	blackNameText.setPosition(sf::Vector2f(600 + nameMidMargin, nameTopMargin));

	blackPlayerName.setFont(font);
	blackPlayerName.setCharacterSize(38);
	blackPlayerName.setString(blackNameString);
	blackPlayerName.setPosition(sf::Vector2f(600 + nameMidMargin + 150, nameTopMargin));

	// Player buttons
	int buttonTopMargin = 300;
	int buttonMidMargin = 100;

	humanButtonTexture.loadFromFile("media/img/humanButton.png");
	humanHighlightedButtonTexture.loadFromFile("media/img/humanHighlightedButton.png");
	humanSelectedButtonTexture.loadFromFile("media/img/humanSelectedButton.png");

	AIButtonTexture.loadFromFile("media/img/computerButton.png");
	AIHighlightedButtonTexture.loadFromFile("media/img/computerHighlightedButton.png");
	AISelectedButtonTexture.loadFromFile("media/img/computerSelectedButton.png");

	// Set white human selected as default
	whiteHumanButton.setTexture(humanSelectedButtonTexture);
	whiteHumanButton.setPosition(sf::Vector2f(buttonMidMargin, buttonTopMargin));
	elements.push_back(&whiteHumanButton);

	blackHumanButton.setTexture(humanButtonTexture);
	blackHumanButton.setPosition(sf::Vector2f(600 + buttonMidMargin, buttonTopMargin));
	elements.push_back(&blackHumanButton);

	whiteAIButton.setTexture(AIButtonTexture);
	whiteAIButton.setPosition(sf::Vector2f(buttonMidMargin + 200, buttonTopMargin));
	elements.push_back(&whiteAIButton);

	// Set black AI selected as default
	blackAIButton.setTexture(AISelectedButtonTexture);
	blackAIButton.setPosition(sf::Vector2f(600 + buttonMidMargin + 200, buttonTopMargin));
	elements.push_back(&blackAIButton);

	// Levels
	int levelTopMargin = 500;
	int levelMidMargin = 100;
	// Normal
	levelOneTexture.loadFromFile("media/img/level1Button.png");
	levelTwoTexture.loadFromFile("media/img/level2Button.png");
	levelThreeTexture.loadFromFile("media/img/level3Button.png");
	levelFourTexture.loadFromFile("media/img/level4Button.png");
	levelFiveTexture.loadFromFile("media/img/level5Button.png");
	// Highlighted
	levelOneHighlightedTexture.loadFromFile("media/img/level1HighlightedButton.png");
	levelTwoHighlightedTexture.loadFromFile("media/img/level2HighlightedButton.png");
	levelThreeHighlightedTexture.loadFromFile("media/img/level3HighlightedButton.png");
	levelFourHighlightedTexture.loadFromFile("media/img/level4HighlightedButton.png");
	levelFiveHighlightedTexture.loadFromFile("media/img/level5HighlightedButton.png");
	// Selected
	levelOneSelectedTexture.loadFromFile("media/img/level1SelectedButton.png");
	levelTwoSelectedTexture.loadFromFile("media/img/level2SelectedButton.png");
	levelThreeSelectedTexture.loadFromFile("media/img/level3SelectedButton.png");
	levelFourSelectedTexture.loadFromFile("media/img/level4SelectedButton.png");
	levelFiveSelectedTexture.loadFromFile("media/img/level5SelectedButton.png");

	whiteLevelOneButton.setTexture(levelOneSelectedTexture);
	whiteLevelOneButton.setPosition(sf::Vector2f(levelMidMargin, levelTopMargin));

	whiteLevelTwoButton.setTexture(levelTwoTexture);
	whiteLevelTwoButton.setPosition(sf::Vector2f(levelMidMargin + 80, levelTopMargin));

	whiteLevelThreeButton.setTexture(levelThreeTexture);
	whiteLevelThreeButton.setPosition(sf::Vector2f(levelMidMargin + 160, levelTopMargin));

	whiteLevelFourButton.setTexture(levelFourTexture);
	whiteLevelFourButton.setPosition(sf::Vector2f(levelMidMargin + 240, levelTopMargin));

	whiteLevelFiveButton.setTexture(levelFiveTexture);
	whiteLevelFiveButton.setPosition(sf::Vector2f(levelMidMargin + 320, levelTopMargin));

	blackLevelOneButton.setTexture(levelOneSelectedTexture);
	blackLevelOneButton.setPosition(sf::Vector2f(600 + levelMidMargin, levelTopMargin));
	blackInformationElements.push_back(&blackLevelOneButton);

	blackLevelTwoButton.setTexture(levelTwoTexture);
	blackLevelTwoButton.setPosition(sf::Vector2f(600 + levelMidMargin + 80, levelTopMargin));
	blackInformationElements.push_back(&blackLevelTwoButton);

	blackLevelThreeButton.setTexture(levelThreeTexture);
	blackLevelThreeButton.setPosition(sf::Vector2f(600 + levelMidMargin + 160, levelTopMargin));
	blackInformationElements.push_back(&blackLevelThreeButton);

	blackLevelFourButton.setTexture(levelFourTexture);
	blackLevelFourButton.setPosition(sf::Vector2f(600 + levelMidMargin + 240, levelTopMargin));
	blackInformationElements.push_back(&blackLevelFourButton);

	blackLevelFiveButton.setTexture(levelFiveTexture);
	blackLevelFiveButton.setPosition(sf::Vector2f(600 + levelMidMargin + 320, levelTopMargin));
	blackInformationElements.push_back(&blackLevelFiveButton);

	// Play button
	playButtonTexture.loadFromFile("media/img/playButton.png");
	playButton.setTexture(playButtonTexture);
	playButton.setPosition(sf::Vector2f(600, 700));
	elements.push_back(&playButton);
}


int NewGameScreen::update(sf::RenderWindow &window)
{
	sf::Event event;
	while(window.pollEvent(event)) {
		sf::Vector2f v = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (event.type == sf::Event::MouseMoved)
		{
			bool buttonHovered = false;
			if (whiteHumanButton.getGlobalBounds().contains(v) && whitePlayerSelected != Human) {
				// Highlight whiteHumanButton
				whiteHumanButton.setTexture(humanHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (blackHumanButton.getGlobalBounds().contains(v) && blackPlayerSelected != Human) {
				// Highlight blackHumanButton
				blackHumanButton.setTexture(humanHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (whiteAIButton.getGlobalBounds().contains(v) && whitePlayerSelected != AI) {
				// Highlight whiteAIButton
				whiteAIButton.setTexture(AIHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (blackAIButton.getGlobalBounds().contains(v) && blackPlayerSelected != AI) {
				// Highlight blackAIButton
				blackAIButton.setTexture(AIHighlightedButtonTexture, true);
				buttonHovered = true;
			} else if (whiteLevelOneButton.getGlobalBounds().contains(v) && whiteLevel != 1) {
				whiteLevelOneButton.setTexture(levelOneHighlightedTexture, true);
				buttonHovered = true;
			} else if (whiteLevelTwoButton.getGlobalBounds().contains(v) && whiteLevel != 2) {
				whiteLevelTwoButton.setTexture(levelTwoHighlightedTexture, true);
				buttonHovered = true;
			} else if (whiteLevelThreeButton.getGlobalBounds().contains(v) && whiteLevel != 3) {
				whiteLevelThreeButton.setTexture(levelThreeHighlightedTexture, true);
				buttonHovered = true;
			} else if (whiteLevelFourButton.getGlobalBounds().contains(v) && whiteLevel != 4) {
				whiteLevelFourButton.setTexture(levelFourHighlightedTexture, true);
				buttonHovered = true;
			} else if (whiteLevelFiveButton.getGlobalBounds().contains(v) && whiteLevel != 5) {
				whiteLevelFiveButton.setTexture(levelFiveHighlightedTexture, true);
				buttonHovered = true;
			} else if (blackLevelOneButton.getGlobalBounds().contains(v) && blackLevel != 1) {
				blackLevelOneButton.setTexture(levelOneHighlightedTexture, true);
				buttonHovered = true;
			} else if (blackLevelTwoButton.getGlobalBounds().contains(v) && blackLevel != 2) {
				blackLevelTwoButton.setTexture(levelTwoHighlightedTexture, true);
				buttonHovered = true;
			} else if (blackLevelThreeButton.getGlobalBounds().contains(v) && blackLevel != 3) {
				blackLevelThreeButton.setTexture(levelThreeHighlightedTexture, true);
				buttonHovered = true;
			} else if (blackLevelFourButton.getGlobalBounds().contains(v) && blackLevel != 4) {
				blackLevelFourButton.setTexture(levelFourHighlightedTexture, true);
				buttonHovered = true;
			} else if (blackLevelFiveButton.getGlobalBounds().contains(v) && blackLevel != 5) {
				blackLevelFiveButton.setTexture(levelFiveHighlightedTexture, true);
				buttonHovered = true;
			} else if(!buttonHovered) {
				// If nothing hovered
				clearButtonHighlights();
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			whiteNameClicked = false;
			blackNameClicked = false;
			if (whiteHumanButton.getGlobalBounds().contains(v) && whitePlayerSelected != Human) {
				// Select white human
				changeWhitePlayerType(Human);
			} else if (blackHumanButton.getGlobalBounds().contains(v) && blackPlayerSelected != Human) {
				// Select black human
				changeBlackPlayerType(Human);
			} else if (whiteAIButton.getGlobalBounds().contains(v) && whitePlayerSelected != AI) {
				// Select white AI
				changeWhitePlayerType(AI);
			} else if (blackAIButton.getGlobalBounds().contains(v) && blackPlayerSelected != AI) {
				// Select black AI
				changeBlackPlayerType(AI);
			} else if (whiteNameText.getGlobalBounds().contains(v) || whitePlayerName.getGlobalBounds().contains(v)) {
				whiteNameClicked = true;
			} else if (blackNameText.getGlobalBounds().contains(v) || blackPlayerName.getGlobalBounds().contains(v)) {
				blackNameClicked = true;
			} else if (whiteLevelOneButton.getGlobalBounds().contains(v)) {
				whiteLevel = 1;
				whiteLevelOneButton.setTexture(levelOneSelectedTexture, true);
			} else if (whiteLevelTwoButton.getGlobalBounds().contains(v)) {
				whiteLevel = 2;
				whiteLevelTwoButton.setTexture(levelTwoSelectedTexture, true);
			} else if (whiteLevelThreeButton.getGlobalBounds().contains(v)) {
				whiteLevel = 3;
				whiteLevelThreeButton.setTexture(levelThreeSelectedTexture, true);
			} else if (whiteLevelFourButton.getGlobalBounds().contains(v)) {
				whiteLevel = 4;
				whiteLevelFourButton.setTexture(levelFourSelectedTexture, true);
			} else if (whiteLevelFiveButton.getGlobalBounds().contains(v)) {
				whiteLevel = 5;
				whiteLevelFiveButton.setTexture(levelFiveSelectedTexture, true);
			} else if (blackLevelOneButton.getGlobalBounds().contains(v)) {
				blackLevel = 1;
				blackLevelOneButton.setTexture(levelOneSelectedTexture, true);
			} else if (blackLevelTwoButton.getGlobalBounds().contains(v)) {
				blackLevel = 2;
				blackLevelTwoButton.setTexture(levelTwoSelectedTexture, true);
			} else if (blackLevelThreeButton.getGlobalBounds().contains(v)) {
				blackLevel = 3;
				blackLevelThreeButton.setTexture(levelThreeSelectedTexture, true);
			} else if (blackLevelFourButton.getGlobalBounds().contains(v)) {
				blackLevel = 4;
				blackLevelFourButton.setTexture(levelFourSelectedTexture, true);
			} else if (blackLevelFiveButton.getGlobalBounds().contains(v)) {
				blackLevel = 5;
				blackLevelFiveButton.setTexture(levelFiveSelectedTexture, true);
			} else if (playButton.getGlobalBounds().contains(v)) {
				createGame();
				return 2;
			}
			return 1;
		}
		else if (event.type == sf::Event::TextEntered) {
			if (whiteNameClicked) {
				if (event.key.code == 8) {
					if (whiteNameString.getSize() > 0) {
						whiteNameString.erase(whiteNameString.getSize() - 1);
					}
				}
				else if (event.text.unicode < 128) {
					whiteNameString.insert(whiteNameString.getSize(), event.text.unicode);
				}
				whitePlayerName.setString(whiteNameString);
			}
			else if (blackNameClicked) {
				if (event.key.code == 8) {
					if (blackNameString.getSize() > 0) {
						blackNameString.erase(blackNameString.getSize() - 1);
					}
				}
				else if (event.text.unicode < 128) {
					blackNameString.insert(blackNameString.getSize(), event.text.unicode);
				}
				blackPlayerName.setString(blackNameString);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return -1;
		}
	}
	return 1;
}


void NewGameScreen::createGame() {
	if (whitePlayerSelected == AI) {
		whiteNameString = "Computer";
	}
	if (blackPlayerSelected == AI) {
		blackNameString = "Computer";
	}
	gameScreen->initialize(whiteNameString, whiteLevel, blackNameString, blackLevel);
}


void NewGameScreen::changeWhitePlayerType(PlayerType type)
{
	whitePlayerSelected = type;
	if (type == Human) {
		whiteHumanButton.setTexture(humanSelectedButtonTexture, true);
		// Remove levels from whiteInformationElements
		whiteInformationElements.erase(whiteInformationElements.end() - 5, whiteInformationElements.end());
		// Add player name element to whiteInformationElements
		whiteInformationElements.push_back(&whiteNameText);
		whiteInformationElements.push_back(&whitePlayerName);
	} else if (type == AI) {
		whiteAIButton.setTexture(AISelectedButtonTexture, true);
		// Remove player name elements from whiteInformationElements
		whiteInformationElements.erase(whiteInformationElements.end() - 2, whiteInformationElements.end());
		// Add level elements to whiteInformationElements
		whiteInformationElements.push_back(&whiteLevelOneButton);
		whiteInformationElements.push_back(&whiteLevelTwoButton);
		whiteInformationElements.push_back(&whiteLevelThreeButton);
		whiteInformationElements.push_back(&whiteLevelFourButton);
		whiteInformationElements.push_back(&whiteLevelFiveButton);
	}
}


void NewGameScreen::changeBlackPlayerType(PlayerType type)
{
	blackPlayerSelected = type;
	if (type == Human) {
		blackHumanButton.setTexture(humanSelectedButtonTexture, true);
		// Remove levels from blackInformationElements
		blackInformationElements.erase(blackInformationElements.end() - 5, blackInformationElements.end());
		// Add player name element to blackInformationElements
		blackInformationElements.push_back(&blackNameText);
		blackInformationElements.push_back(&blackPlayerName);
	} else if (type == AI) {
		blackAIButton.setTexture(AISelectedButtonTexture, true);
		// Remove player name elements from blackInformationElements
		blackInformationElements.erase(blackInformationElements.end() - 2, blackInformationElements.end());
		// Add level elements to blackInformationElements
		blackInformationElements.push_back(&blackLevelOneButton);
		blackInformationElements.push_back(&blackLevelTwoButton);
		blackInformationElements.push_back(&blackLevelThreeButton);
		blackInformationElements.push_back(&blackLevelFourButton);
		blackInformationElements.push_back(&blackLevelFiveButton);
	}
}


void NewGameScreen::clearButtonHighlights()
{
	if (whitePlayerSelected != Human)
		whiteHumanButton.setTexture(humanButtonTexture, true);
	if (blackPlayerSelected != Human)
		blackHumanButton.setTexture(humanButtonTexture, true);
	if (whitePlayerSelected != AI)
		whiteAIButton.setTexture(AIButtonTexture, true);
	if (blackPlayerSelected != AI)
		blackAIButton.setTexture(AIButtonTexture, true);
	if (whiteLevel != 1)
		whiteLevelOneButton.setTexture(levelOneTexture, true);
	if (whiteLevel != 2)
		whiteLevelTwoButton.setTexture(levelTwoTexture, true);
	if (whiteLevel != 3)
		whiteLevelThreeButton.setTexture(levelThreeTexture, true);
	if (whiteLevel != 4)
		whiteLevelFourButton.setTexture(levelFourTexture, true);
	if (whiteLevel != 5)
		whiteLevelFiveButton.setTexture(levelFiveTexture, true);
	if (blackLevel != 1)
		blackLevelOneButton.setTexture(levelOneTexture, true);
	if (blackLevel != 2)
		blackLevelTwoButton.setTexture(levelTwoTexture, true);
	if (blackLevel != 3)
		blackLevelThreeButton.setTexture(levelThreeTexture, true);
	if (blackLevel != 4)
		blackLevelFourButton.setTexture(levelFourTexture, true);
	if (blackLevel != 5)
		blackLevelFiveButton.setTexture(levelFiveTexture, true);
}


void NewGameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0, 0));
	for (auto element : elements) {
		window.draw(*element);
	}
	for (auto element : whiteInformationElements) {
		window.draw(*element);
	}
	for (auto element : blackInformationElements) {
		window.draw(*element);
	}
	window.display();
}