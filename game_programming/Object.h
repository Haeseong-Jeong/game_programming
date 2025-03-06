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

	virtual void move(float deltatime) = 0; //순수 가상함수, cpp파일에 정의 없어도 된다. 대신, 상속 클래스에서 꼭 정의가 되어야 함.
	virtual void remove();

protected:
	Ctrl* game_ctrl;
	sf::Sprite* shape;
	float size;
	float speed;
};

