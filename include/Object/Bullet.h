#pragma once

#include "Object/Object.h"
#include <SFML/Graphics.hpp>

class Game;

class Bullet : public Object {
public:
    Bullet(Game* game, ObjectType type, float size, float speed);
    virtual ~Bullet();

    sf::Vector2f get_bullet_direction();
    virtual void move(float deltatime) override;
    //virtual void remove() override;

private:
    sf::Vector2f direction;
};

