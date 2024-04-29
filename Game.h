#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Grille.h"

// Auteur : Marie
class Game
{
private:
    State gamestate_;
    sf::RenderWindow* window;
	sf::Font font;

    // Menu
    Menu* menu;

    // Grille
    Grille* grille;

    // Joueur
    Player* player;


    // Fonctions priv�es
    void initWindow();
    void initMenu();
    void initGrille();
    void initPlayer();

public:
    // Constructeurs & Destructeurs
    Game();
    virtual ~Game();

    // Fonctions pour la gestion des données du joueur
    int getPlayerScore() const;
    int getPlayerMoves() const;

    // Fonctions
    void run();
    void update();
    void render();
};

#endif