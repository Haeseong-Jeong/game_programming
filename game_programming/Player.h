#pragma once

#include "Enemy.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Player : public Object {
public:
    Player(Ctrl* game_ctrl, ObjectType type, float size, float speed);
    virtual ~Player();

    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:
};
