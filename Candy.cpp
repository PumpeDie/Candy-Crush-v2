#include "Candy.h"

// Fonctions privées
void Candy::initTexture() 
{
    // Charger la texture depuis un fichier (faire plus tard)
    if (!texture.loadFromFile("assets/textures/test.png"))
    {
        std::cout <<"Pas de texture"<< std::endl;
    }
    

}

void Candy::initSprite()
{
    // Charger la texture sur le sprite
    sprite.setTexture(texture);

    // Redimensionner
    sprite.scale(0.3f, 0.3f);
    
}

// Constructeur & Destructeur
Candy::Candy() 
{
    initTexture();
    initSprite();
}

Candy::~Candy()
{

}

// Fonctions
void Candy::update() 
{

}

void Candy::render(sf::RenderTarget& target) 
{
    
}
