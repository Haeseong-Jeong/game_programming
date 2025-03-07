#pragma once

#include "Object.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Bullet : public Object {
public:
    Bullet(Ctrl* game_ctrl, ObjectType type, float size, float speed);
    virtual ~Bullet();

    sf::Vector2f get_bullet_direction();
    virtual void move(float deltatime) override;
    //virtual void remove() override;

private:
    sf::Vector2f direction;
};

