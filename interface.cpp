#include "interface.h"

inter::inter()
{
	//la vie
	m_vie = 100;
	m_i_vie.loadFromFile("images/vie.bmp");
	m_sp_vie.setTexture(m_i_vie);
	m_sp_vie.setPosition(20,HAUTEUR_FENETRE-50);

		//les munitions
	m_nb_ball = NB_MUNITIONS_MAX;
	m_munitions.setSize(sf::Vector2f(180,35));
	m_munitions.setPosition(20,15);
	m_munitions.setOutlineColor(sf::Color(0,0,200));

}

inter::~inter()
{
}

void inter::draw(sf::RenderWindow &App)
{
		//la vie
	m_sp_vie.setTextureRect(sf::IntRect(0,0,m_vie*5,30));
	if(m_vie != 0)
	App.draw(m_sp_vie);

	//les munitions : on dessine jusqu� 10 carr�s  qui representent la proportionde munitions
//	for(int i=0;i<m_nb_ball*15/NB_MUNITIONS_MAX ;i++)// on fera une echelle de 20 pour donner la proportion de balles restantes
//	{
//		
//			m_munitions = sf::Shape::Rectangle(15*i + 20,10,15*i+10,50,sf::Color(0,0,12*i));
//	}


}

void inter::setLife(float relatLife)
{
	m_vie += relatLife;
	if(m_vie <0)
		m_vie = 0;
	

	
}

bool inter::enghBall() //enough ball : il en reste?
{
	std::cout << "munitions :" << m_nb_ball << std::endl;
	if(m_nb_ball > 0)
		return true;
	else
		return false;
}

void inter::setBall(int nbBall)
{
	m_nb_ball += nbBall;
}

bool inter::isAlive()
{
	if(m_vie > 0)
		return true;
	else
		return false;
}
