#include <cmath>
#include <random>
#include <iostream>
#include "Enemy.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 

// random engine (���� ������ �����Ͽ� ���� ��ü�� ���� ����)
std::random_device rd;
std::mt19937 gen(rd()); // ���� ���� ����
std::uniform_int_distribution<int> enemy_color(0, 255); // �� ���� ����
//std::uniform_real_distribution<float> enemy_speed(0.01f, 0.05f); // �ӵ� ���� ����
std::uniform_real_distribution<float> enemy_speed(50.0f, 100.0f); // �ӵ� ���� ����
std::uniform_real_distribution<float> enemy_size(5.0f, 10.0f); // ũ�� ���� ����


Enemy::Enemy(const Enemy& other) : circle(other.circle), speed(other.speed), radius(other.radius) {
    sf::Vector2f position = other.circle.getPosition();
    //circle.setPosition({ position.x + 30, position.y });
    circle.setPosition({ 30, position.y });
    circle.setFillColor(sf::Color::Cyan);
}


Enemy::Enemy(float radius) : circle({ radius }), radius{ radius }, speed{ enemy_speed(gen) } {
    circle.setFillColor(sf::Color::Magenta);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.0f);
}


Enemy::Enemy() : Enemy(enemy_size(gen)) {}
//Enemy::Enemy() : Enemy(enemy_size(gen)) { circle.setFillColor(sf::Color(enemy_color(gen), enemy_color(gen), enemy_color(gen))); }


Enemy& Enemy::operator=(const Enemy& other)
{
    if (this != &other) { // �ڱ� �ڽŰ��� ���� ����
        circle = other.circle;
        speed = other.speed;
        radius = other.radius;

        sf::Vector2f position = other.circle.getPosition();
        circle.setPosition({ 30, position.y });
        //circle.setPosition({ position.x + 30, position.y });
        circle.setFillColor(sf::Color::Cyan);
    }
    return *this;
}


void Enemy::set_position(sf::Window& window)
{
    sf::Vector2u window_size = window.getSize();
    circle.setPosition({ sf::Vector2f(window_size.x - 50, rand() % window_size.y) });
}


sf::Vector2f Enemy::get_position() { return circle.getPosition(); }


float Enemy::get_speed() { return speed; }


void Enemy::draw(sf::RenderWindow& window) { window.draw(circle); }


void Enemy::move(sf::Vector2f player_position, Enemy& enemy, int num_enemy, float speed, float deltatime)
{
    //vector = destination - start
    sf::Vector2f enemy_position = enemy.get_position();

    for (int i = 0; i < num_enemy; i++)
    {
        float enemy_to_player_x = player_position.x - enemy_position.x;
        float enemy_to_player_y = player_position.y - enemy_position.y;

        float distance = sqrt(enemy_to_player_x * enemy_to_player_x + enemy_to_player_y * enemy_to_player_y);

        //enemy.circle.setPosition({ enemy_position.x - enemy_to_player_x / distance * speed, enemy_position.y - enemy_to_player_y / distance * speed });
        enemy.circle.move({ (enemy_to_player_x / distance) * speed * deltatime, (enemy_to_player_y / distance) * speed * deltatime });
    }
}
