#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel

// Declaration pour le type State
enum State { InMenu, InGame };

class Grille
{
private:
    Player* player_;
    std::vector<sf::RectangleShape> lines_;
    int selectedCandyRow_;
    int selectedCandyCol_;

public:
    // Constructeur & Destructeur
    Grille(Player* player);
    virtual ~Grille();

    /* Fonctions */
    // Fonction pour v�rifier les combinaisons et supprimer les bonbons align�s
    void checkAndRemoveCombinations();

    // D�tection des clics de souris sur les bonbons
    void handleMouseClick(sf::RenderWindow* window);

    // Identification des bonbons s�lectionn�s
    void selectCandy(const sf::Vector2i& gridPosition);

    // V�rification de la validit� du d�placement
    bool isValidMove(const sf::Vector2i& source, const sf::Vector2i& destination);

    // �change de bonbons
    void swapCandies(const sf::Vector2i& candy1, const sf::Vector2i& candy2);

    // V�rification des combinaisons de bonbons
    bool checkCombinations(const std::vector<std::vector<int>>& grille);

    // R�arrange la grille 
    void réajustementgrille();

    //Suppression des bonbons contigu
    void suppressionBonbons();
    // Tomb�e des bonbons de la grille
    void faireTomberBonbons();


    void update(sf::RenderWindow* window, State& gamestate, const sf::Event& ev);
    void render(sf::RenderWindow& window);
};

#endif