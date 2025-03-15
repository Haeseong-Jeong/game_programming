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
	virtual void move(float deltatime) = 0; //순수 가상함수, cpp파일에 정의 없어도 된다. 대신, 상속 클래스에서 꼭 정의가 되어야 함.

	//void make_bounding_box();
	//void make_skeleton(float scale);


protected:
	GameObjectManager* objectmanager;
	sf::Sprite* shape;
	bool activate;
	float size;
	float speed;
};

