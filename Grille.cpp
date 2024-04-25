#include "Grille.h"

Grille::Grille() 
{
    // Lignes verticales
	for (int i = 0; i < 11; i++) {
		lines_.push_back(sf::RectangleShape(sf::Vector2f(6, 503)));
	}
	// Lignes horizontales
	for (int i = 0; i < 11; i++) {
		lines_.push_back(sf::RectangleShape(sf::Vector2f(503, 6)));
	}
	// Positionnement des lignes verticales
	int j = 0;
	lines_[0].setPosition(708,300);
	for (int i = 1; i < 11; i++) {
		lines_[i].setPosition(757 + j, 300);
		j+=50;
	}
	// Positionnement des lignes horizontales
	int k = 0;
	lines_[11].setPosition(708,300);
	for (int i = 12; i < 22; i++) {
		lines_[i].setPosition(708, 349 + k);
		k+=50;
	}
	// Lignes de couleurs rouges
	for (int i = 0; i < lines_.size(); i++)
		lines_[i].setFillColor(sf::Color::Red);
}

Grille::~Grille() 
{
    
}

// Fonctions
void Grille::update(sf::RenderWindow* window)
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Jeu");
	while (window->isOpen())
	{
		sf::Event ev;
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window->close();
			if (ev.type == sf::Event::KeyPressed) 
				if (ev.key.code == sf::Keyboard::Escape)
                	window->close();
		}
		window->clear();
		render(*window);
		window->display();
	}
}

void Grille::render(sf::RenderWindow& window) 
{
	for (int i = 0; i < lines_.size(); i++)
		window.draw(lines_[i]);
}