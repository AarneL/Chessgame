#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "headers/screens.hpp"
#include "./headers/base_screen.hpp"
#include "./headers/game_screen.hpp"
#include "./headers/menu_screen.hpp"
#include "./headers/options_screen.hpp"

int main(int argc, char** argv)
{

    // Applications variables
	int screen = 0;
	std::vector<BaseScreen*> screens;

	// screens
	MenuScreen menuScreen;
	GameScreen gameScreen;
	OptionsScreen optionsScreen;
	
	screens.push_back(&menuScreen);
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
        screen = screens[screen]->update(window);
        if (screen >= 0) {
            screens[screen]->draw(window);
        }
    }

    return EXIT_SUCCESS;
}