#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pociski
{
private:
	//sf::RectangleShape pociski;
	sf::Sprite* pociski;
	sf::Texture pociskiTexture;
	int N = 0;
	int iloscPociskow;

public:
	int krawedzPrawa(int i);
	int krawedzLewa(int i);
	int krawedzGorna(int i);
	int krawedzDolna(int i);
	void draw(sf::RenderWindow& window);
	Pociski(int N);
	void strzelanie(int predkosc);
	void tworzeniePocisku(sf::Vector2f nowaPozycja, int nrPocisku);

	void rysujPocisk(sf::RenderWindow& window) {
		window.draw(pociski[0]);
	}

	int iloscpociskow() {
		return iloscPociskow;
	}

	void ustawPozycje(sf::Vector2f nowaPozycja, int nrPocisku) {
		pociski[nrPocisku].setPosition(nowaPozycja);
	}


};

Pociski::Pociski(int Nt)
{
	N = Nt;
	pociskiTexture.loadFromFile("pociskiTexture.png");

	pociski = new sf::Sprite[N]; //tablica dla pocisków
}

void Pociski::strzelanie(int predkosc)
{
	for (int i = 0; i < iloscPociskow; i++)
	{
		pociski[i].move(predkosc, 0);
		//if (i == 0)
			//std::cout << "pociski::strzelanie";
	}
}

int Pociski::krawedzPrawa(int i)
{
	return pociski[i].getPosition().x + 50;
}
int Pociski::krawedzLewa(int i)
{
	return pociski[i].getPosition().x;
}
int Pociski::krawedzGorna(int i)
{
	return pociski[i].getPosition().y;
}
int Pociski::krawedzDolna(int i)
{
	return pociski[i].getPosition().y + 10;
}

void Pociski::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < iloscPociskow; i++)
		window.draw(pociski[i]);
}

void Pociski::tworzeniePocisku(sf::Vector2f nowaPozycja, int nrPocisku)
{
	//std::cout << "Pociski::tworzeniePocisku";
	iloscPociskow = nrPocisku + 1;
	pociski[nrPocisku].setPosition(nowaPozycja);
	pociski[nrPocisku].setTexture(pociskiTexture);

}