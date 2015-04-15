#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include "AnimatedSprite.hpp"

int gridx = 10;
int gridy = 405;





int posx = 0;
int posy = 0;
int status = 1;
enum direction { Down, Left, Right, Up};
sf::Vector2i source(1, Down);
sf::Texture pPlayer;

int sourcex = 32, sourceY = Down;


int main()
{
    int b = 1;
    sf::Vector2i source(1, Down);
    int invmenu = 0;
    int slide = 400;
    int slide2 = 630;
    // create the window
    sf::RenderWindow Window(sf::VideoMode(600, 600), "My window");



    if (!pPlayer.loadFromFile("snfer.png"))
        std::cout << "error" << std::endl;
    sf::Texture myWorld;
    myWorld.loadFromFile("world.jpg");
    sf::Sprite mySprite3(myWorld);
    mySprite3.setPosition(0,0);
    sf::Texture myTexture;
    sf::Texture myTexture2;
    sf::Texture warrior;

    myTexture.loadFromFile("wood.jpg");
    myTexture2.loadFromFile("wood2.jpg");
    sf::Sprite sprite(pPlayer);

    sprite.setPosition(0,0);
    sf::Sprite mySprite(myTexture);
    sf::Sprite mySprite2(myTexture2);
    mySprite.setPosition(1, 400);
    mySprite2.setPosition(430,0);
    mySprite2.scale(4,4);


    sf::Texture sword;
    sword.loadFromFile("ongar.jpg");
    sf::Sprite sward(sword);
    sward.setPosition(120,30);

    sf::Event event;
    while(Window.isOpen())
    {
        while(Window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::I)
                {



                    if (invmenu == 0)
                    {
                        while (slide !=  600)
                        {
                            slide = slide + 1;
                            mySprite.setPosition(1, slide);
                        }

                        while (slide2 !=  800)
                        {
                            slide2++;
                            mySprite2.setPosition(slide2, 0);
                        }
                        invmenu = 1;
                     Window.draw(mySprite3);
                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
                     Window.display();
                     Window.clear();
                    }
                    else if (invmenu == 1)
                    {
                        while (slide !=  400)
                        {
                            slide = slide- 1;
                            mySprite.setPosition(1, slide);
                        }
                        while (slide2 !=  430)
                        {
                            slide2--;
                            mySprite2.setPosition(slide2, 0);
                        }
                        invmenu = 0;
                    }
                    Window.draw(mySprite3);
                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
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
                 while (stopper < 100){
                    sprite.move(-1,0);
                    if (stopper % 20 == 0)
                    source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                     sprite.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                     Window.draw(mySprite3);

                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
                     Window.draw(sward);
                     Window.display();
                     Window.clear();
                     stopper++;
                }
                        }
            if (event.key.code == sf::Keyboard::Right)
           {
                source.y = Right;
                 int stopper = 0;
                 while (stopper < 100){
                    sprite.move(1,0);
                    if (stopper % 20 == 0)
                    source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                     sprite.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                     Window.draw(mySprite3);
                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
                     Window.draw(sward);
                     Window.display();
                     Window.clear();
                     stopper++;
                }
                        }
            if (event.key.code == sf::Keyboard::Up)
                        {
                source.y = Up;
                 int stopper = 0;
                 while (stopper < 100){
                    sprite.move(0,-1);
                    if (stopper % 20 == 0)
                    source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                     sprite.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                     Window.draw(mySprite3);
                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
                     Window.draw(sward);
                     Window.display();
                     Window.clear();
                     stopper++;
                }
                        }


            if (event.key.code == sf::Keyboard::Down)
            {
                source.y = Down;
                 int stopper = 0;
                 while (stopper < 100){
                    sprite.move(0,1);
                    if (stopper % 20 == 0)
                    source.x++;
                    if(source.x * 32 >= pPlayer.getSize().x)
                        source.x = 0;

                     sprite.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));
                     Window.draw(mySprite3);
                     Window.draw(sprite);
                     Window.draw(mySprite2);
                     Window.draw(mySprite);
                     Window.draw(sward);
                     Window.display();
                     Window.clear();
                     stopper++;
                }


            }
        }
        if (sprite.getGlobalBounds().intersects(sward.getGlobalBounds()))
        {
            sward.setPosition(gridx,gridy);
            gridx = gridx + 60;
            if (gridx == 430){
                gridx = 10;

            gridy = gridy + 60;
            }
        }

        Window.draw(mySprite3);
        Window.draw(sprite);
        Window.draw(mySprite2);
        Window.draw(mySprite);
        if (invmenu == 0)
        {
            Window.draw(sward);
        }

        Window.display();
        Window.clear();



    }
}


