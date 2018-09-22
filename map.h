#ifndef MAP
#define MAP
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include <fstream>

class map
{
public:
	map();
	~map();
	void load();
	void draw(sf::RenderWindow &App);
	bool collision(int x, int y);
	sf::Vector2f setZombiePos(int nb_spawn);
	sf::Vector2f setJoueurPos();
	bool getMap(int x,int y);

private:
	sf::Texture m_i_sol;
	sf::Sprite m_sp_sol;

	sf::Texture m_i_obstacle;
	sf::Sprite m_sp_obstacle;

	int m_carte[CASES_X][CASES_Y];//carte
};

#endif
