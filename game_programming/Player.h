#pragma once
//#ifndef _Player
//#define _Player

//#include "Ctrl.h"
#include "Object.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Player : public Object {
public:
    Player(Ctrl* game_ctrl, float size, float speed);
    virtual ~Player();

    virtual void move(float deltatime) override;
    void move_by_mouse(sf::Window& window);

private:

};

//#endif