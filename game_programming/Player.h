#pragma once
//#ifndef _Player
//#define _Player

//#include "Ctrl.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Player{
private:
    // Defined in constructor
    Ctrl* game_ctrl;
    sf::Sprite* shape;
    float size;
	float speed;

public:
    Player(Ctrl* game_ctrl, float size, float speed);
    ~Player() { delete shape; }

    sf::Vector2f get_position();

    void move_by_key(float deltatime);
    void move_by_mouse(sf::Window& window);

    void draw(sf::RenderWindow& window);
};

//#endif