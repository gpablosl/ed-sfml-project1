#include "GameObject.hh"

GameObject::GameObject(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, 
float cropHeight, float scaleX, float scaleY, b2Vec2* position, b2BodyType bodyType,b2World*& world, sf::RenderWindow*& window)
{
    this->texture = texture;
    this->cropPosX = cropPosX;
    this->cropPosY = cropPosY;
    this->cropWidth = cropWidth;
    this->cropHeight = cropHeight;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->window = window;

    tileBaseWidth = cropWidth * scaleX;
    tileBaseHeight = cropHeight * scaleY;

    InitSprite(world, position, bodyType);
}

GameObject::~GameObject()
{
    //delete sprite;
    boxCollider->~BoxCollider();
    /*delete sprite;
    delete this;*/
}

void GameObject::InitSprite(b2World*& world, b2Vec2* position, b2BodyType bodyType)
{
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(cropPosX, cropPosY, cropWidth, cropHeight)));
    sprite->setScale(*(new sf::Vector2f(scaleX, scaleY)));

    Rigidbody* rb{new Rigidbody(world, bodyType, position, tileBaseWidth / 2, tileBaseHeight / 2, 1, 0, 0)};
    rb->SetUserData((void*) this);
    boxCollider = new BoxCollider(position->x, position->y, new sf::Color(0, 255, 0, 255), cropWidth, cropHeight, rb, sprite);
    boxCollider->GetBoxShape()->setScale(scaleX, scaleY);
}

sf::Sprite* GameObject::GetSprite() 
{
    return sprite;
}

void GameObject::SetPosition(float posX, float posY)
{
    sprite->setPosition(posX, posY);
}

void GameObject::Update()
{
    boxCollider->UpdatePhysics();
    window->draw(*sprite);
    if(debug) window->draw(*boxCollider->GetBoxShape());
}

BoxCollider* GameObject::GetCollider() const
{
    return boxCollider;
}

const char* GameObject::GetTagName() const
{
    return tagName;
}

void GameObject::SetTagName(const char* tagName)
{
    this->tagName = tagName;
}

bool GameObject::GetDebug() const
{
    return debug;
}

void GameObject::SetDebug(bool debug)
{
    this->debug = debug;
}