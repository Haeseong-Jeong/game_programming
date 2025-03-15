#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class GameTextureManager;
class GameObjectManager;
class GameLogic;

class Game
{
public:
	GameObjectManager* objectmanager;
	GameTextureManager* texturemanager;
	GameLogic* gamelogic;

public:
	Game(int window_w, int window_h);
	~Game();

	sf::Window& get_window();

	void set_background();
	
	//bool check_collision(Entity* a, Entity* b); // ��ü�� ���밡 �浹�ߴ��� �Ǻ�
	//void is_dead(); // �÷��̾�� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	//void is_hit(); // �Ѿ˰� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	//void is_out_boundary(); // ��ü�� ȭ�� ������ �������� �Ǻ�

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

	sf::Clock clock;
	float deltatime;
};

