#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <cmath>
#include <random>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <SFML/Audio.hpp>
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
    int enemy_num = 10;
    Enemy* enemies = new Enemy[enemy_num];
    for (int i = 0; i < enemy_num; i++) { enemies[i].set_position(window); }

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
        player.move_player_by_key();
        player.move_player_by_mouse(window);

        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player
        player.draw_player(window);

        for (int i = 0; i < enemy_num; i++)
        {
            enemies[i].draw_enemy(window);
            enemies[i].move_enemy(player.get_position(), enemies[i], enemy_num, enemies[i].get_speed());
        }

        // 3. Display the window
        window.display();
    }
    delete[] enemies;
}