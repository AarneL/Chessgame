#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "board.hpp"

class ChessPiece : public Object
{
public:
	ChessPiece();
	void loadContent(const std::string& texturePath, Piece type);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	bool containsMousePos(sf::Vector2f v);
	void changeTexture(const sf::Texture* newTexture);
	const sf::Texture* getTexture() const;
	void setState(ObjectState state);
	Piece getType() const;
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	Piece type;
};

#endif