#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstdio>
#include <string>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Gracz.h"
#include "Pociski.h"
#include "Wrog.h"

#define MAX_LICZBA_POZIOMOW 3

typedef struct
{
	std::string nazwa;
	double scores;
}Player;



int main()
{
	int menu_selected_flag = 0;
	bool isFiring = false;
	int nrPocisku = 0;
	bool nakladaniePocisku = false;
	bool wrogZmianaPozycji = true;
	int predkosc = 6;

	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 600, (sf::VideoMode::getDesktopMode().height / 2) - 400);
	sf::Clock zegar, strzelanieZegar, czasGry;
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	Menu menu(window.getSize().x, window.getSize().y);
	Gracz gracz(sf::Vector2f(50, 50));
	Wrog wrog(5);
	Pociski pociski(101);
	Player player[6];

	// petla wieczna - dopoki okno jest otwarte
	while (window.isOpen())
	{
		// w kazdej iteracji petli sprawdzaj zdarzenia
		sf::Event event;
		while (window.pollEvent(event))
		{
			// jezeli odebrano zdarzenie "Closed" zamknij okno
			if (event.type == sf::Event::Closed)
				window.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			//  POCZ¥TEK MENU -	obsluga menu z poziomu klawiszy (strzalki)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				myDelay(250);
				menu.przesunG();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				myDelay(250);
				menu.przesunD();
			}

			if (menu_selected_flag == 0)
			{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))



				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
				{
					std::cout << "Uruchamiam gre..." << std::endl;
					czasGry.restart();
					menu_selected_flag = 1;
				}

				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
				{
					std::cout << "Najlepsze wyniki..." << std::endl;
					menu_selected_flag = 2;
				}

				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
				{
					std::cout << "Koniec gry..." << std::endl;
					menu_selected_flag = 3;
				}

			}   //}//koniec MENU
		}

		if (menu_selected_flag == 1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				myDelay(10);
				gracz.move(sf::Vector2f(0, -predkosc));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				myDelay(10);
				gracz.move(sf::Vector2f(0, predkosc));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				myDelay(10);
				gracz.move(sf::Vector2f(-predkosc, 0));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				myDelay(10);
				gracz.move(sf::Vector2f(predkosc, 0));
			}

			if (strzelanieZegar.getElapsedTime().asMilliseconds() > 150.0f)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					myDelay(10);
					std::cout << "isFiring == true";
					isFiring = true;
				}

				if (isFiring == true) {
					//std::cout << "isFiring == true";

					int x = gracz.getX();
					int y = gracz.getY() + 20;

					pociski.tworzeniePocisku(sf::Vector2f(x, y), nrPocisku);
					nrPocisku++;
					if (nrPocisku > 100)
						nrPocisku = 0;

					isFiring = false;
					nakladaniePocisku = true;
				}
				strzelanieZegar.restart();
			}

			if (zegar.getElapsedTime().asMilliseconds() > 10.0f) {

				pociski.strzelanie(10);
				for (int i = 0; i < pociski.iloscpociskow(); i++)
				{
					wrog.sprawdzKolizje(pociski, i);
				}
				zegar.restart();
			}

			if (wrog.LiczbaZestrzelonych() % wrog.ileWrogow() == 0 && wrogZmianaPozycji == true) {
				myDelay(10);
				wrog.losujPozycje();
				wrogZmianaPozycji = false;
			}

			if (wrog.LiczbaZestrzelonych() > (wrog.LiczbaLosowan() - 1) * wrog.ileWrogow())
				wrogZmianaPozycji = true;

			gracz.aktulizacjaPunktow(wrog.LiczbaZestrzelonych());

			if (czasGry.getElapsedTime().asSeconds() > 20)  //czas gry
			{
				std::cout << "Kniec Gry!   Zdobyte punkty: " << gracz.getPunkty();
				player[5].scores = gracz.getPunkty();
				player[5].nazwa = 6;
				std::cout << "\nPodaj swoja nazwe: ";

				std::cin >> player[5].nazwa;

				std::cout << "\nWprowadzona nazwa to: ";
				std::cout << player[5].nazwa;

				menu_selected_flag = 0;

				FILE* fp; //file pointer - sposob komunikacji z plikiem
				fp = fopen("dane.dat", "wb"); //strumien plikowy do zapisu r-odczyt, a-dodanie do pliku
				if (fp == NULL)
				{
					perror("Error");
					return(-1);
				}
				else
				{
					fwrite(&player, sizeof(player), 1, fp); //zapis danych do pliku
					fclose(fp);//zamknij dostêp do strumienia plikowego
				}
			}

		}	//Koniec ocji 1 Menu (koniec gry)

		if (menu_selected_flag == 2) {
			FILE* fp;
			fp = fopen("dane.dat", "rb");
			fread(&player, sizeof(player), 1, fp);

			//segregowanie w strukturze
			int tempScore;
			std::string tempNazwa;

			for (int j = 0; j < 6; j++)
			{
				for (int i = 0; i < 6; i++)
				{
					if (player[5].scores > player[i].scores)
					{
						tempScore = player[5].scores;
						tempNazwa = player[5].nazwa;

						player[5].scores = player[i].scores;
						player[5].scores = player[i].scores;

						player[i].scores = tempScore;
						player[i].nazwa = tempNazwa;
					}

				}
			}

			for (int i = 0; i < 6; i++)
			{
				if (player[i].scores != NULL)
				{
					std::cout << i + 1 << ". " << player[i].nazwa << "  score: " << player[i].scores << "\n";
				}
			}

			menu_selected_flag = 0;
			myDelay(50);
		}

		if (menu_selected_flag == 3) {
			return 3;
		}


		// wyczysc obszar rysowania
		window.clear();

		// window.draw(...);
		if (menu_selected_flag == 0)
			menu.draw(window);
		if (menu_selected_flag == 1)
		{
			gracz.draw(window);
			wrog.draw(window);
			pociski.draw(window);
		}

		window.display();
	}

	return 0;
}