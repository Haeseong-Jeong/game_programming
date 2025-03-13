#include "Game/Game.h"
#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include "Entity/Bullet.h"
#include "Entity/Player.h"
#include <iostream>

Game::Game(int window_w, int window_h)
    : player{ nullptr }, background{ nullptr }, deltatime{ 0 }, score{ 0 }, end_game{ false }
{
    window_size = sf::Vector2u(window_w, window_h);
    window = sf::RenderWindow{ sf::VideoMode(window_size), "Game play" },
    entities.clear();
    enemy_gen_num = 5;
}

Game::~Game()
{
}

sf::Window& Game::get_window() { return window; }
sf::Texture& Game::get_ship_texture() { return ship_texture; }
sf::Texture& Game::get_projectile_texture() { return projectile_texture; }

void Game::set_background()
{
    background = new sf::Sprite(background_texture);
    sf::Vector2f texture_size(256.f, 128.f);
    sf::IntRect crop_rect({ 257, 258 }, { 256, 128 });
    background->setTextureRect(crop_rect);
    sf::Vector2f scaleFactor(window_size.x / texture_size.x, window_size.y / texture_size.y);
    background->setScale(scaleFactor);
    background->setColor(sf::Color(255, 255, 255, 50));  // 4번째 인자가 투명도, 0 ~ 256 투명도 (0이 완전 투명)
}

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
                    score += 1;
                    break;
                }
            }
        }
    }
}

void Game::is_dead()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::PLAYER)
        {
            for (int j = 0; j < entities.size(); j++)
            {
                if (entities[j]->get_type() != EntityType::ENEMY) { continue; }
                if (check_collision(entities[i], entities[j]))
                {
                    end_game = true;
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
        if (pos.x < 0 || pos.x > window_size.x || pos.y < 0 || pos.y > window_size.y)
        { 
            if (entities[i]->get_type() == EntityType::PLAYER)
            {
                end_game = true;
                return;
            }
            entities[i]->deactivate(); 
        }
    }
}

void Game::erase_entities()
{
    std::erase_if(entities, [&](Entity* entity)
        {
            if (!entity->is_activate())
            {
                delete entity; // 먼저 객체를 삭제
                return true;   // 벡터에서 제거
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

    set_background();
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
    if (!end_game)
    {
        deltatime = clock.restart().asSeconds();
        player->move_by_mouse(window);

        spwan_enemy();
        spwan_bullet();
    }
}

void Game::update_game()
{
    // 1. Clear screen
    window.clear();
    window.draw(*background);

    // 2. Draw and Move Entity
    if (end_game)
    {
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->draw(window);
        }
        window.display();
        return;
    }

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
        entities[i]->move(deltatime);
        entities[i]->make_bounding_box();
        entities[i]->make_skeleton(0.6);
    }

    //std::cout << "객체 개수 :" << entities.size() << std::endl;
    is_dead();
    is_hit();// 피격 판정
    is_out_boundary(); // 화면 나감 판정
    erase_entities(); // false 객체 제거


    // 3. Display the window
    window.display();
}


void Game::terminate_game()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    delete background;
}