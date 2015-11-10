#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

class GameScreen : public BaseScreen
{
private:
public:
    GameScreen(void);
	virtual void loadContent(void);
	virtual int update(sf::RenderWindow &window);
    virtual void draw(sf::RenderWindow &window);
};

#endif
