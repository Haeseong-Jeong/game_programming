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
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    // Create the main window
    int window_w = 800;
    int window_h = 600;
    sf::RenderWindow window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "SFML window");


    // define player
    Player player(550.0f);  //default constructor method no use ()... ->  Player player;
    player.set_position(window);


    // define enemy
    int enemy_num = 5;
    Enemy* enemies = new Enemy[enemy_num];
    for (int i = 0; i < enemy_num; i++) { enemies[i].set_position(window); }
    // enemy copy
    Enemy* enemies2 = new Enemy[enemy_num];
    for (int i = 0; i < enemy_num; i++) { enemies2[i] = enemies[i]; }  // copy operator!! 


    //defince bullet
    int bullet_num = enemy_num * 2;
    Bullet* bullets = new Bullet[bullet_num];
    bullets[0].shoot_flag = true;
    bullets[0].set_position(player.get_position());


    // Start the game loop
    sf::Clock clock;
    sf::Clock bullet_clock;
    float fire_rate = 1.0f;
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

        // bullet shoot or pass
        for (int i = 0; i < bullet_num; i++)
        {
            //float bullet_time = bullet_clock.getElapsedTime().asSeconds();
            if ( (bullet_clock.getElapsedTime().asSeconds() >= fire_rate) && (bullets[i].shoot_flag == false) )
            {
                bullets[i].shoot_flag = true;
                bullets[i].set_position(player.get_position());
                bullet_clock.restart();
                break;
            }
        }


        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player
        player.draw(window);

        for (int i = 0; i < enemy_num; i++)
        {
            enemies[i].draw(window);
            //enemies2[i].draw(window);
            //enemies[i].move(player.get_position(), enemies[i], enemy_num, enemies[i].get_speed(), deltatime);
            //enemies2[i].move(player.get_position(), enemies2[i], enemy_num, enemies2[i].get_speed());
        }


        for (int i = 0; i < bullet_num; i++)
        {
            if (bullets[i].shoot_flag == true)
            {
                bullets[i].draw(window);
            }
        }

        // bullet move
        for (int i = 0; i < bullet_num; i++)
        {
            if (bullets[i].shoot_flag == true)
            {
                bullets[i].shoot(deltatime);
            }
        }

        // bullet remove within boundary
        for (int i = 0; i < bullet_num; i++)
        {
            if (bullets[i].get_position().x > window_w)
            {
                bullets[i].shoot_flag = false;
            }
        }


        for (int i = 0; i < enemy_num; i++)
        {
            enemies[i].move(player.get_position(), enemies[i], enemy_num, enemies[i].get_speed(), deltatime);
            //enemies2[i].move(player.get_position(), enemies2[i], enemy_num, enemies2[i].get_speed());
        }




        // 3. Display the window
        window.display();
    }
    delete[] enemies;
    delete[] enemies2;
    delete[] bullets;
}