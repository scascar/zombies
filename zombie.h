#ifndef ZOMBIE
#define ZOMBIE
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "map.h"
#include <math.h>

class zombie
{
public:
	zombie();
	~zombie();
	void draw(sf::RenderWindow &App);//affiche
	void orientation(float x,float y);//oriente vers le joueur
	bool canMove(map &map,int x, int y);//check sur la map si il peut bouger
	void move(map &map,int xJoueur, int yJoueur,sf::RenderWindow &App);//avance vers le joueur
	bool attack(int x, int y);//regarde s' il attaque le joueur
	void setLife(int relatLife);//ajoute/enleve de la vie
	sf::Vector2f getPosition();//retourne la position sous forme de vector2f
	void create(map &map,sf::Texture i_zombie, sf::Texture i_zombie_mort,int nb_spawn);//place le zombie a son spawn
	void setPosition(int x,int y);//place le zombie a x et y
	bool isAlive();		//return trus si il est en vie
	void setMap(map &map);	//charge la map
	void setMoveTarget(int x, int y);	//la ou il va bouger
	bool IsMTrgtActive();	
	void reload_image();

private:

	sf::Texture m_i_zombie_mort;
	sf::Texture m_i_zombie;
	sf::Sprite m_sp_zombie;
	int m_speed;
	int m_vie;

	// IA DE PATHFINDING
	bool m_carte[CASES_X][CASES_Y];
	int	m_poids[CASES_X][CASES_Y];
	sf::Vector2f m_moveTarget;
	sf::Clock m_clock;
};

#endif