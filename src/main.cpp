#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "headers/base_screen.hpp"
#include "headers/game_screen.hpp"
#include "headers/menu_screen.hpp"
#include "headers/new_game_screen.hpp"

int main(int argc, char** argv)
{
	// Applications variables
	int screen = 0;
	std::vector<BaseScreen*> screens;

	// Window creation
	sf::RenderWindow window(sf::VideoMode(1400, 850), "Chess game", 4);

	// Screens
	GameScreen gameScreen(window);
	NewGameScreen newGameScreen(&gameScreen, window); // Must be able to modify
	MenuScreen menuScreen(&gameScreen, &newGameScreen, window);

	screens.push_back(&menuScreen);
	screens.push_back(&newGameScreen);
	screens.push_back(&gameScreen);

	// Mouse cursor no more visible
	window.setMouseCursorVisible(true);

	// Load Screen contents, needs to be done only once
	for (auto s : screens)
	{
		s->loadContent();
	}

	// Main loop
	while (screen >= 0)
	{
		// Updates screen elements
		screen = screens[screen]->update();

		if (screen >= 0) {

			// Draws all sprites
			screens[screen]->draw();
		}
	}

	return EXIT_SUCCESS;
}
