#pragma once

#include <SFML/Graphics.hpp>

class GameObjectManager;


class Object
{
public:
	//sf::RectangleShape bounding_box;
	//sf::RectangleShape skeleton;

public:
	Object(GameObjectManager* objectmanager, float size, float speed);
	virtual ~Object();

	sf::Vector2f get_position();
	sf::Sprite* get_shape();

	bool is_activate();
	void deactivate();
	
	void draw(sf::RenderWindow& window);
	virtual void move(float deltatime) = 0; //���� �����Լ�, cpp���Ͽ� ���� ��� �ȴ�. ���, ��� Ŭ�������� �� ���ǰ� �Ǿ�� ��.

	//void make_bounding_box();
	//void make_skeleton(float scale);


protected:
	GameObjectManager* objectmanager;
	sf::Sprite* shape;
	bool activate;
	float size;
	float speed;
};

