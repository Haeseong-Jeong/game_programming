#include <cmath>
#include <random>
#include <iostream>
#include "Enemy.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 

// random engine (전역 변수로 선언하여 여러 객체가 공유 가능)
std::random_device rd;
std::mt19937 gen(rd()); // 난수 생성 엔진
std::uniform_real_distribution<float> enemy_speed(0.01f, 0.05f); // 속도 범위 설정

Enemy::Enemy(float radius) : circle({ radius }), radius{ radius }, speed{ enemy_speed(gen) } {
    circle.setFillColor(sf::Color::Magenta);
}
Enemy::Enemy() : Enemy(10.f) {}


void Enemy::set_position(sf::Window& window)
{
    sf::Vector2u window_size = window.getSize();
    circle.setPosition({ sf::Vector2f(window_size.x - 50, rand() % window_size.y) });
}

sf::Vector2f Enemy::get_position() { return circle.getPosition(); }

float Enemy::get_speed() { return speed; }

void Enemy::draw_enemy(sf::RenderWindow& window) { window.draw(circle); }

void Enemy::move_enemy(sf::Vector2f player_position, Enemy& enemy, int num_enemy, float speed)
{
    //vector = destination - start
    sf::Vector2f enemy_position = enemy.get_position();

    for (int i = 0; i < num_enemy; i++)
    {
        float enemy_to_player_x = player_position.x - enemy_position.x;
        float enemy_to_player_y = player_position.y - enemy_position.y;

        float distance = sqrt(enemy_to_player_x * enemy_to_player_x + enemy_to_player_y * enemy_to_player_y);

        //enemy.circle.setPosition({ enemy_position.x - enemy_to_player_x / distance * speed, enemy_position.y - enemy_to_player_y / distance * speed });
        enemy.circle.move({ enemy_to_player_x / distance * speed, enemy_to_player_y / distance * speed });
    }
}
