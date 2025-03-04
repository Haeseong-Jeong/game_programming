#include "Enemy.h"
#include "Ctrl.h"

#include <cmath>
#include <random>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// random value ->  position_y, speed
// fix value -> color, size(radius) 

// random engine (���� ������ �����Ͽ� ���� ��ü�� ���� ����)
std::random_device rd;
std::mt19937 gen(rd()); // ���� ���� ����
std::uniform_int_distribution<int> dist(0, 1);  // 0 �Ǵ� 1

//std::uniform_int_distribution<int> enemy_color(0, 255);             // �� ���� ����
//std::uniform_real_distribution<float> enemy_speed(200.0f, 350.0f);  // �ӵ� ���� ����
//std::uniform_real_distribution<float> enemy_size(5.0f, 10.0f);      // ũ�� ���� ����
//std::uniform_real_distribution<float> enemy_xposition(0.f, 0.f);    // x ��ġ ���� ����
//std::uniform_real_distribution<float> enemy_yposition(0.f, 0.f);    // y ��ġ ���� ����

//Enemy::Enemy(sf::Vector2u window_size, sf::Vector2f player_position) : radius{enemy_size(gen)}, speed{enemy_speed(gen)}
//{
//    circle.setRadius(radius);
//    circle.setFillColor(sf::Color::Magenta);
//    circle.setOutlineColor(sf::Color::Cyan);
//    circle.setOutlineThickness(1.5f);
//
//    sf::Vector2f random_position = get_random_position(window_size, player_position);
//    circle.setPosition(random_position);
//}
//
//Enemy::Enemy(const Enemy& other) : 
//    circle(other.circle), speed(other.speed), radius(other.radius), distance_from_player{ other.distance_from_player }, direction{other.direction }
//{
//    sf::Vector2f position = other.circle.getPosition();
//    //circle.setPosition({ position.x + 30, position.y });
//    circle.setPosition({ 30, position.y });
//    circle.setFillColor(sf::Color::Cyan);
//}
//
//Enemy::Enemy(float radius) : circle({ radius }), radius{ radius }, speed{ enemy_speed(gen) } {
//    circle.setFillColor(sf::Color::Magenta);
//    circle.setOutlineColor(sf::Color::Cyan);
//    circle.setOutlineThickness(1.5f);
//}
//
//Enemy::Enemy() : Enemy(enemy_size(gen)) {}
//Enemy::Enemy() : Enemy(enemy_size(gen)) { circle.setFillColor(sf::Color(enemy_color(gen), enemy_color(gen), enemy_color(gen))); }


Enemy::Enemy(Ctrl* game_ctrl, float max_size, float max_speed) : game_ctrl{ game_ctrl }
{
    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    std::uniform_real_distribution<float> enemy_size(max_size / 2, max_size);
    std::uniform_real_distribution<float> enemy_speed(max_speed / 2, max_speed);
    size = enemy_size(gen);
    speed = enemy_speed(gen);

    shape = new sf::Sprite(game_ctrl->get_ship_texture());
    shape->setTextureRect(sf::IntRect({ 40,0 }, { 8,8 }));
    shape->setScale(sf::Vector2f(size, size));
    shape->setPosition(get_random_position());
}

Enemy& Enemy::operator=(const Enemy& other)
{
    if (this != &other) { // �ڱ� �ڽŰ��� ���� ����
        game_ctrl = other.game_ctrl; // game_ctrl ��ü�� ���� ������ ���� �������� �ʱ� ������, �׸��� �ϳ��� ��ü�� �� �����ϰ� �ֱ� ������ ���� ���� �ʿ� ������
        shape = new sf::Sprite(*other.shape); //shape = new sf::Sprite(game_ctrl->get_ship_texture());
        speed = other.speed;
        size = other.size;

        shape->setPosition(get_random_position());
    }
    return *this;
}

float Enemy::get_speed() const { return speed; }
float Enemy::get_distance() const { return distance_from_player; }

sf::Vector2f Enemy::get_position() const { return shape->getPosition(); }
sf::Vector2f Enemy::get_direction() const { return direction; }



//sf::Vector2f Enemy::get_random_float();


sf::Vector2f Enemy::get_random_position()
{
    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    sf::Vector2f player_position = game_ctrl->get_player_ptr()->get_position();

    if (player_position.x <= (float)window_size.x/2 && player_position.y <= (float)window_size.y / 2) // 1��и�
    {
        std::uniform_real_distribution<float> x_position_1(window_size.x - 100, window_size.x - 50);   // x ��ġ ���� ����
        std::uniform_real_distribution<float> y_position_1(50, window_size.y - 50);  // y ��ġ ���� ����
        
        std::uniform_real_distribution<float> x_position_2(50, window_size.x - 50);   // x ��ġ ���� ����
        std::uniform_real_distribution<float> y_position_2(window_size.y - 100, window_size.y - 50);  // y ��ġ ���� ����
        
        return dist(gen) ? sf::Vector2f(x_position_1(gen), y_position_1(gen)) : sf::Vector2f(x_position_2(gen), y_position_2(gen));
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y < (float)window_size.y / 2) // 2��и�
    {
        std::uniform_real_distribution<float> x_position_1(50, 100);     
        std::uniform_real_distribution<float> y_position_1(50, window_size.y - 50);  

        std::uniform_real_distribution<float> x_position_2(50, window_size.x - 50);   
        std::uniform_real_distribution<float> y_position_2(window_size.y - 100, window_size.y - 50);

        return dist(gen) ? sf::Vector2f(x_position_1(gen), y_position_1(gen)) : sf::Vector2f(x_position_2(gen), y_position_2(gen));
    }
    else if (player_position.x < (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2) // 3��и�
    {
        std::uniform_real_distribution<float> x_position_1(window_size.x - 100, window_size.x - 50);   // x ��ġ ���� ����
        std::uniform_real_distribution<float> y_position_1(50, window_size.y - 50);  // y ��ġ ���� ����

        std::uniform_real_distribution<float> x_position_2(50, window_size.x - 50);
        std::uniform_real_distribution<float> y_position_2(50, 100);

        return dist(gen) ? sf::Vector2f(x_position_1(gen), y_position_1(gen)) : sf::Vector2f(x_position_2(gen), y_position_2(gen));
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2) // 4��и�
    {
        std::uniform_real_distribution<float> x_position_1(50, 100);
        std::uniform_real_distribution<float> y_position_1(50, window_size.y - 50);

        std::uniform_real_distribution<float> x_position_2(50, window_size.x - 50);
        std::uniform_real_distribution<float> y_position_2(50, 100);
        
        return dist(gen) ? sf::Vector2f(x_position_1(gen), y_position_1(gen)) : sf::Vector2f(x_position_2(gen), y_position_2(gen));
    }
}


void Enemy::coordinate_direction(sf::Vector2f player_position)
{
    //vector = destination - start
    sf::Vector2f enemy_to_player = player_position - shape->getPosition();
    distance_from_player = sqrt(enemy_to_player.x * enemy_to_player.x + enemy_to_player.y * enemy_to_player.y);
    direction = enemy_to_player / distance_from_player;
}


void Enemy::move( float deltatime) { shape->move(direction * speed * deltatime); }

void Enemy::draw(sf::RenderWindow& window) { window.draw(*shape); }
