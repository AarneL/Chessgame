#include "../headers/new_game_screen.hpp"
#include "../headers/game_screen.hpp"
#include "../headers/base_screen.hpp"
#include "../headers/human.hpp"
#include "../headers/ai.hpp"
#include "../headers/player.hpp"
#include "../headers/button.hpp"

NewGameScreen::NewGameScreen(GameScreen* g, sf::RenderWindow &w) : window(w)
{
	gameScreen = g;
}

void NewGameScreen::initialize()
/*
	This method is used every time when the newgame screen is opened
*/
{
	// Default names
	whiteNameString = "Player1";
	whitePlayerName.setString(whiteNameString);
	blackNameString = "Player2";
	blackPlayerName.setString(blackNameString);

	// Clear all button selections
	clearButtonSelections();

	// Set white human selected as default
	whitePlayerSelected = HumanType;
	whiteHumanButton.setState(Selected);

	// Set black AI selected as default
	blackPlayerSelected = AIType;
	blackAIButton.setState(Selected);

	// Set level 1 as default
	whiteLevel = 1;
	currentWhiteLevel = &whiteLevelOneButton;
	whiteLevelOneButton.setState(Selected);

	blackLevel = 1;
	currentBlackLevel = &blackLevelOneButton;
	blackLevelOneButton.setState(Selected);
}

void NewGameScreen::loadContent(void)
{
	sf::Vector2u size = window.getSize();
	// Half of the window width
	int half = size.x / 2;
	// Third of half
	int thirdOfHalf = half / 3;
	// Fifth of half
	int fifthOfHalf = half / 5;
	// Eighth of height
	int eighthOfHeight = size.y / 8;

	// Player texts
	int topMargin = eighthOfHeight; // Text top margin

	whiteText.loadContent("media/img/Calibri.ttf", 70, sf::Vector2f(thirdOfHalf, topMargin), true);
	whiteText.setString("White");
	elements.push_back(&whiteText);

	blackText.loadContent("media/img/Calibri.ttf", 70, sf::Vector2f(half + thirdOfHalf, topMargin), true);
	blackText.setString("Black");
	elements.push_back(&blackText);

	// Line between colors
	line.setSize(sf::Vector2f(eighthOfHeight * 6, 2));
	line.setPosition(half, 50);
	line.rotate(90);

	// Player name texts
	int nameTopMargin = eighthOfHeight * 5;

	whiteNameText.loadContent("media/img/Calibri.ttf", 40, sf::Vector2f(fifthOfHalf, nameTopMargin), true);
	whiteNameText.setString("Name:");
	elements.push_back(&whiteNameText);

	whitePlayerName.loadContent("media/img/Calibri.ttf", 38, sf::Vector2f(fifthOfHalf + 150, nameTopMargin), true);
	whitePlayerName.setString(whiteNameString);
	elements.push_back(&whitePlayerName);

	blackNameText.loadContent("media/img/Calibri.ttf", 40, sf::Vector2f(half + fifthOfHalf, nameTopMargin), false);
	blackNameText.setString("Name:");
	elements.push_back(&blackNameText);

	blackPlayerName.loadContent("media/img/Calibri.ttf", 38, sf::Vector2f(half + fifthOfHalf + 150, nameTopMargin), false);
	blackPlayerName.setString(blackNameString);
	elements.push_back(&blackPlayerName);

	// Player buttons
	int buttonTopMargin = eighthOfHeight * 3;

	whiteHumanButton.loadContent("media/img/humanButton.png", "media/img/humanHighlightedButton.png", "media/img/humanSelectedButton.png", sf::Vector2f(fifthOfHalf, buttonTopMargin), true);
	elements.push_back(&whiteHumanButton);

	blackHumanButton.loadContent("media/img/humanButton.png", "media/img/humanHighlightedButton.png", "media/img/humanSelectedButton.png", sf::Vector2f(half + fifthOfHalf, buttonTopMargin), true);
	elements.push_back(&blackHumanButton);

	whiteAIButton.loadContent("media/img/computerButton.png", "media/img/computerHighlightedButton.png", "media/img/computerSelectedButton.png", sf::Vector2f(fifthOfHalf + 200, buttonTopMargin), true);
	elements.push_back(&whiteAIButton);

	blackAIButton.loadContent("media/img/computerButton.png", "media/img/computerHighlightedButton.png", "media/img/computerSelectedButton.png", sf::Vector2f(half + fifthOfHalf + 200, buttonTopMargin), true);
	elements.push_back(&blackAIButton);

	// levels
	int levelTopMargin = eighthOfHeight * 5;

	whiteLevelOneButton.loadContent("media/img/level1Button.png", "media/img/level1HighlightedButton.png", "media/img/level1SelectedButton.png", sf::Vector2f(fifthOfHalf, levelTopMargin), false);
	elements.push_back(&whiteLevelOneButton);

	whiteLevelTwoButton.loadContent("media/img/level2Button.png", "media/img/level2HighlightedButton.png", "media/img/level2SelectedButton.png", sf::Vector2f(fifthOfHalf + 85, levelTopMargin), false);
	elements.push_back(&whiteLevelTwoButton);

	whiteLevelThreeButton.loadContent("media/img/level3Button.png", "media/img/level3HighlightedButton.png", "media/img/level3SelectedButton.png", sf::Vector2f(fifthOfHalf + 170, levelTopMargin), false);
	elements.push_back(&whiteLevelThreeButton);

	whiteLevelFourButton.loadContent("media/img/level4Button.png", "media/img/level4HighlightedButton.png", "media/img/level4SelectedButton.png", sf::Vector2f(fifthOfHalf + 255, levelTopMargin), false);
	elements.push_back(&whiteLevelFourButton);

	whiteLevelFiveButton.loadContent("media/img/level5Button.png", "media/img/level5HighlightedButton.png", "media/img/level5SelectedButton.png", sf::Vector2f(fifthOfHalf + 345, levelTopMargin), false);
	elements.push_back(&whiteLevelFiveButton);

	blackLevelOneButton.loadContent("media/img/level1Button.png", "media/img/level1HighlightedButton.png", "media/img/level1SelectedButton.png", sf::Vector2f(half + fifthOfHalf, levelTopMargin), true);
	elements.push_back(&blackLevelOneButton);

	blackLevelTwoButton.loadContent("media/img/level2Button.png", "media/img/level2HighlightedButton.png", "media/img/level2SelectedButton.png", sf::Vector2f(half + fifthOfHalf + 85, levelTopMargin), true);
	elements.push_back(&blackLevelTwoButton);

	blackLevelThreeButton.loadContent("media/img/level3Button.png", "media/img/level3HighlightedButton.png", "media/img/level3SelectedButton.png", sf::Vector2f(half + fifthOfHalf + 170, levelTopMargin), true);
	elements.push_back(&blackLevelThreeButton);

	blackLevelFourButton.loadContent("media/img/level4Button.png", "media/img/level4HighlightedButton.png", "media/img/level4SelectedButton.png", sf::Vector2f(half + fifthOfHalf + 255, levelTopMargin), true);
	elements.push_back(&blackLevelFourButton);

	blackLevelFiveButton.loadContent("media/img/level5Button.png", "media/img/level5HighlightedButton.png", "media/img/level5SelectedButton.png", sf::Vector2f(half + fifthOfHalf + 345, levelTopMargin), true);
	elements.push_back(&blackLevelFiveButton);

	// Play button
	playButton.loadContent("media/img/playButton.png", "media/img/playHighlightedButton.png", "", sf::Vector2f(half - 63, eighthOfHeight * 7), true);
	elements.push_back(&playButton);

	// Background
	backgroundTexture.loadFromFile("media/img/game_screen_background.jpg");
	background.setTexture(backgroundTexture);

	// Main menu button
	mainMenuButton.loadContent("media/img/mainMenuButton.png", "media/img/mainMenuHighlightedButton.png", "", sf::Vector2f(100, 750), true);
	elements.push_back(&mainMenuButton);
}


int NewGameScreen::update()
{
	sf::Event event;
	while(window.pollEvent(event)) {
		sf::Vector2f v = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (event.type == sf::Event::MouseMoved)
		{
			bool buttonHovered = false;
			if (whiteHumanButton.containsMousePos(v) && whitePlayerSelected != HumanType) {
				// Highlight whiteHumanButton
				whiteHumanButton.setState(Highlighted);
				buttonHovered = true;
			} else if (blackHumanButton.containsMousePos(v) && blackPlayerSelected != HumanType) {
				// Highlight blackHumanButton
				blackHumanButton.setState(Highlighted);
				buttonHovered = true;
			} else if (whiteAIButton.containsMousePos(v) && whitePlayerSelected != AIType) {
				// Highlight whiteAIButton
				whiteAIButton.setState(Highlighted);
				buttonHovered = true;
			} else if (blackAIButton.containsMousePos(v) && blackPlayerSelected != AIType) {
				// Highlight blackAIButton
				blackAIButton.setState(Highlighted);
				buttonHovered = true;
			}
			if (whitePlayerSelected == AIType) {
				if (whiteLevelOneButton.containsMousePos(v) && whiteLevel != 1) {
					whiteLevelOneButton.setState(Highlighted);
					buttonHovered = true;
				} else if (whiteLevelTwoButton.containsMousePos(v) && whiteLevel != 2) {
					whiteLevelTwoButton.setState(Highlighted);
					buttonHovered = true;
				} else if (whiteLevelThreeButton.containsMousePos(v) && whiteLevel != 3) {
					whiteLevelThreeButton.setState(Highlighted);
					buttonHovered = true;
				} else if (whiteLevelFourButton.containsMousePos(v) && whiteLevel != 4) {
					whiteLevelFourButton.setState(Highlighted);
					buttonHovered = true;
				} else if (whiteLevelFiveButton.containsMousePos(v) && whiteLevel != 5) {
					whiteLevelFiveButton.setState(Highlighted);
					buttonHovered = true;
				}
			} else {
				if (whitePlayerName.containsMousePos(v) && whitePlayerName.getState() != Selected) {
					whitePlayerName.setState(Highlighted);
					buttonHovered = true;
				}
			}
			if (blackPlayerSelected == AIType) {
				if (blackLevelOneButton.containsMousePos(v) && blackLevel != 1) {
					blackLevelOneButton.setState(Highlighted);
					buttonHovered = true;
				} else if (blackLevelTwoButton.containsMousePos(v) && blackLevel != 2) {
					blackLevelTwoButton.setState(Highlighted);
					buttonHovered = true;
				} else if (blackLevelThreeButton.containsMousePos(v) && blackLevel != 3) {
					blackLevelThreeButton.setState(Highlighted);
					buttonHovered = true;
				} else if (blackLevelFourButton.containsMousePos(v) && blackLevel != 4) {
					blackLevelFourButton.setState(Highlighted);
					buttonHovered = true;
				} else if (blackLevelFiveButton.containsMousePos(v) && blackLevel != 5) {
					blackLevelFiveButton.setState(Highlighted);
					buttonHovered = true;
				}
			} else {
				if (blackPlayerName.containsMousePos(v) && blackPlayerName.getState() != Selected) {
					blackPlayerName.setState(Highlighted);
					buttonHovered = true;
				}
			}
			if (playButton.containsMousePos(v)) {
				playButton.setState(Highlighted);
				buttonHovered = true;
			} else if (mainMenuButton.containsMousePos(v)) {
				mainMenuButton.setState(Highlighted);
				buttonHovered = true;
			}
			if (!buttonHovered) {
				// If nothing hovered
				clearButtonHighlights();
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			whitePlayerName.setState(Normal);
			blackPlayerName.setState(Normal);
			if (whiteHumanButton.containsMousePos(v) && whitePlayerSelected != HumanType) {
				// Select white human
				changePlayerType(HumanType, White);
			} else if (blackHumanButton.containsMousePos(v) && blackPlayerSelected != HumanType) {
				// Select black human
				changePlayerType(HumanType, Black);
			} else if (whiteAIButton.containsMousePos(v) && whitePlayerSelected != AIType) {
				// Select white AI
				changePlayerType(AIType, White);
			} else if (blackAIButton.containsMousePos(v) && blackPlayerSelected != AIType) {
				// Select black AI
				changePlayerType(AIType, Black);
			}
			if (whitePlayerSelected == AIType) {
				if (whiteLevelOneButton.containsMousePos(v) && whiteLevel != 1) {
					whiteLevel = 1;
					selectLevel(&whiteLevelOneButton, White);
				} else if (whiteLevelTwoButton.containsMousePos(v) && whiteLevel != 2) {
					whiteLevel = 2;
					selectLevel(&whiteLevelTwoButton, White);
				} else if (whiteLevelThreeButton.containsMousePos(v) && whiteLevel != 3) {
					whiteLevel = 3;
					selectLevel(&whiteLevelThreeButton, White);
				} else if (whiteLevelFourButton.containsMousePos(v) && whiteLevel != 4) {
					whiteLevel = 4;
					selectLevel(&whiteLevelFourButton, White);
				} else if (whiteLevelFiveButton.containsMousePos(v) && whiteLevel != 5) {
					whiteLevel = 5;
					selectLevel(&whiteLevelFiveButton, White);
				}
			} else {
				if (whiteNameText.containsMousePos(v) || whitePlayerName.containsMousePos(v)) {
					whitePlayerName.setState(Selected);
					blackPlayerName.setState(Normal);
				}
			}
			if (blackPlayerSelected == AIType) {
				if (blackLevelOneButton.containsMousePos(v) && blackLevel != 1) {
					blackLevel = 1;
					selectLevel(&blackLevelOneButton, Black);
				} else if (blackLevelTwoButton.containsMousePos(v) && blackLevel != 2) {
					blackLevel = 2;
					selectLevel(&blackLevelTwoButton, Black);
				} else if (blackLevelThreeButton.containsMousePos(v) && blackLevel != 3) {
					blackLevel = 3;
					selectLevel(&blackLevelThreeButton, Black);
				} else if (blackLevelFourButton.containsMousePos(v) && blackLevel != 4) {
					blackLevel = 4;
					selectLevel(&blackLevelFourButton, Black);
				} else if (blackLevelFiveButton.containsMousePos(v) && blackLevel != 5) {
					blackLevel = 5;
					selectLevel(&blackLevelFiveButton, Black);
				}
			} else {
				if (blackNameText.containsMousePos(v) || blackPlayerName.containsMousePos(v)) {
					blackPlayerName.setState(Selected);
					whitePlayerName.setState(Normal);
				}
			}
			if (playButton.containsMousePos(v)) {
				createGame();
				return 2; // Goes to gamescreen
			} else if (mainMenuButton.containsMousePos(v)) {
				return 0;
			}
			return 1;
		}
		else if (event.type == sf::Event::TextEntered) {
			if (whitePlayerName.getState() == Selected) {
				if (event.key.code == 8) {
					if (whiteNameString.getSize() > 0) {
						whiteNameString.erase(whiteNameString.getSize() - 1);
					}
				}
				else if (event.key.code == 10) {
					whitePlayerName.setState(Normal);
				}
				else if (event.text.unicode < 128) {
					whiteNameString.insert(whiteNameString.getSize(), event.text.unicode);
				}
				whitePlayerName.setString(whiteNameString);
			}
			else if (blackPlayerName.getState() == Selected) {
				if (event.key.code == 8) {
					if (blackNameString.getSize() > 0) {
						blackNameString.erase(blackNameString.getSize() - 1);
					}
				}
				else if (event.key.code == 10) {
					blackPlayerName.setState(Normal);
				}
				else if (event.text.unicode < 128) {
					blackNameString.insert(blackNameString.getSize(), event.text.unicode);
				}
				blackPlayerName.setString(blackNameString);
			}
		}
		else if (event.type == sf::Event::Closed) {
			window.close();
			return -1;
		}
	}
	return 1;
}


void NewGameScreen::createGame() {
	if (whitePlayerSelected == AIType) {
		whiteNameString = "Computer";
	}
	if (blackPlayerSelected == AIType) {
		blackNameString = "Computer";
	}
	gameScreen->initialize(whiteNameString, whiteLevel, blackNameString, blackLevel);
}


void NewGameScreen::selectLevel(Button* button, ColorType color)
{
	button->setState(Selected);
	if (color == White) {
		currentWhiteLevel->setState(Normal);
		currentWhiteLevel = button;
	}
	else {
		currentBlackLevel->setState(Normal);
		currentBlackLevel = button;
	}
}

void NewGameScreen::changePlayerType(PlayerType type, ColorType color)
{
	if (color == White) {
		whitePlayerSelected = type;
		if (type == HumanType) {
			whiteHumanButton.setState(Selected);
			whiteAIButton.setState(Normal);
			// Dont draw level elements
			whiteLevelOneButton.drawObject = false;
			whiteLevelTwoButton.drawObject = false;
			whiteLevelThreeButton.drawObject = false;
			whiteLevelFourButton.drawObject = false;
			whiteLevelFiveButton.drawObject = false;
			// Draw name text elements
			whiteNameText.drawObject = true;
			whitePlayerName.drawObject = true;

		} else if (type == AIType) {
			whiteAIButton.setState(Selected);
			whiteHumanButton.setState(Normal);
			// Draw level elements
			whiteLevelOneButton.drawObject = true;
			whiteLevelTwoButton.drawObject = true;
			whiteLevelThreeButton.drawObject = true;
			whiteLevelFourButton.drawObject = true;
			whiteLevelFiveButton.drawObject = true;
			// Dont draw name text elements
			whiteNameText.drawObject = false;
			whitePlayerName.drawObject = false;
		}
	}
	else {
		blackPlayerSelected = type;
		if (type == HumanType) {
			blackHumanButton.setState(Selected);
			blackAIButton.setState(Normal);
			// Dont draw level elements
			blackLevelOneButton.drawObject = false;
			blackLevelTwoButton.drawObject = false;
			blackLevelThreeButton.drawObject = false;
			blackLevelFourButton.drawObject = false;
			blackLevelFiveButton.drawObject = false;
			// Draw name text elements
			blackNameText.drawObject = true;
			blackPlayerName.drawObject = true;

		} else if (type == AIType) {
			blackAIButton.setState(Selected);
			blackHumanButton.setState(Normal);
			// Draw level elements
			blackLevelOneButton.drawObject = true;
			blackLevelTwoButton.drawObject = true;
			blackLevelThreeButton.drawObject = true;
			blackLevelFourButton.drawObject = true;
			blackLevelFiveButton.drawObject = true;
			// Dont draw name text elements
			blackNameText.drawObject = false;
			blackPlayerName.drawObject = false;
		}
	}
}

void NewGameScreen::clearButtonSelections()
{
	for (auto element : elements) {
		element->setState(Normal);
	}
}

void NewGameScreen::clearButtonHighlights()
{
	for (auto element : elements) {
		if (element->getState() != Selected) {
			element->setState(Normal);
		}
	}
}


void NewGameScreen::draw()
{
	window.clear(sf::Color(0, 0, 0, 0));
	window.draw(background);
	for (auto element : elements) {
		element->draw(window);
	}
	window.draw(line);
	window.display();
}