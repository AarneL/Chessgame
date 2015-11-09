#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <iostream>
#include <SFML/Graphics.hpp>

class GameScreen : public BaseScreen
{
private:
public:
    GameScreen(void);
	virtual void LoadContent(void);
	virtual void Update(void);
    virtual int Run(sf::RenderWindow &App);
};

#endif
