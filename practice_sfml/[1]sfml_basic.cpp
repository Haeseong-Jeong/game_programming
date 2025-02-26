#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    // Load a sprite to display
    //const sf::Texture texture("../../../----.jpg");
    //sf::Sprite sprite(texture);


    // Create a graphical text to display
    const sf::Font font("../resources/font/arial.ttf");
    sf::Text text(font, "Hello SFML", 50);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

    // Create a shape
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({ 50, 50 });

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition({ 10, 20 });


    // Load a music to play
    //sf::Music music("nice_music.ogg");

    // Play the music
    //music.play();

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

        // 2. Draw
        //window.draw(sprite);

        // Draw the shape
        window.draw(circle);
        window.draw(rectangle);


        // Draw the string
        window.draw(text);

        // 3. Display the window
        window.display();
    }
}