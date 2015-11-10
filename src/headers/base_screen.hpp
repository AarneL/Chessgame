#ifndef BASESCREEN_H
#define BASESCREEN_H
#include <SFML/Graphics.hpp>
#include <iostream>

class BaseScreen
{
public :
	virtual void loadContent(void) = 0;
	virtual int update(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif