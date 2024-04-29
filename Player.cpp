
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
    default: // Valeur par d�faut, si erreur
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
void Player::setGrille(const std::vector<std::vector<int>> newGrille) {
    // Mettre � jour la grille du joueur avec la nouvelle grille fournie
    grille_ = newGrille;
}
void Player::setMove() {
    // Mettre � jour la grille du joueur avec la nouvelle grille fournie
    int newmoves = moves_ - 1;
    moves_ = newmoves;
}
void Player::upscore() {
    double newscore = score_ + 10;
    score_ = newscore;
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
    initRandomCandies();
}

void Player::save(const std::string& filename)
{
    std::ofstream save(filename); // Ouvre le fichier avec le nom sp�cifi�
    if (!save.is_open())
    {
        // Gestion de l'erreur
        std::cerr << "Erreur lors de l'ouverture du fichier de sauvegarde." << std::endl;
        return;
    }

    // �criture des donn�es dans le fichier
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
    std::ifstream save(filename); // Ouvre le fichier avec le nom sp�cifi�
    if (!save.is_open())
    {
        // Gestion de l'erreur
        std::cerr << "Erreur lors de l'ouverture du fichier de chargement." << std::endl;
        return;
    }

    // Lecture des donn�es depuis le fichier
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

// Fonction pour initialiser la grille avec des bonbons al�atoires
void Player::initRandomCandies()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 5); // Pour 6 couleurs diff�rentes

    for (int i = 0; i < grille_.size(); ++i) {
        for (int j = 0; j < grille_[i].size(); ++j) {
            grille_[i][j] = static_cast<CandyColor>(distrib(gen));
        }
    }
}
