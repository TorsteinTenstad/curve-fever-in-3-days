#include "PCH.hpp"
#include "globals.h"
#include <math.h>	/* sin */
#include <stdlib.h> /* srand, rand */

class Player
{
private:
	sf::Vector2f position_;
	float angle_;

	int left_key_;
	int right_key_;

	float linear_speed_ = 300;
	float angular_speed_ = 1.5;
	float r = 20;

	bool turning_left_;
	bool turning_right_;
	bool drawing_ = true;

	sf::CircleShape shape_;

public:
	Player(int left_key, int right_key, sf::Color color)
	{
		left_key_ = left_key;
		right_key_ = right_key;
		shape_ = sf::CircleShape(r);
		shape_.setFillColor(color);
		shape_.setOrigin(sf::Vector2f(r / 2, r / 2));
		position_ = sf::Vector2(rand() % (int)(SCREEN_X - 2 * r) + r, rand() % (int)(SCREEN_Y - 2 * r) + r);
		angle_ = 2 * PI * rand() / RAND_MAX;
	}

	void Update(sf::RenderWindow& window, float dt)
	{
		if (turning_right_)
		{
			angle_ += dt * angular_speed_;
		}
		if (turning_left_)
		{
			angle_ -= dt * angular_speed_;
		}
		position_ = position_ + linear_speed_ * dt * sf::Vector2f(cos(angle_), sin(angle_));
		shape_.setPosition(position_);
		if (drawing_)
		{
			window.draw(shape_);
		}
	}

	void OnKey(bool is_pressed, int keycode)
	{
		if (keycode == left_key_)
		{
			turning_left_ = is_pressed;
		}
		if (keycode == right_key_)
		{
			turning_right_ = is_pressed;
		}
	}
};