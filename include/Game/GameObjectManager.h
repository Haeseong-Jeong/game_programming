#pragma once

#include <SFML/Graphics.hpp>

class Object;
class Entity;
class Player;
class Enemy;
class Bullet;
class GameTextureManager;

class GameObjectManager
{
public:
	sf::Clock enemy_clock;
	sf::Clock bullet_clock;
	int enemy_gen_num = 5;
	float enemy_period = 5.0f;
	float shoot_period = 1.0f;

public:
	GameObjectManager(GameTextureManager* texturemanager, sf::Vector2u window_size);
	~GameObjectManager();

	sf::Vector2u get_window_size();
	GameTextureManager* get_texturemanager();

	Player* get_player(); // 플레이어 주소 반환
	std::vector<Entity*>& get_entities(); // 객체들 배열 반환

	void spwan_player();
	void spwan_enemy();
	void spwan_bullet();
	void erase_entities();

private:
	sf::Vector2u window_size;

	GameTextureManager* texturemanager;
	Player* player;
	std::vector<Entity*> entities;

};

