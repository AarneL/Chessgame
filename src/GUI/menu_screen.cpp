MenuScreen::MenuScreen(void)
{
}

BaseScreen* MenuScreen::Run(sf::RenderWindow &App)
{
    while (1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return new GameScreen();

        App.clear(sf::Color(200,10,200, 255));
        App.display();
    }
}