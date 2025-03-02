#pragma once

#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 

class Enemy {
private:
    sf::CircleShape circle;
    float speed;
    float radius;
    float distance_from_player;
    float dx, dy;

public:
    Enemy(const Enemy& other);
    Enemy(float radius);
    Enemy();

    Enemy& operator=(const Enemy& other);

    void set_position(sf::Window& window);

    sf::Vector2f get_position();
    sf::Vector2f get_direction();

    float get_distance();
    float get_speed();
    
    void calculate_direction(sf::Vector2f player_position);

    void move(sf::Vector2f player_position, float deltatime);
    
    void draw(sf::RenderWindow& window);
};

//#endif