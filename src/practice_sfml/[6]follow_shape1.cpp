#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <cmath>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const float player_speed = 1.0f;

void move_player(sf::Shape& shape)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.move({ -player_speed, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.move({ player_speed, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        shape.move({ 0.f, -player_speed });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        shape.move({ 0.f, player_speed });
    }
}

void move_enemy(int num_enemy, sf::Vector2f& player_pos, float* enemy_xpos, float* enemy_ypos, float enemy_speed)
{
    for (int i = 0; i < num_enemy; i++)
    {
        float enemy_to_player_x = player_pos.x - enemy_xpos[i]; //x vector
        float enemy_to_player_y = player_pos.y - enemy_ypos[i]; //y vector

        float distance = sqrt(enemy_to_player_x * enemy_to_player_x + enemy_to_player_y * enemy_to_player_y);

        enemy_xpos[i] = enemy_xpos[i] + enemy_to_player_x / distance * enemy_speed;
        enemy_ypos[i] = enemy_ypos[i] + enemy_to_player_y / distance * enemy_speed;
    }
}

int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create the main window
    unsigned int window_w = 800;
    unsigned int window_h = 600;
    sf::RenderWindow window(sf::VideoMode({ window_w, window_h }), "SFML window");

    // define player
    const float player_w = 20.f;
    const float player_h = 20.f;
    sf::RectangleShape player;
    player.setSize({ player_w, player_h });
    player.setPosition({ (float)window_w/2, (float)window_h/2 });
    player.setFillColor(sf::Color::Red);

    // define enemy
    const int num_enemy = 10;
    float enemy_speed = 0.1f;
    float enemy_radius = 10.0f;
    float* enemy_xpos = new float[num_enemy];
    float* enemy_ypos = new float[num_enemy];

    for (int i = 0; i < num_enemy; i++)
    {
        enemy_xpos[i] = window_w-100;
        enemy_ypos[i] = rand() % window_h;
    }

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

        // key press action
        move_player(player);

        // mouse press action
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            player.setPosition({ (float)position.x - player_w / 2, (float)position.y - player_h / 2 });
        }


        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player
        window.draw(player);
        for (int i = 0; i < num_enemy; i++)
        {
            sf::CircleShape enemy;
            enemy.setRadius(enemy_radius);
            enemy.setPosition({ enemy_xpos[i], enemy_ypos[i]});
            enemy.setFillColor(sf::Color::Magenta);
            enemy.setOutlineColor(sf::Color::Red);
            enemy.setOutlineThickness(1.0f);
            window.draw(enemy);
        }

        // enemy postion update
        sf::Vector2f player_pos = player.getPosition();
        move_enemy(num_enemy, player_pos, enemy_xpos, enemy_ypos, enemy_speed);

        // 3. Display the window
        window.display();
    }
    delete[] enemy_xpos;
    delete[] enemy_ypos;
}