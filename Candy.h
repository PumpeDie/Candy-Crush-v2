#ifndef CANDY_H
#define CANDY_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Candy
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    // Fonctions privées
    void initSprite();
    void initTexture();
public:
    // Constructeur & Destructeur
    Candy();
    virtual ~Candy();

    // Fonctions
    void update();
    void render(sf::RenderTarget& target);
};
#endif