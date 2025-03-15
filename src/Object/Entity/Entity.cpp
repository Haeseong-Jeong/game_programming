#include "Game/GameTextureManager.h"
#include "Object/Entity/Entity.h"

Entity::Entity(GameObjectManager* objectmanager, EntityType type, float size, float speed)
    : Object{ objectmanager, size, speed }, type{ type }
{       
}
Entity::~Entity() {}


EntityType Entity::get_type() { return type; }


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