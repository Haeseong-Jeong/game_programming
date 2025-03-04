#pragma once

#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 
class Ctrl;

class Enemy {
private:
    // Defined in constructor
    Ctrl* game_ctrl;
    sf::Sprite* shape;
    float size;
    float speed;

    // Defined later
    float distance_from_player;
    sf::Vector2f direction;

public:
    Enemy(Ctrl* game_ctrl, float max_size, float max_speed);
    //Enemy(sf::Vector2u window_size, sf::Vector2f player_position);
    //Enemy(float radius);
    //Enemy();
    
    ~Enemy() { delete shape; }

    //Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

    //void set_position(sf::Window& window);

    float get_speed() const;
    float get_distance() const;

    sf::Vector2f get_position() const;
    sf::Vector2f get_direction() const;
    sf::Vector2f get_random_position();
    //sf::Vector2f get_random_position(sf::Vector2u window_size, sf::Vector2f player_position);

    void coordinate_direction(sf::Vector2f player_position);
    void move(float deltatime);
    
    void draw(sf::RenderWindow& window);
};

//#endif