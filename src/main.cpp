#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "headers/screens.hpp"
#include "./headers/base_screen.hpp"
#include "./headers/game_screen.hpp"
#include "./headers/menu_screen.hpp"

int main(int argc, char** argv)
{

    // Applications variables
	int screen = 0;
	std::vector<BaseScreen*> Screens;
	
	// Screens
	MenuScreen menuScreen;
	GameScreen gameScreen;

	Screens.push_back(&menuScreen);
	Screens.push_back(&gameScreen);

    // Window creation
    sf::RenderWindow App(sf::VideoMode(800, 800), "Chess game");
	
    // Mouse cursor no more visible
    App.setMouseCursorVisible(true);
	
	// Load Screen contents, needs to be only once
	for (auto s : Screens)
	{
		s->LoadContent();
	}

    // Main loop
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App);
    }
	
    return EXIT_SUCCESS;
}