#include "Ctrl.h"
#include "Player.h"
#include "Bullet.h"

Bullet::Bullet(Ctrl* game_ctrl, float size, float speed) 
	: game_ctrl{ game_ctrl }, size{ size }, speed { speed }, direction{sf::Vector2f(0,0)}
{
	sf::Vector2f player_position = game_ctrl->get_player_ptr()->get_position();
	shape = new sf::Sprite(game_ctrl->get_projectile_texture());
	shape->setTextureRect(sf::IntRect({ 24,24 }, { 8,8 }));
	shape->setScale(sf::Vector2f(size, size));
	shape->setPosition(player_position);

	//shape.emplace(game_ctrl->get_projectile_texture());
	//shape.value().setTextureRect(sf::IntRect({ 24,24 }, { 8,8 }));
	//shape.value().setScale(sf::Vector2f(size, size));
	//shape.value().setPosition(player_position);

	direction = game_ctrl->get_bullet_direction();
}

sf::Vector2f Bullet::get_position() { return sf::Vector2f(shape->getPosition()); }
void Bullet::shoot(float deltatime) { shape->move(direction*speed*deltatime); }
void Bullet::draw(sf::RenderWindow& window) { window.draw(*shape); }
