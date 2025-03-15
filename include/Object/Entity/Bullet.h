#pragma once

#include "Object/Entity/Entity.h"
#include <SFML/Graphics.hpp>

class Game;

class Bullet : public Entity {
public:
    Bullet(Game* game, EntityType type, float size, float speed);
    ~Bullet();

    sf::Vector2f get_bullet_direction();
    virtual void move(float deltatime) override;

private:
    sf::Vector2f direction;
};

