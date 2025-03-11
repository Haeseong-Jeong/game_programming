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

int main()
{
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
    float enemy_xpos[num_enemy] = { 0.0f };
    float enemy_ypos[num_enemy] = { 0.0f };
    for (int i = 0; i < num_enemy; i++)
    {
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

            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            //    // left key is pressed: move our character
            //    rectangle.move({ -3.f, 0.f });
            //}
        }

        // key press
        move_player(player);

        // mouse press
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            player.setPosition({ (float)position.x - player_w / 2, (float)position.y - player_h / 2 });
            //player.setPosition({ (float)window_w / 2, (float)window_h / 2 });
        }

        // 1. Clear screen
        window.clear();

        // 2. Draw enemy and player
        window.draw(player);
        for (int i = 0; i < num_enemy; i++)
        {
            sf::CircleShape enemy;
            enemy.setRadius(enemy_radius);
            enemy.setPosition({ (float)window_w - 30, enemy_ypos[i] });
            enemy.setFillColor(sf::Color::Magenta);
            enemy.setOutlineColor(sf::Color::Red);
            enemy.setOutlineThickness(1.0f);
            window.draw(enemy);
        }

        // 3. Display the window
        window.display();
    }
}