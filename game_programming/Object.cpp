#include "Object.h"

Object::Object(Ctrl* game_ctrl, ObjectType type, float size, float speed)
	: game_ctrl{ game_ctrl }, size{ size }, speed{ speed }, type{ type }, activate{ true } {}

Object::~Object() { delete shape; }

sf::Vector2f Object::get_position() { return shape->getPosition(); }

sf::Sprite* Object::get_shape() { return shape; }

ObjectType Object::get_type() { return type; }

bool Object::is_activate() { return activate; }

void Object::deactivate() { activate = false; }

void Object::draw(sf::RenderWindow& window) { window.draw(*shape); }

void Object::remove() {}
