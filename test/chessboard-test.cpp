#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>


int main() {

	sf::RenderWindow window(sf::VideoMode(800,800), "test");

	//plain white texture
	sf::Texture txtPlain;
	//txtPlain.create(96, 96);
	txtPlain.loadFromFile("square_white.png");
	/*
	uint8_t* white_pixels[64];
	for (int i =0; i<64; i++)
		white_pixels[i] = 255;
	txtPlain.update(white_pixels);
	*/

	sf::Color color_square_dark(210, 105,30);	//"chocolate"
	sf::Color color_square_light(138,54,15);	//"burntsienna"
	sf::Color color_highlight_square_dark(0,200,0);
	sf::Color color_highlight_square_light(0,255,255);

	//Create base board
	std::vector<sf::Sprite> vBoard_base;
	sf::Sprite s;
	for (int i=0; i<64; i++){
		s = sf::Sprite();
		s.setPosition(sf::Vector2f( (i%8)*96, (i/8)*96 ));
		s.setTexture(txtPlain);
		//s.setColor(sf::Color(200, 200, 0, 255));	//R, G, B, alpha
		if ( (i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1) )
				s.setColor(color_square_dark);
		else if ( (i%2==0 && (i/8)%2==1) || (i%2==1 && (i/8)%2==0) )
				s.setColor(color_square_light);

		vBoard_base.push_back(s);
	}



	//main loop
	while (window.isOpen()) {

		sf::Event event;

		//event loop
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();




		//mouse click
		//if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
		if (event.type == sf::Event::MouseButtonPressed) {
			for (std::vector<sf::Sprite>::iterator i=vBoard_base.begin(); i!=vBoard_base.end(); i++){

				if(sf::Mouse::getPosition(window).x > i->getGlobalBounds().left
					&& sf::Mouse::getPosition(window).x < (i->getGlobalBounds().left + i->getGlobalBounds().width)
					&& sf::Mouse::getPosition(window).y > i->getGlobalBounds().top
					&& sf::Mouse::getPosition(window).y < (i->getGlobalBounds().top + i->getGlobalBounds().height))	{
						//set highlight
						if (i->getColor() == color_square_dark)
							i->setColor(color_highlight_square_dark);
						else if (i->getColor() == color_square_light)
							i->setColor(color_highlight_square_light);
						//unset highlight
						else if (i->getColor() == color_highlight_square_dark)
							i->setColor(color_square_dark);
						else if (i->getColor() == color_highlight_square_light)
							i->setColor(color_square_light);

				}
			}
		}	//end of mouse click

		}	//end of events

		window.clear(sf::Color(255,255,255, 255));	//R, G, B, alpha (optional)

		for (std::vector<sf::Sprite>::iterator i=vBoard_base.begin(); i!=vBoard_base.end(); i++)
			window.draw(*i);

		window.display();
	}

	return 0; }
