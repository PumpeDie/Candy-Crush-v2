
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel

// Couleurs des bonbons
enum CandyColor {
    RED = 0,
    BLUE = 1,
    GREEN = 2,
    YELLOW = 3,
    MAGENTA = 4,
    CYAN = 5
};
sf::Color getColorForCandy(CandyColor color);

class Player
{
private:
    int score_;
    int moves_;
    std::vector<std::vector<int>> grille_;
public:
    // Constructeur & Destructeur
    Player();
    virtual ~Player();

    // Fonctions
    int getScore();
    int getMoves();
    //Décrémente d'un le nombre de coups restant
    void setMove();
    //Augmente le score
    void upscore();
    std::vector<std::vector<int>> getGrille() const;
    void reset();
    void save(const std::string& filename);
    void load(const std::string& filename);
    void setGrille(const std::vector<std::vector<int>> newGrille);

    // Fonction pour initialiser la grille avec des bonbons aléatoires
    void initRandomCandies();
};
#endif
