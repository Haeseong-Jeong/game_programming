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
	virtual void move(float deltatime) = 0; //순수 가상함수, cpp파일에 정의 없어도 된다. 대신, 상속 클래스에서 꼭 정의가 되어야 함.
	void make_bounding_box();
	void make_skeleton(float scale);


protected:
	EntityType type;

};

