#ifndef GAME_H
#define GAME_H

#include "Candy.h"
#include "Menu.h"
#include "Grille.h"

class Game
{
private:
    sf::RenderWindow* window;

    // Menu
    Menu* menu;

    // Grille
    Grille* grille;

    // Bonbon
    Candy* candy;

    // Fonctions privées
    void initWindow();
    void initMenu();
    void initGrille();
    void initCandy();

public:
    // Constructeurs & Destructeurs
    Game();
    virtual ~Game();

    // Fonctions
    void run();
    void update();
    void render();
};

#endif