#include "Game.h"

// Fonctions privées
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Candy Crush");
    window->setFramerateLimit(60);
}

void Game::initGrille()
{
    grille = new Grille(player);
}

void Game::initPlayer()
{
    player = new Player();
}

void Game::initMenu()
{
    menu = new Menu(window->getSize().x, window->getSize().y);
}


// Constructeurs & Destructeurs
Game::Game() : gamestate_(State::InMenu), window(nullptr), menu(nullptr), grille(nullptr), player(nullptr)
{
    initWindow();
    initPlayer();
    initGrille();
    initMenu();
}

Game::~Game()
{
    delete window;
    delete player;
    delete grille;
    delete menu;
}

// Fonctions pour la gestion des données du joueur
int Game::getPlayerScore() const
{
    std::ifstream save("data.dat");
    if (!save.is_open()) {
        // Gestion de l'erreur
        return -1;
    }
    int score = player->getScore();
    save.close();
    return score;
}

int Game::getPlayerMoves() const
{
    std::ifstream save("data.dat");
    if (!save.is_open()) {
        // Gestion de l'erreur
        return -1;
    }
    int moves = player->getMoves();
    save.close();
    return moves;
}


// Fonctions
void Game::run()
{
    while (window->isOpen())
    {
        update();
        render();

        if (gamestate_ == State::InGame && getPlayerMoves() == 0)
        {
            gamestate_ = State::GameOver;
        }
    }
}

void Game::update()
{
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.Event::type == sf::Event::Closed)
            window->close();
        else if (gamestate_ == State::InMenu)
        {
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
                    switch (menu->pressed()) {
                    case 0: // Nouvelle Partie
                        player->reset();            // Réinitialiser les données du joueur
                        grille->checkAndRemoveCombinations();
                        gamestate_ = State::InGame;
                        break;
                    case 1: // Continuer
                        player->load("data.dat");   // Charger le jeu depuis une sauvegarde
                        gamestate_ = State::InGame;
                        break;
                    case 2: // Sauvegarder
                        player->save("data.dat");   // Sauvegarder le jeu dans un fichier
                        break;
                    case 3: // Quitter
                        window->close();
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
        else if (gamestate_ == State::InGame)
        {
            if (ev.type == sf::Event::KeyPressed)
                if (ev.key.code == sf::Keyboard::Escape)
                {
                    gamestate_ = State::InMenu;
                    return;
                }
            grille->update(window, gamestate_, ev);
        }
        else if (gamestate_ == State::GameOver)
        {
            window->clear();

            sf::Text gameOverText;
            font.loadFromFile("assets/fonts/Gatrich.otf");
            gameOverText.setFont(font); 
            gameOverText.setString("Game Over");
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(window->getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window->getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);

            sf::Text scoreText;
            scoreText.setFont(font); 
            scoreText.setString("Score: " + std::to_string(getPlayerScore()));
            scoreText.setCharacterSize(30);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(window->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, gameOverText.getPosition().y + gameOverText.getGlobalBounds().height + 20);

            window->draw(gameOverText);
            window->draw(scoreText);
            window->display();
            return;
        }
    }
}

void Game::render()
{
    // Nettoyage frame précédent
    window->clear();

    // Affichage du nouveau frame
    if (gamestate_ == State::InMenu)
        menu->render(*window);
    else if (gamestate_ == State::InGame)
        grille->render(*window);
    window->display();
}