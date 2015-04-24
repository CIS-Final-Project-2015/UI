#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include "AnimatedSprite.hpp"
#include "Main_Game.hpp"
#include <vector>
#include <string>

using namespace std;

string getInventory();

int Game_Main()
{
    enum direction {Down, Left, Right, Up};

    sf::Vector2i source(1, Down);
    vector<sf::Text> inventory;

    int invmenu = 0;
    int player_x = 0;
    int player_y = 0;
    int stopper = 100;

    sf::RenderWindow Window(sf::VideoMode(600, 600), "My window");
    Window.setFramerateLimit(401);

    sf::Texture pPlayer;
    sf::Texture myWorld;
    sf::Texture texture_bottomPanel;
    sf::Texture texture_sidePanel;

    pPlayer.loadFromFile("player.png");
    myWorld.loadFromFile("world.jpg");
    texture_bottomPanel.loadFromFile("wood.jpg");
    texture_sidePanel.loadFromFile("wood2.jpg");

    sf::Sprite player(pPlayer);
    sf::Sprite world(myWorld);
    sf::Sprite bottomPanel(texture_bottomPanel);
    sf::Sprite sidePanel(texture_sidePanel);

    player.setPosition(34,34);
    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));

    world.setPosition(0,0);

    bottomPanel.setPosition(1, 400);

    sidePanel.setPosition(430,0);
    sidePanel.scale(10,3.35);

    sf::Font font;
    if (!font.loadFromFile("dlxfont.ttf"))
    {
        return 1;
    }
    sf::Text itemText(getInventory(), font, 10);
    itemText.setPosition(sidePanel.getPosition());
    inventory.push_back(itemText);

    // Jason's stuff down here

    string inventory_string = getInventory();

    // End of Jason's stuff

    sf::Event event;
    while(Window.isOpen())
    {
        while(Window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                Window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::I)
                {
                    if (invmenu == 0)
                    {
                        sidePanel.setPosition(8000, 0);
                        bottomPanel.setPosition(1, 6000);
                        invmenu = 1;
                    }
                    else if (invmenu == 1)
                    {
                        bottomPanel.setPosition(1, 400);
                        sidePanel.setPosition(430, 0);
                        invmenu = 0;
                    }
                }
            }
        }
        if(event.type == sf::Event::KeyPressed)
        {

            if (event.key.code == sf::Keyboard::Left)
            {
                source.y = Left;
                stopper = 0;
                player_x = -1;
                player_y = 0;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                source.y = Right;
                stopper = 0;
                player_x = 1;
                player_y = 0;
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                source.y = Up;
                stopper = 0;
                player_x = 0;
                player_y = -1;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                source.y = Down;
                stopper = 0;
                player_x = 0;
                player_y = 1;
            }
        }
// Collision detection!
/*
        if (sprite.getGlobalBounds().intersects(sward.getGlobalBounds()))
        {
            int gridx = 10;
            int gridy = 405;
            sward.setPosition(gridx,gridy);
            gridx = gridx + 60;
            if (gridx == 430)
            {
                gridx = 10;
                gridy = gridy + 60;
            }
        }*/

        while (stopper < 100)
        {
            player.move(player_x, player_y);
            if (stopper % 20 == 0)
            {
                source.x++;
            }
            if (source.x * 32 >= pPlayer.getSize().x)
            {
                source.x = 0;
            }
            player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
            Window.draw(world);
            Window.draw(player);
            Window.draw(sidePanel);
            Window.draw(bottomPanel);
            for (int i = 0; i < inventory.size(); i++)
            {
                Window.draw(inventory[i]);
            }
            Window.display();
            Window.clear();
            stopper++;
        }

        Window.draw(world);
        Window.draw(player);
        Window.draw(sidePanel);
        Window.draw(bottomPanel);
        Window.display();
        Window.clear();
    }
    return 0;
}

string getInventory()
{
    string toReturn = "Elysian_Spirit_Shield RUne_Plate_Legs Rune_Plate_Body Rune_Plate_Helmet Dragon_Dagger Dragon_Long_Sword Dragon_Scimitar";

    return toReturn;
}
