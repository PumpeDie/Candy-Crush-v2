#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel et Marie

// Declaration pour le type State
enum State { InMenu, InGame, GameOver };

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
    // Fonction pour vérifier les combinaisons et supprimer les bonbons align�s
    void checkAndRemoveCombinations();

    // Fonction pour remplir les cases vides
    void fillEmptyCells();

    // D�tection des clics de souris sur les bonbons
    void handleMouseClick(sf::RenderWindow* window);

    // Identification des bonbons sélectionnés
    void selectCandy(const sf::Vector2i& gridPosition);

    // Vérification de la validité du déplacement
    bool isValidMove(const sf::Vector2i& source, const sf::Vector2i& destination);

    // Échange de bonbons
    void swapCandies(const sf::Vector2i& candy1, const sf::Vector2i& candy2);

    // Vérification des combinaisons de bonbons
    bool checkCombinations(const std::vector<std::vector<int>>& grille);

    // Réarrange la grille 
    void reajustementgrille();

    //Suppression des bonbons contigu
    void suppressionBonbons();
    
    // Tombée des bonbons de la grille
    void faireTomberBonbons();


    void update(sf::RenderWindow* window, State& gamestate, const sf::Event& ev);
    void render(sf::RenderWindow& window);
};

#endif