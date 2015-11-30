#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Button : public Object
{
public:
	Button();
	void setState(ObjectState state);
	void loadContent(const std::string& normPath, const std::string& hlPath, const std::string& selPath, sf::Vector2f pos, bool draw);
	bool containsMousePos(sf::Vector2f v);
	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow &window);
private:
	sf::Texture normalTexture;
	sf::Texture highlightedTexture;
	sf::Texture selectedTexture;
	sf::Sprite sprite;
};

#endif