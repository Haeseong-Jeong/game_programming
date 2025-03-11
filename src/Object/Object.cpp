#include "Game/Game.h"
#include "Game/ObjectManager.h"
#include "Object/Object.h"

Object::Object(Game* game, ObjectType type, float size, float speed)
    : game{ game }, size{ size }, speed{ speed }, type{ type }, activate{ true }
{       
}

Object::Object(ObjectType type, float size, float speed)
    : size{ size }, speed{ speed }, type{ type }, activate{ true }
{
}

Object::~Object() { delete shape; }

sf::Vector2f Object::get_position() { return shape->getPosition(); }
sf::Sprite* Object::get_shape() { return shape; }
ObjectType Object::get_type() { return type; }

bool Object::is_activate() { return activate; }
void Object::deactivate() { activate = false; }

void Object::draw(sf::RenderWindow& window) { 
    window.draw(*shape);
    //window.draw(bounding_box);
    //window.draw(skeleton);
}

void Object::make_bounding_box()
{
    sf::FloatRect bounds = shape->getGlobalBounds();
    bounding_box = sf::RectangleShape(sf::Vector2f(bounds.size.x, bounds.size.y));
    bounding_box.setPosition(shape->getPosition());
    bounding_box.setFillColor(sf::Color::Transparent);
    bounding_box.setOutlineColor(sf::Color::Red);
    bounding_box.setOutlineThickness(0.7f);
}

void Object::make_skeleton(float scale)
{
    sf::FloatRect bounds = shape->getGlobalBounds();
    float sk_width = bounds.size.x * scale;
    float sk_height = bounds.size.y * scale;

    skeleton = sf::RectangleShape(sf::Vector2f(sk_width, sk_height));
    skeleton.setPosition(bounds.getCenter() - sf::Vector2f(sk_width / 2, sk_height / 2));
    skeleton.setFillColor(sf::Color::Transparent);
    skeleton.setOutlineColor(sf::Color::Yellow);
    skeleton.setOutlineThickness(0.7f);
}