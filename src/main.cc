#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"
#include "Character.hh"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 640
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 0.2f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    //inputs de juego
    Inputs* inputs{new Inputs()};
    //texturas
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);
    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};



    sf::Sprite* tileWall_1_1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 1, 16, 16)))};
    tileWall_1_1->setScale(SPRITE_SCALE, SPRITE_SCALE);

    sf::Sprite* tileWall_1_2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 2, 16, 16)))};
    tileWall_1_2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileWall_1_2->move(tileBaseWidth * 1, tileWall_1_2->getPosition().y);
    
    sf::Sprite* tileWall_1_3{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 3, 16, 16)))};
    tileWall_1_3->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileWall_1_3->move(tileBaseWidth * 2, tileWall_1_3->getPosition().y);



    sf::Sprite* tileGround_1_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 4, 16, 16)))};
    tileGround_1_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_4->move(tileWall_1_3->getPosition().y, tileBaseHeight);

    sf::Sprite* tileGround_2_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 4, 16, 16)))};
    tileGround_2_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_4->move(tileBaseWidth * 1, tileBaseHeight);

    sf::Sprite* tileGround_3_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 4, 16, 16)))};
    tileGround_3_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_4->move(tileBaseWidth * 2, tileBaseHeight);



    sf::Sprite* tileGround_1_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 5, 16, 16)))};
    tileGround_1_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_5->move(tileGround_1_5->getPosition().x, tileBaseHeight*2);

    sf::Sprite* tileGround_2_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 5, 16, 16)))};
    tileGround_2_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_5->move(tileBaseWidth * 1, tileBaseHeight*2);

    sf::Sprite* tileGround_3_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 5, 16, 16)))};
    tileGround_3_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_5->move(tileBaseWidth * 2, tileBaseHeight*2);



    sf::Sprite* tileGround_1_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 6, 16, 16)))};
    tileGround_1_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_6->move(tileGround_1_6->getPosition().x, tileBaseHeight*3);

    sf::Sprite* tileGround_2_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 6, 16, 16)))};
    tileGround_2_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_6->move(tileBaseWidth * 1, tileBaseHeight*3);

    sf::Sprite* tileGround_3_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 6, 16, 16)))};
    tileGround_3_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_6->move(tileBaseWidth * 2, tileBaseHeight*3);


    //w = tileWall_1_1  q = tileWall_1_2    e = tileWall_1_3
    //g = tileGround_1_4    f = tileGround_2_4  d =  tileGround_3_4
    char** tiles
    {
        new char*[10]
        {
            new char[12]{'w','q','w','e','w','w','w','e','w','q','w','w'},
            new char[12]{'g','f','g','d','g','g','f','d','g','g','g','f'},//2
            new char[12]{'g','g','g','d','g','g','g','d','g','g','g','g'},
            new char[12]{'g','f','y','d','g','g','f','d','t','y','g','f'},//4
            new char[12]{'g','g','t','d','g','g','f','f','f','g','g','f'},
            new char[12]{'y','g','g','d','g','g','y','g','g','g','g','d'},//6
            new char[12]{'g','g','y','g','g','g','g','g','g','g','g','f'},
            new char[12]{'f','f','g','t','f','g','g','d','g','g','g','g'},//8
            new char[12]{'g','g','g','d','f','g','f','g','g','g','g','f'},
            new char[12]{'g','f','g','d','g','g','g','t','g','g','g','u'},//10
        }
    };

    std::vector <sf::Sprite> maze;

    for(int i{}; i<10; i++)
    {
        for(int j{}; j<12; j++)
        {
            char& tile = *(*(tiles + i) + j);

            switch (tile)
            {
            case 'w':
            maze.push_back(*tileWall_1_1);
                break;
            case 'q':
            maze.push_back(*tileWall_1_2);
                break;
            case 'e':
            maze.push_back(*tileWall_1_3);
                break;

            case 'g':
            maze.push_back(*tileGround_1_4);
            break;
            case 'f':
            maze.push_back(*tileGround_2_4);
                break;
            case 'd':
            maze.push_back(*tileGround_3_4);
                break;
            case 't':
            maze.push_back(*tileGround_1_6);
                break;
            case 'y':
            maze.push_back(*tileGround_2_6);
                break;
            case 'u':
            maze.push_back(*tileGround_3_6);
                break;
            default:
                break;
            }
            maze.back().move(tileBaseWidth * j, tileBaseHeight * i);
        }
    }

    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, SPRITE_SCALE, SPRITE_SCALE)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );



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
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};
   

        if(sf::Joystick::isConnected(0))
        {
            character1->GetSprite()->move(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED);
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
            character1->GetSprite()->move(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED);
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

        //character1->GetAnimation(0)->Play(deltaTime);


        window->clear(*(new sf::Color(150, 100, 0, 255)));//lipiar la pantalla
        /*
        window->draw(*tileWall_1_1);
        window->draw(*tileWall_1_2);
        window->draw(*tileWall_1_3);

        window->draw(*tileGround_1_4);
        window->draw(*tileGround_2_4);
        window->draw(*tileGround_3_4);

        window->draw(*tileGround_1_5);
        window->draw(*tileGround_2_5);
        window->draw(*tileGround_3_5);

        window->draw(*tileGround_1_6);
        window->draw(*tileGround_2_6);
        window->draw(*tileGround_3_6);*/

        for(auto& mazeTile : maze)
        {
            window->draw(mazeTile);
        }

        window->draw(*character1->GetSprite());
        window->display(); //mostrar en pantalla lo que se va dibujar
        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        clock->restart();
        //std::cout << "delta time: " << deltaTime << std::endl;
        delete keyboardAxis;
        delete joystickAxis;
    }
    return 0;
}