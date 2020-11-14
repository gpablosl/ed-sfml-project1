#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hh"
#include "BoxCollider.hh"
#include "GameObject.hh"

class Character : public GameObject 
{
    private:
        
        Animation** animations;

        void InitSprite(b2World*&, b2Vec2*);

    public:
        Character(sf::Texture*&, float, float, float, float, float, float, b2Vec2*, b2BodyType, b2World*&, sf::RenderWindow*&);
        ~Character();
        void FlipSpriteX(float);
        void SetAnimations(Animation**);
        Animation* GetAnimation(int) const;
        void Move(b2Vec2*);
};
