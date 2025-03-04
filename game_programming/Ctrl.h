#pragma once

//#include "Player.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;

class Ctrl
{
public:
	Ctrl(int window_w, int window_h);
	//~Ctrl();
	sf::Vector2f get_bullet_direction();
	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();
	sf::Window& get_window();
	Player* get_player_ptr();

	bool initialize_game(); // 
	void initialize_objects(); // create player, enemy, bullet, window

	void running_game();
	void process_events(); // close event
	void set_game(); //초기 셋팅?
	void update_game(); // clear -> draw -> move -> display?

	void terminate_game(); // heap memory clear
	
private:
	int window_w;
	int window_h;
	sf::RenderWindow window;

	sf::Texture ship_texture;
	sf::Texture projectile_texture;

	int enemy_gen_num;
	float player_speed;
	float player_size;

	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;

	sf::Clock clock;
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;

	float deltatime;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;
};

