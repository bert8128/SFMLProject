#include <iostream>
#include <SFML/Graphics.hpp>

std::string to_string_trunc(float value)
{
    return std::to_string(static_cast<int>(value));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 320), "SFML works!");

    sf::CircleShape disk(20.f);
    disk.setFillColor(sf::Color::Green);
    disk.setOrigin(20, 20);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Failed to load the font file.\n";
        return EXIT_FAILURE;
    }

    window.setFramerateLimit(60); // 60 fps

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setString("(000.0, 000.0)");
    float textWidth = text.getLocalBounds().width;
    float textHeight = text.getLocalBounds().height;
    text.setOrigin(textWidth / 2, textHeight / 2);

    float x = 50;
    float y = 150;
    float x_speed = 0.1f;
    float y_speed = 0.1f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        x += x_speed;
        y += y_speed;
        if (x < 0 + disk.getRadius() || window.getSize().x - disk.getRadius() < x)
            x_speed *= -1;

        if (y < 0 + disk.getRadius() || window.getSize().y - disk.getRadius() < y)
            y_speed *= -1;

        disk.setPosition(x, y);
        text.setPosition(x, y - disk.getRadius() - textHeight);
        text.setString("(" + to_string_trunc(x) + ", " + to_string_trunc(y) + ")");

        window.clear(sf::Color::White);
        window.draw(disk);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
