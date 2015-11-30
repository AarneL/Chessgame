#include "../headers/square.hpp"
#include <iostream>

Square::Square()
{
}

void Square::loadContent(const std::string& normPath, const std::string& hlPath, sf::Vector2f pos)
{
	if (!normalTexture.loadFromFile(normPath))
		std::cout << "File " << normPath << " not found!" << std::endl;
	if (!highlightedTexture.loadFromFile(hlPath))
		std::cout << "File " << hlPath << " not found!" << std::endl;
	sprite.setPosition(pos);
	sprite.setTexture(normalTexture);

	// Default state normal
	state = Normal;
	drawObject = true;
}

void Square::setState(ObjectState st)
{
	state = st;
	if (state == Normal) {
		sprite.setTexture(normalTexture, true);
	} else if (state == Highlighted) {
		sprite.setTexture(highlightedTexture, true);
	}
}

bool Square::containsMousePos(sf::Vector2f v)
{
	return sprite.getGlobalBounds().contains(v);
}

sf::Vector2f Square::getPosition() const
{
	return sprite.getPosition();
}

void Square::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}
