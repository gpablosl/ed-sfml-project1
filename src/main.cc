#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define SPRITE_SCALE 4.f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Inputs* inputs{new Inputs()};

    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Sprite* sprite1{new sf::Sprite(*tilesTexture1, *(new sf::IntRect(16 * 0, 16 * 11, 16, 16)))};
    sprite1->setScale(*(new sf::Vector2f(SPRITE_SCALE, SPRITE_SCALE)));
    //sprite1->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);

    /*sf::RectangleShape* boxShape{new sf::RectangleShape(*(new sf::Vector2f(100, 100)))};
    boxShape->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);
    boxShape->setFillColor(sf::Color::Transparent);
    boxShape->setOutlineColor(sf::Color::Green);
    boxShape->setOutlineThickness(2.f);

    sf::CircleShape* pointShape{new sf::CircleShape(2.f)};
    pointShape->setPosition(boxShape->getPosition());
    pointShape->setFillColor(sf::Color::White);*/

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
        //std::cout << "keyboard axis x: " << keyboardAxis->x << " keyboard axis y: " << keyboardAxis->y << std::endl;
        //std::cout << "joystic axis x: " << joystickAxis->x << " joystic axis y: " << joystickAxis->y << std::endl;

        /*if(sf::Joystick::isConnected(0))
        {
            //sf::Vector2f* newPosition{new sf::Vector2f(joystickAxis->x, joystickAxis->y)};
            //boxShape->setPosition(boxShape->getPosition() + *newPosition);
            boxShape->move(joystickAxis->x, joystickAxis->y);
        }
        else
        {
            //sf::Vector2f* newPosition{new sf::Vector2f(keyboardAxis->x, keyboardAxis->y)};
            //boxShape->setPosition(boxShape->getPosition() + *newPosition);
            boxShape->move(keyboardAxis->x, keyboardAxis->y);
        }
        
        pointShape->setPosition(boxShape->getPosition());*/

        if(sf::Joystick::isConnected(0))
        {
            sprite1->move(joystickAxis->x, joystickAxis->y);
        }
        else
        {
            sprite1->move(keyboardAxis->x, keyboardAxis->y);
        }

        window->clear(sf::Color::Black);//lipiar la pantalla
        //window->draw(*boxShape); //agregar la caja a las cosas que se van a dibujar
        //window->draw(*pointShape);
        window->draw(*sprite1);
        window->display(); //mostrar en pantalla lo que se va dibujar

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}