#include<iostream>
#include <SFML/Graphics.hpp>
#include<box2d/box2d.h>

#include "Maze.hh"
#include "Inputs.hh"
#include "Character.hh"
#include "Tile.hh"
#include "GameObject.hh"
#include "ContactListener.hh"
#include "Score.hh"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
#define FONT1 "assets/fonts/8-bit Arcade In.ttf"
#define ICON "assets/cheems.ico"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 5.0f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    sf::Image* iconImage{new sf::Image()};
    iconImage->loadFromFile(ICON);
    window->setIcon(64, 64, iconImage->getPixelsPtr());
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Score* score{new Score(FONT1, "Score ", 24, new sf::Vector2f(25, 5), new sf::Color(255, 255, 255), window)};
    

    //physics declaration
    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)}; 

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    //Game inputs
    Inputs* inputs{new Inputs()};
    //Textures
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);
    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};


    //Main player
    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), b2BodyType::b2_dynamicBody, world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );
    
    character1->SetTagName("player");
    //character1->SetDebug(true);

    unsigned int N{17}, M{30};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture3, "assets/mazes/maze1.txt", world)};
    Maze* maze2{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture3, "assets/mazes/maze2.txt", world)};
    Maze*& currentMaze{*&maze1};

    GameObject* treasure{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure->SetTagName("item");
    GameObject* treasure2{new GameObject(tilesTexture3, 16 * 19, 16 * 19, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(200, 400), b2BodyType::b2_staticBody, world, window)}; 
    treasure2->SetTagName("item");

    GameObject* stairs{new GameObject(tilesTexture3, 16 * 3, 16 * 6, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(510, 510), b2BodyType::b2_staticBody, world, window)};
    stairs->SetTagName("stairs");
    //stairs->SetDebug(true);

    std::vector<GameObject*>* items{new std::vector<GameObject*>()};
    items->push_back(treasure);
    items->push_back(treasure2);
    items->push_back(stairs);

    ContactListener* conctactListener{new ContactListener(score, items)};

    world->SetContactListener(conctactListener);

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        switch (conctactListener->GetSceneIndex())
        {
            case 0:
                currentMaze = maze1;
                break;
            case 1:
                currentMaze = maze2;
                break;
            default:
                currentMaze = maze1;
                break;
        }
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        if(sf::Joystick::isConnected(0))
        {
            character1->Move(new b2Vec2(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED));
            character1->FlipSpriteX(joystickAxis->x);

            if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }
        else
        {
            character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED));
            character1->FlipSpriteX(keyboardAxis->x);

            if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }

        window->clear(*(new sf::Color(150, 100, 0, 255)));//lipiar la pantalla

        for(auto& mazeTile : *currentMaze->GetContainer())
        {
            window->draw(*mazeTile->GetSprite());
        }

        //stairs->Update();
        
        for(auto& item : *items)
        {
            item->Update();
        }

        character1->Update();

        score->Update();

        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        world->ClearForces();
        world->Step(1.f / 100 * deltaTime, 8, 8);
        clock->restart();
        
        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}