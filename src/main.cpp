#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/screens.hpp"

int main(int argc, char** argv)
{
    //Applications variables
    BaseScreen* screen = new MenuScreen();

    //Window creation
    sf::RenderWindow App(sf::VideoMode(640, 480, 32), "Best chess game ever");

    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //Main loop
    while (screen != NULL)
    {
        screen = screen->Run(App);
    }

    return EXIT_SUCCESS;
}