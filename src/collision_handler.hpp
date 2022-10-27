#include "PCH.hpp"
#include "globals.h"
#include "utilityfunctions.hpp"

class CollisionHandler
{
private:
	std::vector<sf::Vector2f> collision_points_;
	std::vector<float> radii_;
	std::vector<float> timestamps_;
	std::vector<int> ids_;

public:
	void AddCollisionPoint(sf::Vector2f point, float r, float t, int id)
	{
		collision_points_.push_back(point);
		radii_.push_back(r);
		timestamps_.push_back(t);
		ids_.push_back(id);
	}

	bool HasCollided(sf::RenderWindow& window, sf::Vector2f point, float r, float max_timestamp, int id)
	{
		if ((point.x - r) < 0 || (point.y - r) < 0 || (point.x + r) > window.getSize().x || (point.y + r) > window.getSize().y)
		{
			return true;
		}
		for (unsigned i = 0; i < collision_points_.size(); i++)
		{
			if (Magnitude(collision_points_[i] - point) < (radii_[i] + r))
			{
				if (ids_[i] == id)
				{
					if (timestamps_[i] < max_timestamp)
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
		return false;
	}
};