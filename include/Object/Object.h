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
	virtual void move(float deltatime) = 0; //순수 가상함수, cpp파일에 정의 없어도 된다. 대신, 상속 클래스에서 꼭 정의가 되어야 함.

	void make_bounding_box();
	void make_skeleton(float scale);


protected:
	GameTextuerManager* texturemanager;
	sf::Sprite* shape;
	bool activate;
	float size;
	float speed;
};

