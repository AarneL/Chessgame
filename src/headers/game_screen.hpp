#include <iostream>

#include <SFML/Graphics.hpp>

class GaneScreen : public BaseScreen
{
private:
public:
    GaneScreen(void);
    virtual BaseScreen* Run(sf::RenderWindow &App);
};