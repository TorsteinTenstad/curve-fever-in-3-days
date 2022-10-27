#include "Platform/Platform.hpp"
#include "collision_handler.hpp"
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
	window.create(sf::VideoMode(window.getSize().x * screenScalingFactor, window.getSize().y * screenScalingFactor), "Curve :)", sf::Style::Fullscreen);
	platform.setIcon(window.getSystemHandle());

	CollisionHandler collision_handler = CollisionHandler();
	Player player1 = Player(window, 1, sf::Keyboard::A, sf::Keyboard::D, sf::Color(25, 98, 158), &collision_handler);
	//Player player2 = Player(window, 2, sf::Keyboard::Left, sf::Keyboard::Right, sf::Color(126, 199, 54), &collision_handler);

	sf::Event event;
	float dt;
	float t;

	Timer timer = Timer();
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
				//player2.OnKey(true, event.key.code);
			}
			if (event.type == sf::Event::KeyReleased)
			{
				player1.OnKey(false, event.key.code);
				//player2.OnKey(false, event.key.code);
			}
		}
		if (timer.GetSecondsSinceInit() < GRACE_PERIOD)
		{
			window.clear();
		}
		dt = timer.GetElapsedSeconds();
		t = timer.GetSecondsSinceInit();
		player1.Update(window, dt, t);
		//player2.Update(window, dt, t);
		window.display();
	}
	return 0;
}
