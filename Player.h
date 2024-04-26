#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Auteur : Samuel
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
    int getScore(std::ifstream save);
    int getMoves(std::ifstream save);
    void save(std::ofstream save);
    void load(std::ifstream save);
};
#endif