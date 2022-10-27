#include "PCH.hpp"
#include "globals.h"
#include <math.h>	/* sin */
#include <stdlib.h> /* srand, rand */

class Player
{
private:
	int id_;
	sf::Vector2f position_;
	float angle_;

	int left_key_;
	int right_key_;

	float linear_speed_ = 300;
	float angular_speed_ = 3;
	float r_ = 10;

	bool turning_left_ = false;
	bool turning_right_ = false;
	bool drawing_ = true;

	float jumping_for_ = 0;
	float jump_probability_per_second_ = 0.2;

	bool dead_ = false;

	sf::CircleShape shape_;

	CollisionHandler* collision_handler_;

public:
	Player(int id, int left_key, int right_key, sf::Color color, CollisionHandler* collision_handler)
	{
		id_ = id;
		left_key_ = left_key;
		right_key_ = right_key;
		collision_handler_ = collision_handler;
		shape_ = sf::CircleShape(r_);
		shape_.setFillColor(color);
		shape_.setOrigin(sf::Vector2f(r_ / 2, r_ / 2));
		position_ = sf::Vector2f(rand() % (int)(SCREEN_X / 2) + SCREEN_X / 4, rand() % (int)(SCREEN_Y / 2) + SCREEN_Y / 4);
		angle_ = 2 * PI * (float)rand() / RAND_MAX;
	}

	void Update(sf::RenderWindow& window, float dt, float t)
	{
		if (!dead_)
		{
			float jump_probability = jump_probability_per_second_ * dt;
			if (((float)rand() / RAND_MAX) < jump_probability)
			{
				jumping_for_ = 2;
			}
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
			if (jumping_for_ <= 0)
			{
				window.draw(shape_);
			}

			if (jumping_for_ <= 0 && t > GRACE_PERIOD)
			{
				collision_handler_->AddCollisionPoint(position_, r_, t, id_);
				dead_ = collision_handler_->HasCollided(position_, r_, t - 1.2 * (2 * r_ / linear_speed_), id_);
			}
			else
			{
				jumping_for_ -= dt;
			}
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