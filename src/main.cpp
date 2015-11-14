#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "headers/screens.hpp"
#include "headers/base_screen.hpp"
#include "headers/game_screen.hpp"
#include "headers/menu_screen.hpp"
#include "headers/options_screen.hpp"
//#include "headers/new_game_screen.hpp"

int main(int argc, char** argv)
{
    // Applications variables
	int screen = 0;
	std::vector<BaseScreen*> screens;
	sf::Event event;

	// Screens
	MenuScreen menuScreen;
    //NewGameScreen newGameScreen;
	GameScreen gameScreen;
	OptionsScreen optionsScreen;

	screens.push_back(&menuScreen);
    //screens.push_back(&newGameScreen);
	screens.push_back(&gameScreen);
	screens.push_back(&optionsScreen);

    // Window creation
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess game");

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
		// Update window if event occurs, if screen is already -1 -> break the loop
		while (window.pollEvent(event) && screen != -1) {
		
			// Close whole program
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = -1;
				break;
			}
			
			// Updates screen elements
			screen = screens[screen]->update(window, event);
		}

		if (screen >= 0) {
			
			// Draws all sprites
            screens[screen]->draw(window);
        }
    }

    return EXIT_SUCCESS;
}