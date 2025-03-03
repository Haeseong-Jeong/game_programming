#include "Player.h"
#include <cmath>
#include <random>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player(float width, float height, float speed) : rect({ width, height }), width{ width }, height{ height }, speed{ speed } {
    rect.setFillColor(sf::Color::Red);
}
Player::Player(float width, float speed) : Player(width, width, speed) {}
Player::Player(float speed) : Player(20.f, 20.f, speed) {}
Player::Player() : Player(20.f, 20.f, 0.5f) {}

void Player::set_position(sf::Window& window)
{
    sf::Vector2u window_size = window.getSize();
    rect.setPosition({ sf::Vector2f(window_size.x / 2 + width, window_size.y / 2 + height) });
}

sf::RectangleShape Player::get_shape() { return rect; }

sf::Vector2f Player::get_position() { return rect.getPosition(); }


sf::Vector2f Player::get_bullet_direction(std::vector<Enemy*> enemy, int enemy_num)
{
    int min_idx = 0;
    float min_distance = enemy[0]->get_distance();
    
    for (int i = 1; i < enemy_num; i++)
    {
        float tmp = enemy[i]->get_distance();
        if (tmp < min_distance)
        {
            min_idx = i;
        }
    }
    return enemy[min_idx]->get_direction();
}


void Player::draw(sf::RenderWindow& window) { window.draw(rect); }

void Player::move_by_key(float deltatime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        rect.move({ -speed * deltatime, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        rect.move({ speed * deltatime, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        rect.move({ 0.f, -speed * deltatime });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        rect.move({ 0.f, speed * deltatime });
    }
}

void Player::move_by_mouse(sf::Window& window)
{
    // mouse press
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        rect.setPosition({ (float)position.x - width / 2, (float)position.y - height / 2 });
    }
}

