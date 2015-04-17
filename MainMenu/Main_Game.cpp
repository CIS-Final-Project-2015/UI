#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include "AnimatedSprite.hpp"
#include "Main_Game.hpp"

int gridx = 10;
int gridy = 405;
int posx = 0;
int posy = 0;
int status = 1;
enum direction { Down, Left, Right, Up};
sf::Vector2i source(1, Down);
sf::Texture pPlayer;

int sourcex = 32, sourceY = Down;

void Game_Main()
{
    int b = 1;
    sf::Vector2i source(1, Down);
    int invmenu = 0;
    // create the window
    sf::RenderWindow Window(sf::VideoMode(600, 600), "My window");

    Window.setFramerateLimit(401);

    if (!pPlayer.loadFromFile("player.png")){
        std::cout << "error" << std::endl;
    }
    sf::Sprite player(pPlayer);
    player.setPosition(0,0);

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
                        inventorySprite2.setPosition(800, 0);
                        inventorySprite1.setPosition(1, 600);
                        invmenu = 1;
                        Window.draw(world);
                        Window.draw(player);
                        Window.draw(inventorySprite2);
                        Window.draw(inventorySprite1);
                        Window.display();
                        Window.clear();
                    }
                    else if (invmenu == 1)
                    {
                        inventorySprite1.setPosition(1, 400);
                        inventorySprite2.setPosition(430, 0);
                        invmenu = 0;
                    }
                    Window.draw(world);
                    Window.draw(player);
                    Window.draw(inventorySprite2);
                    Window.draw(inventorySprite1);
                    Window.display();
                    Window.clear();
                }
            }
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                source.y = Left;
                int stopper = 0;
                while (stopper < 100)
                {
                    player.move(-1,0);
                    if (stopper % 20 == 0)
                        source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                    Window.draw(world);
                    Window.draw(player);
                    Window.draw(inventorySprite2);
                    Window.draw(inventorySprite1);
                    Window.display();
                    Window.clear();
                    stopper++;
                }
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                source.y = Right;
                int stopper = 0;
                while (stopper < 100)
                {
                    player.move(1,0);
                    if (stopper % 20 == 0)
                        source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                    Window.draw(world);
                    Window.draw(player);
                    Window.draw(inventorySprite2);
                    Window.draw(inventorySprite1);
                    Window.display();
                    Window.clear();
                    stopper++;
                }
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                source.y = Up;
                int stopper = 0;
                while (stopper < 100)
                {
                    player.move(0,-1);
                    if (stopper % 20 == 0)
                        source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                    Window.draw(world);
                    Window.draw(player);
                    Window.draw(inventorySprite2);
                    Window.draw(inventorySprite1);
                    Window.display();
                    Window.clear();
                    stopper++;
                }
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                source.y = Down;
                int stopper = 0;
                while (stopper < 100)
                {
                    player.move(0,1);
                    if (stopper % 20 == 0)
                        source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                    Window.draw(world);
                    Window.draw(player);
                    Window.draw(inventorySprite2);
                    Window.draw(inventorySprite1);
                    Window.display();
                    Window.clear();
                    stopper++;
                }
            }
        }
 //       if (sprite.getGlobalBounds().intersects(sward.getGlobalBounds()))
 //       {
 //           sward.setPosition(gridx,gridy);
 //           gridx = gridx + 60;
 //           if (gridx == 430)
 //           {
 //               gridx = 10;
 //               gridy = gridy + 60;
 //           }
 //       }
        Window.draw(world);
        Window.draw(player);
        Window.draw(inventorySprite2);
        Window.draw(inventorySprite1);
        Window.display();
        Window.clear();
    }
}
