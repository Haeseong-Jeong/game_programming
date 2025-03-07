#pragma once

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

	sf::Window& get_window();
	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();

	Player* get_player_ptr(); // �÷��̾� �ּ� ��ȯ
	std::vector<Object*> get_objects(); // ��ü�� �迭 ��ȯ
	
	bool check_collision(Object* a, Object* b); // ��ü�� ���밡 �浹�ߴ��� �Ǻ� 
	void is_hit(); // �Ѿ˰� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	void is_out_boundary(); // ��ü�� ȭ�� ������ �������� �Ǻ�

	void spwan_enemy(); // ���� �ð� ���� �� ���� ����
	void spwan_bullet(); // ���� �ð� ���� �Ѿ� ���� ����

	bool initialize_game(); // texture �ҷ�����, initialize_objects() �Լ� ���
	void initialize_objects(); // create player, enemy, bullet

	void running_game();
	void process_events(); // close event
	void set_game(); //�ʱ� ����, 
	void update_game(); // clear -> draw, move, ����� �ڽ� ���� -> display

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

