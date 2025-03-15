#include "Game/GameTextureManager.h"
#include "Game/GameObjectManager.h"

#include "Object/Entity/Player.h"

#include <SFML/Graphics.hpp>

Player::Player(GameObjectManager* objectmanager, EntityType type, float size, float speed) : Entity{ objectmanager, type, size, speed }
{
    shape = new sf::Sprite(objectmanager->get_texturemanager()->get_ship_texture());
    shape->setTextureRect(sf::IntRect({8,0}, {8,8}));
    shape->setScale(sf::Vector2f(size, size));

    make_bounding_box();
    make_skeleton(0.6);
}
Player::~Player() {}


void Player::set_position()
{
    sf::Vector2u window_size = objectmanager->get_window_size();
    shape->setPosition({ sf::Vector2f(window_size.x / 2 + size, window_size.y / 2 + size) });
}

void Player::move(float deltatime)
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

