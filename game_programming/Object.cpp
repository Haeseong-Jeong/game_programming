#include "Object.h"

Object::Object(Ctrl* game_ctrl, float size, float speed) : game_ctrl{game_ctrl}, size{size}, speed{speed} {}

Object::~Object() { delete shape; }

sf::Vector2f Object::get_position() { return shape->getPosition(); }

void Object::draw(sf::RenderWindow& window) { window.draw(*shape); }

void Object::remove() {}
