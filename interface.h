#ifndef INTERFACE
#define INTERFACE
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"

class inter
{
public:
	inter();
	~inter();
	void draw(sf::RenderWindow &App);
	void setLife(float relatLife);
	bool enghBall();
	void setBall(int nbBall);
	bool isAlive();



private:
	//la vie
	float m_vie;
	sf::Texture m_i_vie;
	sf::Sprite m_sp_vie;

	//les munitions
	int m_nb_ball;
	/*sf::Texture m_i_munition;
	sf::Sprite m_sp_munition;*/
	sf::RectangleShape m_munitions;



};

#endif
