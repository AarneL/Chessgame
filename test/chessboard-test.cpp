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

	//Create base board
	std::vector<sf::Sprite> vBoard_base;
	sf::Sprite s;
	for (int i=0; i<64; i++){
		s = sf::Sprite();
		s.setPosition(sf::Vector2f( (i%8)*96, (i/8)*96 ));
		s.setTexture(txtPlain);
		//s.setColor(sf::Color(200, 200, 0, 255));	//R, G, B, alpha
		if ( (i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1) )
				s.setColor(sf::Color(210, 105, 30)); //"chocolate"
		else if ( (i%2==0 && (i/8)%2==1) || (i%2==1 && (i/8)%2==0) )
				s.setColor(sf::Color(138, 54, 15, 255)); //"burntsienna"

		vBoard_base.push_back(s);
	}




	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}


	/*
	//mouse click knight
	if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
		if(sf::Mouse::getPosition(window).x > knight.getGlobalBounds().left
			&& sf::Mouse::getPosition(window).x < (knight.getGlobalBounds().left + knight.getGlobalBounds().width)
			&& sf::Mouse::getPosition(window).y > knight.getGlobalBounds().top
			&& sf::Mouse::getPosition(window).y < (knight.getGlobalBounds().top + knight.getGlobalBounds().height))
				knight.setColor(sf::Color(0,255,0,iALPHA));	//R, G, B, alpha
	}

	if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) ) {
        if(sf::Mouse::getPosition(window).x > knight.getGlobalBounds().left
            && sf::Mouse::getPosition(window).x < (knight.getGlobalBounds().left + knight.getGlobalBounds().width)
            && sf::Mouse::getPosition(window).y > knight.getGlobalBounds().top
            && sf::Mouse::getPosition(window).y < (knight.getGlobalBounds().top + knight.getGlobalBounds().height))
                knight.setColor(sf::Color(255,255,255,iALPHA));	//R, G, B, alpha
    }

	//mouse click queen
	if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
        if(sf::Mouse::getPosition(window).x > queen.getGlobalBounds().left
            && sf::Mouse::getPosition(window).x < (queen.getGlobalBounds().left + queen.getGlobalBounds().width)
            && sf::Mouse::getPosition(window).y > queen.getGlobalBounds().top
            && sf::Mouse::getPosition(window).y < (queen.getGlobalBounds().top + queen.getGlobalBounds().height))
                queen.setColor(sf::Color(255,0,0,iALPHA));    //R, G, B, alpha
    }

    if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) ) {
        if(sf::Mouse::getPosition(window).x > queen.getGlobalBounds().left
            && sf::Mouse::getPosition(window).x < (queen.getGlobalBounds().left + queen.getGlobalBounds().width)
            && sf::Mouse::getPosition(window).y > queen.getGlobalBounds().top
            && sf::Mouse::getPosition(window).y < (queen.getGlobalBounds().top + queen.getGlobalBounds().height))
                queen.setColor(sf::Color(255,255,255,iALPHA));    //R, G, B, alpha
    }

	*/

		window.clear(sf::Color(255,255,255, 255));	//R, G, B, alpha (optional)

		for (std::vector<sf::Sprite>::iterator i=vBoard_base.begin(); i!=vBoard_base.end(); i++)
			window.draw(*i);

		window.display();
	}

	return 0; }
