#pragma once

#include "Object/Object.h"
#include <SFML/Graphics.hpp>

class Game;
//class ObjectManager;

class Player : public Object {
public:
    Player(Game* game, ObjectType type, float size, float speed);
    Player(sf::Texture& texture, ObjectType type, float size, float speed);

    virtual ~Player();

    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:
};
