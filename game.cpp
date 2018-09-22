#include "game.h"

game::game()
{
	m_vague = 1;

	//les sprites des zombies
	sf::Image zomb;
	zomb.loadFromFile("images/zombie.bmp");
	zomb.createMaskFromColor(sf::Color(0, 0, 255, 255));
	m_i_zombie.update(zomb);

	sf::Image zombm;
	zombm.loadFromFile("images/zombie.bmp");
	zombm.createMaskFromColor(sf::Color(0, 0, 255, 255));
	m_i_zombie_mort.update(zombm);


	//les polices d ecriture des manches
	if(!m_police.loadFromFile("polices/batik.ttf"))
	{
		std::cout << "erreur de chargement de la police"<<std::endl;
	}

	m_st_vague.setFont(m_police);
	m_st_vague.setColor(sf::Color(255,0,0));
	m_st_vague.setString("I");
	m_st_vague.setCharacterSize(60);
	m_st_vague.setPosition(LARGEUR_FENETRE-150,HAUTEUR_FENETRE-75);

	m_time_delay = 5; // pour spawner directement les zombies
	m_nb_zombies = 0;
}

game::~game()
{

}

void game::start(sf::RenderWindow &App)
{
	m_carte.load();
	get_nb_zombies();
	m_joueur.create(m_carte,App);
	spawn_zombies();
    while (App.isOpen())// boucle principale
    {
		  sf::Event event;
		  while (App.pollEvent(event))
			if (event.type == sf::Event::Closed)
		    App.close();

		  //on gère le joueur
		m_joueur.move(App,m_carte);
		m_joueur.orientation(App);
		m_joueur.tirer(App);
		//les zombies
		move_zombies(App);
		check_vague_zombies();
		spawn_zombies();

		//les vagues
		set_st_vague();

		//on detecte le game over
		if(!m_joueur.isAlive())
			Game_Over(App);

		//affichage de la scène
		App.clear(sf::Color(50, 50, 50));	
		drawAll(App);
        App.display();
	}

}

void game::drawAll(sf::RenderWindow &App)
{
	m_carte.draw(App);
	draw_zombies(App);
	m_joueur.draw(App);
	App.draw(m_st_vague);
}

void game::set_st_vague()
{
	switch(m_vague)
	{
	case 1:
		m_st_vague.setString("I");
		break;
	case 2:
		m_st_vague.setString("II");
		break;
	case 3:
		m_st_vague.setString("III");
		break;
	case 4:
		m_st_vague.setString("IV");
		break;
	case 5:
		m_st_vague.setString("V");
		break;
	case 6:
		m_st_vague.setString("VI");
		break;
	case 7:
		m_st_vague.setString("VII");
		break;
	case 8:
		m_st_vague.setString("VIII");
		break;
	case 9:
		m_st_vague.setString("IX");
		break;
	case 10:
		m_st_vague.setString("X");
		break;
	case 11:
		m_st_vague.setString("XI");
		break;
	case 12:
		m_st_vague.setString("XII");
		break;
	case 13:
		m_st_vague.setString("XIII");
		break;
	case 14:
		m_st_vague.setString("XIV");
		break;
	case 15:
		m_st_vague.setString("XV");
		break;
	default:
		m_st_vague.setString("666");
		break;
	}
}

void game::get_nb_zombies()
{
	//nouvelle manche: on efface le vector
	m_zombies.clear();
	m_spawn_zombies_restant = m_vague*m_vague + 10;
	m_nb_zombies = 0;
	std::cout << "NOUVELLE VAGUE : " << m_vague << std::endl;

}

void game::spawn_zombies()//on spawn NB_SPAWN_ZOMBIE zombies � la fois
{
//	std::cout << "m_nb_zombies " << m_nb_zombies << std::endl;
//	std::cout << "m_spawn_zombies_restant :  " << m_spawn_zombies_restant << std::endl;
	int rang_vector = m_nb_zombies;
	int nb_spawned = 0;//spawn�s dans la fonction (entre 1 et NB_SPAWN_ZOMBIE  zombies)
	if(m_spawn_zombies_restant >0)
	{
		m_time_delay = m_spawn_delay.getElapsedTime().asSeconds();
		if(m_time_delay > 1 )
		{
			m_spawn_delay.restart();
			if(m_spawn_zombies_restant > NB_SPAWN_ZOMBIE)
			{
				m_zombies.resize(m_nb_zombies + NB_SPAWN_ZOMBIE);
				m_spawn_zombies_restant -= NB_SPAWN_ZOMBIE;
				nb_spawned = NB_SPAWN_ZOMBIE;
			}	
			else
			{
				m_zombies.resize(m_nb_zombies + m_spawn_zombies_restant);
				nb_spawned = m_spawn_zombies_restant;
				m_spawn_zombies_restant = 0;
			}

			m_nb_zombies += nb_spawned;

			for(int i = rang_vector;i<m_nb_zombies;i++)
			{
				m_zombies[i].create(m_carte,m_i_zombie,m_i_zombie_mort,i+1-rang_vector);
				m_zombies[i].setMap(m_carte);
			}
			for(int i = 0;i<m_nb_zombies;i++)
				m_zombies[i].reload_image();
		}
	}

}

void game::draw_zombies(sf::RenderWindow &App)
{
	for(int i = 0;i<m_nb_zombies;i++)
	{
		m_zombies[i].draw(App);
	}

}

void game::move_zombies(sf::RenderWindow &App)
{
		for(int i = 0;i<m_nb_zombies;i++)
	{
		if(m_zombies[i].isAlive())
		{
			if(m_joueur.attack(m_zombies[i].getPosition().x,m_zombies[i].getPosition().y))
				m_zombies[i].setLife(-50);
		m_zombies[i].orientation(m_joueur.getPosition().x,m_joueur.getPosition().y);
		if(m_zombies[i].attack(m_joueur.getPosition().x,m_joueur.getPosition().y))
			m_joueur.setLife(-1);
		else
			m_zombies[i].move(m_carte,m_joueur.getPosition().x,m_joueur.getPosition().y,App);//on le fais bouger si il attaque pas, sinon il peut bloquer le programme en allant dans un mur
		}
	}
}
void game::check_vague_zombies()
{
	bool allDead = true; //une variable pour voir si ils sont morts
	if(m_spawn_zombies_restant == 0)//s'il n' y a plus de zombies � cr�er..
	{

		for(int i = 0;i<m_nb_zombies; i++)
			if(m_zombies[i].isAlive())//s' il y en a un de vivant
			{
				allDead = false; //alors ils sont pas tous morts

			}
	}
	else
		allDead = false;


	m_time_vague_delay = m_vague_delay.getElapsedTime().asSeconds();//ca fait patienter qqes secondes, et ca permet de spawner les zombies sans passer
														//directement a la manche d'apr�s
	if(m_time_vague_delay > 5 )
	{
		m_vague_delay.restart();
		if(allDead)//on passe � la manche suivante
		{
			m_vague++;//on incremente la manche
			get_nb_zombies();//on calcule le nombre de zombies � cr�er
		}
	}
}

void game::Game_Over(sf::RenderWindow &App)
{
	sf::Clock delay_gameO;//pour afficher le game over 5 secondes

	m_st_GameOver.setFont(m_police);
	m_st_GameOver.setString("GAME OVER");
	m_st_GameOver.setColor(sf::Color(255,0,0));
	m_st_GameOver.setCharacterSize(80);
	m_st_GameOver.setPosition(LARGEUR_FENETRE/2 -200,HAUTEUR_FENETRE/2 - 50);

	//on efface tout et on affiche le game over
	App.clear(sf::Color(255,255,255));
	App.draw(m_st_GameOver);
	App.display();

	while(1)
		if(delay_gameO.getElapsedTime().asSeconds() > 5)
		{
			App.close(); // on ferme le jeu
			//NB: Ne ferme pas encore la console
		}
				
}