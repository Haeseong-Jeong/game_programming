/*
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main()
{
    // Create the main window
    unsigned int window_w = 800;
    unsigned int window_h = 600;
    sf::RenderWindow window(sf::VideoMode({ window_w, window_h }), "SFML window");

    // shape initial value
    const int num_rect = 20;

    float rect_w = 50.0f;
    float rect_h = 50.0f;
    float rect_dx = 0.1f;

    float randx[num_rect] = { 0.0f };
    float randy[num_rect] = { 0.0f };

    sf::Color colors[num_rect];

    for (int i = 0; i < num_rect; i++)
    {
        randx[i] = rand() % (int)(window_w - rect_w);
        randy[i] = rand() % (int)(window_h - rect_h);

        colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    }

    // define shape 
    sf::RectangleShape rectangle;

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

        // 1. Clear screen
        window.clear();

        for (int i = 0; i < num_rect; i++)
        {
            rectangle.setSize(sf::Vector2f(rect_w, rect_h));
            if (randx[i] >= (window_w + rect_w))
            {
                rectangle.setPosition({ randx[i] = -rect_w,  randy[i] });
            }
            else
            {
                rectangle.setPosition({ randx[i] += rect_dx,  randy[i] });
            }
            rectangle.setFillColor(colors[i]);
            window.draw(rectangle);
        }

        // 3. Display the window
        window.display();
    }
}
*/