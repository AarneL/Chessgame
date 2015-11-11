#include "../headers/new_game_screen.hpp"
#include "../headers/base_screen.hpp"
#include "../headers/human.hpp"
#include "../headers/ai.hpp"
#include "../headers/player.hpp"
// #include "../headers/game.hpp"

NewGameScreen::NewGameScreen(void)
{
}

void NewGameScreen::loadContent(void)
{
	if (!onePlayerButtonTexture.loadFromFile("media/img/one_player.png"))
		std::cout << "File not found!" << std::endl;
	onePlayerButton.setTexture(onePlayerButtonTexture);
	onePlayerButton.setPosition(sf::Vector2f(300, 200));
	elements.push_back(onePlayerButton);

	if (!twoPlayersButtonTexture.loadFromFile("media/img/two_players.png"))
		std::cout << "File not found!" << std::endl;
	twoPlayersButton.setTexture(twoPlayersButtonTexture);
	twoPlayersButton.setPosition(sf::Vector2f(300, 400));
	elements.push_back(twoPlayersButton);
}

void NewGameScreen::createGame(int players)
{
	if (players == 1) {
		// Name and level should be taken from user input
		std::string name1 = "Pekka";
		ColorType color1 = White;
		Human player1 = Human(name1, color1);
		std::string name2 = "AI";
		ColorType color2 = Black;
		AI player2 = AI(name2, color2, 4);
		std::cout << "created two players:" << std::endl;
		std::cout << player1.getName() << ", " << player1.getColor() << std::endl;
		std::cout << player2.getName() << ", " << player2.getColor() << ", " << player2.getLevel() << std::endl;
	}
	else if (players == 2) {
		// Names should be taken from user input
		std::string name1 = "Pekka";
		ColorType color1 = White;
		Human player1 = Human("Pekka", color1);
		std::string name2 = "Pentti";
		ColorType color2 = Black;
		Human player2 = Human("Pentti", color2);
		std::cout << "created two players:" << std::endl;
		std::cout << player1.getName() << ", " << player1.getColor() << std::endl;
		std::cout << player2.getName() << ", " << player2.getColor() << std::endl;
	}
	// TODO: when players are created, next create the Game with them
	// Game game = Game(player1, player2);
}

int NewGameScreen::update(sf::RenderWindow &window, sf::Event &event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i v = sf::Mouse::getPosition(window);
		std::cout << "Mouse clicked at:(" << v.x << "," << v.y << ")" << std::endl;

		if (onePlayerButton.getGlobalBounds().contains((sf::Vector2f)v))
		{
			std::cout << "User pressed oneplayerbutton." << std::endl;
			createGame(1);
			// Start gamescreen
			std::cout << "players created" << std::endl;
			return 2;
		}
		else if (twoPlayersButton.getGlobalBounds().contains((sf::Vector2f)v))
		{
			std::cout << "User pressed twoplayersbutton." << std::endl;
			createGame(2);
			std::cout << "players created" << std::endl;
			// Start gamescreen
			return 2;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return -1;
	return 1;
}

void NewGameScreen::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 255, 0, 0));
	for (auto element : elements) {
		window.draw(element);
	}
	window.display();
}