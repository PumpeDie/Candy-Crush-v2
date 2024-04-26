#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel

// Declaration pour le type State
enum State {InMenu, InGame};

class Grille
{
private:
    Player* player_;
    std::vector<sf::RectangleShape> lines_;
    
public:
    // Constructeur & Destructeur
    Grille(Player* player);
    virtual ~Grille();

    // Fonctions
    void update(sf::RenderWindow* window, State& gamestate);
    void render(sf::RenderWindow& window);
};

#endif