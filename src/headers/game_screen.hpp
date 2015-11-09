#include <iostream>

#include <SFML/Graphics.hpp>

class GameScreen : public BaseScreen
{
private:
public:
    GameScreen(void);
    virtual BaseScreen* Run(sf::RenderWindow &App);
};
