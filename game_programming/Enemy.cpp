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
std::uniform_int_distribution<int> enemy_color(0, 255); // 색 범위 설정
//std::uniform_real_distribution<float> enemy_speed(0.01f, 0.05f); // 속도 범위 설정
std::uniform_real_distribution<float> enemy_speed(200.0f, 350.0f); // 속도 범위 설정
std::uniform_real_distribution<float> enemy_speed(50.0f, 100.0f); // 속도 범위 설정
std::uniform_real_distribution<float> enemy_size(5.0f, 10.0f); // 크기 범위 설정

std::uniform_real_distribution<float> enemy_xposition(0.f, 0.f); // 위치 범위 설정
std::uniform_real_distribution<float> enemy_yposition(0.f, 0.f); // 위치 범위 설정


Enemy::Enemy(sf::Vector2u window_size, sf::Vector2f player_position) : radius{enemy_size(gen)}, speed{enemy_speed(gen)}
{
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Magenta);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.0f);

    sf::Vector2f random_position = get_random_position(window_size, player_position);
    circle.setPosition(random_position);
}

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
    if (this != &other) { // 자기 자신과의 대입 방지
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


sf::Vector2f Enemy::get_random_position(sf::Vector2u window_size, sf::Vector2f player_position)
{
    if (player_position.x <= (float)window_size.x/2 && player_position.y <= (float)window_size.y / 2)
    {
        enemy_xposition = std::uniform_real_distribution<float>(window_size.x - 100, window_size.x - 50);
        enemy_yposition = std::uniform_real_distribution<float>(window_size.y - 100, window_size.y - 50);
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y < (float)window_size.y / 2)
    {
        enemy_xposition = std::uniform_real_distribution<float>(0.f + 50, 0.f + 100);
        enemy_yposition = std::uniform_real_distribution<float>(window_size.y - 100, window_size.y - 50);
    }
    else if (player_position.x < (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2)
    {
        enemy_xposition = std::uniform_real_distribution<float>(window_size.x - 100, window_size.x - 50);
        enemy_yposition = std::uniform_real_distribution<float>(0.f + 50, 0.f + 100);
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2)
    {
        enemy_xposition = std::uniform_real_distribution<float>(0.f + 50, 0.f + 100);
        enemy_yposition = std::uniform_real_distribution<float>(0.f + 50, 0.f + 100);
    }
    return sf::Vector2f(enemy_xposition(gen), enemy_yposition(gen));
}


sf::Vector2f Enemy::get_direction() { return sf::Vector2f(dx, dy); }
float Enemy::get_distance() { return distance_from_player; }
float Enemy::get_speed() { return speed; }


void Enemy::calculate_direction(sf::Vector2f player_position)
{
    //vector = destination - start
    //sf::Vector2f enemy_position = enemy->get_position();
    sf::Vector2f enemy_position = circle.getPosition();

    float enemy_to_player_x = player_position.x - enemy_position.x;
    float enemy_to_player_y = player_position.y - enemy_position.y;

    distance_from_player = sqrt(enemy_to_player_x * enemy_to_player_x + enemy_to_player_y * enemy_to_player_y);

    dx = (enemy_to_player_x / distance_from_player);
    dy = (enemy_to_player_y / distance_from_player);
}


void Enemy::move(sf::Vector2f player_position, float deltatime)
{
    //enemy.circle.setPosition({ enemy_position.x - enemy_to_player_x / distance * speed, enemy_position.y - enemy_to_player_y / distance * speed });
    calculate_direction(player_position);
    circle.move({ dx * speed * deltatime, dy * speed * deltatime });
}

void Enemy::draw(sf::RenderWindow& window) { window.draw(circle); }
