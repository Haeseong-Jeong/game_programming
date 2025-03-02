#pragma once
//#ifndef _Player
//#define _Player

#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Player{
private:
    sf::RectangleShape rect;
	float speed;
	float width;
	float height;

public:
    Player(float width, float height, float speed);
    Player(float width, float speed);
    Player(float speed);
    Player();

    void set_position(sf::Window& window);

    sf::Vector2f get_position();

    sf::Vector2f get_bullet_direction(std::vector<Enemy*> enemy, int enemy_num);

    void move_by_key(float deltatime);

    void move_by_mouse(sf::Window& window);

    void draw(sf::RenderWindow& window);
};

//#endif