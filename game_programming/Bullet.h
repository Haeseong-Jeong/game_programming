#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape circle;
    float speed;
    float radius;

public:
    Bullet(float radius, float speed);
    Bullet();

    //~Bullet();

    void set_position(Player* player);

    //sf::Vector2f get_position();

    void shoot();

    void draw(sf::RenderWindow& window);
};

