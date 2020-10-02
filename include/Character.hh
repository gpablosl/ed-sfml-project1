#include <SFML/Graphics.hpp>
#include "Animation.hh"
#include "BoxCollider.hh"

class Character
{
    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float cropPosX;  
        float cropPosY;
        float cropWidth;
        float cropHeight;
        float scaleX;
        float scaleY;
        Animation** animations;
        BoxCollider* boxCollider;
        float tileBaseWidth;
        float tileBaseHeight;


        void InitSprite(b2World*&);

    public:
        Character(sf::Texture*&, float, float, float, float, float, float, b2World*&);
        ~Character();
        sf::Sprite* GetSprite();
        void FlipSpriteX(float);
        void SetAnimations(Animation**);
        Animation* GetAnimation(int) const;
        void Move(b2Vec2*);
        BoxCollider* GetCollider() const;
};
