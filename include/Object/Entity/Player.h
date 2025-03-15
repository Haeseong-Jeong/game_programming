#pragma once

#include "Object/Entity/Entity.h"
#include <SFML/Graphics.hpp>

class Game;

class Player : public Entity {
public:
    Player(Game* game, EntityType type, float size, float speed);
    ~Player();

    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:
};
