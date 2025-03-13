#include "Game/Game.h"
#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include "Entity/Bullet.h"
#include "Entity/Player.h"
#include <iostream>

Game::Game(int window_w, int window_h) 
    : window_w{ window_w }, window_h{ window_h }, window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "Game play"), player { nullptr }
{
    entities.clear();
    enemy_gen_num = 5;
}

Game::~Game()
{
}

sf::Window& Game::get_window() { return window; }
sf::Texture& Game::get_ship_texture() { return ship_texture; }
sf::Texture& Game::get_projectile_texture() { return projectile_texture; }

Player* Game::get_player() { return player; }
std::vector<Entity*> Game::get_entities() { return entities; }


bool Game::check_collision(Entity* e, Entity* b) 
{   
    std::optional<sf::Rect<float>> is_intersection = e->skeleton.getGlobalBounds().findIntersection(b->skeleton.getGlobalBounds());
    return is_intersection.has_value();
}

void Game::is_hit()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::BULLET)
        {
            for (int j = 0; j < entities.size(); j++)
            {
                if (entities[j]->get_type() != EntityType::ENEMY) { continue; }
                if (check_collision(entities[i], entities[j]))
                {
                    entities[i]->deactivate();
                    entities[j]->deactivate();
                    break;
                }
            }
        }
    }
}


void Game::is_out_boundary()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::ENEMY) { continue; }
        sf::Vector2f pos = entities[i]->get_position();
        if (pos.x < 0 || pos.x > window_w || pos.y < 0 || pos.y > window_h) { entities[i]->deactivate(); }
    }
}

void Game::erase_entities()
{
    std::erase_if(entities, [&](Entity* entity)
        {
            if (!entity->is_activate())
            {
                delete entity; // ���� ��ü�� ����
                return true;   // ���Ϳ��� ����
            }
            return false;
        }
    );
}

void Game::spwan_enemy()
{
    static bool first_spwan = true;
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spwan)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy(this, EntityType::ENEMY, 3.0f, 350.0f);
            entities.push_back(enemy);
        }
        first_spwan = false;
        enemy_clock.restart();
    }
}


void Game::spwan_bullet()
{
    static bool first_spwan = true;
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spwan)
    {
        Bullet* bullet = new Bullet(this, EntityType::BULLET, 5.f, 550.f);
        entities.push_back(bullet);
        first_spwan = false;
        bullet_clock.restart();
    }
}


bool Game::initialize_game() 
{
    if (!ship_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png")) { return false; }
    if (!projectile_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png")) { return false; }
    if (!background_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png")) { return false; }

    initialize_entities();
    return true;
}


void Game::initialize_entities()
{
    Player* player = new Player(this, EntityType::PLAYER, 3.0f, 550.f);
    entities.push_back(player);
    this->player = player;

    spwan_enemy();
    spwan_bullet();
}

void Game::running_game()
{
    while (window.isOpen())
    {
        process_events();
        set_game();
        update_game();
    }
}

void Game::process_events()
{
    // Process events
    while (const std::optional event = window.pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::set_game()
{
    deltatime = clock.restart().asSeconds();
    player->move_by_mouse(window);

    spwan_enemy();
    spwan_bullet();
}

void Game::update_game()
{
    // 1. Clear screen
    window.clear();

    // 2. Draw and Move Entity 
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
        entities[i]->move(deltatime);
        entities[i]->make_bounding_box();
        entities[i]->make_skeleton(0.6);
    }

    //std::cout << "��ü ���� :" << entities.size() << std::endl;
    is_hit();// �ǰ� ����
    is_out_boundary(); // ȭ�� ���� ����
    erase_entities(); // false ��ü ����


    // 3. Display the window
    window.display();
}


void Game::terminate_game()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
}