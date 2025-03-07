#include "Ctrl.h"
#include "Player.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Player::Player(Ctrl* game_ctrl, ObjectType type, float size, float speed) : Object{ game_ctrl, type, size, speed }
{
    shape = new sf::Sprite(game_ctrl->get_ship_texture());
    shape->setTextureRect(sf::IntRect({8,0}, {8,8}));
    shape->setScale(sf::Vector2f(size, size));
    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    shape->setPosition({ sf::Vector2f(window_size.x / 2 + size, window_size.y / 2 + size) });

    make_bounding_box();
    make_skeleton(0.6);
    //tmp_shape.setTexture(game_ctrl->get_ship_texture());
    //tmp_shape.setTextureRect(sf::IntRect({ 8,0 }, { 8,8 }));
    //tmp_shape.setScale(sf::Vector2f(size, size));
    //tmp_shape.setPosition({ sf::Vector2f(window_size.x / 2 + size, window_size.y / 2 + size) });
}

Player::~Player() {}


void Player::move(float deltatime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape->move({ -speed * deltatime, 0.f });

        //bounding_box.move({ -speed * deltatime, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape->move({ speed * deltatime, 0.f });

        //bounding_box.move({ speed * deltatime, 0.f });

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        shape->move({ 0.f, -speed * deltatime });

        //bounding_box.move({ 0.f, -speed * deltatime });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        shape->move({ 0.f, speed * deltatime });

        //bounding_box.move({ 0.f, speed * deltatime });
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

