#ifndef BASESCREEN_H
#define BASESCREEN_H
#include <SFML/Graphics.hpp>
#include <iostream>

class BaseScreen
{
public:
	virtual void loadContent(void) = 0;
	virtual int update() = 0;
    virtual void draw() = 0;
};

#endif