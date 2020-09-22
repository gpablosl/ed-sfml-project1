#include "Animation.hh"

//constructor
Animation::Animation(unsigned short int startFrame, unsigned short int endFrame, sf::Sprite* sprite, float delay)
{
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->sprite = sprite;
    this->delay = delay;
    currentFrame = startFrame;
}

//destructor
Animation::~Animation(){}
void Animation::Play(float& deltaTime)
{
    timer += deltaTime;
    if(timer >= delay)
    {
        if(currentFrame + 1 > endFrame)
        {
            currentFrame = startFrame;
        }
        else
        {
            currentFrame++;
        }
        
        sprite->setTextureRect(*(new sf::IntRect( 
            sprite->getTextureRect().width * currentFrame, 
            sprite->getTextureRect().top,  
            sprite->getTextureRect().width,  
            sprite->getTextureRect().height)));
               
        timer = 0.f;
    }
}