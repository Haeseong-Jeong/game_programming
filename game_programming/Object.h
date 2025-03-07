#pragma once

#include <SFML/Graphics.hpp>

enum ObjectType { PLAYER, ENEMY, BULLET };

class Ctrl;

class Object
{
public:
	sf::RectangleShape bounding_box;
	sf::RectangleShape skeleton;

public:
	Object(Ctrl* game_ctrl, ObjectType type,float size, float speed);
	virtual ~Object();

	sf::Vector2f get_position();
	sf::Sprite* get_shape();
	ObjectType get_type();

	bool is_activate();
	void deactivate();

	void draw(sf::RenderWindow& window);
	virtual void move(float deltatime) = 0; //���� �����Լ�, cpp���Ͽ� ���� ��� �ȴ�. ���, ��� Ŭ�������� �� ���ǰ� �Ǿ�� ��.

	void make_bounding_box();
	void make_skeleton(float scale);


protected:
	Ctrl* game_ctrl;
	sf::Sprite* shape;
	ObjectType type;
	bool activate;
	float size;
	float speed;
};

