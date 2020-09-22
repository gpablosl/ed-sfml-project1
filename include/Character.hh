#include <SFML/Graphics.hpp>

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

        void InitSprite();

    public:
        Character(sf::Texture*&, float, float, float, float, float, float);
        ~Character();
        sf::Sprite* GetSprite() const;
        void FlipSpriteX(float);
};
