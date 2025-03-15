#pragma once

#include "Object/Entity/Entity.h"
#include <SFML/Graphics.hpp>

class GameObjectManager;

class Player : public Entity {
public:
    Player(GameObjectManager* objectmanager, EntityType type, float size, float speed);
    ~Player();

    void set_position();
    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:
};
