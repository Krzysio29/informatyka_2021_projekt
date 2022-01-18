#pragma once

#include <SFML/Graphics.hpp>

class Gracz
{
private:
	sf::RectangleShape gracz;
	int punkty;
public:
	Gracz(sf::Vector2f size);
	void move(sf::Vector2f kierunek);
	int getX();
	int getY();
	void draw(sf::RenderWindow& window);
	int getPunkty();
	void aktulizacjaPunktow(int LiczbaZastrzelonych);
};

Gracz::Gracz(sf::Vector2f size)
{
	gracz.setSize(size);
	gracz.setFillColor(sf::Color::Blue);
}

void Gracz::move(sf::Vector2f kierunek)
{
	gracz.move(kierunek);
}

int Gracz::getX()
{
	return gracz.getPosition().x;
}

int Gracz::getY()
{
	return gracz.getPosition().y;
}

void Gracz::draw(sf::RenderWindow& window)
{
	window.draw(gracz);
}

void Gracz::aktulizacjaPunktow(int LiczbaZastrzelonych)
{
	punkty = LiczbaZastrzelonych * 2;
}

int Gracz::getPunkty()
{
	return punkty;
}