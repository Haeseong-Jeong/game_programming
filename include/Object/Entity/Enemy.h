#pragma once

#include "Object/Entity/Entity.h"
#include <SFML/Graphics.hpp>

class GameObjectManager;


class Enemy : public Entity {
public:
    Enemy(GameObjectManager* objectmanager, EntityType type, float max_size, float max_speed);
    ~Enemy();

    //Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

    void set_position();
    sf::Vector2f gen_random_position(float min_x, float max_x, float min_y, float max_y);
    sf::Vector2f get_spawn_position();

    void coordinate_direction();
    virtual void move(float deltatime) override;
    
private:
    float distance_from_player;
    sf::Vector2f direction;
};