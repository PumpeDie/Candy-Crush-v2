#ifndef GAME_H
#define GAME_H

#include "Candy.h"
#include "Menu.h"
#include "Grille.h"
#include "Player.h"

// Auteur : Samuel
enum State {InMenu, InGame, None};

class Game
{
private:
    State gamestate_;
    sf::RenderWindow* window;

    // Menu
    Menu* menu;

    // Grille
    Grille* grille;

    // Joueur
    Player* player;

    // Fonctions privées
    void initWindow();
    void initMenu();
    void initGrille();
    void initPlayer();

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