#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape circle;
    sf::Vector2f direction;
    float speed;
    float radius;

public:
    bool shoot_flag;

    Bullet(sf::Vector2f player_position, sf::Vector2f direction);
    Bullet();

    //~Bullet();

    void set_position(sf::Vector2f player_position);

    sf::Vector2f get_position();

    void shoot(float deltatime);

    void draw(sf::RenderWindow& window);
};

