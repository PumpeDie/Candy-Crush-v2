#ifndef MENU_H
#define MENU_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Menu 
{
private:
	sf::Text menuprincipal[3];
	sf::Font font_;
	int selected_;
public :
	// Constructeurs et Destructeurs
	Menu(float width, float height);
	virtual ~Menu();

	// Fonctions
	void MoveUp();
	void MoveDown();
	void setSelected(int n);
	int pressed() {return selected_;}

    void update();
    void render(sf::RenderWindow& window);
};
#endif