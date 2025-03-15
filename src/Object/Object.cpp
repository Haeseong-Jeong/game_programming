#include "Object/Object.h"

Object::Object(GameObjectManager* objectmanager, float size, float speed)
    : objectmanager{ objectmanager }, size{ size }, speed{ speed }, activate{ true }
{}

Object::~Object() { delete shape; }


sf::Vector2f Object::get_position() { return shape->getPosition(); }
sf::Sprite* Object::get_shape() { return shape; }

bool Object::is_activate() { return activate; }
void Object::deactivate() { activate = false; }


void Object::draw(sf::RenderWindow& window) {
    window.draw(*shape);
    //window.draw(bounding_box);
    //window.draw(skeleton);
}