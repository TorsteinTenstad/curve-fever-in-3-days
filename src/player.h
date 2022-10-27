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

	float linear_speed_;
	float angular_speed_;
	float r_;

	float min_time_between_jumps_;
	float max_time_between_jumps_;
	float jump_duration_;

	int left_key_;
	int right_key_;

	float next_jump_time_ = 5;
	bool jumping_ = false;

	bool turning_left_ = false;
	bool turning_right_ = false;
	bool drawing_ = true;
	bool dead_ = false;

	sf::CircleShape shape_;
	sf::CircleShape jump_filler_sprite_;
	sf::Color color_;

	CollisionHandler* collision_handler_;

public:
	Player(sf::RenderWindow& window, int id, float linear_speed, float angular_speed, float r, float min_time_between_jumps, float max_time_between_jumps, float jump_duration, int left_key, int right_key, sf::Color color, CollisionHandler* collision_handler)
	{

		linear_speed_ = linear_speed;
		angular_speed_ = angular_speed;
		r_ = r;
		id_ = id;
		min_time_between_jumps_ = min_time_between_jumps;
		min_time_between_jumps_ = max_time_between_jumps;
		jump_duration_ = jump_duration;
		left_key_ = left_key;
		right_key_ = right_key;
		collision_handler_ = collision_handler;
		color_ = color;
		shape_ = sf::CircleShape(r_);
		shape_.setFillColor(color_);
		shape_.setOrigin(sf::Vector2f(r_, r_));
		position_ = sf::Vector2f(rand() % (int)(window.getSize().x / 2) + window.getSize().x / 4, rand() % (int)(window.getSize().y / 2) + window.getSize().y / 4);
		angle_ = 2 * PI * (float)rand() / RAND_MAX;
	}

	void Update(sf::RenderWindow& window, float dt, float t)
	{
		if (!dead_)
		{
			bool was_jumping = jumping_;
			jumping_ = next_jump_time_ < t && t < (next_jump_time_ + jump_duration_);
			if (jumping_)
			{
				sf::Color dot_color;
				float dot_r;
				if (next_jump_time_ + (2 * (1+r_) / linear_speed_) < t)
				{
					dot_color = sf::Color::Black;
					dot_r = (1+r_);
					sf::CircleShape dot = sf::CircleShape(dot_r);
					dot.setPosition(position_);
					dot.setOrigin(sf::Vector2f(dot_r, dot_r));
					dot.setFillColor(dot_color);
					window.draw(dot);
				}
			}

			if (was_jumping && !jumping_)
			{
				next_jump_time_ = t + min_time_between_jumps_ + (max_time_between_jumps_ - min_time_between_jumps_) * ((float)rand() / RAND_MAX);
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

			window.draw(shape_);

			if (!jumping_ && t > GRACE_PERIOD)
			{
				collision_handler_->AddCollisionPoint(position_, r_, t, id_);
				dead_ = collision_handler_->HasCollided(window, position_, r_, t - 1.2 * (2 * r_ / linear_speed_), id_);
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