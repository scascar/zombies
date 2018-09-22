#include "arme.h"

arme::arme()
{
	m_type_arme = PISTOLET;
	m_n_ball = 0; //le numero de la balle
}

arme::~arme()
{


}

void arme::create()
{
	m_type_arme = PISTOLET;
	m_n_ball = 0; //le numero de la balle
	for(int i =0;i<NB_BALLES_MAX;i++)
		m_balls[i].create();


}
void arme::drawAll(sf::RenderWindow &App)
{
	for(int i =0;i<NB_BALLES_MAX;i++)
		m_balls[i].draw(App);

	int compteur = 0;
	for(int j = 0;j<NB_BALLES_MAX;j++)
		if(!m_balls[j].isActive())
		{
			compteur++;
		}

//std::cout << "balles utilisables : " << compteur << std::endl; //debugging

}

void arme::moveBall(map &map)
{
	for(int i =0;i<NB_BALLES_MAX;i++)
		m_balls[i].move(map);
}


void arme::tirer(int x, int y, int cibleX, int cibleY, float angle)
{
	if(m_n_ball <NB_BALLES_MAX)
	{
		m_n_ball ++;
	}
	else
	{
		m_n_ball = 0;
	}
	//std::cout << m_n_ball << std::endl;
	m_balls[m_n_ball].tirer(x,y,cibleX,cibleY,angle);
}

bool arme::attack(int x, int y)
{
	for(int i =0;i<NB_BALLES_MAX-1;i++)
	{
		if(m_balls[i].isActive())
			if(m_balls[i].attack(x,y))
			return true;
	}
	return false;
}
