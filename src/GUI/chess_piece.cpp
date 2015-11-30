#include "../headers/chess_piece.hpp"
#include <iostream>

ChessPiece::ChessPiece()
{
}

void ChessPiece::loadContent(const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath))
		std::cout << "File " << texturePath << " not found!" << std::endl;

	sprite.setTexture(texture);
}

sf::Vector2f ChessPiece::getPosition() const
{
	return sprite.getPosition();
}

void ChessPiece::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void ChessPiece::setState(ObjectState state)
{
	state = Normal;
}

void ChessPiece::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}