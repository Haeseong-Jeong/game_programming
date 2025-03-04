#include "Ctrl.h"
#include "Player.h"
#include <cmath>
#include <random>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


Player::Player(Ctrl* game_ctrl, float size, float speed) : game_ctrl{ game_ctrl }, size{ size }, speed{ speed }
{
    shape = new sf::Sprite(game_ctrl->get_ship_texture());
    shape->setTextureRect(sf::IntRect({8,0}, {8,8}));
    shape->setScale(sf::Vector2f(size, size));

    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    shape->setPosition({ sf::Vector2f(window_size.x / 2 + size, window_size.y / 2 + size) });
}


sf::Vector2f Player::get_position() { return shape->getPosition(); }

void Player::draw(sf::RenderWindow& window) { window.draw(*shape); }

void Player::move_by_key(float deltatime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape->move({ -speed * deltatime, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape->move({ speed * deltatime, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        shape->move({ 0.f, -speed * deltatime });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        shape->move({ 0.f, speed * deltatime });
    }
}

void Player::move_by_mouse(sf::Window& window)  // mouse press
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        shape->setPosition({ (float)position.x - size / 2, (float)position.y - size / 2 });
    }
}

