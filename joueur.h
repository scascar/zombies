#ifndef JOUEUR
#define JOUEUR
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "map.h"
#include "arme.h"
#include "interface.h"
#include <math.h>



class joueur
{
public:
	joueur();
	~joueur();

	void draw(sf::RenderWindow &App);
	void move(sf::RenderWindow &App,map &map);
	void orientation(sf::RenderWindow &App);//s' oriente en fonction de la souris

	void tirer(sf::RenderWindow &App);
	sf::Vector2f getPosition();
	void setLife(float relatLife);
	bool attack(int x,int y);
	void create(map &map,sf::RenderWindow &App);
	bool isAlive();
	bool canMove(map &,int , int );

private:
	sf::Texture m_i_joueur;
	sf::Sprite m_sp_joueur;
	int m_speed;
	arme m_arme;
	inter m_interface;
	bool m_canShot;
	sf::View m_camera;
	sf::Clock m_clock;

};

#endif