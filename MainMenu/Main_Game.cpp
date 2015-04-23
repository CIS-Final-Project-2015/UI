#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include "AnimatedSprite.hpp"
#include "Main_Game.hpp"

int Game_Main()
{
    enum direction {Down, Left, Right, Up};
    sf::Vector2i source(1, Down);
    int invmenu = 0;
    int x = 0;
    int y = 0;
    int stopper = 100;


    sf::RenderWindow Window(sf::VideoMode(600, 600), "My window");
    Window.setFramerateLimit(401);

    sf::Texture pPlayer;
    if (!pPlayer.loadFromFile("player.png")){
        std::cout << "error" << std::endl;
        return 1;
    }
    sf::Sprite player(pPlayer);
    player.setPosition(34,34);
    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));

    sf::Texture myWorld;
    myWorld.loadFromFile("world.jpg");
    sf::Sprite world(myWorld);
    world.setPosition(0,0);

    sf::Texture inventory1;
    sf::Texture inventory2;
    inventory1.loadFromFile("wood.jpg");
    inventory2.loadFromFile("wood2.jpg");
    sf::Sprite inventorySprite1(inventory1);
    sf::Sprite inventorySprite2(inventory2);
    inventorySprite1.setPosition(1, 400);
    inventorySprite2.setPosition(430,0);
    inventorySprite2.scale(4,4);

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
                        inventorySprite2.setPosition(8000, 0);
                        inventorySprite1.setPosition(1, 6000);
                        invmenu = 1;
                    }
                    else if (invmenu == 1)
                    {
                        inventorySprite1.setPosition(1, 400);
                        inventorySprite2.setPosition(430, 0);
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
                x = -1;
                y = 0;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                source.y = Right;
                stopper = 0;
                x = 1;
                y = 0;
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                source.y = Up;
                stopper = 0;
                x = 0;
                y = -1;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                source.y = Down;
                stopper = 0;
                x = 0;
                y = 1;
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
        }

*/

        while (stopper < 100)
        {
            player.move(x, y);
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
            Window.draw(inventorySprite2);
            Window.draw(inventorySprite1);
            Window.display();
            Window.clear();
            stopper++;
        }

        Window.draw(world);
        Window.draw(player);
        Window.draw(inventorySprite2);
        Window.draw(inventorySprite1);
        Window.display();
        Window.clear();
    }
    return 0;
}
