#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Square : public Object
{
public:
	Square();
	void loadContent(const std::string& normPath, const std::string& hlPath, sf::Vector2f pos);
	void setState(ObjectState state);
	bool containsMousePos(sf::Vector2f v);
	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow &window);
private:
	sf::Texture normalTexture;
	sf::Texture highlightedTexture;
	sf::Sprite sprite;
};

#endif