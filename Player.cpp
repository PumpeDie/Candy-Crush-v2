#include "Player.h"

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

std::vector<std::vector<int>> Player::getGrille() const 
{
    return grille_;
}

void Player::reset()
{
    score_ = 0;
    moves_ = 10;
    grille_ = std::vector<std::vector<int>>(10, std::vector<int>(10, 0));
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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) 
        {
            save << grille_[i][j];
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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) 
        {
            save >> grille_[i][j];
        }
    }
    save.close();
}