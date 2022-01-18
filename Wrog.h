#pragma once

#include <SFML/Graphics.hpp>
#include "pociski.h" 
#include <random>

class Wrog
{
private:
	//sf::RectangleShape wrog;
	sf::Sprite* wrog;
	sf::Texture wrogTexture;
	int N;
	std::random_device rd;
	int ileZestrzelono = 0;
	int ileLosowan = 0;
public:
	Wrog(int Nt) {
		N = Nt;
		wrog = new sf::Sprite[N];
		wrogTexture.loadFromFile("wrogTexture.png");

		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(150, 1100);
		std::uniform_int_distribution<> distY(50, 700);
		for (int i = 0; i < N; i++)
		{
			float x = 0, y = 0;
			x = distX(gen);
			y = distY(gen);
			wrog[i].setTexture(wrogTexture);
			wrog[i].setPosition(sf::Vector2f(x, y));
		}
	}

	void ustawPozycje(sf::Vector2f nowaPozycja, int i) {
		wrog[i].setPosition(nowaPozycja);
	}

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < N; i++)
			window.draw(wrog[i]);
	}

	void sprawdzKolizje(Pociski pociski, int i) {
		for (int j = 0; j < N; j++)
		{
			if (pociski.krawedzDolna(i) > wrog[j].getPosition().y) {
				if (pociski.krawedzGorna(i) < wrog[j].getPosition().y + 50) {
					if (pociski.krawedzPrawa(i) > wrog[j].getPosition().x)
					{
						wrog[j].setPosition(sf::Vector2f(123452, 12521));
						pociski.ustawPozycje(sf::Vector2f(2134213, 12342), i);
						ileZestrzelono++;
					}
				}
			}
		}
	}

	int LiczbaZestrzelonych() {
		return ileZestrzelono;
	}

	int ileWrogow() {
		return N;
	}

	void losujPozycje()
	{
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(150, 1100);
		std::uniform_int_distribution<> distY(50, 700);

		for (int i = 0; i < N; i++) {
			float x, y;
			x = distX(gen);
			y = distY(gen);
			wrog[i].setPosition(sf::Vector2f(x, y));
		}
		ileLosowan++;
	}
	
	int LiczbaLosowan() {
		return ileLosowan;
	}

};