#pragma once

//#include "Player.h"
#include "Object.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;

class Ctrl
{
public:
	const float EPSILON = 1e-6f;

public:
	Ctrl(int window_w, int window_h);
	//~Ctrl();

	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();
	sf::Window& get_window();
	Player* get_player_ptr();
	std::vector<Object*> get_objects();
	
	bool check_collision(Object* a, Object* b);
	void is_hit();
	void is_out_boundary();

	void spwan_enemy();
	void spwan_bullet();

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
	Player* player;
	std::vector<Object*> objects;

	sf::Clock clock;
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;

	float deltatime;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;
};

