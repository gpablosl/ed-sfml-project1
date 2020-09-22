#include "Character.hh"

Character::Character(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, float cropHeight, float scaleX, float scaleY)
{
    this->texture = texture;
    this->cropPosX = cropPosX;
    this->cropPosY = cropPosY;
    this->cropWidth = cropWidth;
    this->cropHeight = cropHeight;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    InitSprite();
}

void Character::InitSprite()
{
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(cropPosX, cropPosY, cropWidth, cropHeight)));
    sprite->setScale(*(new sf::Vector2f(scaleX, scaleY)));
}

sf::Sprite* Character::GetSprite() const
{
    return sprite;
}

void Character::FlipSpriteX(float x)
{
    if( x > 0)
    {
        sprite->setScale(scaleX, scaleY);
        sprite->setOrigin(0.f, 0.f);
    }
    if (x < 0)
    {
        sprite->setScale(-scaleX, scaleY);
        sprite->setOrigin(sprite->getGlobalBounds().width / scaleX, 0.f);
    }
}

void Character::SetAnimations(Animation** animations)
{
    this->animations = animations;
}

Animation* Character::GetAnimation(int index) const
{
    return *(animations + index);
}

Character::~Character(){}