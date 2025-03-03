#pragma once

//#include "Player.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>


class Ctrl
{
public:
	Ctrl(int window_w, int window_h);
	//~Ctrl();
	void initialize_game(float player_size, int enemy_num); // create player, enemy, bullet, window
	
	void running_game();
	void set_game(); //초기 셋팅?
	void update_game(); // clear -> draw -> move -> display?
	void terminate_game();
	void close_events();
	
	sf::RenderWindow& get_window();

private:
	int enemy_gen_num;
	int window_w;
	int window_h;
	sf::RenderWindow window;

	Player player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;

	sf::Clock clock;
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;

	float deltatime;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;
};

