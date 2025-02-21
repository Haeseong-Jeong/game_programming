/*
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Create the main window
    unsigned int window_w = 800;
    unsigned int window_h = 600;
    sf::RenderWindow window(sf::VideoMode({ window_w, window_h }), "SFML window");

    // Create a rectangle shape
    float rect_w = 50.0f;
    float rect_h = 10.0f;
    float rect_x = 0;
    float rect_dx = 0.2;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f( rect_w, rect_h ));
    rectangle.setFillColor(sf::Color::Red);

    sf::RectangleShape rectangle2;
    rectangle2.setSize(sf::Vector2f(rect_w, rect_h));
    rectangle2.setFillColor(sf::Color::Yellow);
    rectangle2.setPosition({ 0.0f, (float)window_h / 2 });

    // Create a circle shape
    float radius = 3.0f;
    float circle_y = 0;
    float circle_dy = 0.5;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Green);


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

        // move and regen rectagle2
        sf::Vector2f rect2_pos = rectangle2.getPosition();
        if (rect2_pos.x >= (window_w + rect_w)) {
            //rectangle2.setPosition({ 0.f, 0.f });
            rectangle2.setPosition({ -rect_w, (float)window_h/2 });
        }
        rectangle2.move({ abs(rect_dx), 0.0f});

        // move and return rectagle xx
        sf::Vector2f rect_pos = rectangle.getPosition();
        if (rect_pos.x >= (window_w - rect_w) || rect_pos.x < 0) {
            rect_dx = -rect_dx;
        }
        rectangle.move({ rect_dx, 0.0f });

        // move and return circle yy
        sf::Vector2f circle_pos = circle.getPosition();
        if (circle_pos.y >= (window_h - radius) || circle_pos.y < 0) {
            circle_dy = -circle_dy;
        }
        circle.move({ 0, circle_dy });


        // 1. Clear screen
        window.clear();

        // Draw the shape
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(circle);

        // 3. Display the window
        window.display();
    }
}
*/