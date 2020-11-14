#include "ContactListener.hh"
#include "GameObject.hh"
#include "Tile.hh"
#include<iostream>
#include<cstring>
#include<algorithm>


ContactListener::ContactListener(Score*& score, std::vector<GameObject*>*& items)
{
    this->score = score;
    this->items = items;
}

ContactListener::~ContactListener()
{
}

int ContactListener::GetSceneIndex() const
{
    return sceneIndex;
}

void ContactListener::BeginContact(b2Contact* contact)
{
    GameObject* bodyDataA = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData();
    GameObject* bodyDataB = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData();

    if(bodyDataA && bodyDataB)
    {
        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "item") == 0)
        {
            std::cout << "collected" << std::endl;
            score->AddPoints(5);
            items->erase(std::remove(items->begin(), items->end(), bodyDataB), items->end());
            bodyDataB->~GameObject();
        }
        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "stairs") == 0)
        {
            std::cout << "stairs" << std::endl;
            bodyDataB->~GameObject();
            sceneIndex++;
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    
}