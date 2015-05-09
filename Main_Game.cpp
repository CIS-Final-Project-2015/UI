#include <SFML/Graphics.hpp>
#include "Main_Game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>

using namespace std;

string getInventory();
string getPartyStats();
string getRooms();

int Game_Main()
{
    enum direction {Down, Left, Right, Up}; // down > left > right > up

    sf::Vector2i source(1, Down);

    vector<sf::Text> inventory; // used to crop out part of player sprite sheet

    bool invmenu = 0; // keeps track if pause is open or closed
    int player_x = 0;
    int player_y = 0;
    int stopper = 100; // used to iterate animation of character 100 pixels
    int player_loc = 0;
    int rooms[] = {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0};

    sf::RenderWindow Window(sf::VideoMode(1000, 1000), "Pathfinder Gaem");

    // get each map zone types for the 6x6 map
    ifstream file;
    file.open("world.txt");
    string info = "";
    string line = "";
    vector<int> map_ints;
    while (getline(file, line))
    {
        map_ints.push_back((line[0]) - 48); // add map zone type to map_ints...
    }
    file.close();

    Window.setFramerateLimit(401);

    sf::Texture pPlayer;
    sf::Texture texture_bottomPanel;
    sf::Texture texture_sidePanel;
    sf::Texture Urban;
    sf::Texture Aquatic;
    sf::Texture Marsh;
    sf::Texture Desert;
    sf::Texture Mountains;
    sf::Texture Hills;
    sf::Texture Forest;
    sf::Texture Plains;
    sf::Texture Dungeon;

    pPlayer.loadFromFile("./images/player.png");
    texture_bottomPanel.loadFromFile("./images/wood_bottom.png");
    texture_sidePanel.loadFromFile("./images/wood2.jpg");
    Urban.loadFromFile("./images/urban.png");
    Aquatic.loadFromFile("./images/aquatic.png");
    Marsh.loadFromFile("./images/marsh.png");
    Desert.loadFromFile("./images/desert.png");
    Mountains.loadFromFile("./images/mountains.png");
    Hills.loadFromFile("./images/hills.png");
    Forest.loadFromFile("./images/forest.png");
    Plains.loadFromFile("./images/plains.png");
    Dungeon.loadFromFile("./images/dungeon.png");

    sf::Sprite player(pPlayer);
    sf::Sprite bottomPanel(texture_bottomPanel);
    sf::Sprite sidePanel(texture_sidePanel);
    sf::Sprite urban(Urban);
    sf::Sprite aquatic(Aquatic);
    sf::Sprite marsh(Marsh);
    sf::Sprite desert(Desert);
    sf::Sprite mountains(Mountains);
    sf::Sprite hills(Hills);
    sf::Sprite forest(Forest);
    sf::Sprite plains(Plains);
    sf::Sprite dungeon(Dungeon);


    vector<sf::Sprite> map_sprites; // holds sprite images for map display

    int tile_x = 0; // Keeps track temporarily 
    int tile_y = 0; // of where to place map sprites into zones

    // Place sprites in correct place on map in a vector
    for(int i = 0; i < map_ints.size(); i++)
    {
        if (map_ints[i] == 1)
        {
            urban.setPosition(tile_x, tile_y);
            map_sprites.push_back(urban);
        }
        if (map_ints[i] == 2)
        {
            aquatic.setPosition(tile_x, tile_y);
            map_sprites.push_back(aquatic);
        }
        if (map_ints[i] == 3)
        {
            marsh.setPosition(tile_x, tile_y);
            map_sprites.push_back(marsh);
        }
        if (map_ints[i] == 4)
        {
            desert.setPosition(tile_x, tile_y);
            map_sprites.push_back(desert);
        }
        if (map_ints[i] == 5)
        {
            mountains.setPosition(tile_x, tile_y);
            map_sprites.push_back(mountains);
        }
        if (map_ints[i] == 6)
        {
            hills.setPosition(tile_x, tile_y);
            map_sprites.push_back(hills);
        }
        if (map_ints[i] == 7)
        {
            forest.setPosition(tile_x, tile_y);
            map_sprites.push_back(forest);
        }
        if (map_ints[i] == 8)
        {
            plains.setPosition(tile_x, tile_y);
            map_sprites.push_back(plains);
        }
        if (map_ints[i] == 9)
        {
            dungeon.setPosition(tile_x, tile_y);
            map_sprites.push_back(dungeon);
        }
	
	// iterate through each sector of the 600x600 pixel map
	// making sure that each 100x100 image is place correctly
        tile_x += 100;
        if (tile_x == 600)
        {
            tile_x = 0;
            tile_y = tile_y + 100;
        }

    }

    // set beginning player to postion in the middle of the first 100x100 square
    player.setPosition(34,34);
    player.setTextureRect(sf::IntRect(source.x *32, source.y * 32, 32, 32));

    // preset the positions of the pause menu.
    bottomPanel.setPosition(1, 400);
    bottomPanel.setScale(10,10);
    sidePanel.setPosition(330,0);
    sidePanel.scale(3,10);

    sf::Font font;
    if (!font.loadFromFile("dlxfont.ttf"))
    {
        return 1;
    }

    // set inventory text
    sf::Text itemText(getInventory(), font, 8);
    itemText.setPosition(sidePanel.getPosition());
    inventory.push_back(itemText);

    // Load and display Party Info
    sf::Text party;

    sf::Vector2f pan_pos = bottomPanel.getPosition();

    sf::Text partyStats(getPartyStats(), font, 8);
    partyStats.setPosition(pan_pos.x + 40, pan_pos.y + 125);

    sf::Texture texture_pikachu;
    texture_pikachu.loadFromFile("./images/pikachu_sprite.png");
    sf::Sprite pikachu(texture_pikachu);
    pikachu.setPosition(pan_pos.x + 25, pan_pos.y + 30);
    pikachu.scale(.8, .8);

    sf::Texture texture_bulbasaur;
    texture_bulbasaur.loadFromFile("./images/bulbasaur_sprite.png");
    sf::Sprite bulbasaur(texture_bulbasaur);
    bulbasaur.setPosition(pan_pos.x + 175, pan_pos.y +30);
    bulbasaur.scale(.8, .8);

    sf::Texture texture_squirtle;
    texture_squirtle.loadFromFile("./images/squirtle_sprite.png");
    sf::Sprite squirtle(texture_squirtle);
    squirtle.setPosition(pan_pos.x + 325, pan_pos.y+30);
    squirtle.scale(.8, .8);

    sf::Texture texture_charmander;
    texture_charmander.loadFromFile("./images/charmander_sprite.png");
    sf::Sprite charmander(texture_charmander);
    charmander.setPosition(pan_pos.x + 475, pan_pos.y+30);
    charmander.scale(.8, .8);


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
                        player_loc -= 1;
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
                        player_loc += 1;
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
                        player_loc -= 6;
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
                        player_loc += 6;
                    }
                }
            }
        }

        //Draws walking animation
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
            // draw world
            for(int i = 0; i < map_sprites.size(); i++)
            {
                Window.draw(map_sprites[i]);
            }
            Window.draw(player);
            Window.display();
            Window.clear();
            stopper++;
        }
        if (player_loc < 0)
        {
            player_loc = 0;
        }
        if (player_loc > 35)
        {
            player_loc = 35;
        }
        if (rooms[player_loc] == 0)
        {
            //keep normal map
            //cout << "0" << endl;
        }
        else if (rooms[player_loc] == 1)
        {
            //draw dungeon
            //cout << "1" << endl;
        }
        else if (rooms[player_loc] == 2)
        {
            //draw town
            //cout << "2" << endl;
        }
        // draw world
        for(int i = 0; i < map_sprites.size(); i++)
        {
            Window.draw(map_sprites[i]);
        }

        Window.draw(player);

        // Draw inventory when toggled
        if(invmenu == 1)
        {
            Window.draw(sidePanel);
            Window.draw(bottomPanel);
            Window.draw(itemText);
            Window.draw(pikachu);
            Window.draw(bulbasaur);
            Window.draw(charmander);
            Window.draw(squirtle);
            Window.draw(partyStats);
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
    return "Sword:\n\t12 dmg\n\t9 lbs\n\nChest_Plate:\n\tdex: 2\n\tarmor_rating: 3\n\tspell_resistance: 4\n";
}

string getRooms()
{
    return "0,0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,1,1,1,1,1";
}

string getPartyStats()
{
    return "health: 9\t\thealth: 10\t\thealth: 10\t\thealth: 9\nstuff: 9 \t\tstuff: 1  \t\tstuff: 1  \t\tstuff: 2";
}
