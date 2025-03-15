#pragma once

#include <SFML/Graphics.hpp>

class GameTextuerManager;

class Entity
{
public:
	sf::RectangleShape bounding_box;
	sf::RectangleShape skeleton;

public:
	Entity(GameTextuerManager* texturemanager, float size, float speed);
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
	GameTextuerManager* texturemanager;
	sf::Sprite* shape;
	bool activate;
	float size;
	float speed;
};

