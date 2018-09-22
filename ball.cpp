#include "ball.h"

ball::ball()
{

}


ball::~ball()
{


}

void ball::draw(sf::RenderWindow &App)
{
	if(m_isActive)
		App.draw(m_sp_ball);

}

void ball::move(map &map)
{
	if(!map.collision((m_sp_ball.getPosition().x+Xmove)/TAILLE_CASE,(m_sp_ball.getPosition().y+Ymove)/TAILLE_CASE))
	m_sp_ball.move(Xmove,Ymove);
	else
		create();

}

void ball::tirer(int x, int y, int cibleX, int cibleY,float angle)
{
	if(m_sp_ball.getPosition().x < 0 ||m_sp_ball.getPosition().x > LARGEUR_FENETRE ||m_sp_ball.getPosition().y < 0 ||m_sp_ball.getPosition().y > HAUTEUR_FENETRE)
	{
		m_isActive = true;
		m_sp_ball.setPosition(x,y);
		XTarget = cibleX;
		YTarget = cibleY;

		Xmove = m_speed*cos(3.14 *(270-angle) / 180 );
		Ymove = m_speed*sin(3.14 *(270 -angle) / 180);
	}
}

bool ball::attack(int x, int y)
{
	if(m_sp_ball.getPosition().x +TAILLE_CASE/2 > x &&m_sp_ball.getPosition().x -TAILLE_CASE/2< x &&m_sp_ball.getPosition().y +TAILLE_CASE/2 > y &&m_sp_ball.getPosition().y -TAILLE_CASE/2 < y )
	{
		create();
		return true;
	}
	else 
	{
		return false;
	}

}

bool ball::isActive()
{
	if(m_isActive)
		return true;
	else
		return false;

}


void ball::create()
{
	m_sp_ball.setRadius(3);
	m_sp_ball.setOutlineColor(sf::Color::Black);
	XTarget = 2000; 
	YTarget = 0;
	m_sp_ball.setPosition(10000,0);
	m_speed = 20;
	m_isActive = false;
}
