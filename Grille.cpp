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
    lines_[0].setPosition(708, 300);
    for (int i = 1; i < 11; i++) {
        lines_[i].setPosition(757 + j, 300);
        j += 50;
    }
    // Positionnement des lignes horizontales
    int k = 0;
    lines_[11].setPosition(708, 300);
    for (int i = 12; i < 22; i++) {
        lines_[i].setPosition(708, 349 + k);
        k += 50;
    }
    // Lignes de couleurs rouges
    for (int i = 0; i < lines_.size(); i++)
        lines_[i].setFillColor(sf::Color::Red);
}

Grille::~Grille()
{

}

/* Fonctions */
void Grille::checkAndRemoveCombinations()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 5); // Pour 6 couleurs différentes

    // Récupérer la grille du joueur
    auto grille =player_->getGrille();

    // Boucle pour vérifier et supprimer les combinaisons
    while (checkCombinations(grille)) {
        // Parcourir chaque bonbon dans la grille
        for (int i = 0; i < grille.size(); ++i) {
            for (int j = 0; j < grille[i].size(); ++j) {
                int candyType = grille[i][j];

                // Vérifier s'il y a une combinaison horizontale
                if (j < grille[i].size() - 2 &&
                    grille[i][j + 1] == candyType &&
                    grille[i][j + 2] == candyType) {
                    // Supprimer un des bonbons alignés horizontalement
                    grille[i][j + 1] = distrib(gen);
                }

                // Vérifier s'il y a une combinaison verticale
                if (i < grille.size() - 2 &&
                    grille[i + 1][j] == candyType &&
                    grille[i + 2][j] == candyType) {
                    // Supprimer un des bonbons alignés verticalement
                    grille[i + 1][j] = distrib(gen);
                }
            }
        }
    }
    player_->setGrille(grille);
}

void Grille::reajustementgrille() {
    int i = 0;
    auto grille = player_->getGrille();
    bool checkCombi = checkCombinations(grille);
    while (checkCombi && i<10) {
        suppressionBonbons();
        player_->upscore();
        faireTomberBonbons();
        i = i + 1;
    }
};
void Grille::suppressionBonbons()

{
    std::vector<std::vector<int>> grille = player_->getGrille();
    bool bonbonsSupprimes = false;

    // Parcourir la grille
    for (int i = 0; i < grille.size(); ++i) {
        for (int j = 0; j < grille[i].size(); ++j) {
            int couleurBonbon = grille[i][j];

            // V�rifier si le bonbon est d'une couleur valide
            if (couleurBonbon >= 0 && couleurBonbon <= 5) {
                // Vérifier les bonbons adjacents
                if (i < grille.size() - 2 && grille[i + 1][j] == couleurBonbon && grille[i + 2][j] == couleurBonbon) {
                    grille[i][j] = -1; // Marquer le bonbon comme supprimé
                    grille[i + 1][j] = -1;
                    grille[i + 2][j] = -1;
                    bonbonsSupprimes = true;
                }
                if (j < grille[i].size() - 2 && grille[i][j + 1] == couleurBonbon && grille[i][j + 2] == couleurBonbon) {
                    grille[i][j] = -1; // Marquer le bonbon comme supprimé
                    grille[i][j + 1] = -1;
                    grille[i][j + 2] = -1;
                    bonbonsSupprimes = true;
                }
            }
        }
    }
    if (bonbonsSupprimes) {
        player_->setGrille(grille);
    }

};

void Grille::faireTomberBonbons() {
    std::vector<std::vector<int>> grille = player_->getGrille();
    const int largeurGrille = grille.size();
    const int hauteurGrille = grille[0].size();

    // Faire tomber les bonbons
    for (int j = 0; j < hauteurGrille; ++j) {
        for (int i = largeurGrille - 1; i >= 0; --i) {
            if (grille[i][j] == -1) {
                // Faire tomber les bonbons au-dessus
                for (int k = i - 1; k >= 0; --k) {
                    if (grille[k][j] != -1) {
                        grille[i][j] = grille[k][j];
                        grille[k][j] = -1;
                        break;
                    }
                }
            }
        }
    }

    // Faire apparaître de nouveaux bonbons au sommet de la grille
    for (int j = 0; j < hauteurGrille; ++j) {
        for (int i = 0; i < largeurGrille; ++i) {
            if (grille[i][j] == -1) {
                // Générer un nouveau bonbon aléatoire
                grille[i][j] = rand() % 6; // 6 représente le nombre de couleurs différentes
            }
        }
    }

    // Mettre à jour la grille du joueur
    player_->setGrille(grille);
}

void Grille::handleMouseClick(sf::RenderWindow* window)
{
    int moves = player_->getMoves();
    if (moves <= 0) {
        std::cout << "Vous n'avez plus de mouvement restant";
    }
    else {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f worldPos = window->mapPixelToCoords(mousePos); 

    // Vérifier si le clic de souris se trouve à l'intérieur de la zone de la grille
        if (worldPos.x >= 714 && worldPos.x < 714 + 10 * 50 &&
            worldPos.y >= 306 && worldPos.y < 306 + 10 * 50) {

        // Convertir les coordonnées de la souris en indices de ligne et de colonne dans la grille
            int col = (worldPos.x - 714) / 50;
            int row = (worldPos.y - 306) / 50;

        // Identifier les bonbons sélectionnés
            if (selectedCandyRow_ == -1 && selectedCandyCol_ == -1) {
            // Sélectionner le bonbon cliqué
                selectCandy(sf::Vector2i(col, row));
            }
            else {
            // Si un bonbon est déjà sélectionné, vérifier si le mouvement est valide
                sf::Vector2i firstSelected(selectedCandyCol_, selectedCandyRow_);
                sf::Vector2i secondSelected(col, row);

            // Vérifier si le mouvement est valide avant d'effectuer l'échange
                if (isValidMove(firstSelected, secondSelected)) {
                // Échanger les bonbons
                    swapCandies(firstSelected, secondSelected);
                    reajustementgrille();
                    player_->setMove();
                    std::cout << "Score :" << player_->getScore();
                    std::cout << "Coups :" << player_->getMoves();
                    render(*window);
                }

            // Réinitialiser les bonbons sélectionnés
                selectedCandyRow_ = -1;
                selectedCandyCol_ = -1;
            };
        };
    };
}

void Grille::selectCandy(const sf::Vector2i& gridPosition)
{
    // Vérifier si les coordonnées de la grille sont valides
    if (gridPosition.x >= 0 && gridPosition.x < 10 &&
        gridPosition.y >= 0 && gridPosition.y < 10) {

        // Vérifier si la case de la grille à ces indices contient un bonbon
        std::vector<std::vector<int>> grille = player_->getGrille();
        if (grille[gridPosition.y][gridPosition.x] < 6) {
            // Sélectionner le bonbon enregistré dans la grille du joueur
            selectedCandyRow_ = gridPosition.y;
            selectedCandyCol_ = gridPosition.x;
        }
    }
}

bool Grille::isValidMove(const sf::Vector2i& source, const sf::Vector2i& destination)
{
    // Vérifier si les positions source et destination sont valides dans la grille
    if (source.x < 0 || source.x >= 10 || source.y < 0 || source.y >= 10 ||
        destination.x < 0 || destination.x >= 10 || destination.y < 0 || destination.y >= 10) {
        std::cout << "Mouvement invalide : positions en dehors des limites de la grille." << std::endl;
        return false;
    }

    // Vérifier si les positions sont adjacentes l'une à l'autre (horizontalement ou verticalement)
    int dx = std::abs(destination.x - source.x);
    int dy = std::abs(destination.y - source.y);
    if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
        // Le mouvement est valide s'il est horizontal ou vertical
        // Assurer que la destination ne d�passe pas les limites de la grille
        if (destination.x >= 0 && destination.x < 10 && destination.y >= 0 && destination.y < 10) {
            // Vérifier si le mouvement forme une combinaison de bonbons
            std::vector<std::vector<int>> tempGrille = player_->getGrille();
            std::swap(tempGrille[source.y][source.x], tempGrille[destination.y][destination.x]);
            bool validMove = checkCombinations(tempGrille);
            if (!validMove) {
                std::cout << "Mouvement invalide : aucun alignement de bonbons apr�s l'�change." << std::endl;
            }
            return validMove;
        }
    }
    // Si aucune des conditions ci-dessus n'est remplie, le mouvement n'est pas valide
    std::cout << "Mouvement invalide : les positions ne sont pas adjacentes." << std::endl;
    return false;
}

void Grille::swapCandies(const sf::Vector2i& candy1, const sf::Vector2i& candy2)
{
    // Vérifier si le mouvement est valide
    if (isValidMove(candy1, candy2)) {
        // Effectuer l'échange temporaire dans la grille
        std::vector<std::vector<int>> tempGrille = player_->getGrille();
        std::swap(tempGrille[candy1.y][candy1.x], tempGrille[candy2.y][candy2.x]);

        // Vérifier si le mouvement forme une combinaison
        if (checkCombinations(tempGrille)) {
            // Si le mouvement est valide et forme une combinaison, effectuer l'échange dans la grille du joueur
            auto grilleswap = player_->getGrille();
            std::swap(grilleswap[candy1.y][candy1.x], grilleswap[candy2.y][candy2.x]);
            player_->setGrille(grilleswap);
        }
    }
}

bool Grille::checkCombinations(const std::vector<std::vector<int>>& grille)
{
    // Logique de vérification des combinaisons de bonbons

    // Parcourir chaque bonbon dans la grille
    for (int i = 0; i < grille.size(); i++) {
        for (int j = 0; j < grille[i].size(); j++) {
            int candyType = grille[i][j];

            // Vérifier s'il y a une combinaison horizontale
            if (j < grille[i].size() - 2 &&
                grille[i][j + 1] == candyType &&
                grille[i][j + 2] == candyType) {
                return true; // Une combinaison horizontale est trouvée
            }

            // Vérifier s'il y a une combinaison verticale
            if (i < grille.size() - 2 &&
                grille[i + 1][j] == candyType &&
                grille[i + 2][j] == candyType) {
                return true; // Une combinaison verticale est trouvée
            }
        }
    }
    // Aucune combinaison n'a été trouvée
    return false;
}


void Grille::update(sf::RenderWindow* window, State& gamestate, const sf::Event& ev)
{
    if (ev.type == sf::Event::Closed)
        window->close();
    else if (ev.type == sf::Event::MouseButtonPressed)
        if (ev.mouseButton.button == sf::Mouse::Left)
            // Gérer les clics de souris gauche
            handleMouseClick(window);
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
            CandyColor color = static_cast<CandyColor>(grille[i][j]); // Obtenir la couleur associ�e au bonbon depuis player_
            candy.setFillColor(getColorForCandy(color)); // Obtenir la couleur associ�e au bonbon
            candy.setPosition(717 + j * 50 + 3, 313 + i * 50);
            window.draw(candy);
        }
    }
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Gatrich.otf")) {
        // Gérer l'erreur de chargement de la police
    }
    sf::Text scoreText("Score: " + std::to_string(player_->getScore()), font, 20);
    scoreText.setPosition(10, 10);
    window.draw(scoreText);

    // Dessiner le nombre de coups
    sf::Text movesText("Coups: " + std::to_string(player_->getMoves()), font, 20);
    movesText.setPosition(10, 40);
    window.draw(movesText);
}