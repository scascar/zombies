#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "joueur.h"
#include "map.h"
#include "zombie.h"

class game
{
public:
	game();
	~game();
	void start(sf::RenderWindow &App);
	void Game_Over(sf::RenderWindow &App);
	void drawAll(sf::RenderWindow &App);

	//zombies
	void set_st_vague();
	void get_nb_zombies();
	void spawn_zombies();
	void draw_zombies(sf::RenderWindow &App);
	void move_zombies(sf::RenderWindow &App);
	void check_vague_zombies();

private:
	map		m_carte;
	joueur	m_joueur;

	//les variables propres aux zombies
	int m_vague;
	int m_nb_zombies;//le nombre de zombies pr�sents
	int m_spawn_zombies_restant;//le nombre restant a spawner
	std::vector<zombie> m_zombies;
	sf::Texture m_i_zombie;//une seule image pour tous les zombies
	sf::Texture m_i_zombie_mort;
	sf::Clock m_spawn_delay;
	float m_time_delay;
	sf::Clock m_vague_delay;
	float m_time_vague_delay;

		//l'affichage des vagues + Game over
	sf::Font m_police;
	sf::Text m_st_vague;
	sf::Text m_st_GameOver;

};

#endif