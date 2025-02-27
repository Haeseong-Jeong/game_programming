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
    Player player;  //default constructor method. no use ()....
    player.set_position(window);


    // define enemy
    int enemy_num = 5;
    Enemy* enemies = new Enemy[enemy_num];
    for (int i = 0; i < enemy_num; i++) { enemies[i].set_position(window); }
    // enemy copy
    Enemy* enemies2 = new Enemy[enemy_num];
    for (int i = 0; i < enemy_num; i++) { enemies2[i] = enemies[i]; }  // copy operator!! 


    //defince bullet
    Bullet bullet;
    bullet.set_position(&player);
    //bullet.shoot();
    //bullet.draw(window);


    // Start the game loop
    while (window.isOpen()) // 1 -> 2 -> 3 loop
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // press action
        player.move_by_key();
        player.move_by_mouse(window);

        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player

        //Bullet bullet;
        //bullet.set_position(&player);
        bullet.draw(window);
        bullet.shoot();

        player.draw(window);

        for (int i = 0; i < enemy_num; i++)
        {
            enemies[i].draw(window);
            enemies[i].move(player.get_position(), enemies[i], enemy_num, enemies[i].get_speed());
            //enemies2[i].draw(window);
            //enemies2[i].move(player.get_position(), enemies2[i], enemy_num, enemies2[i].get_speed());
        }

        // 3. Display the window
        window.display();
    }
    delete[] enemies;
    delete[] enemies2;
}