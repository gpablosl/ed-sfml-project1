#include<SFML/Graphics.hpp>

class Animation
{
    private:
        unsigned short int startFrame;
        unsigned short int endFrame;
        sf::Sprite* sprite;
        float delay;
        int currentFrame;
        float timer{};
    public:
        Animation(unsigned short int, unsigned short int, sf::Sprite*, float);
        ~Animation();
        void Play(float&);
};
