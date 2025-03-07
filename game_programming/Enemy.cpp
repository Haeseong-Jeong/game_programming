#include "Enemy.h"
#include "Ctrl.h"

#include <cmath>
#include <random>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// random engine (전역 변수로 선언하여 여러 객체가 공유 가능)
std::random_device rd;
std::mt19937 gen(rd()); // 난수 생성 엔진
std::uniform_int_distribution<int> dist(0, 1);  // 0 또는 1

Enemy::Enemy(Ctrl* game_ctrl, ObjectType type, float max_size, float max_speed) : Object{ game_ctrl, type, size, speed }
{
    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    std::uniform_real_distribution<float> enemy_size(max_size / 2, max_size);
    std::uniform_real_distribution<float> enemy_speed(max_speed / 2, max_speed);
    size = enemy_size(gen);
    speed = enemy_speed(gen);

    shape = new sf::Sprite(game_ctrl->get_ship_texture());
    //shape->setTextureRect(sf::IntRect({ 40,0 }, { 8,8 }));
    shape->setTextureRect(sf::IntRect({ 40,2 }, { 7,5 }));
    shape->setScale(sf::Vector2f(size, size));

    shape->setPosition(get_spawn_position());
    coordinate_direction();

    make_bounding_box();
    make_skeleton(0.6);
}

Enemy::~Enemy() {}

Enemy& Enemy::operator=(const Enemy& other)
{
    if (this != &other) { // 자기 자신과의 대입 방지
        game_ctrl = other.game_ctrl; // game_ctrl 객체는 가장 마지막 까지 없어지지 않기 때문에, 그리고 하나의 객체로 다 공유하고 있기 때문에 깊은 복사 필요 없을듯
        shape = new sf::Sprite(*other.shape); //shape = new sf::Sprite(game_ctrl->get_ship_texture());
        speed = other.speed;
        size = other.size;

        shape->setPosition(get_spawn_position());
    }
    return *this;
}

sf::Vector2f Enemy::gen_random_position(float min_x, float max_x, float min_y, float max_y)
{
    std::uniform_real_distribution<float> x_position(min_x, max_x);
    std::uniform_real_distribution<float> y_position(min_y, max_y);
    return sf::Vector2f(x_position(gen), y_position(gen));
}

sf::Vector2f Enemy::get_spawn_position()
{
    sf::Vector2u window_size = game_ctrl->get_window().getSize();
    sf::Vector2f player_position = game_ctrl->get_player_ptr()->get_position();

    if (player_position.x <= (float)window_size.x/2 && player_position.y <= (float)window_size.y / 2) // 1사분면
    {
        sf::Vector2f pos_1 = gen_random_position(window_size.x, window_size.x + 50, -50, window_size.y + 50);
        sf::Vector2f pos_2 = gen_random_position(-50, window_size.x + 50, window_size.y, window_size.y + 50);
        return dist(gen) ? pos_1 : pos_2;
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y < (float)window_size.y / 2) // 2사분면
    {
        sf::Vector2f pos_1 = gen_random_position(-50, 0, -50, window_size.y + 50);
        sf::Vector2f pos_2 = gen_random_position(-50, window_size.x + 50, window_size.y, window_size.y + 50);
        return dist(gen) ? pos_1 : pos_2;
    }
    else if (player_position.x < (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2) // 3사분면
    {
        sf::Vector2f pos_1 = gen_random_position(window_size.x, window_size.x + 50, -50, window_size.y + 50);
        sf::Vector2f pos_2 = gen_random_position(-50, window_size.x + 50, -50, 0);
        return dist(gen) ? pos_1 : pos_2;
    }
    else if (player_position.x > (float)window_size.x / 2 && player_position.y > (float)window_size.y / 2) // 4사분면
    {
        sf::Vector2f pos_1 = gen_random_position(-50, 0, -50, window_size.y + 50);
        sf::Vector2f pos_2 = gen_random_position(-50, window_size.x + 50, -50, 0);
        return dist(gen) ? pos_1 : pos_2;
    }
}


void Enemy::coordinate_direction()
{
    //vector = destination - start
    sf::Vector2f player_position = game_ctrl->get_player_ptr()->get_position();
    sf::Vector2f enemy_to_player = player_position - shape->getPosition();
    distance_from_player = sqrt(enemy_to_player.x * enemy_to_player.x + enemy_to_player.y * enemy_to_player.y);
    if (distance_from_player < game_ctrl->EPSILON) { distance_from_player = game_ctrl->EPSILON; }
    direction = enemy_to_player / distance_from_player;
}


void Enemy::move(float deltatime)
{
    coordinate_direction();
    shape->move(direction * speed * deltatime); 

    //bounding_box.move(direction * speed * deltatime);
}