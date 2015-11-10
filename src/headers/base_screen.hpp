#ifndef BASESCREEN_H
#define BASESCREEN_H
#include <SFML/Graphics.hpp>
#include <iostream>

class BaseScreen
{
public :
	virtual void LoadContent(void) = 0;
	virtual void Update(void) = 0;
    virtual int Run (sf::RenderWindow &App) = 0;
};

#endif