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

    // Create a rectangle shape
    const int num_rect = 20;
    const float rect_w = 20.0f;
    const float rect_h = 20.0f;
    const float rect_dx = 0.1f;
    sf::RectangleShape rectangles[num_rect];


    for (int i = 0; i < num_rect; i++)
    {
        float randx = rand() % (int)(window_w - rect_w);
        float randy = rand() % (int)(window_h - rect_h);

        rectangles[i].setSize(sf::Vector2f(rect_w, rect_h));
        rectangles[i].setPosition({ randx,  randy });
        rectangles[i].setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
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

        // 1. Clear screen
        window.clear();

        // 2. Draw shape (move and regen)
        for (int i = 0; i < num_rect; i++)
        {
            sf::Vector2f position = rectangles[i].getPosition();
            if (position.x >= (window_w + rect_w))
            {
                rectangles[i].setPosition({ -rect_w, position.y});
            }
            rectangles[i].move({abs(rect_dx), 0.0f});
            window.draw(rectangles[i]);
        }

        // 3. Display the window
        window.display();
    }
}