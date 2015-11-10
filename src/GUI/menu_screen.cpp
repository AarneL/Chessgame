#include "./../headers/menu_screen.hpp"
#include "./../headers/base_screen.hpp"

MenuScreen::MenuScreen(void)
{
}

void MenuScreen::LoadContent(void)
{
	backgroundtexture.loadFromFile("media/img/background.jpg");
	background.setTexture(backgroundtexture);
	playbuttontexture.loadFromFile("media/img/playbutton.png");
	playbutton.setTexture(playbuttontexture);
	playbutton.setPosition(sf::Vector2f(300, 200));
	optionsbuttontexture.loadFromFile("media/img/optionsbutton.png");
	optionsbutton.setTexture(optionsbuttontexture);
	optionsbutton.setPosition(sf::Vector2f(300, 400));
	exitbuttontexture.loadFromFile("media/img/exitbutton.png");
	exitbutton.setTexture(exitbuttontexture);
	exitbutton.setPosition(sf::Vector2f(300, 600));
}

void MenuScreen::Update(void)
{

}

int MenuScreen::Run(sf::RenderWindow &App)
{
	sf::Event event;
    while (App.pollEvent(event)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i v = sf::Mouse::getPosition(App);
			std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

			if (playbutton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start gamescreen
				std::cout << "User pressed playbutton." << std::endl;
				return 1;
			}
			
			if (optionsbutton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Start optionsscreen
				std::cout << "User pressed optionsbutton." << std::endl;
				return 2;
			}

			if (exitbutton.getGlobalBounds().contains((sf::Vector2f)v))
			{
				// Exit program
				std::cout << "User pressed exitbutton." << std::endl;
				return -1;
			}


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return -1;		
    }

	App.draw(background);
	App.draw(playbutton);
	App.draw(optionsbutton);
	App.draw(exitbutton);
	App.display();
	return 0;
}