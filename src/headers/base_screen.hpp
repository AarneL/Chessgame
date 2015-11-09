#ifndef BASESCREEN_H
#define BASESCREEN_H
#include <SFML/Graphics.hpp>

class BaseScreen
{
public :
    virtual BaseScreen* Run (sf::RenderWindow &App) = 0;
};

#endif