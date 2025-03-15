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
	
	//bool check_collision(Entity* a, Entity* b); // 객체의 뼈대가 충돌했는지 판별
	//void is_dead(); // 플레이어와 적이 맞았는지 판별, check_collision() 활용
	//void is_hit(); // 총알과 적이 맞았는지 판별, check_collision() 활용
	//void is_out_boundary(); // 객체가 화면 밖으로 나갔는지 판별

	bool initialize_game(); // texture 불러오기, initialize_Entitys() 함수 사용
	void initialize_entities(); // create player, enemy, bullet

	void running_game();
	void process_events(); // close event
	void set_game(); //초기 셋팅, 
	void update_game(); // clear -> draw, move, 뼈대와 박스 생성 -> display

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

