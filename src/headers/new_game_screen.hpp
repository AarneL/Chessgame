#ifndef NEW_GAME_SCREEN_H
#define NEW_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "base_screen.hpp"

class NewGameScreen : public BaseScreen
{
public:
    NewGameScreen(void);
	void loadContent(void);
	void createGame(int players);
	int update(sf::RenderWindow &window, sf::Event &event);
    void draw(sf::RenderWindow &window);
private:
	sf::Texture onePlayerButtonTexture;
	sf::Sprite onePlayerButton;
	sf::Texture twoPlayersButtonTexture;
	sf::Sprite twoPlayersButton;
};

#endif
