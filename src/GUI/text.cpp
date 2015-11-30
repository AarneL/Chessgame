#include "../headers/text.hpp"
#include "../headers/object.hpp"
#include <iostream>

Text::Text()
{
}

void Text::loadContent(const std::string& fontPath, int size, sf::Vector2f pos, bool draw)
{
	if (!font.loadFromFile(fontPath))
		std::cout << "File " << fontPath << " not found!" << std::endl;
	// Error handling? what if font file not found
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(pos);
	drawObject = draw;
}

void Text::setState(ObjectState st)
{
	state = st;
	if (st == Normal) {
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Regular);
	} else if (st == Highlighted) {
		text.setColor(sf::Color(255, 255, 255, 200));
	} else if (st == Selected) {
		text.setStyle(sf::Text::Underlined);
	}
}

void Text::setString(const std::string& str)
{
	text.setString(str);
}

bool Text::containsMousePos(sf::Vector2f v)
{
	return text.getGlobalBounds().contains(v);
}

sf::Vector2f Text::getPosition() const
{
	return text.getPosition();
}

void Text::draw(sf::RenderWindow &window)
{
	if (drawObject) {
		window.draw(text);
	}
}
