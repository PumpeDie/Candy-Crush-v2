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
    int getScore();
    int getMoves();
    std::vector<std::vector<int>> getGrille() const;
    void reset();
    void save(const std::string& filename);
    void load(const std::string& filename);
};
#endif