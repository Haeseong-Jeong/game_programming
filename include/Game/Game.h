#pragma once

//#include "Entity/Entity.h"
//#include "Entity/Player.h"
//#include "Entity/Enemy.h"
//#include "Entity/Bullet.h"


#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;
class GameEntityManager;

class Game
{
public:
	const float EPSILON = 1e-6f;

public:
	Game(int window_w, int window_h);
	//~Game();

	sf::Window& get_window();
	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();


	GameEntityManager* get_entitymanager(); // �÷��̾� �ּ� ��ȯ

	//void set_player(Player* player);
	//Player* get_player(); // �÷��̾� �ּ� ��ȯ
	//std::vector<Entity*> get_entities(); // ��ü�� �迭 ��ȯ
	
	bool check_collision(Entity* a, Entity* b); // ��ü�� ���밡 �浹�ߴ��� �Ǻ� 
	void is_hit(); // �Ѿ˰� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	void is_out_boundary(); // ��ü�� ȭ�� ������ �������� �Ǻ�

	//void spwan_enemy(); // ���� �ð� ���� �� ���� ����
	//void spwan_bullet(); // ���� �ð� ���� �Ѿ� ���� ����

	bool initialize_game(); // texture �ҷ�����, initialize_Entitys() �Լ� ���
	//void initialize_entitys(); // create player, enemy, bullet

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

	GameEntityManager entitymanager;

	sf::Clock clock;
	float deltatime;

	//int enemy_gen_num;
	//Player* player;
	//std::vector<Entity*> entities;


	//sf::Clock enemy_clock;
	//sf::Clock bullet_clock;


	//float enemy_period = 5.0f;
	//float shoot_period = 1.0f;
};

