//#pragma once
//
//#include "Entity/Entity.h"
//#include "Entity/Player.h"
//#include "Entity/Enemy.h"
//#include "Entity/Bullet.h"
//#include "Game/Game.h"
//
//#include <SFML/Graphics.hpp>
//
//class Player;
//class Enemy;
//class Bullet;
//
//class GameEntityManager
//{
//public:
//	Game* game;
//
//	sf::Clock enemy_clock;
//	sf::Clock bullet_clock;
//	int enemy_gen_num = 5;
//	float enemy_period = 5.0f;
//	float shoot_period = 1.0f;
//
//public:
//	GameEntityManager(Game* game);
//	~GameEntityManager();
//
//	Player* get_player(); // �÷��̾� �ּ� ��ȯ
//	std::vector<Entity*>& get_entities(); // ��ü�� �迭 ��ȯ
//
//	void spwan_player();
//	void spwan_enemy();
//	void spwan_bullet();
//
//private:
//	Player* player;
//	std::vector<Entity*> entities;
//
//};
//
