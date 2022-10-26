#include "Platform/Platform.hpp"
#include "globals.h"
#include "player.h"
#include "timer.hpp"

int main()
{
	util::Platform platform;
	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(SCREEN_X * screenScalingFactor, SCREEN_Y * screenScalingFactor), "outcast-particle");
	platform.setIcon(window.getSystemHandle());

	Player player1 = Player(sf::Keyboard::A, sf::Keyboard::D, sf::Color(25, 98, 158));
	Player player2 = Player(sf::Keyboard::Left, sf::Keyboard::Right, sf::Color(126, 199, 54));
	Timer timer = Timer();

	sf::Event event;
	float dt;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			if (event.type == sf::Event::KeyPressed)
			{
				player1.OnKey(true, event.key.code);
				player2.OnKey(true, event.key.code);
			}
			if (event.type == sf::Event::KeyReleased)
			{
				player1.OnKey(false, event.key.code);
				player2.OnKey(false, event.key.code);
			}
		}
		//window.clear();
		dt = timer.GetElapsedSeconds();
		player1.Update(window, dt);
		player2.Update(window, dt);
		window.display();
	}
	return 0;
}
