#ifndef NEW_GAME_SCREEN_H
#define NEW_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "base_screen.hpp"
#include "game_screen.hpp"

enum PlayerType {
	Human = 0,
	AI = 1
};

class NewGameScreen : public BaseScreen
{
public:
	NewGameScreen();

	// New game screen needs to be able to use gameScreens initializer
    NewGameScreen(GameScreen* g);
	void loadContent(void);
	int update(sf::RenderWindow &window);
	void createGame();
	void changeWhitePlayerType(PlayerType type);
	void changeBlackPlayerType(PlayerType type);
	void clearButtonHighlights();
    void draw(sf::RenderWindow &window);

private:
	// Containers for sprite elements so it can be looped
	std::vector<sf::Drawable*> elements;
	std::vector<sf::Drawable*> whiteInformationElements;
	std::vector<sf::Drawable*> blackInformationElements;

	GameScreen* gameScreen;

	// Player texts
	sf::Font font;
	sf::Text whitePlayerText;
	sf::Text blackPlayerText;

	// Player name texts
	sf::Text whiteNameText;
	sf::Text blackNameText;

	bool whiteNameClicked;
	bool blackNameClicked;

	sf::String whiteNameString;
	sf::String blackNameString;

	sf::Text whitePlayerName;
	sf::Text blackPlayerName;

	// Player buttons
	sf::Texture humanButtonTexture;
	sf::Texture humanHighlightedButtonTexture;
	sf::Texture humanSelectedButtonTexture;

	sf::Texture AIButtonTexture;
	sf::Texture AIHighlightedButtonTexture;
	sf::Texture AISelectedButtonTexture;

	sf::Sprite whiteHumanButton;
	sf::Sprite blackHumanButton;

	sf::Sprite whiteAIButton;
	sf::Sprite blackAIButton;

	PlayerType whitePlayerSelected;
	PlayerType blackPlayerSelected;

	// Levels
	sf::Texture levelOneTexture;
	sf::Texture levelTwoTexture;
	sf::Texture levelThreeTexture;
	sf::Texture levelFourTexture;
	sf::Texture levelFiveTexture;

	sf::Texture levelOneHighlightedTexture;
	sf::Texture levelTwoHighlightedTexture;
	sf::Texture levelThreeHighlightedTexture;
	sf::Texture levelFourHighlightedTexture;
	sf::Texture levelFiveHighlightedTexture;

	sf::Texture levelOneSelectedTexture;
	sf::Texture levelTwoSelectedTexture;
	sf::Texture levelThreeSelectedTexture;
	sf::Texture levelFourSelectedTexture;
	sf::Texture levelFiveSelectedTexture;

	sf::Sprite whiteLevelOneButton;
	sf::Sprite whiteLevelTwoButton;
	sf::Sprite whiteLevelThreeButton;
	sf::Sprite whiteLevelFourButton;
	sf::Sprite whiteLevelFiveButton;

	sf::Sprite blackLevelOneButton;
	sf::Sprite blackLevelTwoButton;
	sf::Sprite blackLevelThreeButton;
	sf::Sprite blackLevelFourButton;
	sf::Sprite blackLevelFiveButton;

	int whiteLevel;
	int blackLevel;

	// Play
	sf::Texture playButtonTexture;
	sf::Texture playHighlightedButtonTexture;

	sf::Sprite playButton;
};

#endif
