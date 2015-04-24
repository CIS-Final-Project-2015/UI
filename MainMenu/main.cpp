#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include "Main_Game.hpp"

void Settings_Menu();

int main()
{
    unsigned int pos = 0;
    int winSize = 600;
    int sizes[] = {250, 275, 250, 125};
    int positions[] = {(winSize / 2 - sizes[0] / 2), (winSize / 2 - sizes[1] / 2), (winSize / 2 - sizes[2] / 2), (winSize / 2 - sizes[3] / 2)};

    sf::RenderWindow window(sf::VideoMode(600,600), "SFML Works");
    window.setFramerateLimit(60);
    sf::Font font;
    sf::Text newGame("New Game", font, 30);
    sf::Text loadGame("Load Game", font,30);
    sf::Text settings("Settings", font, 30);
    sf::Text quit("Quit", font, 30);

    //centering the options
    newGame.setPosition(positions[0], 150);
    loadGame.setPosition(positions[1], 250);
    settings.setPosition(positions[2], 350);
    quit.setPosition(positions[3], 450);

    sf::RectangleShape select(sf::Vector2f(300, 150));
    select.setPosition((positions[0] - 10), 140);
    select.setSize(sf::Vector2f(250, 50));
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
        //highlights the selected option
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pos = abs((pos - 1) % 4);
            select.setPosition((positions[pos] - 10), (pos * 100 + 140));
            select.setSize(sf::Vector2f(sizes[pos], 50));
            usleep(150000);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pos = abs((pos + 1) % 4);
            select.setPosition((positions[pos] - 10), (pos * 100 + 140));
            select.setSize(sf::Vector2f(sizes[pos], 50));
            usleep(150000);
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
                    window.close();
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
    sf::Text text("   NO SETTINGS!!!", font, 30);
    sf::Text text2("   ENJOY OUR GAME \nTHE WAY WE MADE IT!!!", font, 30);
    text.setPosition(0,225);
    text2.setPosition(0,275);
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
        window.draw(text2);
        window.display();
    }
}

