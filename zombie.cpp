#include "zombie.h"

zombie::zombie()
{




}

zombie::~zombie()
{

}


void zombie::draw(sf::RenderWindow &App)
{
		App.draw(m_sp_zombie);
}

bool zombie::canMove(map &map,int x, int y)
{
	if(map.collision((x-17)/TAILLE_CASE,(y-17)/TAILLE_CASE))
		return false;
	else if(map.collision((x-17)/TAILLE_CASE,(y+17)/TAILLE_CASE))
		return false;
	else if(map.collision((x+17)/TAILLE_CASE,(y-17)/TAILLE_CASE))
		return false;
	else if(map.collision((x+17)/TAILLE_CASE,(y+17)/TAILLE_CASE))
		return false;
	else
		return true;

}

void zombie::orientation(float x,float y)
{
	if(m_vie > 0)//s il est pas mort -_-'
	{
		int ecartX = x - m_sp_zombie.getPosition().x;
		int ecartY = y - m_sp_zombie.getPosition().y;
		
		if(ecartX > 0)
		{
			if(ecartY > 0)
			{
				m_sp_zombie.setRotation(270-180*atan((double)ecartY/ecartX)/3.14);

			}
			if(ecartY < 0)
			{
				m_sp_zombie.setRotation(270+180*atan((double)ecartY/-ecartX)/3.14);
				
			}

		}

		else if(ecartX < 0)
		{
			if(ecartY > 0)
			{
				m_sp_zombie.setRotation(180+180*atan((double)ecartX/ecartY)/3.14);
			}
			if(ecartY < 0)
			{
				m_sp_zombie.setRotation(180*atan((double)-ecartX/-ecartY)/3.14);
		
			}
		}
	}
}

void zombie::move(map &map,int xJoueur, int yJoueur,sf::RenderWindow &App)
{
		if(m_vie > 0)//s il est pas mort 
		{

		// R�cup�ration du temps �coul�
		sf::Time timer = m_clock.getElapsedTime();
		float ElapsedTime = timer.asSeconds();
		m_clock.restart();

		int x = m_sp_zombie.getPosition().x;
		int y = m_sp_zombie.getPosition().y;

		if(!IsMTrgtActive())		///ON CALCULE LA TRAJECTOIRE AFIN DE VISER UNE CASE
		{
			int valeur_poids = 1;
			//on efface les poids prcedents
				for(int i = 0;i<CASES_X;i++)
					for(int j = 0;j<CASES_Y;j++)
						m_poids[i][j] = 0;
				m_poids[xJoueur/TAILLE_CASE][yJoueur/TAILLE_CASE] = 1;//on commence par la case joueur
				//on calcule les poids
				while(m_poids[x/TAILLE_CASE][y/TAILLE_CASE] == 0)//tant que la case du zombie a pas de poids
				{
					for(int i = 0;i<CASES_X;i++)
						for(int j =0;j<CASES_Y;j++)
						{
							if(m_poids[i][j] == valeur_poids)//si le poid se situe a l extremit� 
							{

								if(m_carte[i+1][j] == 0 && m_poids[i+1][j] == 0)
									m_poids[i+1][j] = valeur_poids+1;
								if(m_carte[i-1][j] == 0 && m_poids[i-1][j] == 0)
									m_poids[i-1][j] = valeur_poids+1;
								 if(m_carte[i][j+1] == 0 && m_poids[i][j+1] == 0)
									m_poids[i][j+1] = valeur_poids+1;
								 if(m_carte[i][j-1] == 0 && m_poids[i][j-1] == 0)
									m_poids[i][j-1] = valeur_poids+1;
							}
						}
					valeur_poids ++;
				}

				//on 'cible' une case
				if(m_poids[x/TAILLE_CASE+1][y/TAILLE_CASE] == m_poids[x/TAILLE_CASE][y/TAILLE_CASE]-1)
					setMoveTarget(x+TAILLE_CASE,y);	

				if(m_poids[x/TAILLE_CASE-1][y/TAILLE_CASE] == m_poids[x/TAILLE_CASE][y/TAILLE_CASE]-1)
					setMoveTarget(x-TAILLE_CASE,y);	

				
				if(m_poids[x/TAILLE_CASE][y/TAILLE_CASE+1] == m_poids[x/TAILLE_CASE][y/TAILLE_CASE]-1)
					setMoveTarget(x,y+TAILLE_CASE);	

				if(m_poids[x/TAILLE_CASE][y/TAILLE_CASE-1] == m_poids[x/TAILLE_CASE][y/TAILLE_CASE]-1)
					setMoveTarget(x,y-TAILLE_CASE);	

		}//fin du calcul

		else// ON FAIT BOUGER LE SPRITE VERS LA CASE VIS�E
		{
			if(m_moveTarget.x < x)
			{
				if(x-m_moveTarget.x > 2)// si l ordi est trop lent, pour nepas faire de "tremblement"
					m_sp_zombie.move(-ElapsedTime*m_speed,0);
				else
					m_sp_zombie.setPosition(m_moveTarget.x,m_moveTarget.y);
			}
			if(m_moveTarget.x > x)
			{
				if(m_moveTarget.x-x > 2)
					m_sp_zombie.move(ElapsedTime*m_speed,0);
				else
					m_sp_zombie.setPosition(m_moveTarget.x,m_moveTarget.y);
			}
			if(m_moveTarget.y < y)
			{
				if(y-m_moveTarget.y > 2)
					m_sp_zombie.move(0,-ElapsedTime*m_speed);
				else
					m_sp_zombie.setPosition(m_moveTarget.x,m_moveTarget.y);
			}
			if(m_moveTarget.y > y)   
			{
				if(m_moveTarget.y-y > 2)
					m_sp_zombie.move(0,ElapsedTime*m_speed);
				else
					m_sp_zombie.setPosition(m_moveTarget.x,m_moveTarget.y);
			}
		}
	}//en vie
}

bool zombie::attack(int x, int y)
{
	if(m_vie > 0)
	{
		if(m_sp_zombie.getPosition().x +TAILLE_CASE > x &&m_sp_zombie.getPosition().x -TAILLE_CASE < x &&m_sp_zombie.getPosition().y +TAILLE_CASE > y &&m_sp_zombie.getPosition().y -TAILLE_CASE < y )
		{
			return true;
		}
	}
		return false;
}

void zombie::setLife(int relatLife)
{
	m_vie += relatLife;
	if(m_vie <= 0)
		m_sp_zombie.setTexture(m_i_zombie_mort);

}

sf::Vector2f zombie::getPosition()
{
	return m_sp_zombie.getPosition();
}

void zombie::setPosition(int x,int y)
{
	m_sp_zombie.setPosition(x,y);
}

bool zombie::isAlive()
{
	if(m_vie >0)
		return true;
	else
		return false;
}

void zombie::create(map &map,sf::Texture i_zombie, sf::Texture i_zombie_mort,int nb_spawn)
{
	
	m_speed = 75;
	m_vie = 100;
	m_i_zombie_mort = i_zombie_mort; 
	m_i_zombie = i_zombie;
	m_sp_zombie.setTexture(m_i_zombie);
	m_sp_zombie.setOrigin(TAILLE_CASE/2,TAILLE_CASE/2);
	m_sp_zombie.setPosition(map.setZombiePos(nb_spawn).x,map.setZombiePos(nb_spawn).y);
	m_moveTarget.x = m_sp_zombie.getPosition().x;
	m_moveTarget.y = m_sp_zombie.getPosition().y;
}

void zombie::setMap(map &map)
{
	for(int i = 0;i<CASES_Y;i++)
	{
		for(int j=0;j<CASES_X;j++)
		{
			m_carte[j][i] = map.getMap(j,i);
		}
	}

	

}

void zombie::setMoveTarget(int x, int y)
{
	m_moveTarget.x = x;
	m_moveTarget.y = y;

}

bool zombie::IsMTrgtActive()
{
	if( m_moveTarget.x-1 < m_sp_zombie.getPosition().x &&m_moveTarget.x+1 > m_sp_zombie.getPosition().x &&m_moveTarget.y-1 < m_sp_zombie.getPosition().y &&m_moveTarget.y+1 > m_sp_zombie.getPosition().y)
		return false;
	else
		return true;

}

void zombie::reload_image()
{
	if(m_vie > 0)
	m_sp_zombie.setTexture(m_i_zombie);
	else
		m_sp_zombie.setTexture(m_i_zombie_mort);
}