#pragma once
//#ifndef _Player
//#define _Player

//#include "Ctrl.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Player{
private:

  
    //std::optional<sf::Sprite> shape;
    Ctrl* game_ctrl;
    sf::Sprite* shape;
    float size;
	float speed;


public:
    Player(Ctrl* game_ctrl, float size, float speed);

    //Player(float width, float height, float speed);
    //Player(float width, float speed);
    //Player(float speed);
    //Player();

    ~Player() { delete shape; }

    void set_position(sf::Window& window);
    sf::Vector2f get_position();

    void move_by_key(float deltatime);
    void move_by_mouse(sf::Window& window);

    void draw(sf::RenderWindow& window);
};

//#endif