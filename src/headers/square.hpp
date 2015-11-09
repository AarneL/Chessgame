#ifndef CHESSBOARD_SQUARE
#define CHESSBOARD_SQUARE

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "piece.hpp"


class Square {

	public:

		//Take index number and occupant	//TODO: Pointer or reference to occupant, how about unoccupied squares?
		//Create sprite and set its position, texture, color...
		Square(int num, Piece& p);

		//Check if there is a piece, and return the piece
		bool isOccupied() const;
		Piece* getOccupant() const;

		//Use this when rendering
		sf::Sprite& getSprite() const;


		//Take mouse position
		//Return true if the mouse position matches this square
		bool mouseHits(sf::Vector2i mpos) const;

		//Get the algebraic position, e.g. a4, c7...
		std::string getAlgebraicPosition();

		//std::ostream& operator<<(std::ostream& os, const Square& s);	//TODO inside or outside of class?

	private:

		int number;	//index number in the board list, 0 to 63

		sf::Sprite sprite;			//Base sprite (basically, a white square)
		sf::Color color_base;		//Base color of the square
		sf::Color color_highlight;	//Highlighted color

		//Piece class instance
		//TODO: reference or pointer, how about unoccupied squares? "NonePiece"?
		Piece* occupant;



};


#endif