#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

enum ObjectState {
	Normal = 0,
	Highlighted = 1,
	Selected = 2
};

class Object
{
public:
	ObjectState getState() const;
	virtual void setState(ObjectState state) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	bool drawObject;
protected:
	ObjectState state;
};

#endif