#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 
class Ctrl;

class Enemy : public Object {
public:
    Enemy(Ctrl* game_ctrl, float max_size, float max_speed);
    virtual ~Enemy();

    //Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

    float get_distance() const;
    sf::Vector2f get_direction() const;

    sf::Vector2f gen_random_position(float min_x, float max_x, float min_y, float max_y);
    sf::Vector2f get_spawn_position();

    void coordinate_direction();
    virtual void move(float deltatime) override;
    //virtual void remove() override;
    
private:
    float distance_from_player;
    sf::Vector2f direction;
};

//#endif