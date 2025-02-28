#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape circle;
    float speed;
    float radius;

public:
    bool shoot_flag;

    Bullet(sf::Vector2f player_position);
    Bullet();

    //~Bullet();

    void set_position(sf::Vector2f player_position);

    sf::Vector2f get_position();

    void shoot(float deltatime);

    void draw(sf::RenderWindow& window);
};

