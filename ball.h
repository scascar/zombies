#ifndef BALL
#define BALL
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "map.h"


class ball
{
public:
	ball();
	~ball();
	void create();
	void tirer(int x,int y,int cibleX, int cibleY,float angle);//initialise la balle et ses coordonees
	void move(map &map);			//fait bouger la balle
	void draw(sf::RenderWindow &App);//affiche la balle
	bool attack(int x,int y);			//return true si elle touche un zombie
	bool isActive();

private:

	sf::CircleShape m_sp_ball;
	int XTarget;
	int YTarget;
	double m_speed;
	double Xmove;
	double Ymove;
	bool m_isActive;



};

#endif