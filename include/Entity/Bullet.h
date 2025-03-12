#pragma once

#include "Entity/Entity.h"
#include <SFML/Graphics.hpp>

class Game;

class Bullet : public Entity {
public:
    Bullet(Game* game, EntityType type, float size, float speed);
    virtual ~Bullet();

    sf::Vector2f get_bullet_direction();
    virtual void move(float deltatime) override;
    //virtual void remove() override;

private:
    sf::Vector2f direction;
};

