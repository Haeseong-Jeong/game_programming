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
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const float player_speed = 0.5f;

void move_player_by_key(sf::Shape& shape)
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

void move_player_by_mouse(sf::Shape& shape, sf::Window& window, float player_w, float player_h)
{
    // mouse press
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        shape.setPosition({ (float)position.x - player_w / 2, (float)position.y - player_h / 2 });
    }
}

void move_enemy(sf::Shape& player, sf::Shape& enemy, int num_enemy, float enemy_speed)
{
    sf::Vector2f player_position = player.getPosition();
    sf::Vector2f enemy_position = enemy.getPosition();

    for (int i = 0; i < num_enemy; i++)
    {
        float enemy_to_player_x = player_position.x - enemy_position.x;
        float enemy_to_player_y = player_position.y - enemy_position.y;

        float distance = sqrt(enemy_to_player_x * enemy_to_player_x + enemy_to_player_y * enemy_to_player_y);

        //enemy.setPosition({ enemy_position.x - enemy_to_player_x / distance * enemy_speed, enemy_position.y - enemy_to_player_y / distance * enemy_speed });
        enemy.move({ enemy_to_player_x / distance * enemy_speed, enemy_to_player_y / distance * enemy_speed });
    }
}


int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> random_speed(0.01f, 0.05f);

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
    float enemy_radius = 10.0f;
    float* enemy_speed = new float[num_enemy];
    sf::CircleShape* enemy = new sf::CircleShape[num_enemy];

    for (int i = 0; i < num_enemy; i++)
    {
        enemy_speed[i] = random_speed(gen);
        float enemy_x = window_w - 100;
        float enemy_y = rand() % window_h;
        enemy[i].setPosition({ enemy_x , enemy_y });
        enemy[i].setRadius(enemy_radius);
        enemy[i].setFillColor(sf::Color::Magenta);
        enemy[i].setOutlineColor(sf::Color::Red);
        enemy[i].setOutlineThickness(1.0f);
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

        // press action
        move_player_by_key(player);
        move_player_by_mouse(player, window, player_w, player_h);

        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player
        window.draw(player);
        for (int i = 0; i < num_enemy; i++)
        {
            move_enemy(player, enemy[i], num_enemy, enemy_speed[i]);
            window.draw(enemy[i]);
        }

        // 3. Display the window
        window.display();
    }
    delete[] enemy;
}