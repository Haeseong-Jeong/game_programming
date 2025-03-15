#include "Game/Game.h"
#include "Object/Entity/Entity.h"

Entity::Entity(Game* game, EntityType type, float size, float speed)
    : game{ game }, size{ size }, speed{ speed }, type{ type }, activate{ true }
{       
}

Entity::~Entity() { delete shape; }

sf::Vector2f Entity::get_position() { return shape->getPosition(); }
sf::Sprite* Entity::get_shape() { return shape; }
EntityType Entity::get_type() { return type; }

bool Entity::is_activate() { return activate; }
void Entity::deactivate() { activate = false; }

void Entity::draw(sf::RenderWindow& window) { 
    window.draw(*shape);
    //window.draw(bounding_box);
    //window.draw(skeleton);
}

void Entity::make_bounding_box()
{
    sf::FloatRect bounds = shape->getGlobalBounds();
    bounding_box = sf::RectangleShape(sf::Vector2f(bounds.size.x, bounds.size.y));
    bounding_box.setPosition(shape->getPosition());
    bounding_box.setFillColor(sf::Color::Transparent);
    bounding_box.setOutlineColor(sf::Color::Red);
    bounding_box.setOutlineThickness(0.7f);
}

void Entity::make_skeleton(float scale)
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