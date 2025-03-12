#pragma once

#include "Entity/Entity.h"
#include <SFML/Graphics.hpp>

class Game;
//class EntityManager;

class Player : public Entity {
public:
    Player(Game* game, EntityType type, float size, float speed);
    Player(sf::Texture& texture, EntityType type, float size, float speed);

    virtual ~Player();

    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:
};
