#include "Grille.h"

Grille::Grille(Player* player) : player_(player), selectedCandyRow_(-1), selectedCandyCol_(-1)
{
    // Lignes verticales
	for (int i = 0; i < 11; i++) {
		lines_.push_back(sf::RectangleShape(sf::Vector2f(6, 503)));
	}
	// Lignes horizontales
	for (int i = 0; i < 11; i++) {
		lines_.push_back(sf::RectangleShape(sf::Vector2f(503, 6)));
	}
	// Positionnement des lignes verticales
	int j = 0;
	lines_[0].setPosition(708,300);
	for (int i = 1; i < 11; i++) {
		lines_[i].setPosition(757 + j, 300);
		j+=50;
	}
	// Positionnement des lignes horizontales
	int k = 0;
	lines_[11].setPosition(708,300);
	for (int i = 12; i < 22; i++) {
		lines_[i].setPosition(708, 349 + k);
		k+=50;
	}
	// Lignes de couleurs rouges
	for (int i = 0; i < lines_.size(); i++)
		lines_[i].setFillColor(sf::Color::Red);
}

Grille::~Grille() 
{
    
}

/* Fonctions */
void Grille::handleMouseClick(sf::RenderWindow* window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);

    // Vérifier si le clic de souris se trouve à l'intérieur de la zone de la grille
    if (worldPos.x >= 714 && worldPos.x < 714 + 10 * 50 &&
        worldPos.y >= 306 && worldPos.y < 306 + 10 * 50) {
        
        // Convertir les coordonnées de la souris en indices de ligne et de colonne dans la grille
        int col = (worldPos.x - 714) / 50;
        int row = (worldPos.y - 306) / 50;

		// Identifier les bonbons sélectionnés
        selectCandy(sf::Vector2i(col, row));
    }
}

void Grille::selectCandy(const sf::Vector2i& gridPosition)
{
    // Vérifier si les coordonnées de la grille sont valides
    if (gridPosition.x >= 0 && gridPosition.x < 10 &&
        gridPosition.y >= 0 && gridPosition.y < 10) {
        
        // Vérifier si la case de la grille à ces indices contient un bonbon
        std::vector<std::vector<int>> grille = player_->getGrille();
        if (grille[gridPosition.y][gridPosition.x] != 0) {
            // Sélectionner le bonbon enregistré dans la grille du joueur
            // Vous pouvez stocker ces indices pour une utilisation ultérieure
            // Par exemple, pour le déplacement ou l'échange de bonbons
            selectedCandyRow_ = gridPosition.y;
            selectedCandyCol_ = gridPosition.x;
            
            // Obtenir la couleur du bonbon sélectionné
            sf::Color candyColor = getColorAtPosition(grille, gridPosition.x, gridPosition.y);
            
            // Afficher un message de débogage indiquant le bonbon sélectionné et sa couleur
            std::cout << "Bonbon sélectionné à la position : Ligne " << selectedCandyRow_ << ", Colonne " << selectedCandyCol_ << std::endl;
            std::cout << "Couleur du bonbon : " << grille[gridPosition.y][gridPosition.x] << std::endl;
        }
    }
}
/*
bool Grille::isValidMove(const sf::Vector2i& source, const sf::Vector2i& destination)
{
    // Implémentez la logique de vérification de la validité du mouvement ici
}

void Grille::swapCandies(const sf::Vector2i& candy1, const sf::Vector2i& candy2)
{
    // Implémentez la logique d'échange de bonbons ici
}

void Grille::checkCombinations()
{
    // Implémentez la logique de vérification des combinaisons de bonbons ici
}
*/
void Grille::update(sf::RenderWindow* window, State& gamestate, const sf::Event& ev)
{
	if (ev.type == sf::Event::Closed)
		window->close();
	else if (ev.type == sf::Event::MouseButtonPressed)
		if (ev.mouseButton.button == sf::Mouse::Left)
			// Gérer les clics de souris gauche
			handleMouseClick(window) ;
	window->clear();
	render(*window);
	window->display();
}

void Grille::render(sf::RenderWindow& window) 
{
	// Dessiner les lignes de la grille
	for (int i = 0; i < lines_.size(); i++)
		window.draw(lines_[i]);

	// Dessiner les bonbons sur la grille
    auto grille = player_->getGrille(); // Récupérer la grille depuis player_
    for (int i = 0; i < grille.size(); i++) {
        for (int j = 0; j < grille[i].size(); j++) {
            sf::CircleShape candy(15.f); // Taille arbitraire pour les bonbons
            CandyColor color = static_cast<CandyColor>(grille[i][j]); // Obtenir la couleur associée au bonbon depuis player_
            candy.setFillColor(getColorForCandy(color)); // Obtenir la couleur associée au bonbon
            candy.setPosition(717 + i*50 + 3, 313 + j*50);
            window.draw(candy);
        }
    }
}
