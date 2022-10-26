#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;
	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(1920 * screenScalingFactor, 1080 * screenScalingFactor), "outcast-particle");
	platform.setIcon(window.getSystemHandle());

	sf::CircleShape shape = sf::CircleShape(100);
	shape.setFillColor(sf::Color::White);

	sf::Event event;

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
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}