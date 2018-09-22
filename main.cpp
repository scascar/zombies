//par Oscar Blazejewski
//projet d�but� fin 2009 � peu pr�s, avec juste quelques bases
//repris le 1er juin 2011
//version actuelle: 0.1 solo



#include "define.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    // Cr�ation de la fen�tre de rendu
	sf::RenderWindow App(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "zombies");

	game game;
	game.start(App);

    return EXIT_SUCCESS;
}
