#include "Game.h"

// Fonctions privées
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Candy Crush");
    window->setFramerateLimit(60);
}

void Game::initGrille()
{
    grille = new Grille();
}

void Game::initPlayer()
{
    player = new Player();
}

void Game::initMenu()
{
    menu = new Menu(window->getSize().x,window->getSize().y);
}

// Constructeurs & Destructeurs
Game::Game()
{
    initWindow();
    initGrille();
    initMenu();
    initPlayer();
}

Game::~Game()
{
    delete window;
    delete grille;
    delete menu;
    delete player;
}


// Fonctions
void Game::run()
{
    while (window->isOpen()) 
    {
        update();
        render();
    }
}

void Game::update()
{
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.Event::type == sf::Event::Closed)
            window->close();
        if (ev.type == sf::Event::KeyPressed) 
        {
            if (ev.key.code == sf::Keyboard::Up) {
                menu->MoveUp();
                break;
            }
            if (ev.key.code == sf::Keyboard::Down) {
                menu->MoveDown();
                break;
            }
            if (ev.key.code == sf::Keyboard::Escape) {
                window->close();
                break;
            }
            if (ev.key.code == sf::Keyboard::Return) 
            {
                if (menu->pressed() == 0)
                    grille->update(window);
                if (menu->pressed() == 1)
                    break;
                if (menu->pressed() == 2)
                    break;
                if (menu->pressed() == 3)
                    window->close();
            }
        }
    }
}

void Game::render()
{
    // Nettoyage frame précédent
    window->clear();

    // Affichage du nouveau frame
    menu->render(*window);
    window->display();
}