#include "Ctrl.h"
#include <iostream>

Ctrl::Ctrl(int window_w,int window_h) 
    : window_w{ window_w }, window_h{ window_h }, window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "Game play"), player{nullptr}
{
    objects.clear();
    enemy_gen_num = 5;
}

sf::Window& Ctrl::get_window() { return window; }
sf::Texture& Ctrl::get_ship_texture() { return ship_texture; }
sf::Texture& Ctrl::get_projectile_texture() { return projectile_texture; }

Player* Ctrl::get_player_ptr() { return player; }
std::vector<Object*> Ctrl::get_objects() { return objects; }


bool Ctrl::check_collision(Object* e, Object* b) 
{   
    std::optional<sf::Rect<float>> is_intersection = e->skeleton.getGlobalBounds().findIntersection(b->skeleton.getGlobalBounds());
    return is_intersection.has_value();
}

void Ctrl::is_hit()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->get_type() == ObjectType::BULLET)
        {
            for (int j = 0; j < objects.size(); j++)
            {
                if (objects[j]->get_type() != ObjectType::ENEMY) { continue; }
                if (check_collision(objects[i], objects[j]))
                {
                    objects[i]->deactivate();
                    objects[j]->deactivate();
                    break;
                }
            }
        }
    }
}


void Ctrl::is_out_boundary()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->get_type() == ObjectType::ENEMY) { continue; }
        sf::Vector2f pos = objects[i]->get_position();
        if (pos.x < 0 || pos.x > window_w || pos.y < 0 || pos.y > window_h) { objects[i]->deactivate(); }
    }
}

void Ctrl::spwan_enemy()
{
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy(this, ObjectType::ENEMY, 3.0f, 350.0f);
            objects.push_back(enemy);
        }
        enemy_clock.restart();
    }
}


void Ctrl::spwan_bullet()
{
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period)
    {
        Bullet* bullet = new Bullet(this, ObjectType::BULLET, 5.f, 550.f);
        objects.push_back(bullet);
        bullet_clock.restart();
    }
}


bool Ctrl::initialize_game() 
{
    if (!ship_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png")) { return false; }
    if (!projectile_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png")) { return false; }
    initialize_objects();
    return true;
}


void Ctrl::initialize_objects()
{
    Player* player = new Player(this, ObjectType::PLAYER, 3.0f, 550.f);
    objects.push_back(player);
    this->player = player;

    for (int i = 0; i < enemy_gen_num; i++)
    {
        Enemy* enemy = new Enemy(this, ObjectType::ENEMY, 3.0f, 350.0f);
        objects.push_back(enemy);
    }

    Bullet* bullet = new Bullet(this, ObjectType::BULLET, 5.f, 550.f);
    objects.push_back(bullet);
}

void Ctrl::running_game()
{
    while (window.isOpen())
    {
        process_events();
        set_game();
        update_game();
    }
}

void Ctrl::process_events()
{
    // Process events
    while (const std::optional event = window.pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Ctrl::set_game()
{
    deltatime = clock.restart().asSeconds();
    player->move_by_mouse(window);

    spwan_enemy();
    spwan_bullet();
}

void Ctrl::update_game()
{
    // 1. Clear screen
    window.clear();

    // 2. Draw and Move object 
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw(window);
        objects[i]->move(deltatime);
        objects[i]->make_bounding_box();
        objects[i]->make_skeleton(0.6);
    }

    is_hit();// 피격 판정
    is_out_boundary(); // 화면 나감 판정
    std::erase_if(objects, [&](Object* obj) { return obj->is_activate() == false; }); // 화면 나가거나 피격 되면 제거

    // 3. Display the window
    window.display();
}


void Ctrl::terminate_game()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}