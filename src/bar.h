#pragma once
#include "PCH.hpp"

class Bar
{
private:
	int w_;
	int h_;
	int x_;
	int y_;
	sf::Color outline_color_;
	sf::Color fill_color_;

	int outline_thickness_ = 5;
	sf::RectangleShape base_;

public:
	Bar(int w, int h, int x, int y, sf::Color outline_color, sf::Color fill_color)
	{
		w_ = w;
		h_ = h;
		x_ = x;
		y_ = y;
		outline_color_ = outline_color;
		fill_color_ = fill_color;

		base_ = sf::RectangleShape(sf::Vector2f(w_ - 2 * outline_thickness_, h_ - 2 * outline_thickness_));
		base_.setOutlineThickness(outline_thickness_);
		base_.setFillColor(fill_color_);
		base_.setOutlineColor(outline_color_);
		base_.setPosition(sf::Vector2f(x_ + outline_thickness_, y_ + outline_thickness_));
	}
	void UpdateAndDraw(sf::RenderWindow& window, float fill_value)
	{
		window.draw(base_);

		float missing_pixles = (1 - fill_value) * (w_ - 2 * outline_thickness_);
		sf::RectangleShape black_bar = sf::RectangleShape(sf::Vector2f(missing_pixles, h_ - 2 * outline_thickness_));
		black_bar.setOrigin(sf::Vector2f(missing_pixles, 0));
		black_bar.setPosition(sf::Vector2f(x_ + w_ - outline_thickness_, y_ + outline_thickness_));
		black_bar.setFillColor(sf::Color::Black);
		window.draw(black_bar);
	}
};