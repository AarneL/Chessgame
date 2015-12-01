#ifndef NEW_GAME_SCREEN_H
#define NEW_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "base_screen.hpp"
#include "game_screen.hpp"
#include "button.hpp"
#include "text.hpp"
#include "object.hpp"
#include "player.hpp"

enum PlayerType {
	Human = 0,
	AI = 1
};

class NewGameScreen : public BaseScreen
{
public:
	// New game screen needs to be able to use gameScreens initializer
    NewGameScreen(GameScreen* g, sf::RenderWindow &w);
	void loadContent(void);
	int update();
	void createGame();
	void selectLevel(Button* button, ColorType color);
	void changePlayerType(PlayerType type, ColorType color);
	void clearButtonHighlights();
    void draw();

private:
	sf::RenderWindow &window;

	GameScreen* gameScreen;

	// Vector for all elements to draw (buttons, texts etc..)
	std::vector<Object*> elements;

	// Player texts
	Text whiteText;
	Text blackText;

	// Line between colors
	sf::RectangleShape line;

	// Player name texts
	Text whiteNameText;
	Text blackNameText;
	Text whitePlayerName;
	Text blackPlayerName;

	sf::String whiteNameString;
	sf::String blackNameString;

	// Player types
	PlayerType whitePlayerSelected;
	PlayerType blackPlayerSelected;

	// Player levels
	int whiteLevel;
	int blackLevel;

	Button* currentWhiteLevel;
	Button* currentBlackLevel;

	// Player buttons
	Button whiteHumanButton;
	Button blackHumanButton;

	Button whiteAIButton;
	Button blackAIButton;

	// Levels
	Button whiteLevelOneButton;
	Button whiteLevelTwoButton;
	Button whiteLevelThreeButton;
	Button whiteLevelFourButton;
	Button whiteLevelFiveButton;

	Button blackLevelOneButton;
	Button blackLevelTwoButton;
	Button blackLevelThreeButton;
	Button blackLevelFourButton;
	Button blackLevelFiveButton;

	// Play button
	Button playButton;
};

#endif
