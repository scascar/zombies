#include "joueur.h"

joueur::joueur()
{
	//chargement des images
	sf::Image im;
	im.loadFromFile("images/joueur.bmp");
	im.createMaskFromColor(sf::Color(0, 0, 255, 255));
	m_i_joueur.update(im);
	m_sp_joueur.setTexture(m_i_joueur);

	m_sp_joueur.setOrigin(TAILLE_CASE/2,TAILLE_CASE/2);

	m_speed = 100;
	m_canShot = true;
	m_arme.create();

}

joueur::~joueur()
{
	
} 



void joueur::draw(sf::RenderWindow &App)
{
	App.draw(m_sp_joueur);
	m_arme.drawAll(App);
	m_interface.draw(App);

}

bool joueur::canMove(map &map,int x, int y)
{
	if(map.collision((x-18)/TAILLE_CASE,(y-18)/TAILLE_CASE))
	{
		return false;
	}
	if(map.collision((x-18)/TAILLE_CASE,(y+18)/TAILLE_CASE))
	{
		return false;
	}
	if(map.collision((x+18)/TAILLE_CASE,(y-18)/TAILLE_CASE))
	{
		return false;
	}
	if(map.collision((x+18)/TAILLE_CASE,(y+18)/TAILLE_CASE))
	{
		return false;
	}

	return true;
}

void joueur::orientation(sf::RenderWindow &App)
{
	
	int ecartX = sf::Mouse::getPosition().x - m_sp_joueur.getPosition().x;
	int ecartY = sf::Mouse::getPosition().y - m_sp_joueur.getPosition().y;
	
	if(ecartX > 0)
	{
		if(ecartY > 0)
		{
			m_sp_joueur.setRotation(270-180*atan((double)ecartY/ecartX)/3.14);

		}
		if(ecartY < 0)
		{
			m_sp_joueur.setRotation(270+180*atan((double)ecartY/-ecartX)/3.14);
		
		}

	}

	else if(ecartX < 0)
	{
		if(ecartY > 0)
		{
			m_sp_joueur.setRotation(180+180*atan((double)ecartX/ecartY)/3.14);
		}
		if(ecartY < 0)
		{
			m_sp_joueur.setRotation(180*atan((double)-ecartX/-ecartY)/3.14);
		
		}
	}

}

void joueur::move(sf::RenderWindow &App,map &map)
{
	float distance;
	// R�cup�ration du temps �coul�
	float ElapsedTime = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();
	distance = ElapsedTime* m_speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if(distance+m_sp_joueur.getPosition().x-TAILLE_CASE/2> 0)
			if(canMove(map,-distance + m_sp_joueur.getPosition().x,m_sp_joueur.getPosition().y))
				m_sp_joueur.move(-distance, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		if(distance+m_sp_joueur.getPosition().x+TAILLE_CASE/2 < LARGEUR_FENETRE)
			if(canMove(map,distance+m_sp_joueur.getPosition().x,m_sp_joueur.getPosition().y))
				m_sp_joueur.move( distance, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
	{
		if(distance+m_sp_joueur.getPosition().y-TAILLE_CASE/2 > 0)
			if(canMove(map,m_sp_joueur.getPosition().x,-distance + m_sp_joueur.getPosition().y))
				m_sp_joueur.move(0,-distance);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if(distance+m_sp_joueur.getPosition().y+TAILLE_CASE/2 < HAUTEUR_FENETRE)
			if(canMove(map,m_sp_joueur.getPosition().x,distance+ m_sp_joueur.getPosition().y))
				m_sp_joueur.move(0,distance);
	}

	//on bouge la balle
	m_arme.moveBall(map);
}

void joueur::tirer(sf::RenderWindow &App)
{
	if(m_canShot)
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if(m_interface.enghBall())
			{
				m_arme.tirer(m_sp_joueur.getPosition().x,m_sp_joueur.getPosition().y,sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,m_sp_joueur.getRotation());
				m_interface.setBall(-1);
				m_canShot = false;
			}
			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))//si le bouton est relach�
				m_canShot = true;

}

sf::Vector2f joueur::getPosition()
{
	return m_sp_joueur.getPosition();
}

void joueur::setLife(float relatLife)
{
	m_interface.setLife(relatLife);
}

bool joueur::attack(int x, int y)
{

	if(m_arme.attack(x,y))
		return true;
	else
		return false;
}

void joueur::create(map &map,sf::RenderWindow &App)
{
	m_sp_joueur.setPosition(map.setJoueurPos().x,map.setJoueurPos().y);
	//la camera marche pas trop
	//m_camera.setFromRect(sf::FloatRect(m_sp_joueur.getPosition().x - 300,m_sp_joueur.getPosition().y - 150,m_sp_joueur.getPosition().x + 300,m_sp_joueur.getPosition().y +150));
	//App.setView(m_camera);
}

bool joueur::isAlive()
{
	if(m_interface.isAlive())
		return true;
	else
		return false;
}