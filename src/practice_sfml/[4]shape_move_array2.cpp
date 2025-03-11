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

    const float shape_size_min = 10.0f;
    const float shape_size_max = 20.0f;

    float randx[num_rect] = { 0.0f };
    float randy[num_rect] = { 0.0f };
    float randw[num_rect] = { 0.0f };
    float randh[num_rect] = { 0.0f };
    float rand_dx[num_rect] = { 0.0f };

    sf::Color colors[num_rect];

    for (int i = 0; i < num_rect; i++)
    {
        randw[i] = shape_size_min + static_cast<float>(std::rand()) / RAND_MAX * (shape_size_max - shape_size_min);
        randh[i] = shape_size_min + static_cast<float>(std::rand()) / RAND_MAX * (shape_size_max - shape_size_min);

        randx[i] = rand() % (int)(window_w - randw[i]);
        randy[i] = rand() % (int)(window_h - randh[i]);

        rand_dx[i] = (float)rand() / (float)RAND_MAX;

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


        // 2. Draw shape (move and regen)
        for (int i = 0; i < num_rect/2; i++)
        {
            rectangle.setSize(sf::Vector2f(randw[i], randh[i]));
            if (randx[i] >= (window_w + randw[i]))
            {
                rectangle.setPosition({ randx[i] = -randw[i],  randy[i]});
            }
            else
            {
                rectangle.setPosition({ randx[i] += rand_dx[i],  randy[i] });
            }
            rectangle.setFillColor(colors[i]);
            window.draw(rectangle);
        }


        // 2. Draw shape (move and retrun)
        for (int i = num_rect/2; i < num_rect; i++)
        {
            rectangle.setSize(sf::Vector2f(randw[i], randh[i]));
            if (randx[i] >= (window_w - randw[i]) || randx[i] < 0)
            {
                rand_dx[i] = -rand_dx[i];
            }
            rectangle.setPosition({ randx[i] += rand_dx[i],  randy[i] });
            rectangle.setFillColor(colors[i]);
            window.draw(rectangle);
        }

        // 3. Display the window
        window.display();
    }
}