#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel
class Grille
{
private:
    std::vector<sf::RectangleShape> lines_;
    
public:
    // Constructeur & Destructeur
    Grille();
    virtual ~Grille();

    // Fonctions
    void update(sf::RenderWindow* window);
    void render(sf::RenderWindow& window);
};

#endif