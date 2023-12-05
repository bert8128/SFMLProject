#include <iostream>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>

std::string to_string_trunc(float value)
{
    return std::to_string(static_cast<int>(value));
}

int main()
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()) };

    constexpr auto ww = 480;
    constexpr auto wh = 320;
    sf::RenderWindow window(sf::VideoMode(ww, wh), "SFML works!");

    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(20, 20);

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
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setString("(0, 0)");
    float textWidth = text.getLocalBounds().width;
    float textHeight = text.getLocalBounds().height;
    text.setOrigin(textWidth / 2, textHeight / 2);

    float x = static_cast<float>(mt() % ww);
    float y = static_cast<float>(mt() % wh);
    float x_speed = 0.2789124f;
    float y_speed = 0.1923643f;

    while (window.isOpen())
    {
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }

        x += x_speed;
        y += y_speed;

        if (x < 0 + ball.getRadius() || window.getSize().x - ball.getRadius() < x)
            x_speed *= -1;
        if (y < 0 + ball.getRadius() || window.getSize().y - ball.getRadius() < y)
            y_speed *= -1;

        ball.setPosition(x, y);
        text.setPosition(x, y + ball.getRadius() + textHeight);
        text.setString("(" + to_string_trunc(x) + ", " + to_string_trunc(y) + ")");

        window.clear(sf::Color::White);
        window.draw(ball);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
