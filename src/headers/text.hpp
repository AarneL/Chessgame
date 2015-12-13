#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include "object.hpp"

class Text : public Object
{
public:
	Text();
	void loadContent(const std::string& fontPath, int size, sf::Vector2f pos, bool draw);
	void setState(ObjectState state);
	void setString(const std::string& str);
	void setColor(sf::Color);
	bool containsMousePos(sf::Vector2f v);
	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow &window);
private:
	sf::Font font;
	sf::Text text;
};

#endif