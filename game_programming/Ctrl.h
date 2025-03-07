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

	Player* get_player_ptr(); // 플레이어 주소 반환
	std::vector<Object*> get_objects(); // 객체들 배열 반환
	
	bool check_collision(Object* a, Object* b); // 객체의 뼈대가 충돌했는지 판별 
	void is_hit(); // 총알과 적이 맞았는지 판별, check_collision() 활용
	void is_out_boundary(); // 객체가 화면 밖으로 나갔는지 판별

	void spwan_enemy(); // 일정 시간 마다 적 랜덤 생성
	void spwan_bullet(); // 일정 시간 마다 총알 랜덤 생성

	bool initialize_game(); // texture 불러오기, initialize_objects() 함수 사용
	void initialize_objects(); // create player, enemy, bullet

	void running_game();
	void process_events(); // close event
	void set_game(); //초기 셋팅, 
	void update_game(); // clear -> draw, move, 뼈대와 박스 생성 -> display

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

