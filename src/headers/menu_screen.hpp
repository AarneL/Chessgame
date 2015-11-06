#include <iostream>

#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
private:
public:
    MenuScreen(void);
    virtual BaseScreen* Run(sf::RenderWindow &App);
};
