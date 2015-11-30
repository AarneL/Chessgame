#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <SFML/Graphics.hpp>
#include "object.hpp"

class ChessPiece : public Object
{
public:
	ChessPiece();
	void loadContent(const std::string& texturePath);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	void setState(ObjectState state);
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif