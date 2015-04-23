#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include "Main_Game.hpp"

void Settings_Menu();

int main()
{
    unsigned int pos = 0;
    int sizes[] = {235, 300, 250, 150};
    sf::RenderWindow window(sf::VideoMode(600,600), "SFML Works");
    window.setFramerateLimit(60);
    sf::Font font;
    sf::Text newGame("New Game", font, 30);
    sf::Text loadGame("Load Game", font,30);
    sf::Text settings("Settings", font, 30);
    sf::Text quit("Quit", font, 30);

    newGame.setPosition(200, 150);
    loadGame.setPosition(200, 250);
    settings.setPosition(200, 350);
    quit.setPosition(200, 450);

    sf::RectangleShape select(sf::Vector2f(300, 150));
    select.setPosition(200, 150);
    select.setSize(sf::Vector2f(235, 50));
    select.setFillColor(sf::Color(150, 50, 200));

    if (!font.loadFromFile("dlxfont.ttf"))
    {
        return 1;
    }
    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pos = abs((pos - 1) % 4);
            select.setPosition(200, (pos * 100 + 150));
            select.setSize(sf::Vector2f(sizes[pos], 50));
            usleep(100000);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pos = abs((pos + 1) % 4);
            select.setPosition(200, (pos * 100 + 150));
            select.setSize(sf::Vector2f(sizes[pos], 50));
            usleep(100000);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            usleep(100000);
            switch(pos)
            {
                case 0:
                    window.close();
                    Game_Main();
                    break;
                case 1:
                    std::cout << "Load Game";
                    break;
                case 2:
                    Settings_Menu();
                    break;
                case 3:
                    window.close();
                    break;
                default:
                    std::cout << "ERROR";
            }

        }
        window.clear();
        window.draw(select);
        window.draw(newGame);
        window.draw(loadGame);
        window.draw(settings);
        window.draw(quit);
        window.display();
    }
}
void Settings_Menu()
{
    sf::RenderWindow window(sf::VideoMode(600,600), "Settings");
    sf::Font font;
    sf::Text text("NO SETTINGS ENJOY OUR GAME THE WAY WE MADE IT!!!", font, 30);
    text.setPosition(0,300);
    if (!font.loadFromFile("dlxfont.ttf"))
    {
        window.close();
        std::cout << "ERROR loading game font" << std::endl;
    }
    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}

