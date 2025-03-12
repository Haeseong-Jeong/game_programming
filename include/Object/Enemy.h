#pragma once

#include "Object/Object.h"
#include <SFML/Graphics.hpp>

class Game;

class Enemy : public Object {
public:
    Enemy(Game* game, ObjectType type, float max_size, float max_speed);
    //Enemy(ObjectType type, float max_size, float max_speed);

    virtual ~Enemy();

    //Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

    sf::Vector2f gen_random_position(float min_x, float max_x, float min_y, float max_y);
    sf::Vector2f get_spawn_position();

    void coordinate_direction();
    virtual void move(float deltatime) override;
    
private:
    float distance_from_player;
    sf::Vector2f direction;
};