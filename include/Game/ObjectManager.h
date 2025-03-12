#pragma once

#include "Object/Object.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/Bullet.h"
#include "Game/Game.h"

#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;

class ObjectManager
{
public:
	Game* game;
	sf::Clock clock;
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;

	int enemy_gen_num;
	float deltatime;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;

public:
	ObjectManager(Game* game);
	~ObjectManager();

	Player* get_player(); // �÷��̾� �ּ� ��ȯ
	std::vector<Object*> get_objects(); // ��ü�� �迭 ��ȯ

	void spwan_player();
	void spwan_enemy();
	void spwan_bullet();

private:

};

