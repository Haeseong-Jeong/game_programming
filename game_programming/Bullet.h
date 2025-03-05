#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

class Ctrl;

class Bullet {
private:
    // Defined in constructor
    //std::optional<sf::Sprite> shape;  // ���������� ���� ����
    Ctrl* game_ctrl;
    sf::Sprite* shape;
    float speed;
    float size;
    sf::Vector2f direction;

public:
    Bullet(Ctrl* game_ctrl, float size, float speed);
    ~Bullet() { delete shape; };

    sf::Vector2f get_position();

    void shoot(float deltatime);

    void draw(sf::RenderWindow& window);
};

