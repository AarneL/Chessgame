#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

int main() {

sf::RenderWindow window(sf::VideoMode(640, 480), "test");

//horse
sf::Texture txt_knight;
txt_knight.loadFromFile("pieces/knight_white.png");
sf::Sprite knight;
knight.setTexture(txt_knight);

/*
sf::SoundBuffer sbuf_knight;
sbuf_knight.loadFromFile("horse.wav");
sf::Sound sound_knight;
sound_knight.setBuffer(sbuf_knight);
*/

//queen
sf::Texture txt_queen;
txt_queen.loadFromFile("pieces/queen_black.png");
sf::Sprite queen;
queen.setTexture(txt_queen);
queen.setPosition(312, 232);

//rook
sf::Texture txt_rook;
txt_rook.loadFromFile("pieces/rook_black.png");
sf::Sprite rook;
rook.setTexture(txt_rook);
rook.setPosition(312, 384);

int iALPHA=128;

while (window.isOpen()) {

	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		knight.move(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		knight.move(1, 0);
		//sound_knight.play();
		}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		knight.move(0, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		knight.move(0, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
		iALPHA +=1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
		iALPHA -= 1;

	if (iALPHA < 0)
		iALPHA = 0;
	if (iALPHA >255)
		iALPHA = 255;


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



	window.clear(sf::Color(200,10,200, 255));


	window.draw(rook);
	window.draw(knight);
	window.draw(queen);

	window.display();
}

	return 0; }
