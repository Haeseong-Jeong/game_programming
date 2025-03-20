#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Entity;
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

	Player* get_player();
	std::vector<Entity*>& get_entities();

	sf::Text* get_text();
	sf::Sprite* get_background();

	void set_text();
	void set_background();

	void spwan_player();
	void spwan_enemy(bool first_spawn = false);
	void spwan_bullet(bool first_spawn = false);
	void erase_entities();
	void reset_entities();

private:
	sf::Vector2u window_size;
	GameTextureManager* texturemanager;

	std::string score_str;
	sf::Text* text;
	sf::Sprite* background;

	Player* player;
	std::vector<Entity*> entities;
};

