#include "Player.h"
#include "Bullet.h"

//Bullet::Bullet(sf::Vector2f player_position) : circle({ 5.0f }), radius{ 5.0f }, speed{ 550.0f }, shoot_flag{ false }
//{
//	circle.setPosition(player_position);
//}

Bullet::Bullet(sf::Vector2f player_position, sf::Vector2f direction) : radius{ 3.0f }, speed{ 550.0f }, direction{ direction } {
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(player_position);
}


Bullet::Bullet() : radius{ 3.0f }, speed{ 550.0f } { 
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Green); 
}

//Bullet::~Bullet()
//{
//}

void Bullet::set_position(sf::Vector2f player_position) { circle.setPosition(player_position); }

sf::Vector2f Bullet::get_position() { return sf::Vector2f(circle.getPosition()); }

void Bullet::shoot(float deltatime) { circle.move(direction*speed*deltatime); }

void Bullet::draw(sf::RenderWindow& window) { window.draw(circle); }