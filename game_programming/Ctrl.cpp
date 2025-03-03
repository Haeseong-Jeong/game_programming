#include "Ctrl.h"

Ctrl::Ctrl(int window_w,int window_h) 
    : window_w{ window_w }, window_h{ window_h }, window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "Game play")
{}

void Ctrl::initialize_game(float player_speed, int enemy_gen_num)
{
    // define player
    player = Player(player_speed);  //default constructor method no use ()... ->  Player player;
    player.set_position(window);

    // define enemy
    this->enemy_gen_num = enemy_gen_num;
    for (int i = 0; i < enemy_gen_num; i++)
    {
        Enemy* enemy = new Enemy;
        enemy->set_position(window);
        enemy->calculate_direction(player.get_position());  //enemy not move.. so don't have distance and direction
        enemies.push_back(enemy);
    }

    for (int i = 0; i < enemy_gen_num; i++) // copy enemy
    {
        Enemy* enemy2 = new Enemy(*enemies[i]); //copy constructor, input the pointing data
        enemies.push_back(enemy2);
    }

    // defince bullet
    Bullet* bullet = new Bullet(player.get_position(), player.get_bullet_direction(enemies, enemies.size())); // input the beginning bullet
    bullets.push_back(bullet);
}

void Ctrl::running_game()
{
    while (window.isOpen()) // 1 -> 2 -> 3 loop
    {
        close_events();
        set_game();
        update_game();
    }
}

void Ctrl::set_game()
{
    deltatime = clock.restart().asSeconds();

    // press action
    player.move_by_key(deltatime);
    player.move_by_mouse(window);

    // judge enemy gen
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy{ sf::Vector2u(window_w, window_h), player.get_position() };
            enemies.push_back(enemy);
        }
        enemy_clock.restart();
    }

    // judge bullet shoot
    sf::Vector2f direction = player.get_bullet_direction(enemies, enemies.size());
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period)
    {
        Bullet* bullet = new Bullet(player.get_position(), direction);
        bullets.push_back(bullet);
        bullet_clock.restart();
    }
}

void Ctrl::update_game()
{
    // 1. Clear screen
    window.clear();

    // 2. Draw player, enemy, bullet
    window.draw(player.get_shape());

    for (int i = 0; i < enemies.size(); i++)
    {
        //enemies[i]->draw(window); // == (*enemies[i]).draw(window);
        window.draw(enemies[i]->get_shape());
        enemies[i]->move(player.get_position(), deltatime);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        //bullets[i]->draw(window);
        window.draw(bullets[i]->get_shape());
        bullets[i]->shoot(deltatime);
    }
    // bullet remove within boundary  *** rambda capture!! we have to use outter value (window_w). so, use [&] not []!!
    std::erase_if(bullets, [&](Bullet* bullet) { return bullet->get_position().x > window_w; });

    // 3. Display the window
    window.display();
}


void Ctrl::terminate_game()
{
    // delete new memory
    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
    for (int i = 0; i < bullets.size(); i++)
    {
        delete bullets[i];
    }
}

void Ctrl::close_events()
{
    // Process events
    while (const std::optional event = window.pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

sf::RenderWindow& Ctrl::get_window() { return window; }

