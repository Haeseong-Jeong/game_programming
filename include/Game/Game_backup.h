#pragma once

#include <SFML/Graphics.hpp>

class Entity;
class Player;

class Game
{
public:
	const float EPSILON = 1e-6f;

public:
	Game(int window_w, int window_h);
	~Game();

	sf::Window& get_window();
	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();
	//sf::Texture& get_background_texture();

	void set_background();
	Player* get_player(); // �÷��̾� �ּ� ��ȯ
	std::vector<Entity*> get_entities(); // ��ü�� �迭 ��ȯ
	
	bool check_collision(Entity* a, Entity* b); // ��ü�� ���밡 �浹�ߴ��� �Ǻ�
	void is_dead(); // �÷��̾�� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	void is_hit(); // �Ѿ˰� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	void is_out_boundary(); // ��ü�� ȭ�� ������ �������� �Ǻ�
	void erase_entities();

	void spwan_enemy(); // ���� �ð� ���� �� ���� ����
	void spwan_bullet(); // ���� �ð� ���� �Ѿ� ���� ����

	bool initialize_game(); // texture �ҷ�����, initialize_Entitys() �Լ� ���
	void initialize_entities(); // create player, enemy, bullet

	void running_game();
	void process_events(); // close event
	void set_game(); //�ʱ� ����, 
	void update_game(); // clear -> draw, move, ����� �ڽ� ���� -> display

	void terminate_game(); // heap memory clear
	
private:
	int score;
	bool end_game;

	sf::Vector2u window_size;
	sf::RenderWindow window;
	sf::Sprite* background;

	sf::Texture ship_texture;
	sf::Texture projectile_texture;
	sf::Texture background_texture;

	int enemy_gen_num;
	Player* player;
	std::vector<Entity*> entities;

	sf::Clock clock;
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;
	float deltatime;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;
};

