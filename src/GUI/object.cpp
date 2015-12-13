#include "../headers/object.hpp"

ObjectState Object::getState() const
{
	return state;
}

bool Object::isVisible() const
{
	return drawObject;
}
