#pragma once

#include "Object/Object.h"
#include <SFML/Graphics.hpp>

enum EntityType { PLAYER, ENEMY, BULLET };

//class Game;
class GameTextureManager;
class GameObjectManager;

class Entity : public Object
{
public:
	const float EPSILON = 1e-6f;
	sf::RectangleShape bounding_box;
	sf::RectangleShape skeleton;

public:
	Entity(GameObjectManager* objectmanager, EntityType type, float size, float speed);
	~Entity();

	//sf::Vector2f get_position();
	//sf::Sprite* get_shape();
	//bool is_activate();
	//void deactivate();
	//void draw(sf::RenderWindow& window);

	EntityType get_type();

	virtual void set_position();
	virtual void move(float deltatime) = 0; //���� �����Լ�, cpp���Ͽ� ���� ��� �ȴ�. ���, ��� Ŭ�������� �� ���ǰ� �Ǿ�� ��.
	void make_bounding_box();
	void make_skeleton(float scale);


protected:
	EntityType type;

};

