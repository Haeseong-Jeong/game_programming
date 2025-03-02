#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    // Create the main window
    int window_w = 1200;
    int window_h = 800;
    sf::RenderWindow window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "SFML window");


    // define player
    Player player(550.0f);  //default constructor method no use ()... ->  Player player;
    player.set_position(window);


    // define enemy
    int enemy_num = 5;
    std::vector<Enemy*> enemies;
    for (int i = 0; i < enemy_num; i++)
    {
        //Enemy* enemy = new Enemy{ sf::Vector2u(window_w, window_h), player.get_position() };
        //enemies.push_back(enemy);
        Enemy* enemy = new Enemy;
        enemy->set_position(window);
        enemies.push_back(enemy);
    }

    //for (int i = 0; i < enemy_num; i++) // copy enemy
    //{
    //    Enemy* enemy2 = new Enemy(*enemies[i]); //copy constructor, input the pointing data
    //    enemies.push_back(enemy2);
    //}


    // defince bullet
    std::vector<Bullet*> bullets;
    
    //enemy not move.. so don't have distance and direction
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->calculate_direction(player.get_position());
    }

    Bullet* bullet = new Bullet(player.get_position(), player.get_bullet_direction(enemies, enemies.size())); // input the beginning bullet
    bullets.push_back(bullet); 


    // Start the game loop
    sf::Clock clock;
    sf::Clock enemy_clock;
    sf::Clock bullet_clock;

    float enemy_period = 5.0f;
    float shoot_period = 1.0f;

    while (window.isOpen()) // 1 -> 2 -> 3 loop
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltatime = clock.restart().asSeconds();

        // press action
        player.move_by_key(deltatime);
        player.move_by_mouse(window);

        // judge enemy gen
        if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period)
        {
            for (int i = 0; i < enemy_num; i++)
            {
                Enemy* enemy = new Enemy{ sf::Vector2u(window_w, window_h), player.get_position() };
                enemies.push_back(enemy);
            }
            enemy_clock.restart();
        }


        sf::Vector2f direction = player.get_bullet_direction(enemies, enemies.size());
        // judge bullet shoot
        if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period)
        {
            Bullet* bullet = new Bullet(player.get_position(), direction);
            bullets.push_back(bullet);
            bullet_clock.restart();
        }

        // 1. Clear screen
        window.clear();

        // 2. Draw player, enemy, bullet
        player.draw(window);

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->draw(window); // == (*enemies[i]).draw(window);
            enemies[i]->move(player.get_position(), deltatime);
        }

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i]->draw(window);
            bullets[i]->shoot(deltatime);
        }
        //std::cout << "총알 지우기 전" << bullets.size() << std::endl;

        // bullet remove within boundary
        // rambda capture!! we have to use outter value (window_w). so, use [&] not []!!
        std::erase_if(bullets, [&](Bullet* bullet) { return bullet->get_position().x > window_w; });
        //std::cout << "총알 지우기 후" << bullets.size() << std::endl;


        // 3. Display the window
        window.display();
    }

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