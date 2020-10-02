#include "Character.hh"

Character::Character(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, 
float cropHeight, float scaleX, float scaleY, b2World*& world)
{
    this->texture = texture;
    this->cropPosX = cropPosX;
    this->cropPosY = cropPosY;
    this->cropWidth = cropWidth;
    this->cropHeight = cropHeight;
    this->scaleX = scaleX;
    this->scaleY = scaleY;

    tileBaseWidth = cropWidth * scaleX;
    tileBaseHeight = cropHeight * scaleY;

    InitSprite(world);
}

void Character::InitSprite(b2World*& world)
{
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(cropPosX, cropPosY, cropWidth, cropHeight)));
    sprite->setScale(*(new sf::Vector2f(scaleX, scaleY)));

    boxCollider = new BoxCollider(sprite->getPosition().x, sprite->getPosition().y, new sf::Color(0, 255, 0, 255), cropWidth, cropHeight,
    new Rigidbody(world, b2BodyType::b2_dynamicBody, new b2Vec2(sprite->getPosition().x, sprite->getPosition().y), tileBaseWidth / 2, tileBaseHeight / 2, 1, 0, 0),
    sprite);
    boxCollider->GetBoxShape()->setScale(scaleX, scaleY);
}

void Character::Move(b2Vec2* direction)
{
    boxCollider->Move(direction);
}

sf::Sprite* Character::GetSprite() 
{
    boxCollider->UpdatePhysics();
    return sprite;
}

BoxCollider* Character::GetCollider() const
{
    return boxCollider;
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