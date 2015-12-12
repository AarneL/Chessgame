#include "../headers/chess_piece.hpp"
#include <iostream>

ChessPiece::ChessPiece()
{
}

void ChessPiece::loadContent(const std::string& texturePath, Piece t)
{
	if (!texture.loadFromFile(texturePath))
		std::cout << "File " << texturePath << " not found!" << std::endl;

	sprite.setTexture(texture);
	type = t;
}

sf::Vector2f ChessPiece::getPosition() const
{
	return sprite.getPosition();
}

void ChessPiece::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

bool ChessPiece::containsMousePos(sf::Vector2f v)
{
	return sprite.getGlobalBounds().contains(v);
}

void ChessPiece::changeTexture(const sf::Texture* newTexture)
{
	sprite.setTexture(*newTexture, true);
}

void ChessPiece::changeToInitialTexture()
{
	sprite.setTexture(texture, true);
}

const sf::Texture* ChessPiece::getTexture() const
{
	return sprite.getTexture();
}

void ChessPiece::setState(ObjectState state)
{
	state = Normal;
}

Piece ChessPiece::getType() const
{
	return type;
}

void ChessPiece::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}