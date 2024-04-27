#include "Player.h"

sf::Color getColorForCandy(CandyColor color) {
    switch (color) {
        case RED:
            return sf::Color::Red;
        case BLUE:
            return sf::Color::Blue;
        case GREEN:
            return sf::Color::Green;
        case YELLOW:
            return sf::Color::Yellow;
        case MAGENTA:
            return sf::Color::Magenta;
        case CYAN:
            return sf::Color::Cyan;
        default: // Valeur par défaut, si erreur
            return sf::Color::White; 
    }
}

sf::Color getColorAtPosition(const std::vector<std::vector<int>>& grille, int row, int col) {
    if (row >= 0 && row < grille.size() && col >= 0 && col < grille[0].size()) {
        // Obtenez le type de bonbon à la position spécifiée dans la grille
        int candyType = grille[row][col];
        // Convertissez le type de bonbon en couleur correspondante
        return getColorForCandy(static_cast<CandyColor>(candyType));
    } else {
        // Si la position est en dehors des limites de la grille, retournez une couleur par défaut (par exemple, blanc)
        return sf::Color::White;
    }
}

Player::Player() 
{
    score_ = 0;
    moves_ = 10;
    grille_ = std::vector<std::vector<int>>(10, std::vector<int>(10, 0));
} 

Player::~Player() 
{

}

int Player::getScore()
{
    return score_;
}

int Player::getMoves()
{
    return moves_;
}

std::vector<std::vector<int>>& Player::getGrille() 
{
    return grille_;
}

void Player::reset()
{
    score_ = 0;
    moves_ = 10;
    grille_ = std::vector<std::vector<int>>(10, std::vector<int>(10, 0));
    initRandomCandies();
}

void Player::save(const std::string& filename)
{
    std::ofstream save(filename); // Ouvre le fichier avec le nom spécifié
    if (!save.is_open()) 
    {
        // Gestion de l'erreur
        std::cerr << "Erreur lors de l'ouverture du fichier de sauvegarde." << std::endl;
        return;
    }

    // Écriture des données dans le fichier
    save << score_ << std::endl;
    save << moves_ << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j) 
        {
            save << grille_[i][j] << " ";
        }
        save << std::endl;
    }
    save.close();
}

void Player::load(const std::string& filename)
{
    std::ifstream save(filename); // Ouvre le fichier avec le nom spécifié
    if (!save.is_open()) 
    {
        // Gestion de l'erreur
        std::cerr << "Erreur lors de l'ouverture du fichier de chargement." << std::endl;
        return;
    }

    // Lecture des données depuis le fichier
    save >> score_;
    save >> moves_;
    grille_.resize(10, std::vector<int>(10, 0));
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j) 
        {
            save >> grille_[i][j];
        }
    }
    save.close();
}

// Fonction pour initialiser la grille avec des bonbons aléatoires
void Player::initRandomCandies()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 5); // Pour 6 couleurs différentes

    for (int i = 0; i < grille_.size(); ++i) {
        for (int j = 0; j < grille_[i].size(); ++j) {
            grille_[i][j] = static_cast<CandyColor>(distrib(gen));
        }
    }
}