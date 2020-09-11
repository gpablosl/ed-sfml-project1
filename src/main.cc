#include<iostream>
#include <SFML/Graphics.hpp>
#include <Inputs.hh>
#define WINDOW_WIDHT 800
#define WINDOW_HEIGHT 600
#define GAME_NAME  "Roguelike game"

int main()
{

    //la ventana de tu grafico
    sf::Window* window = new sf::Window(sf::VideoMode(800,600), "Roguelike game");

    //aqui se guardan los eventos dentro de la ventana; ej: teclado, mouse, etc
    sf::Event event;

    Inputs* inputs = new Inputs();

    //loop principal, mientras la ventana este abierta, esto se va a ejecutar
     while(window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va a repetir; ej: teclado, joystick, mouse, etc
       while (window->pollEvent(event))
       {
           //esto es para cerrar la ventata; el evento fue cerrar la ventana, y termina la aplicación
           if(event.type==sf::Event::Closed)
           {
               window->close();
           }
           //los eventos son para botones y cosas que tienen que ocurrir
       }

        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        std::cout<< "Keyboard x: " << keyboardAxis->x << "Keyboard axis y: " << keyboardAxis->y << std::endl;  
        //inputs->GetJoystickAxis();

        delete keyboardAxis;
    }


    return 0;
}