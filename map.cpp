#include "map.h"

map::map()
{
	//chargement des sprites de la carte
	m_i_sol.loadFromFile("images/map/sol.bmp");
	m_sp_sol.setTexture(m_i_sol);

	m_i_obstacle.loadFromFile("images/map/obstacle.bmp");
	m_sp_obstacle.setTexture(m_i_obstacle);

}

map::~map()
{

}

void map::load()
{
	char c;
	std::ifstream fichier("map.txt",std::ios::in);

	for(int i =0;i<CASES_Y;i++)
		for(int j =0;j<CASES_X;j++)
		{
			fichier.get(c);
			if(c == '0')
				m_carte[j][i] = 0;
			else if(c == '1')
				m_carte[j][i] = 1;
			else if(c == '2')//un spawn de zombie
				m_carte[j][i] = 2;
			else if(c == '3')//un spawn de joueur
				m_carte[j][i] = 3;
		}

	fichier.close();

}

void map::draw(sf::RenderWindow &App)
{
	//double boucle qui parcout tout le tableau. si 1 : obstacle si 0.2.3:sol
	for(int i =0;i<CASES_X;i++)
	{
		for(int j =0;j<CASES_Y;j++)
		{
			if(m_carte[i][j] == 0 || m_carte[i][j] == 2|| m_carte[i][j] == 3)
			{
				m_sp_sol.setPosition(i*TAILLE_CASE,j*TAILLE_CASE);
				App.draw(m_sp_sol);
			}
			else if(m_carte[i][j] == 1)
			{
				m_sp_obstacle.setPosition(i*TAILLE_CASE,j*TAILLE_CASE);
				App.draw(m_sp_obstacle);
			}
		}
	}

}

bool map::collision(int x, int y)//renvoie true si obstacle
{
		if(x < CASES_X && y < CASES_Y)
		{
			if(m_carte[x][y] == 1)
			{
			return true ; 
			}
			else
			return false;
		}
	return false;	
}

sf::Vector2f map::setZombiePos(int nb_spawn)
{
	int count_spawn = 0;//pour compter dans quel spawn le zombie apparait
	for(int i =0;i<CASES_X;i++)
		for(int j =0;j<CASES_Y;j++)
		{
			if(m_carte[i][j] ==2)
			{
				count_spawn ++;
				if(count_spawn == nb_spawn)
				{
				m_sp_sol.setPosition(i*TAILLE_CASE+TAILLE_CASE/2,j*TAILLE_CASE+TAILLE_CASE/2);//pour avoir une position en vector2f
				return m_sp_sol.getPosition();
				}
				
			}
		}
	
}

sf::Vector2f map::setJoueurPos()
{
for(int i =0;i<CASES_X;i++)
		for(int j =0;j<CASES_Y;j++)
		{
			if(m_carte[i][j] == 3)
			{
				m_sp_sol.setPosition(i*TAILLE_CASE+TAILLE_CASE/2,j*TAILLE_CASE+TAILLE_CASE/2);//pour avoir une position en vector2f
					return m_sp_sol.getPosition();
			}
		}

}

bool map::getMap(int x, int y)
{
	if(m_carte[x][y] == 0 || m_carte[x][y] == 2|| m_carte[x][y] == 3)
	{
		return false; 		
	}
	else if(m_carte[x][y] == 1)
	{
		return true;
	}
}