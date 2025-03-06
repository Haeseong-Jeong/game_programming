#include "Ctrl.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Ctrl* game_ctrl, float size, float speed) : Object{ game_ctrl,size,speed }
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

Bullet::~Bullet()
{
}

void Bullet::move(float deltatime) { shape->move(direction*speed*deltatime); }

//void Bullet::remove()
//{
//	std::erase_if(bullets, [&](Bullet* bullet) { return bullet->get_position().x > window_w; });
//
//	std::erase_if(game_ctrl.get, [&](Bullet* bullet) { return bullet->get_position().x > window_w; });
//
//}
