//class es para cosas provadas

//struct es para cosas que va a ser publicas

#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.hh"

struct Inputs
{
    float x{};
    float y{};

    Vec2* keyboardAxis;
    Vec2* joystickAxis;

    //Constructor
    Inputs(); 

    Vec2* GetKeyboardAxis();
    Vec2* GetJoystickAxis();
};
