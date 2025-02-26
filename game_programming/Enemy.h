#pragma once

#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 

class Enemy {
private:
    sf::CircleShape circle;
    float speed;
    float radius;

public:
    Enemy(float radius);
    Enemy();

    void set_position(sf::Window& window);
    sf::Vector2f get_position();

    float get_speed();
    void draw_enemy(sf::RenderWindow& window);
    void move_enemy(sf::Vector2f player_position, Enemy& enemy, int num_enemy, float speed);
};

//#endif