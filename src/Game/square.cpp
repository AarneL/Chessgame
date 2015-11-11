#include "square.hpp"




Square::Square(int num, Piece& p) {

	number = num;
	occupant = &p;

	sprite = sf::Sprite();

	if ( (p%2==0 && (p/8)%2==0) || (p%2==1 && (p/8)%2==1) )
		color_base = sf::Color(210, 105, 30);	//dark
	else if ( (p%2==0 && (p/8)%2==1) || (p%2==1 && (p/8)%2==0) )
		color_base = sf::Color(138, 54, 15); //light

	color_highlight = sf::Color(255, 255, 0, 127);	//alpha = 127 -> half transparent!

	sprite.setColor(color_base);

	sprite.setPosition(sf::Vector2f( 64+(i%8)*96, 64+(i/8)*96 ));

}

bool Square::isOccupied() const {

	if (occupant != NULL)
		return true;
	else
		return false;
}


Piece* Square::getOccupant() const{

	return occupant;

}

sf::Sprite& Square::getSprite() const{

	return sprite;

}

bool Square::mouseHits(sf::Vector2i mpos) const{

	return false;	//TODO

}