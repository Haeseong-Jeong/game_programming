#pragma once

#include "Object/Object.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/Bullet.h"

#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;

class ObjectManager
{
public:
 	sf::Clock enemy_clock;
	sf::Clock bullet_clock;
 
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;

public:
	ObjectManager();
	~ObjectManager();



	Player* get_player(); // 플레이어 주소 반환
	std::vector<Object*> get_objects(); // 객체들 배열 반환

	void spwan_player(sf::Texture& texture, sf::Vector2f window_size);
	void spwan_enemy(sf::Texture& texture);
	void spwan_bullet(sf::Texture& texture);

private:
	sf::Texture ship_texture;
	sf::Texture projectile_texture;

	int enemy_gen_num;
	Player* player;
	std::vector<Object*> objects;
};

