#pragma once

#include <SFML/Graphics.hpp>

class Ctrl;

class Object
{
public:
	Object(Ctrl* game_ctrl, float size, float speed);
	virtual ~Object();

	sf::Vector2f get_position();
	void draw(sf::RenderWindow& window);

	virtual void move(float deltatime) = 0; //���� �����Լ�, cpp���Ͽ� ���� ��� �ȴ�. ���, ��� Ŭ�������� �� ���ǰ� �Ǿ�� ��.
	virtual void remove();

protected:
	Ctrl* game_ctrl;
	sf::Sprite* shape;
	float size;
	float speed;
};

