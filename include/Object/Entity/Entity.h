#pragma once

#include <SFML/Graphics.hpp>

enum EntityType { PLAYER, ENEMY, BULLET };

class Game;

class Entity
{
public:
	sf::RectangleShape bounding_box;
	sf::RectangleShape skeleton;

public:
	Entity(Game* game, EntityType type, float size, float speed);
	virtual ~Entity();

	sf::Vector2f get_position();
	sf::Sprite* get_shape();
	EntityType get_type();

	bool is_activate();
	void deactivate();

	void draw(sf::RenderWindow& window);
	virtual void move(float deltatime) = 0; //���� �����Լ�, cpp���Ͽ� ���� ��� �ȴ�. ���, ��� Ŭ�������� �� ���ǰ� �Ǿ�� ��.

	void make_bounding_box();
	void make_skeleton(float scale);


protected:
	Game* game;
	//EntityManager obm;
	sf::Sprite* shape;
	EntityType type;
	bool activate;
	float size;
	float speed;
};

