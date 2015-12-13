#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "../headers/base_screen.hpp"
#include "game_screen.hpp"
#include "new_game_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
public:
    /*
    Menu screen needs to be able to use gameScreens initializer
    and newGameScreens initializer
    */
    MenuScreen(GameScreen* g, NewGameScreen* n, sf::RenderWindow &w);
	virtual void loadContent(void);
	virtual int update();
    virtual void draw();

private:
	sf::RenderWindow &window;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Button continueButton;
	Button newGameButton;
	Button loadGameButton;
	Button exitButton;

	// Background music
	sf::SoundBuffer backgroundMusicBuffer;
	sf::Sound backgroundMusic;

	// Containers for Button elements for iteration
	std::vector<Button*> elements;

	// Utility functions
	void clearButtonHighlights();
	void showContinueButton(); // Moves all buttons down to make room for continueButton
	void hideContinueButton(); // Moves buttons back up
	bool isGameActive();

	GameScreen* gameScreen;
	NewGameScreen* newGameScreen;
};

#endif /* MENU_SCREEN_H */