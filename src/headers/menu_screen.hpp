#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "./../headers/base_screen.hpp"
#include "./../headers/game_screen.hpp"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen
{
private:
public:
    MenuScreen(void);
    virtual BaseScreen* Run(sf::RenderWindow &App);
};

#endif /* MENU_SCREEN_H */