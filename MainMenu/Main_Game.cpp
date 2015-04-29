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

    bool invmenu = 0;
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

    sidePanel.setPosition(330,0);
    sidePanel.scale(3,10);

    sf::Font font;
    if (!font.loadFromFile("dlxfont.ttf"))
    {
        return 1;
    }

    sf::Text itemText(getInventory(), font, 8);
    itemText.setPosition(sidePanel.getPosition());
    inventory.push_back(itemText);

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
                    invmenu = !invmenu;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (invmenu == 0)
                    {
                        source.y = Left;
                        stopper = 0;
                        player_x = -1;
                        player_y = 0;
                    }
                    else
                    {
                        cout << "Success";
                    }
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    if (invmenu == 0)
                    {
                        source.y = Right;
                        stopper = 0;
                        player_x = 1;
                        player_y = 0;
                    }
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    if (invmenu == 0)
                    {
                        source.y = Up;
                        stopper = 0;
                        player_x = 0;
                        player_y = -1;
                    }
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    if (invmenu == 0)
                    {
                        source.y = Down;
                        stopper = 0;
                        player_x = 0;
                        player_y = 1;
                    }
                }
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
            Window.display();
            Window.clear();
            stopper++;
        }
        Window.draw(world);
        Window.draw(player);
        if(invmenu == 1)
        {
            Window.draw(sidePanel);
            Window.draw(bottomPanel);
            Window.draw(itemText);
        }
        Window.display();
        Window.clear();
    }
    return 0;
}

string getInventory()
{
    //Weapons: item_name damge_range weight
    //armor: item_name dexBonus armrPen spellRes
    //consumables: item_name weight
    //other: item_name weight
    string someString = "";
    string toReturn = "Sword:\n\t12dmg\n\t9lbs\n\nChest_Plate:\n\tdex:2\n\tarmor_rating: 3\n\tspell_resistance:4\n";
    /*for (int i = 0; i < toReturn.size(); i++)
    {
        if(toReturn[i] == " ")

    }*/
    return toReturn;
}
