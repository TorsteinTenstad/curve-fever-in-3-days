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
	std::vector<Player> players;

	float linear_speed = 200;		  //px/s
	float angular_speed = 3;		  //rad/s
	float r = 3;					  //px
	float min_time_between_jumps = 1; //s
	float max_time_between_jumps = 5; //s
	float jump_duration = 0.3;		  //s

	players.push_back(Player(window, 1, linear_speed, angular_speed, r, min_time_between_jumps, max_time_between_jumps, jump_duration, sf::Keyboard::A, sf::Keyboard::D, sf::Color(25, 98, 158), &collision_handler));
	players.push_back(Player(window, 2, linear_speed, angular_speed, r, min_time_between_jumps, max_time_between_jumps, jump_duration, sf::Keyboard::Left, sf::Keyboard::Right, sf::Color(126, 199, 54), &collision_handler));

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

			for (auto& player : players)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					player.OnKey(true, event.key.code);
				}
				if (event.type == sf::Event::KeyReleased)
				{
					player.OnKey(false, event.key.code);
				}
			}
		}
		if (timer.GetSecondsSinceInit() < GRACE_PERIOD)
		{
			window.clear();
		}
		dt = timer.GetElapsedSeconds();
		t = timer.GetSecondsSinceInit();
		for (auto& player : players)
		{
			player.Update(window, dt, t);
		}
		window.display();
	}
	return 0;
}
