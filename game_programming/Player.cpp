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

sf::Vector2f Player::get_position() { return rect.getPosition(); }

void Player::draw(sf::RenderWindow& window) { window.draw(rect); }

void Player::move_by_key()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        rect.move({ -speed, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        rect.move({ speed, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        rect.move({ 0.f, -speed });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        rect.move({ 0.f, speed });
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

