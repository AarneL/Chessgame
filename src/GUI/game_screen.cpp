GameScreen::GameScreen(void)
{
}

BaseScreen* GameScreen::Run(sf::RenderWindow &App)
{
    while (1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return new MenuScreen();

        App.clear(sf::Color(0,10,200, 255));
        App.display();
    }
}