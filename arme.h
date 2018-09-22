#ifndef ARME
#define ARME
#include <iostream>
#include "ball.h"
#include <SFML/Graphics.hpp>
#include "map.h"
class arme
{
public:
	arme();
	~arme();
	void create();
	void moveBall(map &map);
	void drawAll(sf::RenderWindow &App);
	void tirer(int x,int y,int cibleX, int cibleY,float angle);
	bool attack(int x,int y);

private:
	ball m_balls[NB_BALLES_MAX];//un tableau qui peut contenir 100 balles (c est à chier mais bon)
	int m_n_ball;
	int m_type_arme;



};
#endif