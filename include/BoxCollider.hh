#include<SFML/Graphics.hpp>

class BoxCollider
{
    private:
        sf::RectangleShape* boxShape;
        float posX;
        float posY;
        sf::Color* borderColor;
        float width;
        float height;

        void InitShape();
        
    public:
        BoxCollider(float, float, sf::Color*, float, float);
        ~BoxCollider();

        sf::RectangleShape* GetBoxShape() const;
};

