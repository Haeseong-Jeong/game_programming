#include "Ctrl.h"

Ctrl::Ctrl(int window_w,int window_h) 
    : window_w{ window_w }, window_h{ window_h }, window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "Game play"), player{nullptr}
{
    enemies.clear();
    bullets.clear();

    enemy_gen_num = 5;
}

sf::Vector2f Ctrl::get_bullet_direction()
{
    int min_idx = 0;
    float min_distance = enemies[0]->get_distance();

    for (int i = 1; i < enemies.size(); i++)
    {
        float tmp = enemies[i]->get_distance();
        if (tmp < min_distance)
        {
            min_idx = i;
        }
    }
    return -enemies[min_idx]->get_direction();
}

sf::Texture& Ctrl::get_ship_texture() { return ship_texture; }
sf::Texture& Ctrl::get_projectile_texture() { return projectile_texture; }
sf::Window& Ctrl::get_window() { return window; }
Player* Ctrl::get_player_ptr() { return player; }


bool Ctrl::initialize_game() 
{
    if (!ship_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png")) { return false; }
    if (!projectile_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png")) { return false; }
    initialize_objects();
    return true;
}


void Ctrl::initialize_objects()
{
    // define player
    Player* player = new Player(this, 3.0f, 550.f);
    objects.push_back(player);
    this->player = player;


    // define enemy
    for (int i = 0; i < enemy_gen_num; i++)
    {
        Enemy* enemy = new Enemy(this, 3.0f, 350.0f);
        enemy->coordinate_direction();
        enemies.push_back(enemy);
        objects.push_back(enemy);
    }

    // defince bullet
    Bullet* bullet = new Bullet(this, 5.f, 550.f); // input the beginning bullet
    objects.push_back(bullet);
    bullets.push_back(bullet);
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

    // judge enemy gen
    //if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period)
    //{
    //    for (int i = 0; i < enemy_gen_num; i++)
    //    {
    //        Enemy* enemy = new Enemy(this, 3.0f, 350.0f);
    //        enemies.push_back(enemy);
    //    }
    //    enemy_clock.restart();
    //}

    // judge bullet shoot
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period)
    {
        Bullet* bullet = new Bullet(this, 5.f, 550.f);
        objects.push_back(bullet);
        bullets.push_back(bullet);
        bullet_clock.restart();
    }
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
    }

    // bullet remove within boundary  *** rambda capture!! we have to use outter value (window_w). so, use [&] not []!!
    std::erase_if(bullets, [&](Bullet* bullet) { return bullet->get_position().x > window_w; });

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