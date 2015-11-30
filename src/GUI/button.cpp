#include "../headers/button.hpp"
#include <iostream>

Button::Button()
{
}

void Button::loadContent(const std::string& normPath, const std::string& hlPath, const std::string& selPath, sf::Vector2f pos, bool draw)
{
	if (!normalTexture.loadFromFile(normPath))
		std::cout << "File " << normPath << " not found!" << std::endl;
	if (!highlightedTexture.loadFromFile(hlPath))
		std::cout << "File " << hlPath << " not found!" << std::endl;
	if (selPath != "") {
		if (!selectedTexture.loadFromFile(selPath))
			std::cout << "File " << selPath << " not found!" << std::endl;
	}

	sprite.setPosition(pos);
	sprite.setTexture(normalTexture);

	// Default state normal
	state = Normal;
	drawObject = draw;
}

void Button::setState(ObjectState st)
{
	state = st;
	if (state == Normal) {
		sprite.setTexture(normalTexture, true);
	} else if (state == Highlighted) {
		sprite.setTexture(highlightedTexture, true);
	} else if (state == Selected) {
		sprite.setTexture(selectedTexture, true);
	}
}

bool Button::containsMousePos(sf::Vector2f v)
{
	return sprite.getGlobalBounds().contains(v);
}

sf::Vector2f Button::getPosition() const
{
	return sprite.getPosition();
}

void Button::draw(sf::RenderWindow &window)
{
	if (drawObject) {
		window.draw(sprite);
	}
}
