#include "Player.h"
#include "Bullet.h"


Bullet::Bullet(float radius, float speed) : circle({radius}), radius{radius}, speed{ speed }
{
	circle.setFillColor(sf::Color::Green);
}

Bullet::Bullet() : Bullet(5.0f, 0.2f) {}

//Bullet::~Bullet()
//{
//}

void Bullet::set_position(Player* player)
{
	sf::Vector2f player_position = player->get_position();
	circle.setPosition(player_position);
}

void Bullet::shoot()
{
	circle.move({ speed, 0.0f });
	//circle.move({ 0.2f, 0.0f });
}

void Bullet::draw(sf::RenderWindow& window) { window.draw(circle); }
