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
    Enemy(const Enemy& other);
    Enemy(float radius);
    Enemy();

    Enemy& operator=(const Enemy& other);

    void set_position(sf::Window& window);

    sf::Vector2f get_position();

    float get_speed();
    
    void move(sf::Vector2f player_position, Enemy& enemy, int num_enemy, float speed, float deltatime);
    
    void draw(sf::RenderWindow& window);
};

//#endif