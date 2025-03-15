#pragma once

#include "Object/Entity/Entity.h"
#include <SFML/Graphics.hpp>

class GameObjectManager;

class Bullet : public Entity {
public:
    Bullet(GameObjectManager* objectmanager, EntityType type, float size, float speed);
    ~Bullet();

    void set_position();
    sf::Vector2f get_bullet_direction();
    virtual void move(float deltatime) override;

private:
    sf::Vector2f direction;
};

