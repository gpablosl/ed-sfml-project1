#include <SFML/Graphics.hpp>
#include "Animation.hh"

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


        void InitSprite();

    public:
        Character(sf::Texture*&, float, float, float, float, float, float);
        ~Character();
        sf::Sprite* GetSprite() const;
        void FlipSpriteX(float);
        void SetAnimations(Animation**);
        Animation* GetAnimation(int) const;
};
