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
	int previousScreen = 0;
	std::vector<BaseScreen*> screens;

	// Window creation
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
	}

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(modes[2]), "Chess game", 4); // Last parameter makes window unresizable

	// Screens
	GameScreen gameScreen(window);
	MenuScreen menuScreen(&gameScreen, window);
	NewGameScreen newGameScreen(&gameScreen, window); // Must be able to modify

	screens.push_back(&menuScreen);
	screens.push_back(&newGameScreen);
	screens.push_back(&gameScreen);

	// Mouse cursor no more visible
	window.setMouseCursorVisible(true);

	// Load Screen contents, needs to be only once
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