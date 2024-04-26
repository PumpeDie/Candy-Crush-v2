#include "Player.h"

Player::Player() 
{
    score_ = 0;
    moves_ = 0;
} 

Player::~Player() 
{

}

int Player::getScore(std::ifstream save)
{
    int score;
    save.open("data.dat");
    save >> score_;
    score = score_;
    save.close();
    return score;
}

int Player::getMoves(std::ifstream save)
{
    int moves;
    save.open("data.dat");
    save >> moves_;
    moves = moves_;
    save.close();
    return moves;
}

void Player::save(std::ofstream save)
{
    save.open("data.dat");
    save << score_ << std::endl;
    save << moves_ << std::endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) 
        {
            save << grille_[i][j];
        }
    }
    save.close();
}

void Player::load(std::ifstream save)
{
    save.open("data.dat");
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